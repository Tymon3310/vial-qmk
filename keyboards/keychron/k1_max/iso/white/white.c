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

#include "quantum.h"

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, CB6_CA1},
    {0, CB6_CA2},
    {0, CB6_CA3},
    {0, CB6_CA4},
    {0, CB6_CA5},
    {0, CB6_CA6},
    {0, CB6_CA7},
    {0, CB6_CA8},
    {0, CB6_CA9},
    {0, CB6_CA10},
    {0, CB6_CA11},
    {0, CB6_CA12},
    {0, CB6_CA13},
    {0, CB6_CA15},
    {0, CB6_CA16},
    {0, CB1_CA8},

    {0, CB5_CA1},
    {0, CB5_CA2},
    {0, CB5_CA3},
    {0, CB5_CA4},
    {0, CB5_CA5},
    {0, CB5_CA6},
    {0, CB5_CA7},
    {0, CB5_CA8},
    {0, CB5_CA9},
    {0, CB5_CA10},
    {0, CB5_CA11},
    {0, CB5_CA12},
    {0, CB5_CA13},
    {0, CB5_CA14},
    {0, CB5_CA15},
    {0, CB5_CA16},
    {0, CB1_CA9},

    {0, CB4_CA1},
    {0, CB4_CA2},
    {0, CB4_CA3},
    {0, CB4_CA4},
    {0, CB4_CA5},
    {0, CB4_CA6},
    {0, CB4_CA7},
    {0, CB4_CA8},
    {0, CB4_CA9},
    {0, CB4_CA10},
    {0, CB4_CA11},
    {0, CB4_CA12},
    {0, CB4_CA13},
    {0, CB4_CA14},
    {0, CB4_CA15},
    {0, CB4_CA16},
    {0, CB1_CA6},

    {0, CB3_CA1},
    {0, CB3_CA2},
    {0, CB3_CA3},
    {0, CB3_CA4},
    {0, CB3_CA5},
    {0, CB3_CA6},
    {0, CB3_CA7},
    {0, CB3_CA8},
    {0, CB3_CA9},
    {0, CB3_CA10},
    {0, CB3_CA11},
    {0, CB3_CA12},
    {0, CB3_CA14},

    {0, CB2_CA1},
    {0, CB2_CA2},
    {0, CB2_CA3},
    {0, CB2_CA4},
    {0, CB2_CA5},
    {0, CB2_CA6},
    {0, CB2_CA7},
    {0, CB2_CA8},
    {0, CB2_CA9},
    {0, CB2_CA10},
    {0, CB2_CA11},
    {0, CB2_CA12},
    {0, CB2_CA14},
    {0, CB2_CA16},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA7},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
    {0, CB2_CA15},
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
        { 77, 78, 79,__, __, __,  80, __, __, __, 81, 82, 83, 84, 85, 86, 87 },
    },
    {
        // LED Index to Physical Position
        {0, 0},          {26, 0}, {39, 0}, {52, 0}, {65, 0}, {85, 0}, { 98, 0}, {111, 0}, {124, 0}, {144, 0}, {157, 0}, {170, 0}, {183, 0}, {198, 0}, {211, 0}, {224, 0},
        {0,14}, {13,14}, {26,14}, {39,14}, {52,14}, {65,14}, {79,14}, { 92,14}, {105,14}, {118,14}, {131,14}, {144,14}, {157,14}, {177,14}, {198,14}, {211,14}, {224,14},
        {3,26}, {20,26}, {33,26}, {46,26}, {59,26}, {72,26}, {85,26}, { 98,26}, {111,26}, {124,26}, {138,26}, {151,26}, {164,26}, {178,33}, {198,26}, {211,26}, {224,26},
        {5,39}, {23,39}, {36,39}, {49,39}, {62,39}, {75,39}, {88,39}, {102,39}, {115,39}, {128,39}, {141,39}, {154,39},           {169,39},
        {2,51}, {16,51}, {30,51}, {43,51}, {56,51}, {69,51}, {82,51}, { 95,51}, {108,51}, {121,51}, {134,51}, {147,51},           {172,51},           {211,51},
        {2,64}, {18,64}, {34,64},                            {84,64},                               {133,64}, {149,64}, {165,64}, {182,64}, {198,64}, {211,64}, {224,64},
    },
    {
        // RGB LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1, 1, 1,          1,          1, 1, 1, 1, 1, 1, 1,
    }
};
#endif
