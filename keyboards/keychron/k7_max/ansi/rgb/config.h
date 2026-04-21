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
/* RGB Matrix driver configuration */
#    define SNLED27351_SELECT_PINS \
        { B8, B9 }

/* LED Current Configuration */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL
#    define SNLED27351_CURRENT_TUNE \
        { 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14 }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 68

/* Indications */
#    define CAPS_LOCK_INDEX 30
#    define BT_INDCATION_LED_MATRIX_LIST \
        { 16, 17, 18 }
#    define P24G_INDICATION_LED_INDEX 19
#    define LOW_BAT_IND_INDEX \
        { 61 }

#endif
