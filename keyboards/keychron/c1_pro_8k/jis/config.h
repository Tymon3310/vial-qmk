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
/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 91
#    define DRIVER_COUNT 2
#    define SNLED27351_SELECT_PINS \
        { A8, C9 }

/* Scan phase of led driver */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL
/* Set led driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86 }

/* Turn off backllit if brightness value is low */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48

#endif
