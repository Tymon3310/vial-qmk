/* Copyright 2025 @ Keychron (https://www.keychron.com)
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

#ifdef USB_REPORT_INTERVAL_ENABLE

#    include <string.h>
#    include "eeconfig_kb.h"
#    include "raw_hid.h"
#    include "eeconfig.h"
#    include "quantum.h"
#    include "keychron_raw_hid.h"
#    include "usb_endpoints.h"
#    include "backlit_indicator.h"
#    include "eeprom.h"
#    include "state_notify.h"

enum {
    KEY_RATE_PRESS_FN     = 0x01 << 0,
    KEY_RATE_PRESS_SELECT = 0x01 << 1,
    KEY_RATE_PRESS_1K     = 0x01 << 2,
    KEY_RATE_PRESS_2K     = 0x01 << 3,
    KEY_RATE_PRESS_4K     = 0x01 << 4,
    KEY_RATE_PRESS_8K     = 0x01 << 5,
    KEY_RATE_COMBO_1K     = KEY_RATE_PRESS_FN | KEY_RATE_PRESS_SELECT | KEY_RATE_PRESS_1K,
    KEY_RATE_COMBO_4K     = KEY_RATE_PRESS_FN | KEY_RATE_PRESS_SELECT | KEY_RATE_PRESS_4K,
    KEY_RATE_COMBO_8K     = KEY_RATE_PRESS_FN | KEY_RATE_PRESS_SELECT | KEY_RATE_PRESS_8K,
};

static uint8_t report_rate_div   = 0;
static uint8_t report_rate_combo = 0;

void report_rate_update_interval(void) {
    extern void update_usb_report_interval(USBDriver * usbp, uint8_t interval);
    update_usb_report_interval(&USB_DRIVER, (0x01U << report_rate_div) - 1);
}

void report_rate_reset(void) {
    report_rate_div = 3;
    eeprom_update_byte((uint8_t *)(EECONFIG_BASE_HSUSB_REPORT_RATE), report_rate_div);
    report_rate_update_interval();
}

void report_rate_init(void) {
    report_rate_div = 3;

    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    report_rate_div = eeprom_read_byte((uint8_t *)(EECONFIG_BASE_HSUSB_REPORT_RATE));
    if (report_rate_div > 6) report_rate_div = 0;

    report_rate_update_interval();
}

static bool report_rate_get(uint8_t *data) {
    data[1] = report_rate_div;
    data[2] = 0x7F;
    return true;
}

static bool report_rate_set(uint8_t *data, bool notify) {
    if (data[0] > 6) return false;

    report_rate_div = data[0];
    eeprom_update_byte((uint8_t *)(EECONFIG_BASE_HSUSB_REPORT_RATE), report_rate_div);
    report_rate_update_interval();

#    ifdef STATE_NOTIFY_ENABLE
    if (notify) {
        usb_report_rate_notify(report_rate_div);
    }
#    endif
    (void)notify;

    return true;
}

void report_rate_hid_rx(uint8_t *data, uint8_t length) {
    uint8_t cmd     = data[1];
    bool    success = true;

    switch (cmd) {
        case REPORT_RATE_GET:
            success = report_rate_get(&data[2]);
            break;

        case REPORT_RATE_SET:
            success = report_rate_set(&data[2], false);
            break;

        default:
            data[0] = 0xFF;
            break;
    }

    data[2] = success ? 0 : 1;
}

#if defined(KEY_RATE_1K) && defined(KEY_RATE_4K) && defined(KEY_RATE_8K) && defined(KEY_RATE_SELECT)
__attribute__((weak)) void report_rate_indicator_set(uint8_t report_rate) {
#    ifdef RGB_MATRIX_ENABLE
    RGB color = {.r = 0, .g = 0, .b = 0};

    switch (report_rate) {
        case 0: // 8K
            color.r = 255;
            break;
        case 1: // 4K
            color.b = 255;
            break;
        case 3: // 1K
            color.g = 255;
            break;
    }
    backlight_indicator_start(250, 250, 3, color);
#    endif
}
#endif

bool process_record_report_rate(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(1)... MO(15):
            if (record->event.pressed) {
                report_rate_combo |= KEY_RATE_PRESS_FN;
            } else {
                report_rate_combo &= ~KEY_RATE_PRESS_FN;
            }
            break;
#if defined(KEY_RATE_1K) && defined(KEY_RATE_4K) && defined(KEY_RATE_8K) && defined(KEY_RATE_SELECT)
        case KEY_RATE_SELECT:
            if (record->event.pressed) {
                report_rate_combo |= KEY_RATE_PRESS_SELECT;
                if (report_rate_combo & KEY_RATE_PRESS_FN) return false;
            } else {
                report_rate_combo &= ~KEY_RATE_PRESS_SELECT;
            }
            break;

        case KEY_RATE_1K:
            if (record->event.pressed) {
                report_rate_combo |= KEY_RATE_PRESS_1K;

                if (report_rate_combo == KEY_RATE_COMBO_1K) {
                    uint8_t report_rate = 3;
                    report_rate_set(&report_rate, true);
                    report_rate_indicator_set(report_rate);
                    return false;
                }
            } else {
                report_rate_combo &= ~KEY_RATE_PRESS_1K;
            }
            break;

        case KEY_RATE_4K:
            if (record->event.pressed) {
                report_rate_combo |= KEY_RATE_PRESS_4K;

                if (report_rate_combo == KEY_RATE_COMBO_4K) {
                    uint8_t report_rate = 1;
                    report_rate_set(&report_rate, true);
                    report_rate_indicator_set(report_rate);
                    return false;
                }
            } else {
                report_rate_combo &= ~KEY_RATE_PRESS_4K;
            }
            break;

        case KEY_RATE_8K:
            if (record->event.pressed) {
                report_rate_combo |= KEY_RATE_PRESS_8K;

                if (report_rate_combo == KEY_RATE_COMBO_8K) {
                    uint8_t report_rate = 0;
                    report_rate_set(&report_rate, true);
                    report_rate_indicator_set(report_rate);
                    return false;
                }
            } else {
                report_rate_combo &= ~KEY_RATE_PRESS_8K;
            }
            break;
#endif
        default:break;
    }

    return true;
}
#endif
