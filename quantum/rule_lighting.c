/* Copyright 2024
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rule_lighting.h"
#include "keymap_introspection.h"
#include "dynamic_keymap.h"
#include <stddef.h>
#include <string.h>

#ifdef SPLIT_KEYBOARD
#include "keyboard.h"
#include "transactions.h"
#include "timer.h"
#endif

#ifdef RGB_MATRIX_ENABLE

/* Forward declarations for EEPROM access */
extern int nvm_dynamic_keymap_get_rgb_indicator_config(rule_lighting_config_t *config);
extern int nvm_dynamic_keymap_set_rgb_indicator_config(const rule_lighting_config_t *config);
extern int nvm_dynamic_keymap_get_rgb_indicator_entry(uint8_t index, rule_lighting_entry_t *entry);
extern int nvm_dynamic_keymap_set_rgb_indicator_entry(uint8_t index, const rule_lighting_entry_t *entry);

/* RAM cache of config and entries */
static rule_lighting_config_t indicator_config;
static rule_lighting_entry_t indicator_entries[RULE_LIGHTING_ENTRIES];

/**
 * Clear RAM cache to blank/off state
 */
static void rule_lighting_clear_ram(void) {
    indicator_config.entry_count = 0;

    /* Clear all entries to off */
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        indicator_entries[i] = (rule_lighting_entry_t){
            .layer_enable = 0,
            .caps_enable = 0,
            .layer = 0,
            .mods = 0,
            .keycode_start = 0,
            .keycode_end = 0,
            .sat_idle = VIAL_RGB_SAT_OFF,
            .h_idle = 0,
            .sat_pressed = VIAL_RGB_SAT_OFF,
            .h_pressed = 0,
        };
    }
}

/**
 * Reset rule lighting to defaults and save to EEPROM
 * Called from eeconfig_update_rgb_matrix_default() when RGB Matrix is uninitialized
 */
void rule_lighting_reset(void) {
    rule_lighting_clear_ram();

    /* Save blank state to EEPROM */
    nvm_dynamic_keymap_set_rgb_indicator_config(&indicator_config);
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        nvm_dynamic_keymap_set_rgb_indicator_entry(i, &indicator_entries[i]);
    }
}

/**
 * Load config and rules from EEPROM (no validation)
 */
void rule_lighting_load(void) {
#ifdef SPLIT_KEYBOARD
    /* On split keyboards, only master has EEPROM access */
    if (!is_keyboard_master()) {
        /* Slave starts blank - will be synced via split transport */
        rule_lighting_clear_ram();
        return;
    }
#endif

    nvm_dynamic_keymap_get_rgb_indicator_config(&indicator_config);

    /* Sanity check entry_count */
    if (indicator_config.entry_count > RULE_LIGHTING_ENTRIES) {
        indicator_config.entry_count = 0;  /* Treat as empty */
    }

    /* Load all entries */
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        nvm_dynamic_keymap_get_rgb_indicator_entry(i, &indicator_entries[i]);
    }
}

/* rule_lighting_init is defined at end of file with split sync support */

/**
 * Get a rule entry
 */
rule_lighting_entry_t* rule_lighting_get_entry(uint8_t index) {
    if (index >= RULE_LIGHTING_ENTRIES) {
        return NULL;
    }
    return &indicator_entries[index];
}

/**
 * Set a rule entry (RAM only, call rule_lighting_save for EEPROM)
 */
void rule_lighting_set_entry(uint8_t index, const rule_lighting_entry_t *entry) {
    if (index >= RULE_LIGHTING_ENTRIES) {
        return;
    }
    indicator_entries[index] = *entry;
}

/**
 * Get the global config
 */
rule_lighting_config_t* rule_lighting_get_config(void) {
    return &indicator_config;
}

/**
 * Set the global config (RAM only, call rule_lighting_save for EEPROM)
 */
void rule_lighting_set_config(const rule_lighting_config_t *config) {
    indicator_config = *config;
}

/**
 * Save all rule lighting data to EEPROM
 */
void rule_lighting_save(void) {
    nvm_dynamic_keymap_set_rgb_indicator_config(&indicator_config);

    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        nvm_dynamic_keymap_set_rgb_indicator_entry(i, &indicator_entries[i]);
    }
}

/**
 * Get pointer to sync data (for split keyboard master)
 * Returns a static struct containing config + all entries
 */
const rule_lighting_sync_t* rule_lighting_get_sync_data(void) {
    static rule_lighting_sync_t sync_data;
    sync_data.config = indicator_config;
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        sync_data.entries[i] = indicator_entries[i];
    }
    return &sync_data;
}

/**
 * Apply sync data (for split keyboard slave)
 * Copies received data into RAM cache (no EEPROM write)
 */
void rule_lighting_apply_sync_data(const rule_lighting_sync_t *sync_data) {
    indicator_config = sync_data->config;
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        indicator_entries[i] = sync_data->entries[i];
    }
}

/*
 * Split keyboard sync support
 * Automatically syncs rule lighting config and keymap to slave half
 */
#ifdef SPLIT_KEYBOARD

/* Keymap sync data structure (one layer at a time, includes counter) */
typedef struct {
    uint8_t counter;
    uint8_t layer;
    uint16_t keycodes[MATRIX_ROWS][MATRIX_COLS];
} __attribute__((packed)) keymap_layer_sync_t;

/* Synced keymap storage on slave (RAM) */
static uint16_t synced_keymap[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS];
static uint8_t synced_counter = 0xFF;       /* Counter for completed sync */
static uint8_t pending_counter = 0xFF;      /* Counter currently being synced */
static uint8_t pending_mask = 0;            /* Layers received for pending_counter */

