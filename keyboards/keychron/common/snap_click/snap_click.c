/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include "eeconfig_kb.h"
#include "snap_click.h"
#include "raw_hid.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "matrix.h"
#include "quantum.h"
#include "keychron_raw_hid.h"

#if defined(SNAP_CLICK_ENABLE) && defined(EECONFIG_SIZE_SNAP_CLICK)

enum {
    SNAP_CLICK_TYPE_NONE = 0,
    SNAP_CLICK_TYPE_REGULAR,
    SNAP_CLICK_TYPE_LAST_INPUT,
    SNAP_CLICK_TYPE_FIRST_KEY,
    SNAP_CLICK_TYPE_SECOND_KEY,
    SNAP_CLICK_TYPE_NEUTRAL,
    SNAP_CLICK_TYPE_MAX,
};

#    define SC_MASK_BOTH_KEYS_PRESSED 3

snap_click_config_t snap_click_pair[SNAP_CLICK_COUNT];
snap_click_state_t  snap_click_state[SNAP_CLICK_COUNT];

void snap_click_config_reset(void) {
    memset(snap_click_pair, 0, sizeof(snap_click_pair));
    eeprom_update_block(snap_click_pair, (uint8_t *)(EECONFIG_BASE_SNAP_CLICK), sizeof(snap_click_pair));
}

void snap_click_init(void) {
    eeprom_read_block(snap_click_pair, (uint8_t *)(EECONFIG_BASE_SNAP_CLICK), sizeof(snap_click_pair));
    memset(snap_click_state, 0, sizeof(snap_click_state));
}

bool process_record_snap_click(uint16_t keycode, keyrecord_t *record) {
    for (uint8_t i = 0; i < SNAP_CLICK_COUNT; i++) {
        snap_click_config_t *p = &snap_click_pair[i];

        if (p->type && (keycode == p->key[0] || keycode == p->key[1])) {
            snap_click_state_t *pState = &snap_click_state[i];
            uint8_t             index  = keycode == p->key[1]; // 0 or 1 of key pair

            if (record->event.pressed) {
                uint8_t state = 0x01 << index;

                if (pState->state == 0) {
                    // Single key down
                    pState->state_keys = pState->last_single_key = state;
                } else if ((state & pState->state_keys) == 0) { // TODO: do we need checking?
                    // Both keys are pressed
                    pState->state_keys = SC_MASK_BOTH_KEYS_PRESSED;
                    switch (p->type) {
                        case SNAP_CLICK_TYPE_REGULAR:
                        case SNAP_CLICK_TYPE_LAST_INPUT:
                            unregister_code(p->key[1 - index]);
                            register_code(p->key[index]);
                            break;
                        case SNAP_CLICK_TYPE_FIRST_KEY:
                            unregister_code(p->key[1]);
                            register_code(p->key[0]);
                            break;
                        case SNAP_CLICK_TYPE_SECOND_KEY:
                            unregister_code(p->key[0]);
                            register_code(p->key[1]);
                            break;
                        case SNAP_CLICK_TYPE_NEUTRAL:
                            unregister_code(p->key[1 - index]);
                            break;
                    }
                    return false;
                }
            } else {
                if (pState->state_keys == SC_MASK_BOTH_KEYS_PRESSED) {
                    // Snap click active
                    uint8_t state      = 0x01 << (1 - index);
                    pState->state_keys = pState->last_single_key = state;

                    switch (p->type) {
                        case SNAP_CLICK_TYPE_REGULAR:
                            unregister_code(p->key[index]);
                            break;
                        case SNAP_CLICK_TYPE_LAST_INPUT:
                        case SNAP_CLICK_TYPE_FIRST_KEY:
                        case SNAP_CLICK_TYPE_SECOND_KEY:
                            if (is_key_pressed(p->key[index])) {
                                unregister_code(p->key[index]);
                            }
                            if (!is_key_pressed(p->key[1 - index])) {
                                register_code(p->key[1 - index]);
                            }
                            break;
                        case SNAP_CLICK_TYPE_NEUTRAL:
                            register_code(p->key[1 - index]);
                            break;
                    }

                    return false;
                } else {
                    pState->state = 0;
                }
            }
        }
    }

    return true;
}

static bool snap_click_get_info(uint8_t *data) {
    data[1] = SNAP_CLICK_COUNT;

    return true;
}

static bool snap_click_get(uint8_t *data) {
    uint8_t start = data[0];
    uint8_t count = data[1];

    if (count > 9 || start + count > SNAP_CLICK_COUNT) return false;
    memcpy(&data[1], &snap_click_pair[start], count * sizeof(snap_click_config_t));

    return true;
}

static bool snap_click_set(uint8_t *data) {
    uint8_t start = data[0];
    uint8_t count = data[1];

    if (count > 9 || start + count > SNAP_CLICK_COUNT) return false;
    for (uint8_t i = 0; i < count; i++) {
        uint8_t offset   = 2 + sizeof(snap_click_config_t) * i;
        uint8_t type     = data[offset];
        uint8_t keycode1 = data[offset + 1];
        uint8_t keycode2 = data[offset + 2];

        if (type >= SNAP_CLICK_TYPE_MAX) return false;

        if (type != 0 && (keycode1 == 0 || keycode2 == 0)) return false;
    }
    memcpy(&snap_click_pair[start], &data[2], count * sizeof(snap_click_config_t));

    return true;
}

static bool snap_click_save(uint8_t *data) {
    eeprom_update_block(snap_click_pair, (uint8_t *)(EECONFIG_BASE_SNAP_CLICK), sizeof(snap_click_pair));

    return true;
}

void snap_click_rx(uint8_t *data, uint8_t length) {
    uint8_t cmd     = data[1];
    bool    success = true;

    switch (cmd) {
        case SNAP_CLICK_GET_INFO:
            success = snap_click_get_info(&data[2]);
            break;

        case SNAP_CLICK_GET:
            success = snap_click_get(&data[2]);
            break;

        case SNAP_CLICK_SET:
            success = snap_click_set(&data[2]);
            break;

        case SNAP_CLICK_SAVE:
            success = snap_click_save(&data[2]);
            break;

        default:
            data[0] = 0xFF;
            break;
    }

    data[2] = success ? 0 : 1;
}
#endif
