/* Copyright 2023 ~ 2025 @ Keychron (https://www.keychron.com)
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

enum layers {
    BASE,
    FUNC,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE,  MO(FUNC), KC_ESC,   KC_BSPC,  KC_TAB,
        _______,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        _______,  KC_P4,    KC_P5,    KC_P6,
        _______,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        _______,  KC_P0,              KC_PDOT),

    [FUNC] = LAYOUT_numpad_6x5(
        UG_TOGG,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,
        _______,  UG_NEXT,  UG_VALU,  UG_HUEU,  KC_DEL,
        _______,  UG_PREV,  UG_VALD,  UG_HUED,  _______,
        _______,  UG_SATU,  UG_SPDU,  KC_MPRV,
        _______,  UG_SATD,  UG_SPDD,  KC_MPLY,  _______,
        _______,  UG_TOGG,            KC_MNXT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FUNC] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
};
#endif // ENCODER_MAP_ENABLE
