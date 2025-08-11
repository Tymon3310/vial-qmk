/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "encoder_config.h"

// Explicitly define encoder pins in the keymap directory too
// These are already defined in the main config.h, but defining them here ensures they're picked up
// With the updated Vial, we need to undefine these before they get redefined in quantum/encoder.h
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS
// #define ENCODERS_PAD_A { B15 }
// #define ENCODERS_PAD_B { B14 }
// #define ENCODER_RESOLUTION 4

#define VIAL_KEYBOARD_UID {0xB1, 0x17, 0xD8, 0x63, 0x21, 0x08, 0xA4, 0x1D}

// The four corners (ESC, CTRL, NUM DOT, END)
// #define VIAL_UNLOCK_COMBO_ROWS { 0, 0, 5, 5 }
// #define VIAL_UNLOCK_COMBO_COLS { 0, 17, 0, 17 }

// The four corners (ESC, CTRL, NUM ENTER, DIAL)
#define VIAL_UNLOCK_COMBO_ROWS {0, 5, 4, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 0, 18, 18}

// Esc + Enter
// #define VIAL_UNLOCK_COMBO_ROWS {0, 3}
// #define VIAL_UNLOCK_COMBO_COLS {0, 12}

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// LED index for Caps Lock key (used by keyboard-level indicators)
// From ansi_encoder.c led_config_t mapping: row 3, col 0 -> index 51
#define CAPS_LOCK_INDEX 51

// Enable QMK settings tab and features
#define QMK_SETTINGS_ENABLE
// VIAL_INSECURE is already defined in rules.mk
#define DYNAMIC_KEYMAP_MACRO_ENABLE

// QMK Settings specific features
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 10

// Mouse Keys configuration
#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_WHEEL_DELAY 10

// Enable additional keycodes
// #define DEFERRED_EXEC_ENABLE // Commented out due to linking error
#define PDF_ENABLE
// Configure Layer Lock
#define LAYER_LOCK_IDLE_TIMEOUT 300000 // 5 minutes

// SOCD Cleaner Configuration
// Using default behavior - no need for additional configuration

// Combo Configuration
// Use VIAL_COMBO_ENTRIES instead of COMBO_COUNT for Vial
#define VIAL_COMBO_ENTRIES 8
#define COMBO_TERM 50

// Key Override is already enabled by VIAL_KEY_OVERRIDE_ENABLE
// #define KEY_OVERRIDE_LAYER_ENABLE

// Enable all QMK RGB matrix effects via a dedicated header
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_effects_conf.h"
#endif
