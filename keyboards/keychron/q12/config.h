/* Copyright 2023 ~ 2025 @ Keychron (https://www.keychron.com)
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

/* Shift register configuration for matrix scan */
#define HC595_STCP A0
#define HC595_SHCP A1
#define HC595_DS C15
#define HC595_START_INDEX 10
#define HC595_END_INDEX 17

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix Driver Configuration */
#    define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_VDDIO
#    define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_GND

/* Increase I2C speed to 1000 KHz */
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 3U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 15U
#    define I2C1_TIMINGR_SCLL 51U

/* Set LED Current */
#    define SNLED27351_CURRENT_TUNE \
        { 0xAD, 0xAD, 0x55, 0xAD, 0xAD, 0x55, 0xAD, 0xAD, 0x55, 0xAD, 0xAD, 0x55 }

#endif

#define CUSTOM_KEYCODES_ENABLE

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_KEY_2 MO(3)
