/* Copyright 2021 ~ 2025 @ Keychron (https://www.keychron.com)
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
    {0, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {0, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {0, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {0, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {0, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {0, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {0, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {0, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {0, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {0, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {0, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {0, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {0, CB3_CA4,    CB1_CA4,    CB2_CA4},
    {0, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},

    {0, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {0, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {0, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {0, CB6_CA13,   CB4_CA13,   CB5_CA13},
    {0, CB6_CA12,   CB4_CA12,   CB5_CA12},
    {0, CB6_CA11,   CB4_CA11,   CB5_CA11},
    {0, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {0, CB6_CA9,    CB4_CA9,    CB5_CA9},
    {0, CB6_CA8,    CB4_CA8,    CB5_CA8},
    {0, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {0, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {0, CB6_CA5,    CB4_CA5,    CB5_CA5},
    {0, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {0, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {0, CB6_CA2,    CB4_CA2,    CB5_CA2},

    {1, CB3_CA16,   CB1_CA16,   CB2_CA16},
    {1, CB3_CA15,   CB1_CA15,   CB2_CA15},
    {1, CB3_CA14,   CB1_CA14,   CB2_CA14},
    {1, CB3_CA13,   CB1_CA13,   CB2_CA13},
    {1, CB3_CA12,   CB1_CA12,   CB2_CA12},
    {1, CB3_CA11,   CB1_CA11,   CB2_CA11},
    {1, CB3_CA10,   CB1_CA10,   CB2_CA10},
    {1, CB3_CA9,    CB1_CA9,    CB2_CA9},
    {1, CB3_CA8,    CB1_CA8,    CB2_CA8},
    {1, CB3_CA7,    CB1_CA7,    CB2_CA7},
    {1, CB3_CA6,    CB1_CA6,    CB2_CA6},
    {1, CB3_CA5,    CB1_CA5,    CB2_CA5},
    {1, CB3_CA3,    CB1_CA3,    CB2_CA3},
    {1, CB3_CA2,    CB1_CA2,    CB2_CA2},

    {1, CB9_CA16,   CB7_CA16,   CB8_CA16},
    {1, CB9_CA15,   CB7_CA15,   CB8_CA15},
    {1, CB9_CA14,   CB7_CA14,   CB8_CA14},
    {1, CB9_CA13,   CB7_CA13,   CB8_CA13},
    {1, CB9_CA12,   CB7_CA12,   CB8_CA12},
    {1, CB9_CA11,   CB7_CA11,   CB8_CA11},
    {1, CB9_CA10,   CB7_CA10,   CB8_CA10},
    {1, CB9_CA9,    CB7_CA9,    CB8_CA9},
    {1, CB9_CA8,    CB7_CA8,    CB8_CA8},
    {1, CB9_CA7,    CB7_CA7,    CB8_CA7},
    {1, CB9_CA6,    CB7_CA6,    CB8_CA6},
    {1, CB9_CA5,    CB7_CA5,    CB8_CA5},
    {1, CB9_CA4,    CB7_CA4,    CB8_CA4},
    {1, CB9_CA3,    CB7_CA3,    CB8_CA3},
    {1, CB9_CA2,    CB7_CA2,    CB8_CA2},

    {1, CB6_CA16,   CB4_CA16,   CB5_CA16},
    {1, CB6_CA15,   CB4_CA15,   CB5_CA15},
    {1, CB6_CA14,   CB4_CA14,   CB5_CA14},
    {1, CB6_CA10,   CB4_CA10,   CB5_CA10},
    {1, CB6_CA7,    CB4_CA7,    CB5_CA7},
    {1, CB6_CA6,    CB4_CA6,    CB5_CA6},
    {1, CB6_CA5,    CB4_CA5,    CB5_CA5},
    {1, CB6_CA4,    CB4_CA4,    CB5_CA4},
    {1, CB6_CA3,    CB4_CA3,    CB5_CA3},
    {1, CB6_CA2,    CB4_CA2,    CB5_CA2}
};

led_config_t g_led_config = {
    {
        {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     14 },
        {  15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29 },
        {  30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,     NO_LED, 42,     43 },
        {  44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57,     58 },
        {  59,     60,     61,     NO_LED, NO_LED, NO_LED, 62,     NO_LED, NO_LED, 63,     64,     65,     66,     67,     68 }
    },
    {
        {0, 0}, {14, 0}, {29, 0}, { 44, 0}, { 59, 0}, { 74, 0}, { 89, 0}, {104, 0}, {119, 0}, {134, 0}, {149, 0}, {164, 0}, {179, 0}, {201, 0}, {224, 0},
        {3,16}, {22,16}, {37,16}, { 52,16}, { 67,16}, { 82,16}, { 97,16}, {112,16}, {126,16}, {141,16}, {156,16}, {171,16}, {186,16}, {205,16}, {224,16},
        {5,32}, {26,32}, {41,32}, { 55,32}, { 70,32}, { 85,32}, {100,32}, {115,32}, {130,32}, {145,32}, {160,32}, {175,32}, {199,32},           {224,32},
        {2,48}, {15,48}, {33,48}, {48,48},  { 63,48}, { 78,48}, { 93,48}, {108,48}, {123,48}, {138,48}, {153,48}, {167,48}, {188,48}, {209,48}, {224,48},
        {1,64}, {20,64}, {39,64},                               { 95,64},                     {149,64}, {164,64}, {179,64}, {194,64}, {209,64}, {224,64}
    },
    {
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    8,    8,    8,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,          4,    4,
        4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
        4,    4,    4,                      4,                4,    4,    4,    4,    4,    4,
    }
};
#endif
