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
#    define RGB_MATRIX_LED_COUNT 112

#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define SNLED27351_SELECT_PINS \
        { B8, B9 }
#    define SNLED27351_SPI_DIVISOR 16
#    define SPI_DRIVER SPID1

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12 }

#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48

/* Indications */
#    define LOW_BAT_IND_INDEX \
        { 101 }
#    define NUM_LOCK_INDEX 38

#endif
