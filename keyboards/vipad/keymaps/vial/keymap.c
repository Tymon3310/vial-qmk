/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY,
        KC_P7, KC_P8, KC_P9, KC_PSLS,
        KC_P4, KC_P5, KC_P6, KC_PMNS,
        KC_P1, KC_P2, KC_P3, KC_PPLS,
        KC_P0, KC_PDOT, KC_PENT, MO(1)),
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
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [1] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    return OLED_ROTATION_180;
}

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
    case 2:
        oled_write_P(PSTR("Layer: 2\n"), false);
        break;
    case 3:
        oled_write_P(PSTR("Layer: 3\n"), false);
        break;
    case 4:
        oled_write_P(PSTR("Layer: 4\n"), false);
        break;
    case 5:
        oled_write_P(PSTR("Layer: 5\n"), false);
        break;
    case 6:
        oled_write_P(PSTR("Layer: 6\n"), false);
        break;
    case 7:
        oled_write_P(PSTR("Layer: 7\n"), false);
        break;
    case 8:
        oled_write_P(PSTR("Layer: 8\n"), false);
        break;
    case 9:
        oled_write_P(PSTR("Layer: 9\n"), false);
        break;
    case 10:
        oled_write_P(PSTR("Layer: 10\n"), false);
        break;
    case 11:
        oled_write_P(PSTR("Layer: 11\n"), false);
        break;
    case 12:
        oled_write_P(PSTR("Layer: 12\n"), false);
        break;
    case 13:
        oled_write_P(PSTR("Layer: 13\n"), false);
        break;
    case 14:
        oled_write_P(PSTR("Layer: 14\n"), false);
        break;
    case 15:
        oled_write_P(PSTR("Layer: 15\n"), false);
        break;
    case 16:
        oled_write_P(PSTR("Layer: 16\n"), false);
        break;
    case 17:
        oled_write_P(PSTR("Layer: 17\n"), false);
        break;
    case 18:
        oled_write_P(PSTR("Layer: 18\n"), false);
        break;
    default:
        oled_write_P(PSTR("Layer: CUST\n"), false);
        break;
    }

    oled_write_P(PSTR("--------------------\n"), false);
    oled_write_P(PSTR("E1: Vol | E2: Scroll\n"), false);

    return false;
}
#endif