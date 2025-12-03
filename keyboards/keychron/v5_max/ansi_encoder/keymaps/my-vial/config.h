/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xC7, 0x1B, 0x5D, 0x9A, 0x42, 0xE3, 0x8F, 0x10}

// The four corners (ESC, CTRL, NUM DOT, END)
// #define VIAL_UNLOCK_COMBO_ROWS { 0, 0, 5, 5 }
// #define VIAL_UNLOCK_COMBO_COLS { 0, 17, 0, 17 }

// The four corners (ESC, CTRL, NUM ENTER, DIAL)
#define VIAL_UNLOCK_COMBO_ROWS {0, 5, 4, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 0, 18, 18}

// Esc + Enter
// #define VIAL_UNLOCK_COMBO_ROWS {0, 3}
// #define VIAL_UNLOCK_COMBO_COLS {0, 12}

#define DYNAMIC_KEYMAP_LAYER_COUNT 16

// Enable all QMK RGB matrix effects via a dedicated header
#define MOUSE_TURBO_CLICK_PERIOD 50

/* Snap Click Configuration */
/* Enable visual indication when toggling snap click */
#define SNAP_CLICK_TOGGLE_INDICATION_ENABLE

/* Default snap click pairs for gaming (A/D for strafing, W/S for forward/back)
 * SC_TYPE_LAST_INPUT: The last key pressed takes priority, and when released,
 *                     the other key (if still held) becomes active again.
 * This is ideal for WASD gaming movement.
 */
#define SNAP_CLICK_DEFAULT_PAIRS            \
    {                                       \
        {SC_TYPE_LAST_INPUT, {KC_A, KC_D}}, \
        {SC_TYPE_LAST_INPUT, {KC_W, KC_S}}, \
    }