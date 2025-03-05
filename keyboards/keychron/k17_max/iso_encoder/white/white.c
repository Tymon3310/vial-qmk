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
    {0, CB6_CA1},
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
    {0, CB6_CA15},
    {0, CB6_CA16},
    {0, CB1_CA8},
    {0, CB1_CA9},
    {0, CB1_CA10},

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
    {0, CB5_CA15},
    {0, CB5_CA16},
    {0, CB8_CA7},
    {0, CB8_CA8},
    {0, CB8_CA9},

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
    {0, CB4_CA15},
    {0, CB4_CA16},
    {0, CB8_CA12},
    {0, CB8_CA13},
    {0, CB8_CA14},

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
    {0, CB7_CA7},
    {0, CB7_CA8},
    {0, CB7_CA9},

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
    {0, CB2_CA15},
    {0, CB6_CA14},
    {0, CB7_CA10},
    {0, CB7_CA11},
    {0, CB7_CA12},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB8_CA10},
    {0, CB1_CA7},
    {0, CB8_CA15},
    {0, CB7_CA13},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA15},
    {0, CB1_CA16},
    {0, CB7_CA14},
    {0, CB1_CA14},
    {0, CB7_CA16},

};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17 },
        { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
        { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 },
        { 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, __, 66, 67, 68, 69, 70 },
        { 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88 },
        { 89, 90, 91, __, __, 92, 93, 94, 95, __, 96, 97, 98, 99,100,101,102,103 },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {12, 0}, {24, 0}, {36, 0}, {48, 0}, {60, 0}, {72, 0}, {84, 0}, {96, 0}, {108, 0}, {120, 0}, {132, 0}, {144, 0},   {168, 0}, {180, 0}, {192, 0},{203, 0},{213,0},
        {0,13}, {12,13}, {24,13}, {36,13}, {48,13}, {60,13}, {72,13}, {84,13}, {96,13}, {108,13}, {120,13}, {132,13}, {144,13},   {162,13}, {180,13}, {192,13},{203,13},{213,13},
        {2,26}, {18,26}, {30,26}, {42,26}, {54,26}, {66,26}, {78,26}, {90,26}, {102,26},{114,26}, {126,26}, {138,26}, {150,26},   {164,32}, {180,26}, {192,26},{203,26},{213,26},
        {4,39}, {22,39}, {34,39}, {46,39}, {58,39}, {70,39}, {82,39}, {94,39}, {106,39},{118,39}, {130,39}, {142,39},             {154,39}, {180,39}, {192,39},{203,39},{213,39},
        {1,51}, {14,51}, {28,51}, {40,51}, {52,51}, {64,51}, {76,51}, {88,51}, {100,51},{112,51}, {124,51}, {136,51}, {148,51},   {168,51}, {156, 0}, {192,51},{203,51},{213,51},
        {1,64}, {16,64}, {30,64},                   {224,13},{78,64}, {224,32},{224,57},          {120,64}, {132,64}, {144,64},   {168,64}, {180,64}, {197,64},{156,64},{213,64},
    },
    {
        // LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,       1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1, 1,
    }
};
#endif
