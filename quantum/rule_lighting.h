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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef RGB_MATRIX_ENABLE

/* Default number of RGB indicator entries based on EEPROM size
 * Matches entry count pattern from other Vial features (tap dance, combos, etc.)
 * Each entry is 8 bytes, config is 1 byte */
#ifndef RULE_LIGHTING_ENTRIES
    #if TOTAL_EEPROM_BYTE_COUNT > 4000
        #define RULE_LIGHTING_ENTRIES 32
    #elif TOTAL_EEPROM_BYTE_COUNT > 2000
        #define RULE_LIGHTING_ENTRIES 16
    #elif TOTAL_EEPROM_BYTE_COUNT > 1000
        #define RULE_LIGHTING_ENTRIES 8
    #else
        #define RULE_LIGHTING_ENTRIES 4
    #endif
#endif

/*
 * Split keyboard configuration for rule lighting
 * Auto-configures RPC buffer size and split state syncing
 * Transaction IDs are defined in transaction_id_define.h
 */
#if defined(SPLIT_KEYBOARD) && defined(RULE_LIGHTING_ENABLE)

/*
 * RPC buffer size calculation
 * Buffer must fit the larger of:
 *   - rule_lighting_sync_t: 1 + 8 * RULE_LIGHTING_ENTRIES
 *   - keymap_layer_sync_t:  2 + MATRIX_ROWS * MATRIX_COLS * 2
 */
#define _RL_SYNC_SIZE (1 + 8 * RULE_LIGHTING_ENTRIES)
#define _KM_SYNC_SIZE (2 + MATRIX_ROWS * MATRIX_COLS * 2)
#define _RL_RPC_BUFFER_SIZE ((_RL_SYNC_SIZE > _KM_SYNC_SIZE) ? _RL_SYNC_SIZE : _KM_SYNC_SIZE)

#ifndef RPC_M2S_BUFFER_SIZE
    #define RPC_M2S_BUFFER_SIZE _RL_RPC_BUFFER_SIZE
#elif RPC_M2S_BUFFER_SIZE < _RL_RPC_BUFFER_SIZE
    #undef RPC_M2S_BUFFER_SIZE
    #define RPC_M2S_BUFFER_SIZE _RL_RPC_BUFFER_SIZE
#endif

/* Enable required split state syncing */
#ifndef SPLIT_LAYER_STATE_ENABLE
    #define SPLIT_LAYER_STATE_ENABLE
#endif
#ifndef SPLIT_LED_STATE_ENABLE
    #define SPLIT_LED_STATE_ENABLE
#endif
#ifndef SPLIT_MODS_ENABLE
    #define SPLIT_MODS_ENABLE
#endif

#endif /* SPLIT_KEYBOARD && RULE_LIGHTING_ENABLE */

/**
 * Saturation modes (2 bits)
 */
typedef enum {
    VIAL_RGB_SAT_OFF    = 0b00,  // LED off (RGB 0,0,0)
    VIAL_RGB_SAT_WHITE  = 0b01,  // S=0 (white/grayscale)
    VIAL_RGB_SAT_PASTEL = 0b10,  // S=128 (soft color)
    VIAL_RGB_SAT_PURE   = 0b11,  // S=255 (vivid color)
} vial_rgb_saturation_t;

#define VIAL_RGB_SAT_IS_ON(sat) ((sat) != VIAL_RGB_SAT_OFF)

/**
 * RGB Indicator Rule Entry (8 bytes)
 *
 * Bit layout:
 *   Byte 0-1 (condition):
 *     Bit 0:    layer_enable (0 = any layer, 1 = match layer field)
 *     Bit 1:    caps_enable (0 = any caps state, 1 = caps must be ON)
 *     Bits 2-3: reserved
 *     Bits 4-7: layer (0-15)
 *     Bits 8-15: mods (modifier mask, 0 = any)
 *
 *   Byte 2-3: keycode_start (full 16-bit range)
 *   Byte 4-5: keycode_end (full 16-bit range, inclusive)
 *
 *   Byte 6 (color_idle):
 *     Bits 0-1: sat_idle
 *     Bits 2-7: h_idle (6-bit hue, use << 2 for 8-bit)
 *
 *   Byte 7 (color_pressed):
 *     Bits 0-1: sat_pressed
 *     Bits 2-7: h_pressed (6-bit hue)
 */