/**
 * Slave callback for rule lighting sync
 */
static void rule_lighting_slave_handler(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    if (m2s_size == sizeof(rule_lighting_sync_t)) {
        rule_lighting_apply_sync_data((const rule_lighting_sync_t *)m2s_buffer);
    }
}

/**
 * Slave callback for keymap sync
 */
static void keymap_slave_handler(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    /* Master is querying our counter */
    if (m2s_size == 0 && s2m_size == 1) {
        *(uint8_t *)s2m_buffer = synced_counter;
        return;
    }

    /* Master is sending layer data */
    if (m2s_size == sizeof(keymap_layer_sync_t)) {
        const keymap_layer_sync_t *data = (const keymap_layer_sync_t *)m2s_buffer;

        if (data->layer >= DYNAMIC_KEYMAP_LAYER_COUNT) return;

        /* New counter? Reset pending state */
        if (data->counter != pending_counter) {
            pending_counter = data->counter;
            pending_mask = 0;
        }

        /* Store layer data */
        memcpy(synced_keymap[data->layer], data->keycodes, sizeof(data->keycodes));
        pending_mask |= (1 << data->layer);

        /* All layers received? Commit the sync */
        uint8_t all_layers = (1 << DYNAMIC_KEYMAP_LAYER_COUNT) - 1;
        if (pending_mask == all_layers) {
            synced_counter = pending_counter;
        }
    }
}

/**
 * Resolve KC_TRNS to effective keycode by checking lower layers
 */
static uint16_t resolve_keycode(uint8_t layer, uint8_t row, uint8_t col, bool use_synced) {
    if (use_synced && synced_counter == 0xFF) {
        return KC_NO;  /* No valid sync yet */
    }

    for (int8_t l = layer; l >= 0; l--) {
        uint16_t kc = use_synced ? synced_keymap[l][row][col]
                                 : dynamic_keymap_get_keycode(l, row, col);
        if (kc != KC_TRNS) {
            return kc;
        }
    }
    return KC_NO;
}

/**
 * Get keycode with split keyboard awareness
 * Master uses dynamic_keymap, slave uses synced_keymap
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col) {
    if (row >= MATRIX_ROWS || col >= MATRIX_COLS) {
        return KC_NO;
    }
    return resolve_keycode(layer, row, col, !is_keyboard_master());
}

/**
 * Register split transactions - must be called AFTER split_post_init()
 * This is called from keyboard_post_init_kb() to ensure slave transport is ready
 */
void rule_lighting_post_init(void) {
    transaction_register_rpc(SPLIT_RULE_LIGHTING_SYNC_ID, rule_lighting_slave_handler);
    transaction_register_rpc(SPLIT_KEYMAP_SYNC_ID, keymap_slave_handler);
}

/**
 * Master sync task - called from rule_lighting_task
 */
static void rule_lighting_master_sync(void) {
    static uint32_t last_check = 0;
    static uint8_t sync_layer = 0xFF;  /* 0xFF = idle, 0-N = syncing layer N */
    static uint8_t sync_counter = 0;   /* Counter we're syncing */

    /* Query slave every 5 seconds when idle, or send layers quickly when syncing */
    uint32_t interval = (sync_layer == 0xFF) ? 5000 : 100;

    if (timer_elapsed32(last_check) > interval) {
        last_check = timer_read32();

        if (sync_layer == 0xFF) {
            /* Idle mode: query slave's counter and send rule lighting */
            uint8_t slave_counter = 0xFF;
            bool ok = transaction_rpc_exec(SPLIT_KEYMAP_SYNC_ID, 0, NULL, 1, &slave_counter);
            uint8_t master_counter = dynamic_keymap_get_change_counter();

            if (ok && slave_counter != master_counter) {
                sync_layer = 0;
                sync_counter = master_counter;
            }

            /* Always sync rule lighting */
            const rule_lighting_sync_t *sync_data = rule_lighting_get_sync_data();
            transaction_rpc_send(SPLIT_RULE_LIGHTING_SYNC_ID, sizeof(rule_lighting_sync_t), sync_data);
        } else {
            /* Syncing mode: send one layer with counter */
            keymap_layer_sync_t layer_data;
            layer_data.counter = sync_counter;
            layer_data.layer = sync_layer;
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    layer_data.keycodes[row][col] = dynamic_keymap_get_keycode(sync_layer, row, col);
                }
            }
            transaction_rpc_send(SPLIT_KEYMAP_SYNC_ID, sizeof(keymap_layer_sync_t), &layer_data);

            sync_layer++;
            if (sync_layer >= DYNAMIC_KEYMAP_LAYER_COUNT) {
                sync_layer = 0xFF;  /* Done, back to idle */
            }
        }
    }
}

#else /* !SPLIT_KEYBOARD */

/**
 * Non-split keyboard: just use dynamic_keymap directly
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col) {
    return keycode_at_keymap_location_raw(layer, row, col);
}

#endif /* SPLIT_KEYBOARD */

/**
 * Initialize rule lighting (early init, called from rgb_matrix_init)
 * Note: Split keyboard RPC handlers are registered later in rule_lighting_post_init()
 */
void rule_lighting_init(void) {
    rule_lighting_load();
    /* Split RPC registration moved to rule_lighting_post_init()
     * which is called from keyboard_post_init_kb() after split_post_init() */
}

/**
 * Housekeeping task for rule lighting
 * Call this from housekeeping_task or rgb_matrix_indicators
 */
void rule_lighting_task(void) {
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        rule_lighting_master_sync();
    }
#endif
}

#endif /* RGB_MATRIX_ENABLE */
