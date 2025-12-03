/* Copyright 2023 ~ 2025 @ lokher (https://www.keychron.com)
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
#include "eeconfig.h"
#include "config.h"
#include "usb_main.h"
#include "eeprom.h"
#include "nvm_eeprom_eeconfig_internal.h"
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#include "keychron_common.h"
#include "keychron_task.h"
#include "backlit_indicator.h"
#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
#    include "transport.h"
#    include "wireless.h"
#endif

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)

typedef struct {
    uint32_t timer;
    uint16_t on_time;
    uint16_t off_time;
    uint8_t  repeat_count;
    uint8_t  current_count;
    bool     state;
    bool     active;
#    if defined(RGB_MATRIX_ENABLE)
    RGB color;
#    endif
} backlight_indicator_t;

static backlight_indicator_t backlit_ind;

void indicator_enable(void) {
    if (!LED_DRIVER_IS_ENABLED()) {
        LED_DRIVER_ENABLE_NOEEPROM();
    }
}

void indicator_disable(void) {
    LED_DRIVER_DISABLE_NOEEPROM();
}

bool indicator_is_enabled(void) {
    return LED_DRIVER_IS_ENABLED();
}

void indicator_eeconfig_reload(void) {
    LED_DRIVER_EECONFIG_RELOAD();
}

__attribute__((weak)) void os_state_indicate(void) {
#    if defined(RGB_MATRIX_SLEEP) || defined(LED_MATRIX_SLEEP)
#        if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
    if (get_transport() == TRANSPORT_USB && USB_DRIVER.state == USB_SUSPENDED) return;
#        else
    if (USB_DRIVER.state == USB_SUSPENDED) return;
#        endif
#    endif

#    if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
#        if defined(DIM_NUM_LOCK)
        SET_LED_OFF(NUM_LOCK_INDEX);
#        else
        SET_LED_ON(NUM_LOCK_INDEX);
#        endif
    }
#    endif
#    if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
#        if defined(DIM_CAPS_LOCK)
        SET_LED_OFF(CAPS_LOCK_INDEX);
#        else
        SET_LED_ON(CAPS_LOCK_INDEX);
#        endif
    }
#    endif
#    if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        SET_LED_ON(SCROLL_LOCK_INDEX);
    }
#    endif
#    if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) {
        SET_LED_ON(COMPOSE_LOCK_INDEX);
    }
#    endif
#    if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) {
        SET_LED_ON(KANA_LOCK_INDEX);
    }
#    endif

#    if defined(WINLOCK_LED_LIST) || defined(WIN_LOCK_LED_PIN)
#        if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
    // TODO: check if we can use (get_transport() == TRANSPORT_USB || wireless_get_state() == WT_CONNECTED)
    if (get_transport() == TRANSPORT_USB || ((get_transport() & TRANSPORT_WIRELESS) && wireless_get_state() == WT_CONNECTED))
#        endif
    {
#        ifdef WIN_BASE_LAYER
        if (get_highest_layer(default_layer_state) == WIN_BASE_LAYER)
#        endif
        {
#        if defined(WINLOCK_LED_LIST)
            uint8_t idx_list[] = WINLOCK_LED_LIST;
            for (uint8_t i = 0; i < sizeof(idx_list); i++) {
                if (keymap_config.no_gui) {
#            ifdef DIM_WIN_LOCK
                    SET_LED_OFF(idx_list[i]);
#            else
                    rgb_matrix_set_color(idx_list[i], 255, 0, 0);
#            endif
                }
            }
#        endif
#        if defined(WIN_LOCK_LED_PIN)
            gpio_set_pin_output_push_pull(WIN_LOCK_LED_PIN);
            gpio_write_pin(WIN_LOCK_LED_PIN, keymap_config.no_gui ? WIN_LOCK_LED_PIN_ON_STATE : !WIN_LOCK_LED_PIN_ON_STATE);
#        endif
        }
#        if defined(WIN_BASE_LAYER) && defined(WIN_LOCK_LED_PIN)
        else {
            gpio_set_pin_output_push_pull(WIN_LOCK_LED_PIN);
            gpio_write_pin(WIN_LOCK_LED_PIN, !WIN_LOCK_LED_PIN_ON_STATE);
        }
#        endif
    }
#    endif
}

void backlight_indicator_init(void) {
    memset(&backlit_ind, 0, sizeof(backlight_indicator_t));
}

#    if defined(RGB_MATRIX_ENABLE)
void backlight_indicator_start(uint16_t on_time, uint16_t off_time, uint8_t repeat_count, RGB color) {
#    else
void backlight_indicator_start(uint16_t on_time, uint16_t off_time, uint8_t repeat_count) {
#    endif

    backlit_ind.on_time       = on_time;
    backlit_ind.off_time      = off_time;
    backlit_ind.repeat_count  = repeat_count;
    backlit_ind.current_count = 0;
    backlit_ind.state         = true;
    backlit_ind.active        = true;
    backlit_ind.timer         = timer_read32();

#    if defined(RGB_MATRIX_ENABLE)
    backlit_ind.color = color;
#    endif

    indicator_enable();

#    if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_set_color_all(backlit_ind.color.r, backlit_ind.color.g, backlit_ind.color.b);
#    else
    led_matrix_set_value_all(255);
#    endif
}

void backlight_indicator_stop(void) {
    backlit_ind.active = false;
    indicator_eeconfig_reload();
    if (!LED_DRIVER_IS_ENABLED()) {
        SET_ALL_LED_OFF();
        extern void os_state_indicate(void);
        os_state_indicate();
        LED_DRIVER.flush();
        indicator_disable();
    }
}

void backlit_indicator(void) {
    if (!backlit_ind.active) return;

    uint32_t elapsed        = timer_elapsed32(backlit_ind.timer);
    uint16_t current_period = backlit_ind.state ? backlit_ind.on_time : backlit_ind.off_time;

    if (elapsed >= current_period) {
        backlit_ind.timer = timer_read32();
        backlit_ind.state = !backlit_ind.state;

        if (backlit_ind.state) {
            backlit_ind.current_count++;
            if (backlit_ind.current_count >= backlit_ind.repeat_count) {
                backlight_indicator_stop();
                return;
            }
        }
    }

    if (backlit_ind.state) {
#    if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_set_color_all(backlit_ind.color.r, backlit_ind.color.g, backlit_ind.color.b);
#    else
        led_matrix_set_value_all(255);
#    endif
    } else {
        SET_ALL_LED_OFF();
    }
}

bool backlight_indicator_is_active(void) {
    return backlit_ind.active;
}
#endif

__attribute__((weak)) void suspend_power_down_keychron_kb(void) {}
__attribute__((weak)) void suspend_wakeup_init_keychron_kb(void) {}

void suspend_power_down_kb(void) {
#if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(WINLOCK_LED_LIST)
    uint8_t idx_list[] = WINLOCK_LED_LIST;
    for (uint8_t i = 0; i < sizeof(idx_list); i++) {
        if (keymap_config.no_gui) {
            SET_LED_OFF(idx_list[i]);
        }
    }
#endif
#if defined(WIN_LOCK_LED_PIN)
    gpio_write_pin(WIN_LOCK_LED_PIN, !WIN_LOCK_LED_PIN_ON_STATE);
#endif
    suspend_power_down_keychron_kb();
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
#if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(WINLOCK_LED_LIST)
    uint8_t idx_list[] = WINLOCK_LED_LIST;
    for (uint8_t i = 0; i < sizeof(idx_list); i++) {
        if (keymap_config.no_gui) {
#    ifdef DIM_WIN_LOCK
            SET_LED_OFF(idx_list[i]);
#    else
#        if defined(RGB_MATRIX_ENABLE)
            // Only rgb matrix is support
            rgb_matrix_set_color(i, 255, 0, 0);
#        endif
#    endif
        }
    }
#endif
#if defined(WIN_LOCK_LED_PIN)
    gpio_write_pin(WIN_LOCK_LED_PIN, keymap_config.no_gui ? WIN_LOCK_LED_PIN_ON_STATE : !WIN_LOCK_LED_PIN_ON_STATE);
#endif
    suspend_wakeup_init_keychron_kb();
    suspend_wakeup_init_user();
}
