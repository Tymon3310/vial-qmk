/* Copyright 2025 ~ 2026 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "xinput_keycodes.h"

uint8_t profile_gobal_mode[PROFILE_COUNT] = {
    AKM_REGULAR,
    AKM_RAPID,
    AKM_RAPID,
};

// clang-format off
const uint16_t PROGMEM default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tenkey_27(
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,                0         ),

    [1] = LAYOUT_tenkey_27(
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,                0         ),

    [2] = LAYOUT_tenkey_27(
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,       0,       0,
        0,       0,       0,       0,       0,
        0,       0,                0         )

};
