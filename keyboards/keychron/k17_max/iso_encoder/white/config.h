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

#ifdef LED_MATRIX_ENABLE
/* LED Matrix driver configuration */
#    define LED_MATRIX_LED_COUNT 104
#    define DRIVER_CS_PINS \
        { B9 }

/* Scan phase of led driver */
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL
/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A }

/* Set to infinit, which is use in USB mode by default */
#    define LED_MATRIX_TIMEOUT LED_MATRIX_TIMEOUT_INFINITE
/* Allow shutdown of led driver to save power */
#    define LED_MATRIX_DRIVER_SHUTDOWN_ENABLE
#    define LED_MATRIX_DRIVER_LOAD_ENABLE
/* Turn off backlight on low brightness to save power */
#    define LED_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48

/* Indications */
#    define DIM_CAPS_LOCK
#    define CAPS_LOCK_INDEX 54
#    define DIM_NUM_LOCK
#    define NUM_LOCK_INDEX 33
#    define LOW_BAT_IND_INDEX \
        { 93 }
#    define BT_INDCATION_LED_MATRIX_LIST \
        { 19, 20, 21 }
#    define P24G_INDICATION_LED_MATRIX_INDEX 22
#    define BAT_LEVEL_LED_LIST \
        { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 }

#    define LED_MATRIX_KEYPRESSES
#endif
