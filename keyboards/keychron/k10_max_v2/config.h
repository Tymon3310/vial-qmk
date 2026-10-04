/* Copyright 2025 ~ 2026 @ Keychron (https://www.keychron.com)
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
#include "eeconfig_kb.h"

/* HC595 configuration */
#define HC595_STCP C3
#define HC595_SHCP B10
#define HC595_DS C8
#define HC595_START_INDEX 13
#define HC595_END_INDEX 20

/* MAC/WIN Led pins */
#define LED_WIN_PIN A0
#define LED_MAC_PIN A2
#define LED_OS_PIN_ON_STATE 1

#if defined(RGB_MATRIX_ENABLE) || defined(LK_WIRELESS_ENABLE)
/* Hardware configuration */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#endif

#if defined(RGB_MATRIX_ENABLE)
#    define SNLED27351_SDB_PIN C5
#    define SNLED27351_SPI_DIVISOR 16

#    ifdef LK_WIRELESS_ENABLE
#        define BT_INDCATION_LED_MATRIX_LIST \
            { 17, 18, 19 }

#        define P24G_INDICATION_LED_INDEX 20

#        define BAT_LEVEL_LED_LIST \
            { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 }

/* Reinit LED driver on tranport changed */
#        define LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE
#    endif
#endif

#ifdef LK_WIRELESS_ENABLE
/* Hardware configuration */
#    define P24G_MODE_SELECT_PIN A9
#    define BT_MODE_SELECT_PIN A10

#    define LKBT51_RESET_PIN C4
#    define WIRELESS_TO_MCU_INT_PIN B1
#    define MCU_TO_WIRELESS_INT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_CHARGING_PIN B13
#    define BAT_CHARGING_LEVEL 0

#    define BAT_LOW_LED_PIN A3
#    define BAT_LOW_LED_PIN_ON_STATE 1

#    define BT_HOST_DEVICES_COUNT 3

/* Keep USB connection in wireless mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Enable wireless NKRO */
#    define WIRELESS_NKRO_ENABLE

#endif

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_KEY_2 MO(3)

#define MATRIX_IO_DELAY 10
