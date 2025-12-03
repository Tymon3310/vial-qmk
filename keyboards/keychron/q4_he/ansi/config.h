/* Copyright 2025 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE
/* LED Current Configuration */
#    define SNLED27351_CURRENT_TUNE \
        { 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48 }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 61

/* Indications */
#    define CAPS_LOCK_INDEX 28
#    define PROFILE_LED_MATRIX_LIST \
        { 42, 43, 44 }
#    define LOW_BAT_IND_INDEX \
        { 56 }

#endif
