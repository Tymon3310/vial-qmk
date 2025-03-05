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

#include "quantum.h"
#include "keychron_task.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "keychron_common.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "transport.h"
#    include "keychron_wireless_common.h"
#    include "battery.h"
#endif

#include "print.h"

#define POWER_ON_LED_DURATION 3000
static uint32_t power_on_indicator_timer;

#ifdef BT_INDICATION_LED_PIN_LIST
pin_t bt_led_pins[] = BT_INDICATION_LED_PIN_LIST;
#endif

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 2));
    }
    dip_switch_update_user(index, active);

    return true;
}

#if 0
extern bool wakeup_from_lpm;

void early_hardware_init_post(void)
{
    if (!wakeup_from_lpm)
    {
        gpio_set_pin_output_push_pull(LED_CAPS_LOCK_PIN);
        gpio_write_pin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
    }
}
#endif

void keyboard_post_init_kb(void) {
#ifdef LK_WIRELESS_ENABLE
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    ifdef P2P4_MODE_SELECT_PIN
    palSetLineMode(P2P4_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    elif defined(USB_MODE_SELECT_PIN)
    palSetLineMode(USB_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    endif

    gpio_write_pin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
    lkbt51_init(false);
    wireless_init();
#endif

    power_on_indicator_timer = timer_read32();
#ifdef ENCODER_ENABLE
    encoder_cb_init();
#endif

#if defined(MCU_UNUSED_PINS) && defined(MCU_UNSED_PINS_STATE)
    pin_t    unused_pins[]       = MCU_UNUSED_PINS;
    uint32_t unused_pins_state[] = MCU_UNSED_PINS_STATE;

    for (uint8_t i = 0; i < ARRAY_SIZE(unused_pins); i++) {
        palSetLineMode(unused_pins[i], unused_pins_state[i]);
    }
#endif

    keyboard_post_init_user();
}

bool keychron_task_kb(void) {
    if (power_on_indicator_timer) {
        if (timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
            power_on_indicator_timer = 0;

            // if (!host_keyboard_led_state().caps_lock) gpio_write_pin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            // for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
            //     gpio_write_pin(bt_led_pins[i], 1);
#endif

        } else {
            // gpio_write_pin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            gpio_write_pin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
            // if (get_transport() != TRANSPORT_P2P4)
            //     for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
            //         gpio_write_pin(bt_led_pins[i], 0);
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
