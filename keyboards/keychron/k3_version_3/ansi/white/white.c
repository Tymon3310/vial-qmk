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
    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA4},
    {0, CB1_CA5},
    {0, CB1_CA6},
    {0, CB1_CA7},
    {0, CB1_CA8},
    {0, CB1_CA9},
    {0, CB1_CA10},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},

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
    {0, CB2_CA16},

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
    {0, CB3_CA13},
    {0, CB3_CA14},
    {0, CB3_CA16},

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
    {0, CB4_CA14},
    {0, CB4_CA16},

    {0, CB5_CA1},
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
    {0, CB5_CA14},
    {0, CB5_CA15},
    {0, CB5_CA16},

    {0, CB6_CA1},
    {0, CB6_CA2},
    {0, CB6_CA3},
    {0, CB6_CA7},
    {0, CB6_CA11},
    {0, CB6_CA12},
    {0, CB6_CA13},
    {0, CB6_CA14},
    {0, CB6_CA15},
    {0, CB6_CA16}
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, __, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, __, 45 },
        { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, __, 58, __, 59 },
        { 60, __, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, __, 71, 72, 73 },
        { 74, 75, 76, __, __, __, 77, __, __, __, 78, 79, 80, 81, 82, 83 }
    },
    {
        // LED Index to Physical Position
        {3, 0}, {14, 0}, {33, 0}, {48, 0}, {63, 0}, {78, 0}, { 93,  0}, {108,  0}, {123,  0}, {138,  0}, {153,  0}, {168,  0}, {183,  0}, {198,  0}, {213,0},  {223,  0},
        {3,12}, {14,12}, {33,12}, {48,12}, {63,12}, {78,12}, { 93, 12}, {108, 12}, {123, 12}, {138, 12}, {153, 12}, {168, 12}, {183, 12}, {205, 12},           {223, 12},
        {7,25}, {22,25}, {37,25}, {52,25}, {67,25}, {82,25}, { 97, 25}, {112, 25}, {126, 25}, {141, 25}, {156, 25}, {171, 25}, {186, 25}, {205, 25},           {223, 25},
        {8,38}, {26,38}, {41,38}, {55,38}, {70,38}, {85,38}, {100, 38}, {115, 38}, {130, 38}, {145, 38}, {160, 38}, {183, 38},            {205, 38},           {223, 38},
        {9,51},          {33,51}, {48,51}, {63,51}, {78,51}, { 93, 51}, {108, 51}, {123, 51}, {138, 51}, {153, 51}, {168, 51},            {190, 51}, {213, 51},{223, 51},
        {1,64}, {20,64}, {39,64},                            { 95, 64},                                  {149, 64}, {164, 64}, {183, 64}, {198, 64}, {213, 64},{223, 64}
    },
    {
        // LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1,          1,          1, 1, 1, 1, 1, 1,
    }
};
#endif
