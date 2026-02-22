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

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* SNLED27351 Driver Configuration */
#ifdef RGB_MATRIX_ENABLE
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MOSI_PIN A7
#    define SNLED27351_SELECT_PINS \
        { A8, C9 }
#    define SNLED27351_SDB_PIN B7
#    define SNLED27351_SPI_DIVISOR 64
#endif

/* Custom keycodes */
#define CUSTOM_KEYCODES_ENABLE

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_KEY_2 MO(3)
