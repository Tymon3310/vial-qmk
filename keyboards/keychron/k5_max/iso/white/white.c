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
    {0, CB6_CA14},
    {0, CB8_CA7},
    {0, CB8_CA8},
    {0, CB8_CA9},
    {0, CB8_CA10},

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
    {0, CB7_CA7},
    {0, CB7_CA8},
    {0, CB7_CA9},
    {0, CB7_CA10},
    {0, CB7_CA11},

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
    {0, CB7_CA12},
    {0, CB7_CA13},
    {0, CB7_CA14},
    {0, CB7_CA15},
    {0, CB7_CA16},

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
    {0, CB3_CA13},
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
    {0, CB2_CA14},
    {0, CB2_CA16},
    {0, CB2_CA13},
    {0, CB8_CA11},
    {0, CB8_CA12},
    {0, CB8_CA13},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA7},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
    {0, CB8_CA14},
    {0, CB8_CA15},
    {0, CB8_CA16},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  __,  13,  14,  15,  16,  17,  18,  19 },
        {  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40 },
        {  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61 },
        {  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  __,  74,  __,  __,  __,  75,  76,  77,  __ },
        {  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  __,  90,  __,  91,  __,  92,  93,  94,  95 },
        {  96,  97,  98,  __,  __,  __,  99,  __,  __,  __,  100, 101, 102, 103, 104, 105, 106, 107, __, 108,  __ },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {21, 0}, {32, 0}, {42, 0}, {53, 0}, {69, 0}, {79, 0}, {90, 0}, {100, 0}, {116, 0}, {127, 0}, {137, 0}, {148, 0},           {160, 0}, {170, 0}, {181, 0}, {192, 0}, {203, 0}, {213, 0}, {224, 0},
        {0,14}, {11,14}, {21,14}, {32,14}, {42,14}, {53,14}, {63,14}, {74,14}, { 84,14}, { 95,14}, {106,14}, {116,14}, {127,14}, {143,14}, {160,14}, {170,14}, {181,14}, {192,14}, {203,14}, {213,14}, {224,14},
        {3,26}, {16,26}, {26,26}, {37,26}, {48,26}, {58,26}, {69,26}, {79,26}, { 90,26}, {100,26}, {111,26}, {121,26}, {132,26}, {145,32}, {160,26}, {170,26}, {181,26}, {192,26}, {203,26}, {213,26}, {224,33},
        {4,39}, {19,39}, {29,39}, {40,39}, {50,39}, {61,39}, {71,39}, {82,39}, { 92,39}, {103,39}, {114,39}, {124,39}, {134,39},                                         {192,39}, {203,39}, {213,39},
        {4,51}, {12,39}, {24,51}, {34,51}, {45,51}, {55,51}, {66,51}, {77,51}, { 87,51}, { 98,51}, {108,51}, {119,51},          {139,51},           {170,51},           {192,51}, {203,51}, {213,51}, {224,58},
        {1,64}, {15,64}, {28,64},                            {67,64},                              {107,64}, {120,64}, {133,64}, {147,64}, {160,64}, {170,64}, {181,64}, {198,64},           {213,64},
    },
    {
        // LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,          1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,    1,    1, 1, 1, 1,
        1, 1, 1,          1,          1, 1, 1, 1, 1, 1, 1, 1,    1,
    }
};
#endif
