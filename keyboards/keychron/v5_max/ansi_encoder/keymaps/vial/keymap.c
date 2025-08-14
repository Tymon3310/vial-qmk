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
#include "tap_dance.h"         // Include tap dance definitions
#include "caps_word.h"         // For is_caps_word_on()
#include "socd_cleaner.h"      // SOCD Cleaner module
#include "community_modules.h" // brings MOUSE_TURBO_CLICK and process_record_* prototypes
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h" // For RGB_MATRIX_INDICATOR_SET_COLOR macro
#endif

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

// Wrapper keycodes for exposing SOCD Cleaner controls via Vial (QK_KB_16+ unused)
enum socd_wrapper_keycodes {
    SOC_ON_WRAPPER = QK_KB_16,
    SOC_OFF_WRAPPER,
    SOC_TOG_WRAPPER,
};

// WASD<->Arrow swap toggle keycode (next free in keyboard range)
enum wasd_swap_keycodes {
    WASD_ARROW_TOG = QK_KB_19, // repurpose existing custom keycode to trigger swap-hands
};

// Add Turbo Click wrapper in the keyboard range so Vial can show it
enum turbo_wrapper_keycodes {
    TURBO_WRAPPER = QK_KB_20,
};

// Track swap-hands state (mirroring) separately for LED indication
static bool swap_hands_active = false;

// Timer for temporarily disabling layer RGB coloring when RGB keycodes are used
static uint32_t rgb_keycode_timer = 0;
static bool rgb_layer_coloring_enabled = true;

// Disable SOCD Cleaner by default (module defaults to enabled). This runs after init.
void keyboard_post_init_user(void) {
    socd_cleaner_enabled = false;
}

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

// Define SOCD Cleaner opposing pairs for WASD and arrow keys (mutable resolutions)
socd_cleaner_t socd_opposing_pairs[] = {
    {{KC_W, KC_S}, SOCD_CLEANER_LAST, {false, false}},       // WASD vertical
    {{KC_A, KC_D}, SOCD_CLEANER_LAST, {false, false}},       // WASD horizontal
    {{KC_UP, KC_DOWN}, SOCD_CLEANER_LAST, {false, false}},   // Arrow vertical
    {{KC_LEFT, KC_RIGHT}, SOCD_CLEANER_LAST, {false, false}} // Arrow horizontal
};

// Swap-hands configuration restricted to swapping WASD with arrow cluster only.
// All other positions map to themselves to avoid full keyboard mirroring.
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Row 0
    { {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0}, {8,0}, {9,0}, {10,0}, {11,0}, {12,0}, {13,0}, {14,0}, {15,0}, {16,0}, {17,0}, {18,0} },
    // Row 1
    { {0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,1}, {9,1}, {10,1}, {11,1}, {12,1}, {13,1}, {14,1}, {15,1}, {16,1}, {17,1}, {18,1} },
    // Row 2 (W at col2 mapped to Up arrow position col14,row4)
    { {0,2}, {1,2}, {14,4}, {3,2}, {4,2}, {5,2}, {6,2}, {7,2}, {8,2}, {9,2}, {10,2}, {11,2}, {12,2}, {13,2}, {14,2}, {15,2}, {16,2}, {17,2}, {18,2} },
    // Row 3 (A,S,D at cols1,2,3 mapped to Left,Down,Right arrow positions col13/14/15,row5)
    { {0,3}, {13,5}, {14,5}, {15,5}, {4,3}, {5,3}, {6,3}, {7,3}, {8,3}, {9,3}, {10,3}, {11,3}, {12,3}, {13,3}, {14,3}, {15,3}, {16,3}, {17,3}, {18,3} },
    // Row 4 (Up arrow at col14 mapped back to W at col2,row2)
    { {0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {8,4}, {9,4}, {10,4}, {11,4}, {12,4}, {13,4}, {2,2}, {15,4}, {16,4}, {17,4}, {18,4} },
    // Row 5 (Left/Down/Right arrows at cols13/14/15 mapped back to A,S,D at 1/2/3,row3)
    { {0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}, {7,5}, {8,5}, {9,5}, {10,5}, {11,5}, {12,5}, {1,3}, {2,3}, {3,3}, {16,5}, {17,5}, {18,5} }
};

