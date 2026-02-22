/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, CB1_CA16},
    {0, CB1_CA14},
    {0, CB1_CA13},
    {0, CB1_CA12},
    {0, CB1_CA11},
    {0, CB1_CA10},
    {0, CB1_CA9},
    {0, CB1_CA8},
    {0, CB1_CA7},
    {0, CB1_CA6},
    {0, CB1_CA5},
    {0, CB1_CA4},
    {0, CB1_CA3},
    {0, CB1_CA2},
    {0, CB1_CA1},
    {0, CB4_CA2},

    {0, CB2_CA16},
    {0, CB2_CA15},
    {0, CB2_CA14},
    {0, CB2_CA13},
    {0, CB2_CA12},
    {0, CB2_CA11},
    {0, CB2_CA10},
    {0, CB2_CA9},
    {0, CB2_CA8},
    {0, CB2_CA7},
    {0, CB2_CA6},
    {0, CB2_CA5},
    {0, CB2_CA4},
    {0, CB2_CA3},
    {0, CB2_CA2},
    {0, CB2_CA1},
    {0, CB5_CA2},

    {0, CB3_CA16},
    {0, CB3_CA15},
    {0, CB3_CA14},
    {0, CB3_CA13},
    {0, CB3_CA12},
    {0, CB3_CA11},
    {0, CB3_CA10},
    {0, CB3_CA9},
    {0, CB3_CA8},
    {0, CB3_CA7},
    {0, CB3_CA6},
    {0, CB3_CA5},
    {0, CB3_CA4},
    {0, CB3_CA3},
    {0, CB3_CA2},
    {0, CB3_CA1},
    {0, CB4_CA1},

    {0, CB4_CA16},
    {0, CB4_CA15},
    {0, CB4_CA14},
    {0, CB4_CA13},
    {0, CB4_CA12},
    {0, CB4_CA11},
    {0, CB4_CA10},
    {0, CB4_CA9},
    {0, CB4_CA8},
    {0, CB4_CA7},
    {0, CB4_CA6},
    {0, CB4_CA5},
    {0, CB4_CA3},

    {0, CB5_CA16},
    {0, CB5_CA15},
    {0, CB5_CA14},
    {0, CB5_CA13},
    {0, CB5_CA12},
    {0, CB5_CA11},
    {0, CB5_CA10},
    {0, CB5_CA9},
    {0, CB5_CA8},
    {0, CB5_CA7},
    {0, CB5_CA6},
    {0, CB5_CA5},
    {0, CB5_CA3},
    {0, CB5_CA1},

    {0, CB6_CA16},
    {0, CB6_CA15},
    {0, CB6_CA14},
    {0, CB6_CA10},
    {0, CB6_CA6},
    {0, CB6_CA5},
    {0, CB6_CA4},
    {0, CB6_CA3},
    {0, CB6_CA2},
    {0, CB6_CA1},
    {0, CB4_CA4},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0, __,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 },
        { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, __, 62, __, __, __ },
        { 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, __, 75, __, 76, __ },
        { 77, 78, 79, __, __, __, 80, __, __, __, 81, 82, 83, 84, 85, 86, 87 },
    },
    {
        // LED Index to Physical Position
        {0, 0},          {25, 0}, {38, 0}, {51, 0}, {64, 0}, {84, 0}, { 97, 0}, {110, 0}, {123, 0}, {142, 0}, {156, 0}, {168, 0}, {180, 0}, {198, 0}, {211, 0}, {224, 0},
        {0,14}, {12,14}, {25,14}, {38,14}, {51,14}, {64,14}, {77,14}, { 90,14}, {103,14}, {116,14}, {129,14}, {142,14}, {156,14}, {175,14}, {198,14}, {211,14}, {224,14},
        {3,26}, {19,26}, {32,26}, {45,26}, {58,26}, {71,26}, {84,26}, { 97,26}, {110,26}, {123,26}, {136,26}, {149,26}, {162,26}, {178,26}, {198,26}, {211,26}, {224,26},
        {4,39}, {22,39}, {35,39}, {48,39}, {61,39}, {74,39}, {87,39}, {100,39}, {113,39}, {126,39}, {139,39}, {152,39},           {165,39},
        {1,51}, {14,51}, {29,51}, {42,51}, {55,51}, {68,51}, {81,51}, {94,51},  {107,51}, {120,51}, {132,51}, {145,51},           {172,51},           {211,51},
        {1,64}, {17,64}, {34,64},                            {82,64},                               {131,64}, {147,64}, {164,64}, {180,64}, {198,64}, {211,64}, {224,64}
    },
    {
        // LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1, 1, 1,          1,          1, 1, 1, 1, 1, 1, 1,
    }
};

#endif
