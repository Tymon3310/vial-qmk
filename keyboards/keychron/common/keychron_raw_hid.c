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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "keychron_raw_hid.h"
#include "raw_hid.h"
#include "version.h"
#include "language.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#ifdef ANANLOG_MATRIX
#    include "analog_matrix.h"
#endif
#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
#    include "battery.h"
#endif
#ifdef DYNAMIC_DEBOUNCE_ENABLE
#    include "keychron_debounce.h"
#endif
#ifdef SNAP_CLICK_ENABLE
#    include "snap_click.h"
#endif
#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
#    include "wireless.h"
#    ifdef LK_WIRELESS_ENABLE
#        include "lkbt51.h"
#    else
#        include "ckbt51.h"
#    endif
#endif

#ifdef RAW_ENABLE
extern void dfu_info_rx(uint8_t *data, uint8_t length);
extern void nkro_rx(uint8_t *data, uint8_t length);

void get_support_feature(uint8_t *data) {
    data[0] = 0;
    data[1] = FEATURE_DEFAULT_LAYER
#    ifdef KC_BLUETOOTH_ENABLE
              | FEATURE_BLUETOOTH
#    endif
#    ifdef LK_WIRELESS_ENABLE
              | FEATURE_BLUETOOTH | FEATURE_P24G
#    endif
#    ifdef ANANLOG_MATRIX
              | FEATURE_ANALOG_MATRIX
#    endif
#    ifdef STATE_NOTIFY_ENABLE
              | FEATURE_STATE_NOTIFY
#    endif
#    ifdef DYNAMIC_DEBOUNCE_ENABLE
              | FEATURE_DYNAMIC_DEBOUNCE
#    endif
#    if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
              | FEATURE_SNAP_CLICK
#    endif
#    ifdef KEYCHRON_RGB_ENABLE
              | FEATURE_KEYCHRON_RGB
#    endif
        ;

    data[2] = (FEATURE_QUICK_START | FEATURE_NKRO) >> 8;
}

#    ifdef ANANLOG_MATRIX
void send_analog_matrix(uint8_t *data, uint8_t length) {
    uint8_t offset = data[2];
    uint8_t rows   = 28 / ((MATRIX_COLS + 7) / 8);
    uint8_t i      = 3;
    for (uint8_t row = 0; row < rows && row + offset < MATRIX_ROWS; row++) {
        matrix_row_t value = analog_matrix_get_row(row + offset);
#        if (MATRIX_COLS > 24)
        data[i++] = (value >> 24) & 0xFF;
#        endif
#        if (MATRIX_COLS > 16)
        data[i++] = (value >> 16) & 0xFF;
#        endif
#        if (MATRIX_COLS > 8)
        data[i++] = (value >> 8) & 0xFF;
#        endif
        data[i++] = value & 0xFF;
    }
    /* Response is sent by raw_hid_receive() via via_raw_hid_send().
     * Do NOT call via_raw_hid_send here — that would cause a double-send. */
}
#    endif

void get_firmware_version(uint8_t *data) {
    uint8_t i = 0;
    data[i++] = 'v';
    if ((DEVICE_VER & 0xF000) != 0) itoa((DEVICE_VER >> 12), (char *)&data[i++], 16);
    itoa((DEVICE_VER >> 8) & 0xF, (char *)&data[i++], 16);
    data[i++] = '.';
    itoa((DEVICE_VER >> 4) & 0xF, (char *)&data[i++], 16);
    data[i++] = '.';
    itoa(DEVICE_VER & 0xF, (char *)&data[i++], 16);
    data[i++] = ' ';
    memcpy(&data[i], QMK_BUILDDATE, sizeof(QMK_BUILDDATE));
    i += sizeof(QMK_BUILDDATE);
}

void kc_raw_hid_send(uint8_t src, uint8_t *data, uint8_t len) {
    if (src == RAW_HID_SRC_USB) {
        extern host_driver_t chibios_driver;
        chibios_driver.send_raw_hid(data, len);
    }
#    ifdef LK_WIRELESS_ENABLE
    else if (wireless_get_state() == WT_CONNECTED) {
        extern wt_func_t wireless_transport;
        if (wireless_transport.send_raw_hid) {
            /* XOR-encode outgoing response before sending via LKBT51.
             * Matches the decode in wireless.c EVT_RAW_HID handler
             * and the encode/decode in the GUI bridge layer. */
            for (uint8_t i = 0; i < len; i++) {
                data[i] ^= WIRELESS_RAW_HID_XOR_KEY;
            }
            wireless_transport.send_raw_hid(data, len);
        }
    }
#    endif
}

