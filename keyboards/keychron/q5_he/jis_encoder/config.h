/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

/* External EEPROM Write Protect Pin*/
#define EXTERNAL_EEPROM_WP_PIN C8

/* Analog Matrix Configuration */
#define ANALOG_MATRIX_POWER_PIN C12

/* HC164 Shift Register Configuration */
#define HC164_CP D2
#define HC164_MR B5

#ifdef RGB_MATRIX_ENABLE
/* LED Current Configuration */
#    define SNLED27351_CURRENT_TUNE \
        { 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C }

/* RGB Matrix Configuration */
#    define RGB_MATRIX_LED_COUNT 105

/* Indications */
#    define NUM_LOCK_INDEX 33
#    define CAPS_LOCK_INDEX 56
#    define LOW_BAT_IND_INDEX \
        { 95 }
#    define PROFILE_LED_MATRIX_LIST \
        { 74, 75, 76 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif
