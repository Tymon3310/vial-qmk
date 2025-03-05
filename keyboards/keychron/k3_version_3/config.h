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

/* I2C Driver Configuration */
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

/* EEPROM Driver Configuration */
#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_WRITE_TIME 3

#define I2C1_OPMODE OPMODE_I2C
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010
#define DYNAMIC_KEYMAP_BUFFER_ENABLE

#if defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE) || defined(LK_WIRELESS_ENABLE)
/* SPI configuration */
#    define SPI_DRIVER SPIDQ
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(LED_MATRIX_ENABLE)
#    define SNLED27351_SDB_PIN B7
#    define SNLED23751_SPI_DIVISOR 16

#    ifdef LK_WIRELESS_ENABLE
#        define BT_INDCATION_LED_MATRIX_LIST \
            { 17, 18, 19 }

#        define BAT_LEVEL_LED_LIST \
            { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 }

/* Backlit disable timeout when keyboard is disconnected(unit: second) */
#        define DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT 40
/* Backlit disable timeout when keyboard is connected(unit: second) */
#        define CONNECTED_BACKLIGHT_DISABLE_TIMEOUT 600
/* Reinit LED driver on tranport changed */
#        define REINIT_LED_DRIVER 1
#    endif
#endif

#ifdef LK_WIRELESS_ENABLE
/* Hardware configuration */
#    define BT_MODE_SELECT_PIN A10

#    define LKBT51_RESET_PIN C4
#    define LKBT51_INT_INPUT_PIN B1
#    define LKBT51_INT_OUTPUT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_CHARGING_PIN B13
#    define BAT_CHARGING_LEVEL 0

#    define BAT_LOW_LED_PIN B12
#    define BAT_LOW_LED_PIN_ON_STATE 1

#    define DP_PULLUP_CONTROL_PIN B15

#    define BT_HOST_DEVICES_COUNT 3
#endif

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_KEY_2 MO(3)

#define MATRIX_IO_DELAY 30