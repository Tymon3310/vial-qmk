/* Copyright 2022 ~ 2025 @ lokher (https://www.keychron.com)
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
#include "wireless.h"
#include "indicator.h"
#include "lpm.h"
#include "mousekey.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#endif
#include "transport.h"
#if defined(LK_WIRELESS_ENABLE)
#    include "lkbt51.h"
#elif defined(KC_BLUETOOTH_ENABLE)
#    include "ckbt51.h"
#endif
#include "eeconfig_wireless.h"

#ifdef REINIT_LED_DRIVER
#    error "REINIT_LED_DRIVER is depreated, please use LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE instead"
#endif

#if defined(PROTOCOL_CHIBIOS)
extern host_driver_t chibios_driver;
#endif
extern host_driver_t   wireless_driver;
extern keymap_config_t keymap_config;
extern wt_func_t       wireless_transport;

static transport_t transport = TRANSPORT_NONE;

#ifdef NKRO_ENABLE
nkro_t nkro = {false, false};
#endif

static void transport_changed(transport_t new_transport);

__attribute__((weak)) void bt_transport_enable(bool enable) {
    if (enable) {
        // if (host_get_driver() != &wireless_driver) {
        host_set_driver(&wireless_driver);

        /* Disconnect and reconnect to sync the wireless state
         * TODO: query wireless state to sync
         */
        wireless_disconnect();

        uint32_t t = timer_read32();
        while (timer_elapsed32(t) < 100) {
            wireless_transport.task();
        }
        // wireless_connect();

        wireless_connect_ex(30, 0);
        // TODO: Clear USB report
        //}
    } else {
        indicator_stop();

        if (wireless_get_state() == WT_CONNECTED && transport == TRANSPORT_BLUETOOTH) {
            report_keyboard_t empty_report = {0};
            wireless_driver.send_keyboard(&empty_report);
        }
    }
}

__attribute__((weak)) void p24g_transport_enable(bool enable) {
#if defined(LK_WIRELESS_ENABLE)
    if (enable) {
        // if (host_get_driver() != &wireless_driver) {
        host_set_driver(&wireless_driver);

        /* Disconnect and reconnect to sync the wireless state
         * TODO: query bluetooth state to sync
         */
        wireless_disconnect();

        uint32_t t = timer_read32();
        while (timer_elapsed32(t) < 100) {
            wireless_transport.task();
        }
        wireless_connect_ex(P24G_INDEX, 0);
        // wireless_connect();
        //  TODO: Clear USB report
        //}
    } else {
        indicator_stop();

        if (wireless_get_state() == WT_CONNECTED && transport == TRANSPORT_P2P4) {
            report_keyboard_t empty_report = {0};
            wireless_driver.send_keyboard(&empty_report);
        }
    }
#endif
}

__attribute__((weak)) void usb_power_connect(void) {}
__attribute__((weak)) void usb_power_disconnect(void) {}

__attribute__((weak)) void usb_transport_enable(bool enable) {
    if (enable) {
        if (host_get_driver() != &chibios_driver) {
#if !defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
            usb_power_connect();
#    if defined(FORCE_USB_DISCONNECT_ON_USB_TRANSPORT_ENABLE)
            usbDisconnectBus(&USBD1);
            wait_ms(30);
#    endif
            restart_usb_driver(&USBD1);
#endif
            host_set_driver(&chibios_driver);
        }
    } else {
        if (USB_DRIVER.state == USB_ACTIVE) {
            report_keyboard_t empty_report = {0};
            chibios_driver.send_keyboard(&empty_report);
        }

#if !defined(KEEP_USB_CONNECTION_IN_WIRELESS_MODE)
        usbStop(&USBD1);
        usbDisconnectBus(&USBD1);
        usb_power_disconnect();
#endif
    }
}

