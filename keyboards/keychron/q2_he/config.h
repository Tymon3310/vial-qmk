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

#include "eeconfig_kb.h"

/* External EEPROM Configuration*/
#define I2C_DRIVER I2CD3
#define I2C1_SCL_PIN A8
#define I2C1_SDA_PIN C9
#define EXTERNAL_EEPROM_WP_PIN B10

/* Analog Matrix Configuration */
#define ANALOG_MATRIX_POWER_PIN C13
#define ANALOG_MATRIX_POWER_ENABLE_LEVEL 1
#define ANALOG_MATRIX_WAKEUP_PIN C5

#define ENCODER_SWITCH_PIN A3
#define ENCODER_MATRIX_ROW 0
#define ENCODER_MATROX_COL 14

/* Joystick Configuration */
#ifdef JOYSTICK_ENABLE
#    define JOYSTICK_AXIS_COUNT 6
#    define JOYSTICK_BUTTON_COUNT 16
#endif

/* SPI Configuration */
#if defined(RGB_MATRIX_ENABLE) || defined(LK_WIRELESS_ENABLE)
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#endif

/* SNLED27351 Driver Configuration */
#if defined(RGB_MATRIX_ENABLE)
#    define SN3734_SELECT_PINS \
        { B8 }
#    define SN3734_SDB_PIN B7
#    define SN3734_SPI_DIVISOR 16
#endif

/* Wireless Configuration */
#ifdef LK_WIRELESS_ENABLE
/* Hardware Configuration */
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define P24G_MODE_SELECT_PIN A10
#    define BT_MODE_SELECT_PIN A9

#    define LKBT51_RESET_PIN C4
#    define WIRELESS_TO_MCU_INT_PIN B1
#    define MCU_TO_WIRELESS_INT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_CHARGING_PIN B13
#    define BAT_CHARGING_LEVEL 0

#    if defined(RGB_MATRIX_ENABLE)
#        define BT_INDCATION_LED_MATRIX_LIST \
            { 15, 16, 17 }

#        define P24G_INDICATION_LED_INDEX 18

#        define BAT_LEVEL_LED_LIST \
            { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }

/* Reinit LED driver on tranport changed */
#        define LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE
#    endif

/* Keep USB connection in wireless mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Enable wireless NKRO */
#    define WIRELESS_NKRO_ENABLE
#endif

/* Factory test keys */
#define FN_KEY_1 MO(4)
#define FN_Z_KEY UG_PREV
#define FN_BL_TRIG_KEY KC_END

/* Retail Demo Keys*/
#define RETAIL_DEMO_KEY_2 KC_E
#define RETAIL_DEMO_KEY_1 KC_D
