/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_task.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "keychron_common.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "keychron_wireless_common.h"
#    include "battery.h"
#endif

#define POWER_ON_LED_DURATION 3000
static uint32_t power_on_indicator_timer;

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        if (active) { // Mac position
            layer_on(0);
        } else { // Win position
            layer_on(2);
        }
    }
    dip_switch_update_user(index, active);

    return true;
}
#endif

void keyboard_post_init_kb(void) {
#ifdef LK_WIRELESS_ENABLE
    palSetLineMode(P2P4_MODE_SELECT_PIN, PAL_MODE_INPUT);
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);

    writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);

    lkbt51_init(false);
    wireless_init();
#endif

    power_on_indicator_timer = timer_read32();
#ifdef ENCODER_ENABLE
    encoder_cb_init();
#endif

    keyboard_post_init_user();
}

#ifdef RGB_MATRIX_ENABLE
#    include "caps_word.h"
#    include "rgb_matrix.h"
// Forward declaration from indicator.c to reuse its ephemeral refresh path
bool led_update_kb(led_t led_state);
// Ensure Caps Word state influences indicators even when RGB is toggled off.
// We piggyback on the existing led_update_kb path by overriding the weak user hook here.
bool rgb_matrix_indicators_user(void) {
    // If Caps Word is active, ensure the Caps Lock indicator LED is lit.
    if (is_caps_word_on()) {
#    if defined(CAPS_LOCK_INDEX)
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 255, 255, 255);
#    endif
    }
    return true; // allow other user-level indicators as well
}

// Override the weak os_state_indicate from indicator.c so we can also light Caps for Caps Word
void os_state_indicate(void) {
    // Mirror host lock LEDs and add Caps Word support
    led_t host = host_keyboard_led_state();

#    ifdef NUM_LOCK_INDEX
    if (host.num_lock) {
        rgb_matrix_set_color(NUM_LOCK_INDEX, 255, 255, 255);
    }
#    endif

#    ifdef CAPS_LOCK_INDEX
    if (host.caps_lock || is_caps_word_on()) {
#        ifdef DIM_CAPS_LOCK
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
#        else
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 255, 255, 255);
#        endif
    } else {
        // Explicitly clear when neither Caps Lock nor Caps Word is active to avoid stale LED when RGB is off
        rgb_matrix_set_color(CAPS_LOCK_INDEX, 0, 0, 0);
    }
#    endif

#    ifdef SCROLL_LOCK_INDEX
    if (host.scroll_lock) {
        rgb_matrix_set_color(SCROLL_LOCK_INDEX, 255, 255, 255);
    }
#    endif

#    ifdef COMPOSE_LOCK_INDEX
    if (host.compose) {
        rgb_matrix_set_color(COMPOSE_LOCK_INDEX, 255, 255, 255);
    }
#    endif

#    ifdef KANA_LOCK_INDEX
    if (host.kana) {
        rgb_matrix_set_color(KANA_LOCK_INDEX, 255, 255, 255);
    }
#    endif
}

// Ensure LED refresh on Caps Word state change, even when RGB is toggled off
void caps_word_set_user(bool active) {
    // Force an indicator refresh using the same path host LEDs use, which
    // temporarily wakes the driver, paints, flushes, and re-shuts down if needed.
    (void)active;
    led_update_kb(host_keyboard_led_state());
}
#endif

bool keychron_task_kb(void) {
    if (power_on_indicator_timer) {
        if (timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
            power_on_indicator_timer = 0;

#ifdef LK_WIRELESS_ENABLE
            writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#endif
        } else {
#ifdef LK_WIRELESS_ENABLE
            writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#endif
        }
    }
    return true;
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return power_on_indicator_timer == 0 && !factory_reset_indicating();
}
#endif
