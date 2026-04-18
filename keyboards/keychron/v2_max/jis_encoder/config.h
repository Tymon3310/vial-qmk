/* Copyright 2025 @ Keychron (https://www.keychron.com)
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
        { 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 70

/* Indications */
#    define BT_INDCATION_LED_MATRIX_LIST \
        { 16, 17, 18 }

#    define P24G_INDICATION_LED_INDEX 19

#    define BAT_LEVEL_LED_LIST \
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 }

#    define CAPS_LOCK_INDEX 30
#    define LOW_BAT_IND_INDEX \
        { 62 }

#endif
