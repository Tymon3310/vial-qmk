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

#include <string.h>
#include "eeconfig_kb.h"
#include "retail_demo.h"
#include "eeconfig.h"
#include "matrix.h"
#include "quantum.h"
#include "eeprom.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "keychron_common.h"
#include "factory_test.h"
#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
#    include "transport.h"
#endif

#if defined(RETAIL_DEMO_ENABLE) && defined(KEYCHRON_RGB_ENABLE) && defined(EECONFIG_SIZE_CUSTOM_RGB)

#    ifndef RETAIL_DEMO_KEY_1
#        ifdef RGB_MATRIX_ENABLE
#            define RETAIL_DEMO_KEY_1 UG_HUEU
#        else
#            define RETAIL_DEMO_KEY_1 KC_D
#        endif
#    endif

#    ifndef RETAIL_DEMO_KEY_2
#        ifdef RGB_MATRIX_ENABLE
#            define RETAIL_DEMO_KEY_2 UG_HUED
#        else
#            define RETAIL_DEMO_KEY_2 KC_E
#        endif
#    endif

#    ifndef EFFECT_DURATION
#        define EFFECT_DURATION 10000
#    endif

enum {
    KEY_PRESS_D           = 0x01 << 1,
    KEY_PRESS_E           = 0x01 << 2,
    KEY_PRESS_RETAIL_DEMO = KEY_PRESS_FN | KEY_PRESS_D | KEY_PRESS_E,
};

uint8_t         retail_demo_enable = 0;
static uint8_t  retail_demo_combo  = 0;
static uint32_t retail_demo_timer  = 0;

extern void rgb_save_retail_demo(void);

bool process_record_retail_demo(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(0)... MO(15):
            if (record->event.pressed)
                retail_demo_combo |= KEY_PRESS_FN;
            else
                retail_demo_combo &= ~KEY_PRESS_FN;
            break;

        case RETAIL_DEMO_KEY_1:
            if (record->event.pressed) {
                retail_demo_combo |= KEY_PRESS_D;
                if (retail_demo_combo == KEY_PRESS_RETAIL_DEMO) retail_demo_timer = timer_read32();
            } else {
                retail_demo_combo &= ~KEY_PRESS_D;
                retail_demo_timer = 0;
            }
            break;

        case RETAIL_DEMO_KEY_2:
            if (record->event.pressed) {
                retail_demo_combo |= KEY_PRESS_E;
                if (retail_demo_combo == KEY_PRESS_RETAIL_DEMO) retail_demo_timer = timer_read32();
            } else {
                retail_demo_combo &= ~KEY_PRESS_E;
                retail_demo_timer = 0;
            }
            break;
    }

    if (retail_demo_enable && keycode >= UG_TOGG && keycode <= UG_SPDD) return false;

    return true;
}

void retail_demo_start(void) {
    extern bool mixed_rgb_set_regions(uint8_t * data);
    extern bool mixed_rgb_set_effect_list(uint8_t * data);

    uint8_t index      = 0;
    uint8_t this_count = 28;
    uint8_t data[31]   = {0};

    // Set all LED to region 0
    while (index < RGB_MATRIX_LED_COUNT - 1) {
        memset(data, 0, 31);

        if ((index + this_count) >= RGB_MATRIX_LED_COUNT)
            this_count = RGB_MATRIX_LED_COUNT - 1 - index;
        else
            this_count = 28;

        data[0] = index;
        data[1] = this_count;
        mixed_rgb_set_regions(data);

        index += this_count;
    }

    uint8_t effect_list[5] = {4, 7, 8, 11, 14};
    // Set effect list
    for (uint8_t i = 0; i < 5; i++) {
        data[0]  = 0;              // regsion
        data[1]  = i;              // start
        data[2]  = 1;              // count
        data[3]  = effect_list[i]; // effect
        data[4]  = 0;              // hue
        data[5]  = 255;            // sat
        data[6]  = 127;            // speed;
        data[7]  = EFFECT_DURATION & 0xFF;
        data[8]  = (EFFECT_DURATION >> 8) & 0xFF;
        data[9]  = (EFFECT_DURATION >> 16) & 0xFF;
        data[10] = (EFFECT_DURATION >> 24) & 0xFF;

        mixed_rgb_set_effect_list(data);
    }

    HSV hsv = rgb_matrix_get_hsv();
    hsv.v = hsv.s = UINT8_MAX;
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    rgb_matrix_set_speed_noeeprom(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_MIXED_RGB);
}

void retail_demo_stop(void) {
    retail_demo_enable = false;
    rgb_save_retail_demo();
    eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
}

static inline void retail_demo_timer_check(void) {
    if (timer_elapsed32(retail_demo_timer) > 5000) {
        retail_demo_timer = 0;

        if (retail_demo_combo == KEY_PRESS_RETAIL_DEMO) {
            retail_demo_combo  = 0;
            retail_demo_enable = !retail_demo_enable;

            if (retail_demo_enable) {
#    if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
                // Retail demo is allowed only in wireless mode
                if (get_transport() != TRANSPORT_USB) {
                    retail_demo_enable = false;
                    return;
                }
#    endif
            } else {
                eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
            }
            rgb_save_retail_demo();

            if (!retail_demo_enable) {
                extern void eeconfig_init_custom_rgb(void);
                eeconfig_init_custom_rgb();
            }
        }
    }
}

void retail_demo_task(void) {
    if (retail_demo_timer) retail_demo_timer_check();
    if (retail_demo_enable && rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_MIXED_RGB) retail_demo_start();
}
#endif
