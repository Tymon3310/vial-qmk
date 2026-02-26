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
#include "config.h"
#include "keychron_common.h"
#include "keychron_rgb_type.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif

extern os_indicator_config_t os_ind_cfg;

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    LAYER_4,
    LAYER_5,
    LAYER_6,
    LAYER_7,
    LAYER_8,
    LAYER_9,
    LAYER_10,
    LAYER_11,
    LAYER_12,
    LAYER_13,
    LAYER_14,
    LAYER_15,
};

/* Custom keycodes - after SC_TOGG (index 16) */
enum custom_keycodes {
    WASD_TOG = QK_KB_17, /* WASD <-> Arrow swap toggle */
};

/* Track swap-hands state for LED indication */
static bool wasd_swap_active = false;

/* Timer for temporarily disabling layer RGB coloring when RGB keycodes are used */
static uint32_t rgb_keycode_timer          = 0;
static bool     rgb_layer_coloring_enabled = true;

/* LED indices for indicators */
#define CAPS_LOCK_LED_INDEX 51
/* WASD LED indices (from led_config_t matrix mapping):
 *   W [2,2] -> LED 33
 *   A [3,1] -> LED 52
 *   S [3,2] -> LED 53
 *   D [3,3] -> LED 54
 */
#define W_LED_INDEX 33
#define A_LED_INDEX 52
#define S_LED_INDEX 53
#define D_LED_INDEX 54
/* Arrow key LED indices:
 *   Up   [4,14] -> LED 80
 *   Left [5,13] -> LED 92
 *   Down [5,14] -> LED 93
 *   Right[5,15] -> LED 94
 */
#define ARROW_UP_LED_INDEX 80
#define ARROW_LEFT_LED_INDEX 92
#define ARROW_DOWN_LED_INDEX 93
#define ARROW_RIGHT_LED_INDEX 94

/* Layer color definitions - 16 distinct colors
 * Using HSV with spread across the spectrum plus variations
 * to ensure all 16 layers have unique, easily distinguishable colors
 */
typedef struct {
    uint8_t r, g, b;
} layer_color_t;

static const layer_color_t layer_colors[16] = {
    [MAC_BASE] = {0, 0, 0},     /* Base - no color overlay (use effect) */
    [MAC_FN]   = {150, 80, 30}, /* Mac FN - Warm Orange */
    [WIN_BASE] = {0, 0, 0},     /* Base - no color overlay (use effect) */
    [WIN_FN]   = {150, 80, 30}, /* Win FN - Warm Orange */
    [LAYER_4]  = {255, 0, 0},   /* Red */
    [LAYER_5]  = {255, 127, 0}, /* Orange */
    [LAYER_6]  = {255, 255, 0}, /* Yellow */
    [LAYER_7]  = {127, 255, 0}, /* Chartreuse */
    [LAYER_8]  = {0, 255, 0},   /* Green */
    [LAYER_9]  = {0, 255, 127}, /* Spring Green */
    [LAYER_10] = {0, 255, 255}, /* Cyan */
    [LAYER_11] = {0, 127, 255}, /* Azure */
    [LAYER_12] = {0, 0, 255},   /* Blue */
    [LAYER_13] = {127, 0, 255}, /* Violet */
    [LAYER_14] = {255, 0, 255}, /* Magenta */
    [LAYER_15] = {255, 0, 127}, /* Rose */
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
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  SC_TOGG,  WASD_TOG, _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
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
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  SC_TOGG,  WASD_TOG, _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    /* Layers 4-15: Empty templates for Vial customization */
    [LAYER_4] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_5] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_6] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_7] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_8] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_9] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_10] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_11] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_12] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_13] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_14] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
    [LAYER_15] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,  _______,  _______,    
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______            ),
 };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [LAYER_4]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_5]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_6]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_7]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_8]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_9]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_10] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_11] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_12] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_13] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_14] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_15] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif // ENCODER_MAP_ENABLE

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
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            /* Temporarily disable layer coloring when RGB keys are used */
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
                rgb_keycode_timer          = timer_read32();
                rgb_layer_coloring_enabled = false;
                break;

            /* WASD <-> Arrow swap toggle */
            case WASD_TOG:
                swap_hands_toggle();
                wasd_swap_active = is_swap_hands_on();
#ifdef RGB_MATRIX_ENABLE
                /* Visual feedback: cyan flash when enabled, red flash when disabled */
                if (wasd_swap_active) {
                    rgb_matrix_set_color_all(0, 255, 255); /* Cyan */
                } else {
                    rgb_matrix_set_color_all(255, 0, 0); /* Red */
                }
#endif
                return false;

            default:
                break;
        }
    }
    return true;
}

/* Define handedness of the keyboard layout for Chordal Hold */
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, {'L', 'L', 'L', '*', '*', '*', '*', '*', '*', '*', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    /* Skip if RGB Matrix is disabled or suspended */
    if (!rgb_matrix_get_flags()) {
        return false;
    }

    /* Re-enable layer coloring after 3 seconds of no RGB keycode activity */
    if (!rgb_layer_coloring_enabled && rgb_keycode_timer && timer_elapsed32(rgb_keycode_timer) > 3000) {
        rgb_layer_coloring_enabled = true;
        rgb_keycode_timer          = 0;
    }

    /* === WASD <-> Arrow swap indicator ===
     * When active: Light both WASD and Arrow keys in Cyan
     * This makes it visually clear that they are swapped
     */
    if (wasd_swap_active) {
        const uint8_t wasd_leds[]  = {W_LED_INDEX, A_LED_INDEX, S_LED_INDEX, D_LED_INDEX};
        const uint8_t arrow_leds[] = {ARROW_UP_LED_INDEX, ARROW_LEFT_LED_INDEX, ARROW_DOWN_LED_INDEX, ARROW_RIGHT_LED_INDEX};

        /* Light WASD keys in Cyan */
        for (uint8_t i = 0; i < sizeof(wasd_leds); i++) {
            uint8_t idx = wasd_leds[i];
            if (idx >= led_min && idx < led_max) {
                RGB_MATRIX_INDICATOR_SET_COLOR(idx, 0, 255, 255);
            }
        }

        /* Light Arrow keys in Cyan */
        for (uint8_t i = 0; i < sizeof(arrow_leds); i++) {
            uint8_t idx = arrow_leds[i];
            if (idx >= led_min && idx < led_max) {
                RGB_MATRIX_INDICATOR_SET_COLOR(idx, 0, 255, 255);
            }
        }
    }

    /* === Layer color overlay ===
     * Only apply if enabled and not temporarily disabled by RGB keycode use
     * Each layer 4-15 has a unique, easily distinguishable color
     */
    if (rgb_layer_coloring_enabled) {
        uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);

        /* Skip base layers (0-3) - let the RGB effect handle them */
        if (current_layer >= LAYER_4 || current_layer == MAC_FN || current_layer == WIN_FN) {
            layer_color_t color = layer_colors[current_layer];

            /* Only apply if the layer has a defined color */
            if (color.r != 0 || color.g != 0 || color.b != 0) {
                for (uint8_t i = led_min; i < led_max; i++) {
                    rgb_matrix_set_color(i, color.r, color.g, color.b);
                }
            }
        }
    }

    return false; /* Allow kb-level/other indicators to run */
}
#endif

/* Ensure no LEDs are left on when the host suspends/powers off USB */
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
