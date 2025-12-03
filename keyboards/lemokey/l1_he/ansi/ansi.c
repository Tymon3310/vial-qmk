/* Copyright 2025 @ Keychron (https://www.keychron.com)
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
const matrix_row_t analog_matrix_mask[] = {
  0b1111111111111110,
  0b1111111111111110,
  0b1111111111111111,
  0b0111111111111111,
  0b1101111111111011,
  0b1111110001001111,
};

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {0, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {0, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {0, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {0, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {0, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {0, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {0, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {0, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {0, CB7_CA1,    CB9_CA1,    CB8_CA1},

    {0, CB1_CA15,   CB3_CA15,   CB2_CA15},
    {0, CB1_CA14,   CB3_CA14,   CB2_CA14},
    {0, CB1_CA13,   CB3_CA13,   CB2_CA13},
    {0, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {0, CB1_CA11,   CB3_CA11,   CB2_CA11},
    {0, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {0, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {0, CB1_CA8,    CB3_CA8,    CB2_CA8},
    {0, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {0, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {0, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {0, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {0, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {0, CB1_CA2,    CB3_CA2,    CB2_CA2},
    {0, CB1_CA1,    CB3_CA1,    CB2_CA1},

    {1, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {0, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {0, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {0, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {0, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {0, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {0, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {0, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {0, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {0, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {0, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {0, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {0, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {0, CB4_CA1,    CB6_CA1,    CB5_CA1},

    {1, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {1, CB1_CA15,   CB3_CA15,   CB2_CA15},
    {1, CB1_CA14,   CB3_CA14,   CB2_CA14},
    {1, CB1_CA13,   CB3_CA13,   CB2_CA13},
    {1, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {1, CB1_CA11,   CB3_CA11,   CB2_CA11},
    {1, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {1, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {1, CB1_CA8,    CB3_CA8,    CB2_CA8},
    {1, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {1, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {1, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {1, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {1, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {1, CB1_CA2,    CB3_CA2,    CB2_CA2},

    {1, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {1, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {1, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {1, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {1, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {1, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {1, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {1, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {1, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {1, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {1, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {1, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {1, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {1, CB7_CA1,    CB9_CA1,    CB8_CA1},

    {1, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {1, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {1, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {1, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {1, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {1, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {1, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {1, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {1, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {1, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {1, CB4_CA1,    CB6_CA1,    CB5_CA1},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
        { __, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
        { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 },
        { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, __ },
        { 61, 62, __, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, __, 73, 74 },
        { 75, 76, 77, 78, __, __, 79, __, __, __, 80, 81, 82, 83, 84, 85 },
    },
    {
        // LED Index to Physical Position
                {24, 0}, {40, 0}, {53, 0}, {67, 0}, {80, 0}, { 96, 0}, {109, 0}, {122, 0}, {135, 0}, {152, 0}, {165, 0}, {178, 0}, {191, 0}, {207, 0}, {224, 0},
                {24,15}, {37,15}, {50,15}, {63,15}, {76,15}, { 90,15}, {103,15}, {116,15}, {129,15}, {142,15}, {155,15}, {168,15}, {181,15}, {201,15}, {224,15},
        {0,21}, {27,26}, {44,26}, {57,26}, {70,26}, {83,26}, { 96,26}, {109,26}, {122,26}, {135,26}, {148,26}, {162,26}, {175,26}, {188,26}, {204,26}, {224,26},
        {0,34}, {29,38}, {47,38}, {60,38}, {73,38}, {86,38}, { 99,38}, {112,38}, {126,38}, {139,38}, {152,38}, {165,38}, {178,38},           {201,38}, {224,38},
        {0,46}, {29,49},          {53,49}, {67,49}, {80,49}, { 93,49}, {106,49}, {119,49}, {132,49}, {145,49}, {158,49}, {171,49}, {189,49}, {201,52},
        {0,58}, {26,61}, {42,61}, {58,61},                   {107,61},                               {155,61}, {168,61}, {181,61}, {195,64}, {201,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1,
        1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,       1,          1, 1, 1, 1, 1, 1
    }
};

// Default Color of Per Key RGB
#define DC_RED {HSV_RED}
#define DC_BLU {HSV_BLUE}
#define DC_YLW {HSV_YELLOW}

HSV default_per_key_led[RGB_MATRIX_LED_COUNT] = {
            DC_RED, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
            DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,
    DC_YLW, DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW,
    DC_YLW, DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU,         DC_RED, DC_YLW,
    DC_YLW, DC_YLW,         DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,
    DC_YLW, DC_YLW, DC_YLW, DC_YLW,                 DC_BLU,                         DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW
};

// Default mixed RGB region
uint8_t default_region[RGB_MATRIX_LED_COUNT] = {
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0,
    0, 0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,       0,          0, 0, 0, 0, 0, 0
};
#endif
