/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
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
    {0, CB1_CA16},
    {0, CB1_CA15},
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
    {0, CB2_CA3},
    {0, CB2_CA2},
    {0, CB2_CA1},
    {0, CB7_CA4},
    {0, CB7_CA5},

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
    {0, CB4_CA3},
    {0, CB4_CA2},
    {0, CB4_CA1},
    {0, CB7_CA8},
    {0, CB7_CA3},

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
    {0, CB5_CA2},
    {0, CB5_CA1},
    {0, CB7_CA9},
    {0, CB7_CA10},

    {0, CB6_CA16},
    {0, CB6_CA15},
    {0, CB6_CA14},
    {0, CB6_CA13},
    {0, CB6_CA10},
    {0, CB6_CA8},
    {0, CB6_CA7},
    {0, CB6_CA6},
    {0, CB6_CA5},
    {0, CB6_CA4},
    {0, CB6_CA3},
    {0, CB6_CA2},
    {0, CB6_CA1},
    {0, CB7_CA11},
    {0, CB7_CA12},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17  },
        {  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35  },
        {  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53  },
        {  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71  },
        {  72,  __,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88  },
        {  89,  90,  91,  92,  __,  __,  93,  __,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103  },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {13, 0}, {25, 0}, {37, 0}, {50, 0}, {62, 0}, {75, 0}, {87, 0}, {100, 0}, {112, 0}, {125, 0}, {137, 0}, {150, 0}, {162, 0}, {175, 0}, {187, 0}, {200, 0}, {212, 0},
        {0,13}, {13,13}, {25,13}, {37,13}, {50,13}, {62,13}, {75,13}, {87,13}, {100,13}, {112,13}, {125,13}, {137,13}, {150,13}, {175,13}, {187,13}, {200,13}, {212,13}, {224,13},
        {3,26}, {19,26}, {31,26}, {44,26}, {56,26}, {69,26}, {81,26}, {94,26}, {106,26}, {119,26}, {131,26}, {144,26}, {156,26}, {172,33}, {187,26}, {200,26}, {212,26}, {224,32},
        {5,39}, {23,39}, {35,39}, {47,39}, {59,39}, {72,39}, {84,39}, {97,39}, {110,39}, {122,39}, {135,39}, {147,39}, {162,51}, {158,39}, {187,39}, {200,39}, {212,39}, {224, 0},
        {4,51},          {28,51}, {40,51}, {53,51}, {65,51}, {78,51}, {90,51}, {102,51}, {115,51}, {127,51}, {140,51}, {151,51}, {173,51}, {187,51}, {200,51}, {212,51}, {224,57},
        {2,64}, {17,64}, {30,64}, {42,64},                   {80,64},          {162,13}, {114,64}, {125,64}, {137,64}, {150,64}, {165,64}, {175,64}, {187,64}, {200,64}, {212,64},
    },
    {
        // LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1,       1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    }
};
#endif
