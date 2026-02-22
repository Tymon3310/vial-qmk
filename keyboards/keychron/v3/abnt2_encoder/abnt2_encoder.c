/* Copyright 2021 ~ 2025 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE
// clang-format off
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {0, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {0, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {0, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {0, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {0, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {0, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9 },
    {0, CB7_CA8,    CB9_CA8,    CB8_CA8 },
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7 },
    {0, CB7_CA6,    CB9_CA6,    CB8_CA6 },
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5 },
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4 },
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2 },
    {0, CB7_CA1,    CB9_CA1,    CB8_CA1 },
    {1, CB1_CA3,    CB3_CA3,    CB2_CA3},

    {0, CB1_CA16,   CB3_CA16,   CB2_CA16},
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
    {1, CB1_CA2,    CB3_CA2,    CB2_CA2},

    {0, CB10_CA16,  CB12_CA16,  CB11_CA16},
    {0, CB10_CA15,  CB12_CA15,  CB11_CA15},
    {0, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {0, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {0, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {0, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {0, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {0, CB10_CA4,   CB12_CA4,   CB11_CA4},
    {0, CB10_CA3,   CB12_CA3,   CB11_CA3},
    {0, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {0, CB10_CA1,   CB12_CA1,   CB11_CA1},
    {1, CB1_CA1,    CB3_CA1,    CB2_CA1},

    {1, CB1_CA16,   CB3_CA16,   CB2_CA16},
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

    {1, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {1, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {1, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {1, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {1, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {1, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {1, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {1, CB7_CA9,    CB9_CA9,    CB8_CA9 },
    {1, CB7_CA8,    CB9_CA8,    CB8_CA8 },
    {1, CB7_CA7,    CB9_CA7,    CB8_CA7 },
    {1, CB7_CA6,    CB9_CA6,    CB8_CA6 },
    {1, CB7_CA5,    CB9_CA5,    CB8_CA5 },
    {1, CB7_CA4,    CB9_CA4,    CB8_CA4 },
    {1, CB7_CA3,    CB9_CA3,    CB8_CA3 },
    {1, CB7_CA1,    CB9_CA1,    CB8_CA1 },

    {1, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {1, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {1, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {1, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {1, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {1, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {1, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {1, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {1, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {1, CB4_CA1,    CB6_CA1,    CB5_CA1},
    {1, CB7_CA2,    CB9_CA2,    CB8_CA2 },
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, __, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 },
        { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, __, __, __, __ },
        { 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, __, 77, __ },
        { 78, 79, 80, __, __, __, 81, __, __, __, 82, 83, 84, 85, 86, 87, 88 },
    },
    {
        // LED Index to Physical Position
        {0,0},  {16,0},  {29,0},  {42,0},  {55,0},  {71,0},  {84,0},  {97,0},   {110,0},  {126,0},  {139,0},  {152,0},  {165,0},            {198,0},  {211,0},  {224,0},
        {0,15}, {13,15}, {26,15}, {39,15}, {52,15}, {65,15}, {78,15}, {91,15},  {104,15}, {117,15}, {130,15}, {143,15}, {156,15}, {169,15}, {198,15}, {211,15}, {224,15},
        {7,28}, {19,28}, {32,28}, {45,28}, {59,28}, {72,28}, {85,28}, {98,28},  {111,28}, {124,28}, {137,28}, {150,28}, {163,28}, {170,34}, {198,28}, {211,28}, {224,28},
        {7,40}, {23,40}, {36,40}, {49,40}, {62,40}, {75,40}, {88,40}, {101,40}, {114,40}, {127,40}, {140,40}, {153,40}, {166,40},
        {8,52}, {13,52}, {26,52}, {39,52}, {52,52}, {65,52}, {78,52}, {91,52},  {104,52}, {117,52}, {130,52}, {143,52}, {156,52}, {170,52},           {211,52},
        {2,64}, {16,64}, {31,64},                            {81,64},                               {130,64}, {143,64}, {156,64}, {169,64},  {198,64}, {211,64}, {224,64},
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
        1, 1, 1,          4,          1, 1, 1, 1, 1, 1, 1,
    }
};

// Default Color of Per Key RGB
#define DC_RED {HSV_RED}
#define DC_BLU {HSV_BLUE}
#define DC_YLW {HSV_YELLOW}

HSV default_per_key_led[RGB_MATRIX_LED_COUNT] = {
    DC_RED, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,         DC_YLW, DC_YLW, DC_YLW,
    DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_RED, DC_YLW, DC_YLW, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW,         DC_YLW,
    DC_YLW, DC_YLW, DC_YLW,                         DC_BLU,                         DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
};

// Default mixed RGB region
uint8_t default_region[RGB_MATRIX_LED_COUNT] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,
    0, 0, 0,          0,          0, 0, 0, 0, 0, 0, 0,
};
#endif
