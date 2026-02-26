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
    _BASE,
    _FN1,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_6x4(
        MO(_FN1), KC_ESC,   KC_BSPC,  KC_TAB,
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,
        KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_P1,    KC_P2,    KC_P3,
        KC_P0,              KC_PDOT,  KC_PENT),

    [_FN1] = LAYOUT_numpad_6x4(
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,
        UG_NEXT,  UG_VALU,  UG_HUEU,  KC_DEL,
        UG_PREV,  UG_VALD,  UG_HUED,
        UG_SATU,  UG_SPDU,  KC_MPRV,  _______,
        UG_SATD,  UG_SPDD,  KC_MPLY,
        UG_TOGG,            KC_MNXT,  _______)
};


