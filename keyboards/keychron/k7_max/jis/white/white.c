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
    {0, CB4_CA16},

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

    {0, CB2_CA1},
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
    {0, CB2_CA14},
    {0, CB2_CA15},
    {0, CB2_CA16},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA4},
    {0, CB1_CA7},
    {0, CB1_CA10},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, __, 30 },
        { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, __, 43, __, 44 },
        { 45, __, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, __, 56, 57, 58 },
        { 59, 60, 61, 62, __, __, 63, __, __, 64, 65, 66, 67, 68, 69, 70 },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {15, 0}, {30, 0}, {45, 0}, {60, 0}, {75, 0}, { 90, 0}, {105, 0}, {119, 0}, {134, 0}, {149, 0}, {164, 0}, {179, 0}, {194, 0}, {209, 0}, {224, 0},
        {4,16}, {22,16}, {37,16}, {52,16}, {67,16}, {82,16}, { 97,16}, {112,16}, {127,16}, {142,16}, {157,16}, {172,16}, {187,16}, {205,24},           {224,16},
        {7,32}, {26,32}, {41,32}, {56,32}, {71,32}, {86,32}, {101,32}, {116,32}, {131,32}, {146,32}, {161,32}, {175,32},           {200,32},           {224,32},
        {8,48},          {34,48}, {49,48}, {64,48}, {78,48}, { 93,48}, {108,48}, {123,48}, {138,48}, {153,48}, {168,48}, {183,48},           {201,48}, {224,48},
        {0,64}, {15,64}, {30,64}, {45,64},                   { 90,64},                     {134,64}, {149,64}, {164,64}, {179,64}, {194,64}, {209,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1, 1,       1,       1, 1, 1, 1, 1, 1, 1
    }

};
#endif
