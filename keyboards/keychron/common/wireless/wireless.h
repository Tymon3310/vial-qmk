/* Copyright 2023 ~ 2025 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "wireless_event_type.h"
#include "action.h"

#ifdef KC_DEBUG
#    define kc_printf dprintf
#else
#    define kc_printf(format, ...)
#endif

#define RAW_HID_SRC_WIRELESS (RAW_HID_SRC_USB+1)

/* XOR key for encoding raw HID data over wireless.
 * The LKBT51 module's proprietary firmware crashes when certain byte values
 * appear in raw HID packets.  Confirmed problematic: the entire 0xF0-0xFF
 * range (originally discovered via 0xFE, then 0xFA also caused crashes).
 * XOR-encoding all bytes with a fixed key avoids these values.
 *
 * Key 0x28 is chosen so that no standard VIA/Vial/Keychron command byte
 * (0x00-0x12, 0xA0-0xAB, 0xFE, 0xFF) maps into the dangerous 0xF0-0xFF
 * range, and none collide with FR commands (0xB1-0xBA) or state-notify
 * markers (0xBC, 0xE2).
 *
 * The GUI must use the same key when communicating via the bridge dongle. */
#ifndef WIRELESS_RAW_HID_XOR_KEY
#    define WIRELESS_RAW_HID_XOR_KEY 0x28
#endif

/* Low power mode */
#ifndef LOW_POWER_MODE
#    ifdef QMK_MCU_SERIES_STM32L4XX
#        define LOW_POWER_MODE PM_STOP1
#    else
#        define LOW_POWER_MODE PM_STOP
#    endif
#endif

/* Wake pin used for blueooth module/controller to wake up MCU in low power mode*/
#ifndef BLUETOOTH_INT_INPUT_PIN
#    define WAKE_PIN A5
#endif

// clang-format off
/* Type of an enumeration of the possible wireless transport state.*/
typedef enum {
    WT_RESET,
    WT_INITIALIZED,   // 1
    WT_DISCONNECTED,  // 2
    WT_CONNECTED,     // 3
    WT_PARING,        // 4
    WT_RECONNECTING,  // 5
    WT_SUSPEND
} wt_state_t;

//extern event_listener_t wireless_driver;

typedef struct {
    void (*init)(bool);
    void (*connect_ex)(uint8_t, uint16_t);
    void (*pairing_ex)(uint8_t, void *);
    void (*disconnect)(void);
    void (*send_keyboard)(uint8_t *);
    void (*send_nkro)(uint8_t *);
    void (*send_consumer)(uint16_t);
    void (*send_system)(uint16_t);
    void (*send_mouse)(uint8_t *);
    void (*send_raw_hid)(uint8_t *, uint8_t);
    void (*update_bat_level)(uint8_t);
    void (*task)(void);
} wt_func_t;
// clang-format on

extern void register_wt_tasks(void);

void wireless_init(void);
void wireless_config_reset(void);

void wireless_set_transport(wt_func_t *transport);
void wireless(void);

bool wireless_event_enqueue(wireless_event_t event);

void wireless_connect(void);
void wireless_connect_ex(uint8_t host_idx, uint16_t timeout);
void wireless_disconnect(void);

void wireless_pairing(void);
void wireless_pairing_ex(uint8_t host_idx, void *param);
// bool bluetooth_is_activated(void);

void wireless_enter_reset_kb(uint8_t reason);
void wireless_enter_discoverable_kb(uint8_t host_idx);
void wireless_enter_reconnecting_kb(uint8_t host_idx);
void wireless_enter_connected_kb(uint8_t host_idx);
void wireless_enter_disconnected_kb(uint8_t host_idx, uint8_t reason);
void wireless_enter_bluetooth_pin_code_entry_kb(void);
void wireless_exit_bluetooth_pin_code_entry_kb(void);
bool is_wireless_pin_code_entry(void);
void wireless_enter_sleep_kb(void);

void wireless_task(void);
void wireless_pre_task(void);
void wireless_post_task(void);
void send_string_task(void);

wt_state_t wireless_get_state(void);

void wireless_low_battery_shutdown(void);

bool process_record_wireless(uint16_t keycode, keyrecord_t *record);

void wireless_raw_hid_rx(uint8_t *data, uint8_t length);