typedef struct {
    /* Condition (16 bits) */
    uint16_t layer_enable   : 1;
    uint16_t caps_enable    : 1;
    uint16_t reserved       : 2;
    uint16_t layer          : 4;
    uint16_t mods           : 8;

    /* Keycode range (32 bits) */
    uint16_t keycode_start;
    uint16_t keycode_end;

    /* Colors (16 bits) */
    uint8_t  sat_idle       : 2;
    uint8_t  h_idle         : 6;
    uint8_t  sat_pressed    : 2;
    uint8_t  h_pressed      : 6;

} __attribute__((packed)) rule_lighting_entry_t;

_Static_assert(sizeof(rule_lighting_entry_t) == 8,
    "Unexpected size of rule_lighting_entry_t structure");

/**
 * Global RGB Indicator Config (1 byte)
 * Note: Speed/brightness use rgb_matrix_get_speed()/get_val() from RGB Matrix
 * Effect is enabled/disabled by selecting it from the RGB Matrix effect list
 */
typedef struct {
    uint8_t entry_count;    // Number of active rules (0-255)
} __attribute__((packed)) rule_lighting_config_t;

_Static_assert(sizeof(rule_lighting_config_t) == 1,
    "Unexpected size of rule_lighting_config_t structure");

/**
 * Initialize the RGB indicator system (early init)
 * Called from rgb_matrix_init() during keyboard_init()
 */
void rule_lighting_init(void);

/**
 * Post-initialization for split keyboard support
 * Registers RPC handlers - must be called AFTER split_post_init()
 * Called from keyboard_post_init_kb()
 */
void rule_lighting_post_init(void);

/**
 * Housekeeping task for rule lighting
 * Handles split keyboard sync on master
 */
void rule_lighting_task(void);

/**
 * Reset rule lighting to defaults and save to EEPROM
 */
void rule_lighting_reset(void);

/**
 * Load config and rules from EEPROM
 */
void rule_lighting_load(void);

/**
 * Save all rule lighting data to EEPROM
 */
void rule_lighting_save(void);

/**
 * Get a rule entry
 */
rule_lighting_entry_t* rule_lighting_get_entry(uint8_t index);

/**
 * Set a rule entry and save to EEPROM
 */
void rule_lighting_set_entry(uint8_t index, const rule_lighting_entry_t *entry);

/**
 * Get the global config
 */
rule_lighting_config_t* rule_lighting_get_config(void);

/**
 * Set the global config and save to EEPROM
 */
void rule_lighting_set_config(const rule_lighting_config_t *config);

/**
 * Sync data structure for split keyboard transport
 */
typedef struct {
    rule_lighting_config_t config;
    rule_lighting_entry_t entries[RULE_LIGHTING_ENTRIES];
} __attribute__((packed)) rule_lighting_sync_t;

/**
 * Get pointer to sync data (for split keyboard master)
 */
const rule_lighting_sync_t* rule_lighting_get_sync_data(void);

/**
 * Apply sync data (for split keyboard slave)
 */
void rule_lighting_apply_sync_data(const rule_lighting_sync_t *sync_data);

/**
 * Get keycode for a key position (supports split keyboard sync)
 * Weak function - keyboards can override with synced keymap support
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col);

/**
 * Convert 6-bit hue to 8-bit
 */
#define VIAL_RGB_HUE_6TO8(h6) ((h6) << 2)

/**
 * Convert saturation mode to S value (0-255)
 */
static inline uint8_t vial_rgb_sat_to_value(uint8_t sat_mode) {
    switch (sat_mode) {
        case VIAL_RGB_SAT_OFF:    return 0;
        case VIAL_RGB_SAT_WHITE:  return 0;
        case VIAL_RGB_SAT_PASTEL: return 128;
        case VIAL_RGB_SAT_PURE:   return 255;
        default:                   return 0;
    }
}

#else /* RGB_MATRIX_ENABLE */

/* Stub when RGB Matrix is disabled */
#define RULE_LIGHTING_ENTRIES 0

#endif /* RGB_MATRIX_ENABLE */
