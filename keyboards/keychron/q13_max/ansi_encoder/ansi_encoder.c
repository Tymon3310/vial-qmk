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
    {0, CB1_CA2,    CB3_CA2,    CB2_CA2},
    {0, CB1_CA3,    CB3_CA3,    CB2_CA3},
    {0, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {0, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {0, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {0, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {0, CB1_CA8,    CB3_CA8,    CB2_CA8},
    {0, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {0, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {0, CB1_CA11,   CB3_CA11,   CB2_CA11},
    {0, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {0, CB1_CA13,   CB3_CA13,   CB2_CA13},
    {0, CB1_CA14,   CB3_CA14,   CB2_CA14},
    {0, CB1_CA16,   CB3_CA16,   CB2_CA16},
    {0, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {0, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {0, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {0, CB4_CA13,   CB6_CA13,   CB5_CA13},

    {0, CB10_CA1,   CB12_CA1,   CB11_CA1},
    {0, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {0, CB10_CA3,   CB12_CA3,   CB11_CA3},
    {0, CB10_CA4,   CB12_CA4,   CB11_CA4},
    {0, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {0, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {0, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {0, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {0, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {0, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {0, CB10_CA15,  CB12_CA15,  CB11_CA15},
    {0, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {0, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {0, CB4_CA9,    CB6_CA9,    CB5_CA9},

    {0, CB7_CA1,    CB9_CA1,    CB8_CA1},
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {0, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {0, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {0, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {0, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {0, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {0, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {0, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {0, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {0, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {0, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {0, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {0, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {0, CB4_CA5,    CB6_CA5,    CB5_CA5},

    {1, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {1, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {1, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {1, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {1, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {1, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {1, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {1, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {1, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {1, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {1, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {1, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {1, CB7_CA3,    CB9_CA3,    CB8_CA3},
    {1, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {1, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {1, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {1, CB10_CA12,  CB12_CA12,  CB11_CA12},

    {1, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {1, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {1, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {1, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {1, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {1, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {1, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {1, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {1, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {1, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {1, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {1, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {1, CB4_CA3,    CB6_CA3,    CB5_CA3},
    {1, CB4_CA2,    CB6_CA2,    CB5_CA2},
    {1, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {1, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {1, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {1, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {1, CB10_CA9,   CB12_CA9,   CB11_CA9},

    {1, CB1_CA16,   CB3_CA16,   CB2_CA16},
    {1, CB1_CA15,   CB3_CA15,   CB2_CA15},
    {1, CB1_CA14,   CB3_CA14,   CB2_CA14},
    {1, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {1, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {1, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {1, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {1, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {1, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {1, CB1_CA1,    CB3_CA1,    CB2_CA1},
    {1, CB10_CA1,   CB12_CA1,   CB11_CA1},
    {1, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {1, CB10_CA3,   CB12_CA3,   CB11_CA3},
    {1, CB10_CA4,   CB12_CA4,   CB11_CA4},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  __,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  __,  13,  __,  14,  15,  16,  17 },
        {  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  __,  __,  33,  34,  35,  36 },
        {  37,  38,  39,  40,  41,  42,  43,  __,  44,  45,  46,  47,  48,  49,  50,  51,  __,  52,  53,  54,  55 },
        {  56,  57,  58,  59,  60,  61,  62,  __,  63,  64,  65,  66,  67,  68,  69,  __,  __,  70,  71,  72,  __ },
        {  73,  74,  __,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  __,  87,  88,  89,  90,  91 },
        {  92,  93,  94,  __,  95,  __,  96,  97,  __,  98,  __,  99, 100,  __,  __, 101, 102, 103, 104, 105,  __ },
    },
    {
        // LED Index to Physical Position
                {16, 0}, {29, 0}, {39, 0}, {51, 1}, {61, 3}, {74, 6}, {84, 8}, {103, 8}, {113, 6}, {126, 3}, {136, 1}, {148, 0}, {158, 0},           {175, 0},           {193, 0}, {203, 0}, {214, 0}, {224, 0},
        {4,14}, {20,14}, {31,14}, {41,13}, {52,15}, {63,17}, {73,20}, {83,22}, { 99,22}, {109,20}, {119,17}, {130,15}, {141,13}, {151,14}, {167,14},                     {193,14}, {203,14}, {214,14}, {224,14},
        {3,24}, {21,24}, {34,24}, {45,24}, {55,27}, {66,29}, {76,31},          { 96,33}, {106,31}, {117,29}, {127,26}, {137,24}, {148,24}, {159,24}, {172,24},           {193,24}, {203,24}, {214,24}, {224,29},
        {1,34}, {20,34}, {34,34}, {45,35}, {56,37}, {66,39}, {76,42},          {101,42}, {111,40}, {121,38}, {132,36}, {143,34}, {153,34}, {170,34},                     {193,34}, {203,34}, {214,34},
        {0,45}, {20,45},          {37,45}, {48,46}, {59,48}, {69,51}, {79,53}, { 95,54}, {106,52}, {116,50}, {126,48}, {136,46}, {148,45}, {162,45},           {179,47}, {193,45}, {203,45}, {214,45}, {224,50},
        {0,55}, {15,55}, {28,55},          {48,57},          {66,61}, {82,64},           {107,63},           {126,58}, {136,56},                     {169,58}, {179,58}, {190,58}, {203,55}, {214,55}
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1,       1, 1, 1,
        1, 1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1,
        1, 1, 1,    1,    1, 1,    1,    1, 1,       1, 1, 1, 1, 1
    }
};
#endif
