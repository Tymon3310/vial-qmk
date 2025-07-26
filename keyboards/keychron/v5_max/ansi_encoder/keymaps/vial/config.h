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

// Secure settings by default
// VIAL_INSECURE is already defined in rules.mk

// Reduce firmware size to fit all features
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Enable Snap Click Feature
#define SNAP_CLICK_ENABLE
#define SNAP_CLICK_DURATION_MS 300
#define SNAP_CLICK_DB_THRESHOLD 5
#define SNAP_CLICK_ACTIVATION_THRESHOLD 30
#define SNAP_CLICK_MOUSE_BUTTON_MASK (1 << MB_LEFT)
#define SNAP_CLICK_HAPTIC_FEEDBACK_ENABLE

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

// Tap Dance Configuration
#define TAPPING_TERM 200
// TAPPING_TERM_PER_KEY is already defined
#define TAP_CODE_DELAY 10

// Combo Configuration
// Use VIAL_COMBO_ENTRIES instead of COMBO_COUNT for Vial
#define VIAL_COMBO_ENTRIES 4
#define COMBO_TERM 50

// Key Override is already enabled by VIAL_KEY_OVERRIDE_ENABLE
// #define KEY_OVERRIDE_LAYER_ENABLE

// Reduce RGB options to save space
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

// Custom RGB configuration
#    define EFFECT_LAYERS 2
#    define EFFECTS_PER_LAYER 3
#endif
