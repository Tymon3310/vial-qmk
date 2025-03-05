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
    {0, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {0, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {0, CB7_CA16,   CB9_CA16,   CB8_CA16},
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

    {0, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {0, CB4_CA14,   CB6_CA14,   CB5_CA14},
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

    {0, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {0, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {0, CB4_CA11,   CB6_CA11,   CB5_CA11},
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

    {1, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {1, CB10_CA12,  CB12_CA12,  CB11_CA12},
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
    {1, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {1, CB1_CA2,    CB3_CA2,    CB2_CA2},

    {1, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {1, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {1, CB10_CA15,  CB12_CA15,  CB11_CA15},
    {1, CB7_CA16,   CB9_CA16,   CB8_CA16},
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
    {1, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {1, CB7_CA2,    CB9_CA2,    CB8_CA2},

    {1, CB10_CA16,  CB12_CA16,  CB11_CA16},
    {1, CB4_CA16,   CB6_CA16,   CB5_CA16},
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
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17 },
        { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 },
        { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55 },
        { 56, 57, 58, __, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, __ },
        { 73, 74, 75, 76, 77, __, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, __ },
        { __, 90, 91, __, 92, 93, 94, __, __, __, 95, __, __, 96, 97, 98, 99,100, 101},
    },
    {
        //  LED Index to Physical Position
                {10, 0}, {20, 0}, {30, 0},  {47, 0}, {62, 0}, {73, 0}, {84, 0}, {95, 0}, {110,0}, {120, 0}, {131, 0}, {142, 0}, {155, 0}, {166, 0}, {177,0},  {190, 0},  {205,0},  {224,0},
        {0,15}, {10,15}, {20,15}, {30,15},  {47,15}, {58,15}, {69,15}, {80,15}, {91,15}, {102,15},{113,15}, {124,15}, {135,15}, {146,15}, {157,15}, {168,15}, {179,15},  {200,15}, {224,15},
        {0,26}, {10,26}, {20,26}, {30,32},  {49,26}, {64,26}, {75,26}, {86,26}, {97,26}, {108,26},{119,26}, {130,26}, {141,26}, {152,26}, {163,26}, {174,26}, {185,26},  {205,26}, {224,26},
        {0,38}, {10,38}, {20,38},           {52,38}, {68,38}, {79,38}, {90,38}, {101,38},{112,38},{123,38}, {134,38}, {145,38}, {156,38}, {167,38}, {178,38}, {197,38},            {224,38},
        {0,49}, {10,49}, {20,49}, {30,55},  {55,49},          {73,49}, {84,49}, {95,49}, {106,49},{117,49}, {128,49}, {139,49}, {151,49}, {162,49}, {173,49}, {190,49},  {210,51},
                {5,61},  {20,61},           {48,61}, {62,61}, {79,61},                            {117,61},                     {159,61}, {170,64}, {182,61}, {198,63},  {210,63}, {224,63}
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
           1, 1,    1, 1, 1,          1,       1, 1, 1, 1, 1, 1,
    }
};
#endif
