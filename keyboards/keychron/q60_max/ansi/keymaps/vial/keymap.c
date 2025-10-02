// Vial keymap upgraded: add Mac/Win base + FN layers with wireless & RGB (derived from default keymap style)
#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_60(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(FN),
                          KC_LOPTN,KC_LCMMD,                           KC_SPC,                         KC_RCMMD, KC_ROPTN),

    [WIN_BASE] = LAYOUT_ansi_60(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, MO(FN),
                          KC_LWIN, KC_LALT,                            KC_SPC,                         KC_RALT,  KC_RWIN),

    [FN] = LAYOUT_ansi_60(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, BT_HST1, BT_HST2, BT_HST3, P2P4G,   _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______,           KC_BSPC,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RIGHT,                  _______,
        _______,          RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, BAT_LVL, NK_TOGG, _______, KC_END,  KC_PGDN, KC_DOWN,          _______, _______,
                          _______, _______,                           _______,                        _______, _______)
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
