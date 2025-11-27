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
const matrix_row_t analog_matrix_mask[] = {
    0b0111111111111111101,
    0b1111111111111111111,
    0b1111111111111111111,
    0b0111011111111111111,
    0b1111111011111111101,
    0b0110111111001000111,
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
    {0, CB10_CA3,   CB12_CA3,   CB11_CA3},
    {0, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {0, CB10_CA1,   CB12_CA1,   CB11_CA1},

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
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {0, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {0, CB10_CA4,   CB12_CA4,   CB11_CA4},

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
    {0, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},

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
    {1, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {1, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {1, CB10_CA7,   CB12_CA7,   CB11_CA7},

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
    {1, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {1, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {1, CB10_CA4,   CB12_CA4,   CB11_CA4},
    {1, CB10_CA3,   CB12_CA3,   CB11_CA3},

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
    {1, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {1, CB10_CA1,   CB12_CA1,   CB11_CA1},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {   0,  __,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  __ },
        {  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35 },
        {  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54 },
        {  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  __,  69,  70,  71,  __ },
        {  72,  __,  73,  74,  75,  76,  77,  78,  79,  80,  81,  __,  82,  83,  84,  85,  86,  87,  88 },
        {  89,  90,  91,  __,  __,  __,  92,  __,  __,  93,  94,  95,  96,  97,  98,  __,  99, 100,  __ },
    },
    {
        // LED Index to Physical Position
        {0, 0},          {23, 0}, {34, 0}, {46, 0}, {57, 0}, {75, 0}, {86, 0}, { 98, 0}, {109, 0}, {127, 0}, {138, 0}, {150, 0}, {161, 0}, {175, 0}, {189, 0}, {201, 0}, {212, 0},
        {0,15}, {12,15}, {23,15}, {35,15}, {46,15}, {58,15}, {69,15}, {81,15}, { 92,15}, {104,15}, {115,15}, {127,15}, {138,15}, {158,15}, {175,15}, {189,15}, {201,15}, {212,15}, {224,15},
        {3,26}, {17,26}, {29,26}, {40,26}, {52,26}, {63,26}, {75,26}, {86,26}, { 98,26}, {109,26}, {121,26}, {132,26}, {144,26}, {158,26}, {175,26}, {189,26}, {201,26}, {212,26}, {224,32},
        {4,38}, {20,38}, {32,38}, {43,38}, {55,38}, {66,38}, {78,38}, {89,38}, {101,38}, {112,38}, {124,38}, {135,38},           {158,38}, {175,38}, {189,38}, {201,38}, {212,38},
        {7,26},          {26,50}, {37,50}, {49,50}, {60,50}, {72,50}, {83,50}, { 95,50}, {106,50}, {118,50}, {129,50}, {145,50}, {164,52},           {189,50}, {201,50}, {212,50}, {224,55},
        {1,61}, {16,61}, {30,61},                            {73,61},                    {115,61}, {126,61}, {138,61}, {152,64}, {164,64}, {175,64},           {195,61}, {212,61}
    },
    {
        // RGB LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,          1,       1, 1, 1, 1, 1, 1,    1, 1
    }
};

// Default Color of Per Key RGB
#define DC_RED {HSV_RED}
#define DC_BLU {HSV_BLUE}
#define DC_YLW {HSV_YELLOW}

HSV default_per_key_led[RGB_MATRIX_LED_COUNT] = {
    DC_RED, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,         DC_YLW, DC_YLW, DC_YLW,
    DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_RED, DC_YLW,         DC_YLW, DC_YLW, DC_YLW,
    DC_YLW,         DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,         DC_YLW, DC_YLW, DC_YLW, DC_RED,
    DC_YLW, DC_YLW, DC_YLW,                         DC_BLU,                 DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,         DC_YLW, DC_YLW
};

// Default mixed RGB region
uint8_t default_region[RGB_MATRIX_LED_COUNT] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0,
    0, 0, 0,          0,       0, 0, 0, 0, 0, 0,    0, 0
};
#endif
