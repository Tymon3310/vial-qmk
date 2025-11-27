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
  0b1111111111111111110,
  0b1111111111111111111,
  0b1111111111111111111,
  0b0111111111111110111,
  0b1110111111111111111,
  0b1111110010001110110,
};

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB10_CA15,  CB12_CA15,  CB11_CA15},
    {0, CB10_CA16,  CB12_CA16,  CB11_CA16},
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

    {0, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {0, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {0, CB10_CA14,  CB12_CA14,  CB11_CA14},
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

    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {0, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {0, CB4_CA16,   CB6_CA16,   CB5_CA16},
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
    {1, CB7_CA14,   CB9_CA14,   CB8_CA14},
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
        {  __,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17 },
        {  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36 },
        {  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55 },
        {  56,  57,  58,  __,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  __ },
        {  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  __,  88,  89,  90 },
        {  __,  91,  92,  __,  93,  94,  95,  __,  __,  __,  96,  __,  __,  97,  98,  99, 100, 101, 102 },
    },
    {
        // LED Index to Physical Position
                {12, 0}, {23, 0}, {35, 0},  {49, 0}, {64, 0}, {75, 0}, {86, 0}, { 98, 0}, {112, 0}, {124, 0}, {135, 0}, {147, 0}, {161, 0}, {173, 0}, {184, 0}, {197, 0}, {208, 0}, {224, 0},
        {0,15}, {12,15}, {23,15}, {35,15},  {49,15}, {61,15}, {72,15}, {84,15}, { 95,15}, {107,15}, {128,15}, {130,15}, {141,15}, {153,15}, {164,15}, {176,15}, {187,15}, {204,15}, {224,15},
        {0,26}, {12,26}, {23,26}, {35,30},  {54,26}, {66,26}, {77,26}, {89,26}, {100,26}, {112,26}, {123,26}, {135,26}, {146,26}, {158,26}, {169,26}, {181,26}, {192,26}, {208,32}, {224,26},
        {0,38}, {12,38}, {23,38},           {55,38}, {69,38}, {81,38}, {92,38}, {104,38}, {115,38}, {127,38}, {138,38}, {150,38}, {161,38}, {173,38}, {184,38}, {195,38},           {224,38},
        {0,50}, {12,50}, {23,50}, {35,55},  {57,50}, {64,50}, {75,50}, {86,50}, { 98,50}, {109,50}, {121,50}, {132,50}, {144,50}, {155,50}, {167,52}, {178,50}, {196,50}, {212,50},
        {6,61},          {23,61},           {50,61}, {65,61}, {81,61},                              {122,61},                     {162,61}, {174,61}, {188,61}, {200,64}, {212,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
           1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1,    1,     1, 1, 1,          1,       1, 1, 1, 1, 1, 1
    }
};

// Default Color of Per Key RGB
#define DC_RED {HSV_RED}
#define DC_BLU {HSV_BLUE}
#define DC_YLW {HSV_YELLOW}

HSV default_per_key_led[RGB_MATRIX_LED_COUNT] = {
            DC_YLW, DC_YLW, DC_YLW,  DC_RED, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW,
    DC_YLW, DC_YLW, DC_YLW, DC_YLW,  DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,
    DC_YLW, DC_YLW, DC_YLW, DC_YLW,  DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_RED, DC_YLW,
    DC_YLW, DC_YLW, DC_YLW,          DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU,         DC_YLW,
    DC_YLW, DC_YLW, DC_YLW, DC_RED,  DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,
    DC_YLW,         DC_YLW,          DC_YLW, DC_YLW, DC_YLW,                         DC_BLU,                 DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW
};

// Default mixed RGB region
uint8_t default_region[RGB_MATRIX_LED_COUNT] = {
       0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,     0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,
    0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0,     0, 0, 0,          0,       0, 0, 0, 0, 0, 0
};
#endif
