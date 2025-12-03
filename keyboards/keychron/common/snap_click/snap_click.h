/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
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
#include "action.h"

/* Snap Click Types - for use in SNAP_CLICK_DEFAULT_PAIRS */
#define SC_TYPE_NONE        0
#define SC_TYPE_REGULAR     1  /* Last key pressed wins, releases normally */
#define SC_TYPE_LAST_INPUT  2  /* Last key pressed wins, other key activates on release */
#define SC_TYPE_FIRST_KEY   3  /* First key always wins when both pressed */
#define SC_TYPE_SECOND_KEY  4  /* Second key always wins when both pressed */
#define SC_TYPE_NEUTRAL     5  /* Both keys cancel out (no output) when pressed together */

/* Macro for defining snap click pairs in keymap config.h
 * Usage: #define SNAP_CLICK_DEFAULT_PAIRS { \
 *            { SC_TYPE_LAST_INPUT, KC_A, KC_D }, \
 *            { SC_TYPE_LAST_INPUT, KC_W, KC_S }, \
 *        }
 */
#define SC_PAIR(type, key1, key2) { type, { key1, key2 } }

typedef struct __attribute__((__packed__)) {
    uint8_t type;
    uint8_t key[2];
} snap_click_config_t;
// size  = 3 bytes

typedef union {
    uint8_t state;
    struct {
        uint8_t state_key_1 : 1;
        uint8_t state_key_2 : 1;
        uint8_t last_single_key_1 : 1;
        uint8_t last_single_key_2 : 1;
        uint8_t reserved : 4;
    };
    struct {
        uint8_t state_keys : 2;
        uint8_t last_single_key : 2;
        uint8_t reserved2 : 4;
    };
} snap_click_state_t;

void snap_click_config_reset(void);
void snap_click_init(void);
bool snap_click_is_enabled(void);
void snap_click_toggle(void);
void snap_click_enable(void);
void snap_click_disable(void);
bool process_record_snap_click(uint16_t keycode, keyrecord_t *record);
void snap_click_rx(uint8_t *data, uint8_t length);
