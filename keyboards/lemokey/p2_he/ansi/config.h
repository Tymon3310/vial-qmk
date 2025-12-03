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

#define VIA_FIRMWARE_VERSION 0x00000001

#ifdef RGB_MATRIX_ENABLE
/* LED Current Configuration */
#    define SNLED27351_CURRENT_TUNE \
        { 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38 }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 65

/* Indications */
#    define CAPS_LOCK_INDEX 29
#    define DIM_WIN_LOCK
#    define WINLOCK_LED_LIST \
        { 57 }
#    define LOW_BAT_IND_INDEX \
        { 59 }
#    define PROFILE_LED_MATRIX_LIST \
        { 44, 45, 46 }

#endif
