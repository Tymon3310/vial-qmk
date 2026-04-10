/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
    {0, CB7_CA1},
    {0, CB7_CA2},
    {0, CB7_CA3},
    {0, CB7_CA4},
    {0, CB7_CA5},

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
    {0, CB5_CA2},
    {0, CB2_CA3},
    {0, CB2_CA2},
    {0, CB2_CA1},
    {0, CB8_CA1},
    {0, CB8_CA2},
    {0, CB8_CA3},
    {0, CB8_CA4},
    {0, CB8_CA5},

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
    {0, CB7_CA6},
    {0, CB7_CA7},
    {0, CB7_CA8},
    {0, CB7_CA9},
    {0, CB7_CA10},

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
    {0, CB4_CA4},
    {0, CB8_CA7},
    {0, CB8_CA8},
    {0, CB8_CA9},

    {0, CB5_CA16},
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
    {0, CB5_CA4},
    {0, CB5_CA3},
    {0, CB5_CA1},
    {0, CB8_CA6},
    {0, CB8_CA11},
    {0, CB8_CA12},
    {0, CB8_CA10},

    {0, CB6_CA16},
    {0, CB6_CA15},
    {0, CB6_CA14},
    {0, CB6_CA13},
    {0, CB6_CA10},
    {0, CB6_CA7},
    {0, CB6_CA6},
    {0, CB6_CA5},
    {0, CB6_CA4},
    {0, CB6_CA3},
    {0, CB6_CA2},
    {0, CB6_CA1},
    {0, CB7_CA13},
    {0, CB7_CA11},
    {0, CB7_CA12}
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {   0,  __,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18 },
        {  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  34,  35,  36,  37,  38,  39,  40 },
        {  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61 },
        {  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  19,  41,  62,  96,  76,  77,  78 },
        {  79,  __,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  __,  92,  33,  93,  94,  95 },
        {  97,  98,  99, 100,  __,  __, 101,  __,  __, 102, 103, 104, 105, 106, 107, 108, 109,  __, 110, 111 },
    },
    {
        // LED Index to Physical Position
        {0, 0},            {21,  0}, {31,  0}, {42,  0}, {52,  0}, {68,  0}, {78,  0}, {89,  0}, {99,   0}, {115,  0}, {125,  0}, {136,  0}, {146,  0},             {159,  0}, {169,  0}, {180,  0},  {193,  0}, {203,  0}, {214,  0}, {224,  0},
        {3, 15}, {10, 15}, {21, 15}, {31, 15}, {42, 15}, {52, 15}, {63, 15}, {73, 15}, {83, 15}, {94,  15}, {104, 15}, {115, 15}, {125, 15}, {136, 15}, {141, 15},  {159, 15}, {169, 15}, {180, 15},  {193, 15}, {203, 15}, {213, 15}, {224, 15},
        {3, 26}, {16, 26}, {26, 26}, {36, 26}, {47, 26}, {57, 26}, {68, 26}, {78, 26}, {89, 26}, {99,  26}, {109, 26}, {120, 26}, {130, 26}, {143, 33},             {159, 26}, {169, 26}, {180, 26},  {193, 26}, {203, 26}, {214, 26}, {224, 26},
        {4, 40}, {18, 40}, {29, 40}, {39, 40}, {50, 40}, {60, 40}, {70, 40}, {81, 40}, {91, 40}, {102, 40}, {112, 40}, {123, 40}, {134, 40},                                                          {193, 40}, {203, 40}, {214, 33},
        {7, 52},           {23, 52}, {34, 52}, {44, 52}, {55, 52}, {65, 52}, {76, 52}, {86, 52}, {96,  52}, {107, 52}, {117, 52}, {130, 52}, {141, 52},                        {169, 52},             {193, 52}, {203, 52}, {214, 52}, {224, 58},
        {1, 64}, {14, 64}, {23, 64}, {44, 64},                     {66, 64},                                {96,  64}, {105, 64}, {118, 64}, {131, 64}, {145, 64},  {159, 64}, {169, 64}, {180, 64},  {198, 64},            {214, 64}
    },
    {
        // LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,     1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,     1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                  1, 1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,        1,     1, 1, 1, 1,
        1, 1, 1, 1,       1,          1, 1, 1, 1, 1,  1, 1, 1,  1,   1
    }
};
#endif