#if defined(SWAP_HANDS_ENABLE) && defined(ENCODER_MAP_ENABLE)
// Single encoder, no change when swapping (self-map)
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = { 0 };
#endif

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Forward our Vial-visible wrapper to the module's TURBO keycode (handles press/release + double-tap lock)
    if (keycode == TURBO_WRAPPER) {
        (void)process_record_mouse_turbo_click(MOUSE_TURBO_CLICK, record);
        return false; // suppress original wrapper
    }

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    // Check for RGB keycodes and disable layer coloring temporarily
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_TOG:
            case RGB_MOD:
            case RGB_RMOD:
            case RGB_HUI:
            case RGB_HUD:
            case RGB_SAI:
            case RGB_SAD:
            case RGB_VAI:
            case RGB_VAD:
            case RGB_SPI:
            case RGB_SPD:
                rgb_keycode_timer = timer_read32();
                rgb_layer_coloring_enabled = false;
                break;
            case SOC_ON_WRAPPER:
                socd_cleaner_enabled = true;
                return false;
            case SOC_OFF_WRAPPER:
                socd_cleaner_enabled = false;
                return false;
            case SOC_TOG_WRAPPER:
                socd_cleaner_enabled = !socd_cleaner_enabled;
                return false;
            case WASD_ARROW_TOG:
                swap_hands_toggle();
                swap_hands_active = is_swap_hands_on();
                return false;
            default:
                break;
        }
    }

    // Let SOCD module process the effective key
    if (!process_record_socd_cleaner(keycode, record)) {
        return false;
    }
    return true;
}

// Define handedness of the keyboard layout for Chordal Hold (unused in logic here but preserved)
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', '*', '*', '*', '*', '*', '*', '*', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
};

// Implementation is provided by the module; no local definition here.

#ifdef RGB_MATRIX_ENABLE
// Light the Caps Lock key LED when Caps Lock OR Caps Word is active.
// Caps Lock LED index derived from led_config_t mapping in ansi_encoder.c: row 3, col 0 -> index 51.
#    define CAPS_LOCK_LED_INDEX 51
// Arrow key LED indices (derived from led_config_t matrix mapping):
// Matrix positions:
//   Up   [4,14] -> LED 80
//   Left [5,13] -> LED 92
//   Down [5,14] -> LED 93
//   Right[5,15] -> LED 94
#    define ARROW_UP_LED_INDEX 80
#    define ARROW_LEFT_LED_INDEX 92
#    define ARROW_DOWN_LED_INDEX 93
#    define ARROW_RIGHT_LED_INDEX 94

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // If RGB Matrix is disabled or suspended, don't light indicators
    if (!rgb_matrix_get_flags()) {
        return false;
    }

    // Re-enable layer coloring after 3 seconds of no RGB keycode activity
    if (!rgb_layer_coloring_enabled && rgb_keycode_timer && timer_elapsed32(rgb_keycode_timer) > 3000) {
        rgb_layer_coloring_enabled = true;
        rgb_keycode_timer = 0;
    }

    const bool caps_hw   = host_keyboard_led_state().caps_lock;
    const bool caps_word = is_caps_word_on();

    if (caps_hw || caps_word) {
        if (CAPS_LOCK_LED_INDEX >= led_min && CAPS_LOCK_LED_INDEX < led_max) {
            // Bright white for active Caps indicator
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
        }
    } else {
        // Ensure LED is off when neither is active (let the running effect handle it otherwise)
        if (CAPS_LOCK_LED_INDEX >= led_min && CAPS_LOCK_LED_INDEX < led_max) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }

    // Arrow cluster indicators:
    //  - Green when WASD<->Arrow swap active
    //  - Red when SOCD enabled (and swap not active)
    //  - Yellow when both active
    if (socd_cleaner_enabled || swap_hands_active) {
        uint8_t r = 0, g = 0, b = 0;
        if (swap_hands_active && socd_cleaner_enabled) {
            r = 255;
            g = 160;
            b = 0;
        } // both -> amber
        else if (swap_hands_active) {
            r = 0;
            g = 255;
            b = 0;
        } // swap only
        else {
            r = 255;
            g = 0;
            b = 0;
        } // socd only
        const uint8_t arrow_leds[] = {ARROW_UP_LED_INDEX, ARROW_LEFT_LED_INDEX, ARROW_DOWN_LED_INDEX, ARROW_RIGHT_LED_INDEX};
        for (uint8_t i = 0; i < sizeof(arrow_leds); i++) {
            uint8_t idx = arrow_leds[i];
            if (idx >= led_min && idx < led_max) {
                RGB_MATRIX_INDICATOR_SET_COLOR(idx, r, g, b);
            }
        }
    }

    // Only apply layer coloring if enabled and not temporarily disabled
    if (rgb_layer_coloring_enabled) {
        for (uint8_t i = led_min; i < led_max; i++) {
            switch (get_highest_layer(layer_state | default_layer_state)) {
                case 3:
                    rgb_matrix_set_color(i, RGB_BLUE);
                    break;
                default:
                    break;
            }
        }
    }

    // Return false to allow kb-level/other indicators to run as well
    return false;
}
#endif

// Ensure no LEDs are left on when the host suspends/powers off USB
void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
    rgb_matrix_set_color_all(0, 0, 0);
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}