bool kc_raw_hid_rx(uint8_t src, uint8_t *data, uint8_t length) {
#    if defined(ANANLOG_MATRIX) && defined(VIA_ENABLE)
    if (src == RAW_HID_SRC_USB && data[0] == id_get_keyboard_value && data[1] == id_switch_matrix_state) {
        send_analog_matrix(data, length);
        return true;
    }
#    endif

    switch (data[0]) {
#    ifdef VIA_ENABLE
        case id_get_protocol_version:
            if (src != RAW_HID_SRC_USB) {
                data[3] = VENDOR_ID >> 8;
                data[4] = VENDOR_ID & 0xFF;
                data[5] = PRODUCT_ID >> 8;
                data[6] = PRODUCT_ID & 0xFF;
                data[7] = DEVICE_VER >> 8;
                data[8] = DEVICE_VER & 0xFF;
            }
            return false;
#    endif
        case KC_GET_PROTOCOL_VERSION:
            data[1] = PROTOCOL_VERSION;
            data[2] = 0;
            data[3] = QMK_COMMAND_SET;
            break;

        case KC_GET_FIRMWARE_VERSION:
            get_firmware_version(&data[1]);
            break;

        case KC_GET_SUPPORT_FEATURE:
            get_support_feature(&data[1]);
            break;

        case KC_GET_DEFAULT_LAYER:
            data[1] = get_highest_layer(default_layer_state);
            break;

        case KC_GET_BATTERY_LEVEL:
#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
            /* Report battery only when keyboard is actually on wireless connection */
            if (wireless_get_state() == WT_CONNECTED) {
                data[1] = battery_get_percentage();
            } else {
                data[1] = 0; /* On USB, no battery */
            }
#else
            data[1] = 0; /* Wireless not supported */
#endif
            break;

        case KC_MISC_CMD_GROUP:
            switch (data[1]) {
                case MISC_GET_PROTOCOL_VER:
                    data[2] = 0;
                    data[3] = MISC_PROTOCOL_VERSION & 0xFF;
                    data[4] = (MISC_PROTOCOL_VERSION >> 8) & 0xFF;
                    data[5] = MISC_DFU_INFO | MISC_LANGUAGE
#    ifdef DYNAMIC_DEBOUNCE_ENABLE
                              | MISC_DEBOUNCE
#    endif
#    if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
                              | MISC_SNAP_CLICK
#    endif
#    if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
                              | MISC_WIRELESS_LPM
#    endif
#    ifdef USB_REPORT_INTERVAL_ENABLE
                              | MISC_REPORT_REATE
#    endif
                              | MISC_QUICK_START
#    ifdef NKRO_ENABLE
                              | MISC_NKRO
#    endif
                        ;
                    break;

                case DFU_INFO_GET:
                    dfu_info_rx(data, length);
                    break;

                case LANGUAGE_GET ... LANGUAGE_SET:
                    language_rx(data, length);
                    break;

#    if defined(DYNAMIC_DEBOUNCE_ENABLE)
                case DEBOUNCE_GET ... DEBOUNCE_SET:
                    debounce_rx(data, length);
                    break;
#    endif
#    if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
                case SNAP_CLICK_GET_INFO ... SNAP_CLICK_SAVE:
                    snap_click_rx(data, length);
                    break;
#    endif
#    if (defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)) && defined(EECONFIG_BASE_WIRELESS_CONFIG)
                case WIRELESS_LPM_GET ... WIRELESS_LPM_SET:
                    wireless_raw_hid_rx(data, length);
                    break;
#    endif
#    if defined(USB_REPORT_INTERVAL_ENABLE)
                case REPORT_RATE_GET ... REPORT_RATE_SET: {
                    extern void report_rate_hid_rx(uint8_t * data, uint8_t length);
                    report_rate_hid_rx(data, length);
                } break;
#    endif
                case NKRO_GET ... NKRO_SET:
                    nkro_rx(data, length);
                    break;

                default:
                    data[0] = 0xFF;
                    data[1] = 0x00;
                    break;
            }
            break;

#    if defined(KEYCHRON_RGB_ENABLE)
        case 0xA8: {
            extern void kc_rgb_matrix_rx(bool usb, uint8_t *data, uint8_t length);
            kc_rgb_matrix_rx(src == RAW_HID_SRC_USB, data, length);
        } break;
#    endif

#    ifdef ANANLOG_MATRIX
        case 0xA9:
            analog_matrix_rx(data, length);
            return true;
#    endif
        case 0xAA:
            if (src == RAW_HID_SRC_USB) {
#    ifdef LK_WIRELESS_ENABLE
                lkbt51_dfu_rx(data, length);
                return true;
#    endif
#    ifdef KC_BLUETOOTH_ENABLE
                ckbt51_dfu_rx(data, length);
                return true;
#    endif
            }
#    ifdef FACTORY_TEST_ENABLE
        case 0xAB:
            factory_test_rx(src == RAW_HID_SRC_USB, data, length);
            return true;

#    endif
        default:
            return false;
    }

    /* Return true to indicate command was handled, caller decides whether to send response */
    return true;
}

#    if defined(VIA_ENABLE)
/* Override raw_hid_receive_kb to handle Keychron-specific commands */
/* VIA will send the response for us, so we just modify data[] */
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    /* Try to handle as Keychron command, if not handled set id_unhandled */
    if (!kc_raw_hid_rx(RAW_HID_SRC_USB, data, length)) {
        data[0] = 0xFF; /* id_unhandled */
    }
    /* Note: VIA's raw_hid_receive will call via_raw_hid_send after this returns */
}

/* Override default via_raw_hid_send implement */
void via_raw_hid_send(uint8_t src, uint8_t *data, uint8_t len) {
    kc_raw_hid_send(src, data, len);
}
#    else
void raw_hid_receive(uint8_t src, uint8_t *data, uint8_t length) {
    if (kc_raw_hid_rx(src, data, length)) {
        kc_raw_hid_send(src, data, length);
    }
}
#    endif
#endif
