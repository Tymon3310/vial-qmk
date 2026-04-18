/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
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

#pragma once

#ifdef RGB_MATRIX_ENABLE
/* LED Current Configuration */
#    define SNLED27351_CURRENT_TUNE \
         { 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36 }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 61

/* Indications */
#    define BT_INDCATION_LED_MATRIX_LIST \
        { 15, 16, 17 }

#    define P24G_INDICATION_LED_INDEX 18

#    define BAT_LEVEL_LED_LIST \
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }

#    define CAPS_LOCK_INDEX 28
#    define LOW_BAT_IND_INDEX \
        { 56 }

#endif
