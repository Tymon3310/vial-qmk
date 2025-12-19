/* Copyright 2022 ~ 2025 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wireless.h"
#include "indicator.h"
#include "transport.h"
#include "battery.h"
#include "bat_level_animation.h"
#include "lpm.h"
#include "keychron_wireless_common.h"
#include "keychron_task.h"
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#elif defined(KC_BLUETOOTH_ENABLE)
#    include "ckbt51.h"
#endif

bool firstDisconnect = true;

static uint32_t pairing_key_timer;
static uint8_t  host_idx = 0;
extern uint16_t connected_idle_time;
#if defined(KC_BLUETOOTH_ENABLE)
static uint32_t kc_bt_reset_timer = 0;
#endif

void wireless_common_init(void) {
#ifdef BT_MODE_SELECT_PIN
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);
#endif
#ifdef BAT_LOW_LED_PIN
    gpio_write_pin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#endif

#if defined(LK_WIRELESS_ENABLE)
#    ifdef P24G_MODE_SELECT_PIN
    palSetLineMode(P24G_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    endif
    lkbt51_init(false);
#elif defined(KC_BLUETOOTH_ENABLE)
#if defined(CKBT51_RESET_PIN)
    /* Currently we don't use this reset pin */
    palSetLineMode(CKBT51_RESET_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palWriteLine(CKBT51_RESET_PIN, PAL_HIGH);
#endif
    ckbt51_init(false);
#endif

    wireless_init();
}

bool process_record_keychron_wireless(uint16_t keycode, keyrecord_t *record) {
    // static uint8_t host_idx;

    switch (keycode) {
        case BT_HST1 ... BT_HST3:
#ifndef KEYCOMBO_CONN_SWITCH_ENABLE
            if (get_transport() == TRANSPORT_BLUETOOTH)
#endif
            {
                if (record->event.pressed) {
#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
                    if (eeprom_read_transport() != TRANSPORT_BLUETOOTH) {
                        set_transport(TRANSPORT_BLUETOOTH);
                        eeprom_update_transport(TRANSPORT_BLUETOOTH);
                        // wait_ms(50);
                    }
#endif
                    host_idx = keycode - BT_HST1 + 1;

                    pairing_key_timer = timer_read32();
                    wireless_connect_ex(host_idx, 0);
                } else {
                    host_idx          = 0;
                    pairing_key_timer = 0;
                }
            }
            break;

#if defined(P24G_MODE_SELECT_PIN) || defined(KEYCOMBO_CONN_SWITCH_ENABLE)
        case P2P4G:
#    ifdef P24G_MODE_SELECT_PIN
            if (get_transport() == TRANSPORT_P2P4)
#    endif
            {
                if (record->event.pressed) {
#    ifdef KEYCOMBO_CONN_SWITCH_ENABLE
#        if (EECONFIG_KB_DATA_SIZE > 0)
                    if (eeprom_read_transport() != TRANSPORT_P2P4) {
                        set_transport(TRANSPORT_P2P4);
                        eeprom_update_transport(TRANSPORT_P2P4);
                    }
#        else
                    set_transport(TRANSPORT_P2P4);
#        endif
#    endif
                    host_idx = P24G_INDEX;

                    pairing_key_timer = timer_read32();
                } else {
                    host_idx          = 0;
                    pairing_key_timer = 0;
                }
            }
            break;
#endif

#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
        case TP_USB:
            if (record->event.pressed) {
                // if (usb_power_connected())
                {
#    if (EECONFIG_KB_DATA_SIZE > 0)
                    if (eeprom_read_transport() != TRANSPORT_USB) {
                        set_transport(TRANSPORT_USB);
                        eeprom_update_transport(TRANSPORT_USB);
                        set_transport(TRANSPORT_USB);
                    }
#    else
                    set_transport(TRANSPORT_USB);
#    endif
                }
            }
            break;
#endif

#if (defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)) && defined(BAT_LEVEL_LED_LIST)
        case BAT_LVL:
            if ((get_transport() & TRANSPORT_WIRELESS) && !usb_power_connected()) {
                bat_level_animiation_start(battery_get_percentage());
            }
            break;
#endif

        default:
#ifdef USB_INDICATION_LED_INDEX
            if (get_transport() == TRANSPORT_USB && !usb_power_connected()) {
                rgb_matrix_set_suspend_state(false);
                if (USBD1.state != USB_ACTIVE) indicator_set(WT_RECONNECTING, USB_HOST_INDEX);
            }
#endif
            break;
    }

    return true;
}

