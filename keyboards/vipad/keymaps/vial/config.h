/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x5A, 0x42, 0xC3, 0x19, 0x8E, 0x4F, 0x22, 0xD7}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

#define I2C_DRIVER          I2CD1
#define I2C1_SDA_PIN        GP14
#define I2C1_SCL_PIN        GP15

// #define OLED_DISPLAY_128X64 // Default is 128x32 (SSD1306 0.91" 4-pin OLED)
#define OLED_TIMEOUT        60000