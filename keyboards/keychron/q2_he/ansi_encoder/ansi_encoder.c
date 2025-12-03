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
  0b011111111111111,
  0b111111111111111,
  0b110111111111111,
  0b011111111111101,
  0b111111001000111,
};

#ifdef RGB_MATRIX_ENABLE
const sn3734_led_t g_sn3734_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SN3734 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS3_SW1,   CS1_SW1,   CS2_SW1},
    {0, CS3_SW2,   CS1_SW2,   CS2_SW2},
    {0, CS3_SW3,   CS1_SW3,   CS2_SW3},
    {0, CS3_SW4,   CS1_SW4,   CS2_SW4},
    {0, CS3_SW5,   CS1_SW5,   CS2_SW5},
    {0, CS3_SW6,   CS1_SW6,   CS2_SW6},
    {0, CS3_SW7,   CS1_SW7,   CS2_SW7},
    {0, CS3_SW8,   CS1_SW8,   CS2_SW8},
    {0, CS3_SW9,   CS1_SW9,   CS2_SW9},
    {0, CS3_SW10,  CS1_SW10,  CS2_SW10},
    {0, CS3_SW11,  CS1_SW11,  CS2_SW11},
    {0, CS3_SW12,  CS1_SW12,  CS2_SW12},
    {0, CS18_SW1,  CS16_SW1,  CS17_SW1},
    {0, CS18_SW2,  CS16_SW2,  CS17_SW2},

    {0, CS6_SW1,   CS4_SW1,   CS5_SW1},
    {0, CS6_SW2,   CS4_SW2,   CS5_SW2},
    {0, CS6_SW3,   CS4_SW3,   CS5_SW3},
    {0, CS6_SW4,   CS4_SW4,   CS5_SW4},
    {0, CS6_SW5,   CS4_SW5,   CS5_SW5},
    {0, CS6_SW6,   CS4_SW6,   CS5_SW6},
    {0, CS6_SW7,   CS4_SW7,   CS5_SW7},
    {0, CS6_SW8,   CS4_SW8,   CS5_SW8},
    {0, CS6_SW9,   CS4_SW9,   CS5_SW9},
    {0, CS6_SW10,  CS4_SW10,  CS5_SW10},
    {0, CS6_SW11,  CS4_SW11,  CS5_SW11},
    {0, CS6_SW12,  CS4_SW12,  CS5_SW12},
    {0, CS18_SW3,  CS16_SW3,  CS17_SW3},
    {0, CS18_SW4,  CS16_SW4,  CS17_SW4},
    {0, CS18_SW5,  CS16_SW5,  CS17_SW5},

    {0, CS9_SW1,   CS7_SW1,   CS8_SW1},
    {0, CS9_SW2,   CS7_SW2,   CS8_SW2},
    {0, CS9_SW3,   CS7_SW3,   CS8_SW3},
    {0, CS9_SW4,   CS7_SW4,   CS8_SW4},
    {0, CS9_SW5,   CS7_SW5,   CS8_SW5},
    {0, CS9_SW6,   CS7_SW6,   CS8_SW6},
    {0, CS9_SW7,   CS7_SW7,   CS8_SW7},
    {0, CS9_SW8,   CS7_SW8,   CS8_SW8},
    {0, CS9_SW9,   CS7_SW9,   CS8_SW9},
    {0, CS9_SW10,  CS7_SW10,  CS8_SW10},
    {0, CS9_SW11,  CS7_SW11,  CS8_SW11},
    {0, CS9_SW12,  CS7_SW12,  CS8_SW12},
    {0, CS18_SW6,  CS16_SW6,  CS17_SW6},
    {0, CS18_SW7,  CS16_SW7,  CS17_SW7},

    {0, CS15_SW1,  CS13_SW1,  CS14_SW1},
    {0, CS15_SW3,  CS13_SW3,  CS14_SW3},
    {0, CS15_SW4,  CS13_SW4,  CS14_SW4},
    {0, CS15_SW5,  CS13_SW5,  CS14_SW5},
    {0, CS15_SW6,  CS13_SW6,  CS14_SW6},
    {0, CS15_SW7,  CS13_SW7,  CS14_SW7},
    {0, CS15_SW8,  CS13_SW8,  CS14_SW8},
    {0, CS15_SW9,  CS13_SW9,  CS14_SW9},
    {0, CS15_SW10, CS13_SW10, CS14_SW10},
    {0, CS15_SW11, CS13_SW11, CS14_SW11},
    {0, CS15_SW12, CS13_SW12, CS14_SW12},
    {0, CS18_SW8,  CS16_SW8,  CS17_SW8},
    {0, CS18_SW9,  CS16_SW9,  CS17_SW9},

    {0, CS12_SW1,  CS10_SW1,  CS11_SW1},
    {0, CS12_SW2,  CS10_SW2,  CS11_SW2},
    {0, CS12_SW3,  CS10_SW3,  CS11_SW3},
    {0, CS12_SW7,  CS10_SW7,  CS11_SW7},
    {0, CS12_SW10, CS10_SW10, CS11_SW10},
    {0, CS12_SW11, CS10_SW11, CS11_SW11},
    {0, CS12_SW12, CS10_SW12, CS11_SW12},
    {0, CS12_SW6,  CS10_SW6,  CS11_SW6},
    {0, CS12_SW8,  CS10_SW8,  CS11_SW8},
    {0, CS12_SW9,  CS10_SW9,  CS11_SW9},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, __ },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 },
        { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, __, 41, 42 },
        { 43, __, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, __ },
        { 56, 57, 58, __, __, __, 59, __, __, 60, 61, 62, 63, 64, 65 },
    },
    {
        // LED Index to Physical Position
        {0, 0}, {15, 0}, {29, 0}, {44, 0}, {59, 0}, {73, 0}, {88, 0}, {103, 0}, {117, 0}, {132, 0}, {146, 0}, {161, 0}, {180, 0}, {194, 0},
        {4,15}, {22,15}, {37,15}, {51,15}, {66,15}, {81,15}, {95,15}, {110,15}, {125,15}, {139,15}, {154,15}, {168,15}, {183,15}, {194,15}, {224,15},
        {6,30}, {23,30}, {40,30}, {55,30}, {70,30}, {84,30}, {99,30}, {114,30}, {128,30}, {143,30}, {158,30}, {172,30},           {196,30}, {224,30},
        {9,45},          {33,45}, {48,45}, {62,45}, {77,45}, {92,45}, {106,45}, {121,45}, {136,45}, {150,45}, {165,45}, {188,45}, {202,49},
        {2,60}, {19,60}, {37,60},                            {94,60},                     {147,60}, {161,60}, {180,60}, {192,64}, {202,64}, {224,64}
    },
    {
        // RGB LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,          1,       1, 1, 1, 1, 1, 1
    }
};

// Default Color of Per Key RGB
#define DC_RED {HSV_RED}
#define DC_BLU {HSV_BLUE}
#define DC_YLW {HSV_YELLOW}

HSV default_per_key_led[RGB_MATRIX_LED_COUNT] = {
    DC_RED, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW,
    DC_YLW, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU,         DC_RED, DC_YLW,
    DC_YLW,         DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_BLU, DC_YLW, DC_YLW,
    DC_YLW, DC_YLW, DC_YLW,                         DC_BLU,                 DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW, DC_YLW
};

// Default mixed RGB region
uint8_t default_region[RGB_MATRIX_LED_COUNT] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,    0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,          0,       0, 0, 0, 0, 0, 0
};
#endif
