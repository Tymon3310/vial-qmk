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
#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB7_CA1,    CB9_CA1,    CB8_CA1},
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {0, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {0, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {0, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {0, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {0, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {0, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {0, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {0, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {0, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {0, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {1, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {1, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {0, CB10_CA16,  CB12_CA16,  CB11_CA16},

    {0, CB4_CA1,    CB6_CA1,    CB5_CA1},
    {0, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {0, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {0, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {0, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {0, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {0, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {0, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {0, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {0, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {0, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {0, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {0, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {0, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {0, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},

    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {0, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {0, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {0, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {0, CB10_CA15,  CB12_CA15,  CB11_CA15},

    {1, CB7_CA1,    CB9_CA1,    CB8_CA1},
    {1, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {1, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {1, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {1, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {1, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {1, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {1, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {1, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {1, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {1, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {1, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {1, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {1, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {1, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {1, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {1, CB10_CA9,   CB12_CA9,   CB11_CA9},

    {1, CB1_CA1,    CB3_CA1,    CB2_CA1},
    {1, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {1, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {1, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {1, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {1, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {1, CB1_CA8,    CB3_CA8,    CB2_CA8},
    {1, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {1, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {1, CB1_CA11,   CB3_CA11,   CB2_CA11},
    {1, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {1, CB1_CA13,   CB3_CA13,   CB2_CA13},
    {1, CB1_CA15,   CB3_CA15,   CB2_CA15},
    {1, CB1_CA16,   CB3_CA16,   CB2_CA16},
    {1, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {1, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {1, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {1, CB10_CA13,  CB12_CA13,  CB11_CA13},

    {1, CB4_CA1,    CB6_CA1,    CB5_CA1},
    {1, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {1, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {1, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {1, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {1, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {1, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {1, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {1, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {1, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {1, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {1, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {1, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {1, CB10_CA16,  CB12_CA16,  CB11_CA16}
};


#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to RGB Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, __ },
        { 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 },
        { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, __, 52, 53, 54, 55, 56, 57 },
        { 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, __, 70, __, 71, 72, 73, 74, __ },
        { 75, __, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, __, 87, 88, 89, 90, 91, 92 },
        { 93, 94, 95, 96, __, __, 97, __, __, 98, 99,100,101,102,103,104,105, __,106, __ },
    },
    {
        // RGB Index to Physical Position
        {0, 0}, {12, 0}, {24, 0}, {36, 0}, {48, 0}, {60, 0}, {72, 0}, {84, 0}, {96, 0}, {108, 0}, {120, 0}, {132, 0}, {144, 0}, {156, 0}, {168, 0}, {180, 0},{192, 0},{203, 0},{213, 0},
        {0,13}, {12,13}, {24,13}, {36,13}, {48,13}, {60,13}, {72,13}, {84,13}, {96,13}, {108,13}, {120,13}, {132,13}, {144,13}, {156,13}, {168,13}, {180,13},{192,13},{203,13},{213,13},{224,13},
        {2,26}, {18,26}, {30,26}, {42,26}, {54,26}, {66,26}, {78,26}, {90,26}, {102,26},{114,26}, {126,26}, {138,26}, {150,26},           {168,32}, {180,26},{192,26},{203,26},{213,26},{224,32},
        {4,39}, {22,39}, {34,39}, {46,39}, {58,39}, {70,39}, {82,39}, {94,39}, {106,39},{118,39}, {130,39}, {142,39},           {154,39},           {180,39},{192,39},{203,39},{213,39},
        {7,51},          {28,51}, {40,51}, {52,51}, {64,51}, {76,51}, {88,51}, {100,51},{112,51}, {124,51}, {136,51}, {148,51}, {168,51},           {180,51},{192,51},{203,51},{213,51},{224,57},
        {1,64}, {15,64}, {30,64}, {42,64},                   {78,64},                   {114,64}, {126,64}, {140,64},           {154,64}, {168,64}, {180,64},{192,64},{202,64},{213,64},
    },
    {
        // RGB Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1, 1, 1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,       1,       1, 1, 1, 1, 1, 1, 1, 1,    1,
    }
};
#endif
