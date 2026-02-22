/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
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

#ifdef LED_MATRIX_ENABLE
/* LED matrix driver configuration */
#    define SNLED27351_SELECT_PINS \
        { C9 }

/* LED Matrix Current Configuration */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_8_CHANNEL
#    define SNLED27351_CURRENT_TUNE \
        { 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60 }

/* LED Matrix Configuration */
#    define LED_MATRIX_LED_COUNT 88

/* Indications */
#    ifdef LK_WIRELESS_ENABLE
#        define BT_INDCATION_LED_MATRIX_LIST \
            { 17, 18, 19 }
#        define P24G_INDICATION_LED_INDEX 20
#        define BAT_LEVEL_LED_LIST \
            { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 }
#    endif

#endif
