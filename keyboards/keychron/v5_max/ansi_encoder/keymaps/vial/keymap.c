/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "tap_dance.h" // Include tap dance definitions
#include "modules/socd_cleaner/socd_cleaner.h" // Include SOCD Cleaner module

// Function prototype for our SOCD cleaner implementation
bool process_record_socd_cleaner(uint16_t keycode, keyrecord_t *record);

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

// SOCD Cleaner keycodes - must come after keychron_common.h which defines its own SAFE_RANGE
enum socd_keycodes {
    SOCDON = NEW_SAFE_RANGE,  // Turn SOCD Cleaner on
    SOCDOFF,                  // Turn SOCD Cleaner off
    SOCDTOG                   // Toggle SOCD Cleaner
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [MAC_BASE] = LAYOUT_ansi_98(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            KC_DEL,   KC_HOME,  KC_END,     KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,      KC_PPLS,  
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,       
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,      KC_PENT,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT               ),
    [MAC_FN] = LAYOUT_ansi_98(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [WIN_BASE] = LAYOUT_ansi_98(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             KC_DEL,   KC_HOME,  KC_END,     KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_NUM,   KC_PSLS,  KC_PAST,    KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,      KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,     
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,      KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT            ),
    [WIN_FN] = LAYOUT_ansi_98(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,            _______,  _______,  _______,    RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
 };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Process SOCD (Simultaneous Opposite Cardinal Directions) cleaner first
    if (!process_record_socd_cleaner(keycode, record)) {
        return false;
    }
    
    // Then process Keychron common features
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    
    return true;
}

// Define handedness of the keyboard layout for Chordal Hold
// This keyboard has a split-hand layout where left keys are on the left hand
// and right keys are on the right hand
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
    {'L', 'L', 'L', '*', '*', '*', '*', '*', '*', '*', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
};

// Define SOCD Cleaner opposing pairs
// We're setting up WASD keys with last input priority (recommended for gaming)
// and arrow keys as an additional set
// Define SOCD Cleaner opposing pairs for WASD and arrow keys
socd_cleaner_t socd_opposing_pairs[] = {
    {{KC_W, KC_S}, SOCD_CLEANER_LAST, {false, false}},  // Up/Down with last input priority 
    {{KC_A, KC_D}, SOCD_CLEANER_LAST, {false, false}},  // Left/Right with last input priority
    {{KC_UP, KC_DOWN}, SOCD_CLEANER_LAST, {false, false}},  // Up/Down arrows
    {{KC_LEFT, KC_RIGHT}, SOCD_CLEANER_LAST, {false, false}}  // Left/Right arrows
};

// Global variable for enabling/disabling SOCD cleaner
bool socd_cleaner_enabled = true;

// Implementation of SOCD cleaner key handling
bool process_record_socd_cleaner(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case SOCDON:  // Turn SOCD Cleaner on
            if (record->event.pressed) {
                socd_cleaner_enabled = true;
            }
            return false;
        case SOCDOFF:  // Turn SOCD Cleaner off
            if (record->event.pressed) {
                socd_cleaner_enabled = false;
            }
            return false;
        case SOCDTOG:  // Toggle SOCD Cleaner
            if (record->event.pressed) {
                socd_cleaner_enabled = !socd_cleaner_enabled;
            }
            return false;
    }
    
    // Skip SOCD processing if disabled
    if (!socd_cleaner_enabled) {
        return true;
    }
    
    // Process each opposing pair
    for (int i = 0; i < sizeof(socd_opposing_pairs) / sizeof(socd_opposing_pairs[0]); ++i) {
        socd_cleaner_t* state = &socd_opposing_pairs[i];
        
        // Check if this keycode is part of this opposing pair
        if (keycode != state->keys[0] && keycode != state->keys[1]) {
            continue;  // Not relevant for this pair
        }
        
        // The current event corresponds to index `i`, 0 or 1, in the SOCD key pair
        const uint8_t idx = (keycode == state->keys[1]) ? 1 : 0;
        const uint8_t opposing = idx ^ 1;  // Index of the opposing key
        
        // Track which keys are physically held (vs. keys in the report)
        state->held[idx] = record->event.pressed;
        
        // Perform SOCD resolution for events where the opposing key is held
        if (state->held[opposing]) {
            switch (state->resolution) {
                case SOCD_CLEANER_LAST:  // Last input priority with reactivation
                    // If the current event is a press, then release the opposing key
                    // Otherwise if this is a release, then press the opposing key
                    if (record->event.pressed) {
                        del_key(state->keys[opposing]);
                    } else {
                        add_key(state->keys[opposing]);
                    }
                    break;
                    
                case SOCD_CLEANER_NEUTRAL:  // Neutral resolution
                    // Same logic as SOCD_CLEANER_LAST, but skip default handling so that
                    // the current key has no effect while the opposing key is held
                    if (record->event.pressed) {
                        del_key(state->keys[opposing]);
                    } else {
                        add_key(state->keys[opposing]);
                    }
                    // Send updated report (normally, default handling would do this)
                    send_keyboard_report();
                    return false;  // Skip default handling
                    
                case SOCD_CLEANER_0_WINS:  // Key 0 wins
                case SOCD_CLEANER_1_WINS:  // Key 1 wins
                    if (opposing == (state->resolution - SOCD_CLEANER_0_WINS)) {
                        // The opposing key is the winner. The current key has no effect
                        return false;  // Skip default handling
                    } else {
                        // The current key is the winner. Update logic is same as above
                        if (record->event.pressed) {
                            del_key(state->keys[opposing]);
                        } else {
                            add_key(state->keys[opposing]);
                        }
                    }
                    break;
            }
        }
        
        // If we processed a relevant key, we're done
        return true;
    }
    
    // No relevant pairs found
    return true;
}
