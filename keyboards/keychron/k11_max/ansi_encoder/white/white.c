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
    {0, CB4_CA16},

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
    {0, CB3_CA16},

    {0, CB2_CA1},
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
    {0, CB2_CA15},
    {0, CB2_CA16},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA6},
    {0, CB1_CA7},
    {0, CB1_CA8},
    {0, CB1_CA10},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, __, __ },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, __, 28 },
        { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, __, 41, __, 42 },
        { 43, __, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, __, 54, 55, 56 },
        { 57, 58, 59, __, __, 60, 61, 62, __, 63, __, __, 64, 65, 66, 67 },
    },
    {
        // LED Index to Physical Position
        {8, 1}, {20, 1}, {33, 0}, {48, 3}, {61, 6}, {74, 8}, {87,11}, {106,11}, {119, 8}, {132, 6}, {145, 3}, {160, 0}, {173, 1}, {193, 1},
        {8,14}, {24,14}, {39,14}, {52,17}, {65,20}, {78,22}, {103,25},{116,22}, {129,20}, {142,17}, {155,14}, {170,14}, {183,14}, {200,14},           {222,14},
        {8,27}, {24,27}, {39,28}, {52,30}, {65,33}, {78,36}, {109,37},{122,34}, {135,32}, {148,29}, {162,27}, {176,27},           {197,27},           {224,27},
        {8,40},          {28,40}, {43,42}, {56,44}, {69,47}, {82,50}, {102,52}, {115,49}, {128,46}, {141,44}, {154,44},           {169,40}, {189,40}, {209,43},
        {0,53}, {16,53}, {42,55},                   {65,60}, {86,64}, {107,64},           {131,59},                     {156,54}, {196,56}, {209,56}, {222,56},
    },
    {
        //LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1,       1, 1, 1,    1,       1, 1, 1, 1,
    }
};

#endif
