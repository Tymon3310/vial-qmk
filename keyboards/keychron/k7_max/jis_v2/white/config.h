/* Copyright 2025 ~ 2026@ Keychron (https://www.keychron.com)
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

#ifdef LED_MATRIX_ENABLE
/* LED matrix driver configuration */
#    define SNLED27351_SELECT_PINS \
        { B9 }

/* LED Current Configuration */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_6_CHANNEL
#    define SNLED27351_CURRENT_TUNE \
        { 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A }

/* LED matrix driver configuration */
#    define LED_MATRIX_LED_COUNT 71

/* Indications */
#    define DIM_CAPS_LOCK
#    define CAPS_LOCK_INDEX 31
#    define BT_INDCATION_LED_MATRIX_LIST \
        { 17, 18, 19 }
#    define P24G_INDICATION_LED_INDEX 20
#    define LOW_BAT_IND_INDEX \
        { 63 }

#endif