#ifdef LK_WIRELESS_ENABLE
void lkbt51_param_init(void) {
    /* Set bluetooth device name */
    lkbt51_set_local_name(PRODUCT);
    wait_ms(3);
    // clang-format off
    /* Set bluetooth parameters */
    module_param_t param = {.event_mode             = 0x02,
                            .connected_idle_timeout = connected_idle_time,
                            .pairing_timeout        = 180,
                            .pairing_mode           = 0,
                            .reconnect_timeout      = 5,
                            .report_rate            = 90,
                            .vendor_id_source       = 1,
#if (VID == 0x3434 || VID == 0x362D)
                            .verndor_id             = VID, // Must be 0x3434 or 0x362D
#endif
                            .product_id             = PRODUCT_ID};
    // clang-format on
    lkbt51_set_param(&param);

#    ifdef MS_SWIFT_PAIR_NAME
    wait_ms(3);
    lkbt51_set_ms_swift_pair_name(MS_SWIFT_PAIR_NAME);
#    endif
}
#elif defined(KC_BLUETOOTH_ENABLE)
void ckbt51_param_init(void) {
    /* Set bluetooth device name */
    // ckbt51_set_local_name(STR(PRODUCT));
    ckbt51_set_local_name(PRODUCT);
    wait_ms(10);
    /* Set bluetooth parameters */
    module_param_t param = {.event_mode = 0x02,
                            .connected_idle_timeout = connected_idle_time,
                            .pairing_timeout = 180,
                            .pairing_mode = 0,
                            .reconnect_timeout = 5,
                            .report_rate = 90,
                            .vendor_id_source = 1,
                            .verndor_id = 0, // Must be 0x3434
                            .product_id = PRODUCT_ID};
    ckbt51_set_param(&param);
    wait_ms(10);
}
#endif

void wireless_enter_reset_kb(uint8_t reason) {
#ifdef LK_WIRELESS_ENABLE
    lkbt51_param_init();
#endif
}

void wireless_enter_disconnected_kb(uint8_t host_idx, uint8_t reason) {
    /* CKBT51 bluetooth module boot time is slower, it enters disconnected after boot,
    so we place initialization here. */
    if (firstDisconnect && timer_read32() < 1000) {
#ifdef LK_WIRELESS_ENABLE
        lkbt51_param_init();
#elif defined(KC_BLUETOOTH_ENABLE)
        ckbt51_param_init();
#endif

        if (get_transport() == TRANSPORT_BLUETOOTH) wireless_connect();
        firstDisconnect = false;
    } else if (reason) {
#if defined(KC_BLUETOOTH_ENABLE)
        ckbt51_param_init();
        kc_bt_reset_timer = timer_read32();
#endif
    }
}

void keychron_wireless_common_task(void) {
    if (pairing_key_timer) {
        if (timer_elapsed32(pairing_key_timer) > 2000) {
            pairing_key_timer = 0;
            wireless_pairing_ex(host_idx, NULL);
        }
    }
#if defined(KC_BLUETOOTH_ENABLE)
    if (kc_bt_reset_timer && timer_elapsed32(kc_bt_reset_timer) > 2000) {
        kc_bt_reset_timer = 0;
#    ifdef CKBT51_RESET_PIN
        palWriteLine(CKBT51_RESET_PIN, PAL_LOW);
        wait_ms(5);
        palWriteLine(CKBT51_RESET_PIN, PAL_HIGH);
#    endif
    }
#endif
}

void wireless_pre_task(void) {
#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
    if (get_transport() == TRANSPORT_NONE) {
        uint8_t mode = eeprom_read_transport();
        if (mode == 0) {
            mode = TRANSPORT_USB;
            eeprom_update_transport(mode);
        }

        set_transport(mode);
    }
#else
    static uint8_t dip_switch_state = 0;
    static uint32_t time = 0;

    if (time == 0) {
        uint8_t pins_state = (gpio_read_pin(BT_MODE_SELECT_PIN) << 1)
#    ifdef P24G_MODE_SELECT_PIN
                             | gpio_read_pin(P24G_MODE_SELECT_PIN)
#    endif
            ;

        if (pins_state != dip_switch_state) {
            dip_switch_state = pins_state;
            time = timer_read32();
        }
    }

    if ((time && timer_elapsed32(time) > 100) || get_transport() == TRANSPORT_NONE) {
        uint8_t pins_state = (gpio_read_pin(BT_MODE_SELECT_PIN) << 1)
#    ifdef P24G_MODE_SELECT_PIN
                             | gpio_read_pin(P24G_MODE_SELECT_PIN)
#    endif
            ;

        if (pins_state == dip_switch_state) {
            time = 0;

            switch (dip_switch_state) {
#    ifndef P24G_MODE_SELECT_PIN
                case 0x00:
                    set_transport(TRANSPORT_BLUETOOTH);
                    break;
#    else
                case 0x01:
                    set_transport(TRANSPORT_BLUETOOTH);
                    break;
                case 0x02:
                    set_transport(TRANSPORT_P2P4);
                    break;
#    endif
                default:
                    set_transport(TRANSPORT_USB);
                    break;
            }
        } else {
            dip_switch_state = pins_state;
            time = timer_read32();
        }
    }

#endif
}

#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
#    include "usb_device_state.h"
#    include "rgb_matrix.h"
void notify_usb_device_state_change_kb(enum usb_device_state usb_device_state) {
#    ifdef USB_INDICATION_LED_INDEX
    if (get_transport() == TRANSPORT_USB) {
        static enum usb_device_state last_state = USB_DEVICE_STATE_NO_INIT;

        if (usb_device_state == USB_DEVICE_STATE_CONFIGURED) {
            if (last_state != USB_DEVICE_STATE_SUSPEND) {
                rgb_matrix_set_suspend_state(false);
                indicator_set(WT_CONNECTED, USB_HOST_INDEX);
            }
        } else if (usb_device_state != USB_DEVICE_STATE_SUSPEND) {
            rgb_matrix_set_suspend_state(false);
            indicator_set(WT_RECONNECTING, USB_HOST_INDEX);
        }

        if (last_state != usb_device_state) last_state = usb_device_state;
    }
#    endif
    notify_usb_device_state_change_user(usb_device_state);
}
#endif
