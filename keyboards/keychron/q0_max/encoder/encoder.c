/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// clang-format off

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {0, CB10_CA3,   CB12_CA3,   CB11_CA3},
    {0, CB10_CA4,   CB12_CA4,   CB11_CA4},
    {0, CB10_CA5,   CB12_CA5,   CB11_CA5},

    {0, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},

    {0, CB7_CA1,    CB9_CA1,    CB8_CA1},
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {0, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5},

    {0, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {0, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9},

    {0, CB1_CA1,    CB3_CA1,    CB2_CA1},
    {0, CB1_CA2,    CB3_CA2,    CB2_CA2},
    {0, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {0, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {0, CB1_CA5,    CB3_CA5,    CB2_CA5},

    {0, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {0, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {0, CB1_CA9,    CB3_CA9,    CB2_CA9},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3 },
        {  4,  5,  6,  7,  8 },
        {  9, 10, 11, 12, 13 },
        { 14, 15, 16, 17, __ },
        { 18, 19, 20, 21, 22 },
        { 23, 24, __, 25, __ }

    },
    {
        //  LED Index to Physical Position
                 {102, 0},{117, 0}, {132, 0}, {147, 0},
        {87,15}, {102,15},{117,15}, {132,15}, {147,15},
        {87,26}, {102,26},{117,26}, {132,26}, {147,32},
        {87,38}, {102,38},{117,38}, {132,38},
        {87,49}, {102,49},{117,49}, {132,49}, {147,55},
        {87,61}, {110,61},          {132,61},
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1,    1,
    }
};
#endif
