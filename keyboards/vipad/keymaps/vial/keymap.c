/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY,
        KC_P7, KC_P8, KC_P9, KC_PAST,
        KC_P4, KC_P5, KC_P6, KC_PSLS,
        KC_P1, KC_P2, KC_P3, KC_PMNS,
        KC_P0, KC_PDOT, KC_PENT, KC_PPLS),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

#include "print.h"


void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    dprintf("\n=== VIPAD MATRIX DIAGNOSTIC STARTED ===\n");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("KEY EVENT: Row %d, Col %d | %s (keycode 0x%04X)\n",
            record->event.key.row,
            record->event.key.col,
            record->event.pressed ? "DOWN" : "UP",
            keycode);
    return true;
}



#ifdef OLED_ENABLE
bool oled_task_user(void)
{
    oled_write_P(PSTR("Vipad | "), false);
    switch (get_highest_layer(layer_state))
    {
    case 0:
        oled_write_P(PSTR("Layer: BASE\n"), false);
        break;
    case 1:
        oled_write_P(PSTR("Layer: FN\n"), false);
        break;
    default:
        oled_write_P(PSTR("Layer: CUST\n"), false);
        break;
    }

    oled_write_P(PSTR("---------------------\n"), false);
    oled_write_P(PSTR("E1: Vol\n"), false);
    oled_write_P(PSTR("E2: Scroll\n"), false);

    return false;
}
#endif