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
    {0, CB6_CA14},
    {0, CB6_CA15},
    {0, CB6_CA16},

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

    {0, CB3_CA1},
    {0, CB3_CA2},
    {0, CB3_CA3},
    {0, CB3_CA4},
    {0, CB3_CA5},
    {0, CB3_CA6},
    {0, CB3_CA7},
    {0, CB3_CA9},
    {0, CB3_CA10},
    {0, CB3_CA11},
    {0, CB3_CA12},
    {0, CB3_CA13},
    {0, CB3_CA14},
    {0, CB3_CA15},
    {0, CB3_CA16},

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
    {0, CB2_CA13},
    {0, CB2_CA14},
    {0, CB2_CA15},
    {0, CB2_CA16},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA4},
    {0, CB1_CA5},
    {0, CB1_CA7},
    {0, CB1_CA10},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46 },
        { 47, 48, 49, 50, 51, 52, __, 53, 54, 55, 56, 57, 58, 59, 60, 61 },
        { 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77 },
        { 78, 79, 80, 81, __, 82, __, 83, __, 84, 85, 86, __, 87, 88, 89 },
    },
    {
        // LED Index to Physical Position
                {19, 0}, {34, 0}, {46, 0}, {59, 1}, {71, 3}, {86, 6}, { 98, 8}, {121, 8}, {133, 6}, {147, 3}, {159, 1}, {173, 0}, {185, 0}, {203, 0}, {220, 0},
        {5,14}, {24,14}, {36,14}, {48,13}, {61,15}, {73,17}, {85,20}, { 97,22}, {116,22}, {128,20}, {140,17}, {152,15}, {165,13}, {177,14}, {195,14}, {220,14},
        {4,24}, {24,24}, {40,24}, {53,24}, {65,27}, {77,29}, {89,31}, {113,33}, {125,31}, {137,29}, {149,26}, {161,24}, {174,24}, {186,24}, {201,29}, {222,24},
        {2,34}, {23,34}, {40,34}, {53,35}, {65,37}, {77,39}, {89,42},           {118,42}, {130,40}, {142,38}, {154,36}, {167,34}, {179,34}, {192,34}, {224,35},
        {0,45}, {18,45}, {33,45}, {44,45}, {57,46}, {69,48}, {81,51}, { 93,53}, {112,54}, {124,52}, {136,50}, {148,48}, {160,46}, {173,45}, {190,45}, {210,47},
        {0,55}, {18,55}, {33,55}, {56,57},          {77,61},          { 96,64},           {125,63}, {147,58}, {159,56},           {198,58}, {210,58}, {222,58}
    },
    {
        // LED LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,    1,    1,    1, 1, 1,    1, 1, 1
    }
};
#endif
