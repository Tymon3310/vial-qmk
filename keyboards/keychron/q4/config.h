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

#ifdef RGB_MATRIX_ENABLE
/* Increase I2C speed to 1000 KHz */
#    define I2C1_TIMINGR_PRESC 0U
#    define I2C1_TIMINGR_SCLDEL 3U
#    define I2C1_TIMINGR_SDADEL 0U
#    define I2C1_TIMINGR_SCLH 15U
#    define I2C1_TIMINGR_SCLL 51U

/* Set LED current */
#    define SNLED27351_CURRENT_TUNE \
        { 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60 }
#endif

#define CUSTOM_KEYCODES_ENABLE

/* Factory test keys */
#define FN_KEY_1 MO(2)
#define FN_KEY_2 MO(3)
#define FN_KEY_3 MO(4)
#define FN_BL_TRIG_KEY KC_END