void set_transport(transport_t new_transport) {
    if (transport != new_transport) {
        if (transport == TRANSPORT_USB || ((transport != TRANSPORT_USB) && wireless_get_state() == WT_CONNECTED)) {
            clear_keyboard();
        }

        transport = new_transport;

        switch (transport) {
            case TRANSPORT_USB:
                usb_transport_enable(true);
                bt_transport_enable(false);
                wait_ms(5);
                p24g_transport_enable(false);
                wireless_disconnect();
                lpm_timer_stop();
                transport_changed(transport); // Need to be called before indicator_set()
#if defined(KEYCOMBO_CONN_SWITCH_ENABLE)
                if (USBD1.state == USB_ACTIVE)
                    indicator_set(WT_CONNECTED, USB_HOST_INDEX);
                else
                    indicator_set(WT_RECONNECTING, USB_HOST_INDEX);
#endif
                break;

            case TRANSPORT_BLUETOOTH:
                p24g_transport_enable(false);
                wait_ms(1);
                bt_transport_enable(true);
                usb_transport_enable(false);
                lpm_timer_reset();
                transport_changed(transport);
                break;

            case TRANSPORT_P2P4:
                bt_transport_enable(false);
                wait_ms(1);
                p24g_transport_enable(true);
                usb_transport_enable(false);
                lpm_timer_reset();
                transport_changed(transport);
                break;

            default:
                break;
        }
    }
}

transport_t get_transport(void) {
    return transport;
}

#ifdef LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE
/* Changing transport may cause bronw-out reset of led driver
 * without MCU reset, which lead backlight to not work,
 * reinit the led driver workgound this issue */
static void reinit_led_drvier(void) {
#    if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_DRIVER_SHUTDOWN_ENABLE)
    led_matrix_driver_shutdown();
#    endif
#    if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE)
    rgb_matrix_driver_shutdown();
#    endif

    /* Wait circuit to discharge for a while */
    wait_ms(100);

#    ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#    endif
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#    endif
}
#endif

void transport_changed(transport_t new_transport) {
    kc_printf("transport_changed %d\n\r", new_transport);
#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
    if (new_transport != TRANSPORT_USB) {
#    if defined(LED_MATRIX_ENABLE)
        led_matrix_set_suspend_state(false);
#    endif
#    if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_set_suspend_state(false);
#    endif
    }
#else
    indicator_init();
#endif

#ifdef LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE
    reinit_led_drvier();
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_TIMEOUT)
#    if (RGB_MATRIX_TIMEOUT > 0)
    rgb_matrix_disable_timeout_set(RGB_MATRIX_TIMEOUT_INFINITE);
    rgb_matrix_disable_time_reset();
#    endif
#endif
#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_TIMEOUT)
#    if (LED_MATRIX_TIMEOUT > 0)
    led_matrix_disable_timeout_set(LED_MATRIX_TIMEOUT_INFINITE);
    led_matrix_disable_time_reset();
#    endif
#endif
    led_update_kb(host_keyboard_led_state());
}

void usb_remote_wakeup(void) {
    usb_event_queue_task();

    if (USB_DRIVER.state == USB_SUSPENDED) {
#if defined(WB32F3G71xx)
        // wait_ms(300);
        // if (!usb_power_connected()) return;
#endif
        while (USB_DRIVER.state == USB_SUSPENDED) {
            wireless_pre_task();
            if (get_transport() != TRANSPORT_USB) {
                suspend_wakeup_init_quantum();
                return;
            }
#if defined(KEYCOMBO_CONN_SWITCH_ENABLE)
            if (get_transport() == TRANSPORT_USB && !usb_power_connected()) return;
#endif
            /* Do this in the suspended state */
            suspend_power_down(); // on AVR this deep sleeps for 15ms
            /* Remote wakeup */
            if (suspend_wakeup_condition()
#ifdef ENCODER_ENABLE
                || encoder_task()
#endif
            ) {
                usbWakeupHost(&USB_DRIVER);
                wait_ms(300);
#ifdef MOUSEKEY_ENABLE
                // Wiggle to wakeup
                mousekey_on(MS_LEFT);
                mousekey_send();
                wait_ms(10);
                mousekey_on(MS_RGHT);
                mousekey_send();
                wait_ms(10);
                mousekey_off((MS_RGHT));
                mousekey_send();
#else
                set_mods(0x02);
                send_keyboard_report();
                wait_ms(10);
                del_mods(0x02);
                send_keyboard_report();
#endif
            }
        }
        /* Woken up */
        // variables has been already cleared by the wakeup hook
        send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
        mousekey_send();
#endif /* MOUSEKEY_ENABLE */
    }
}

#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
uint8_t eeprom_read_transport(void) {
    return eeprom_read_byte((uint8_t *)EECONFIG_BASE_WIRELESS_CONFIG + OFFSET_TRANSPORT);
}

void eeprom_update_transport(uint8_t val) {
    eeprom_write_byte((uint8_t *)EECONFIG_BASE_WIRELESS_CONFIG + OFFSET_TRANSPORT, val);
}
#endif
