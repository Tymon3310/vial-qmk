/* Copyright 2021 ~ 2025 @ Keychron (https://www.keychron.com)
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

/* I2C Driver Configuration */
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C1_OPMODE OPMODE_I2C

/* EEPROM Driver Configuration */
#define EXTERNAL_EEPROM_BYTE_COUNT 8192
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_WRITE_TIME 5
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix driver configuration */
#    define SPI_DRIVER SPIDQ
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#    define SNLED27351_SELECT_PINS \
        { A8, A9 }
#    define SNLED27351_SDB_PIN B7
#    define SNLED27351_SPI_DIVISOR 32

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92 }

#    define RGB_MATRIX_LED_COUNT 89
#    define CAPS_LOCK_INDEX 50
#endif

#define UID_BASE (0x1FFFF204UL)
