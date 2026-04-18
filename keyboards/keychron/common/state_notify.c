/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "keychron_raw_hid.h"
#include "raw_hid.h"
#include "usb_descriptor.h"

layer_state_t default_layer_state_set_kb(layer_state_t state) {
#ifdef RAW_ENABLE
    uint8_t buf[RAW_EPSIZE] = {0};

    buf[0] = KC_GET_DEFAULT_LAYER;
    buf[1] = get_highest_layer(state);

    raw_hid_send(buf, RAW_EPSIZE);
#endif
    return default_layer_state_set_user(state);
}

void factory_reset_nofity(void) {
#ifdef RAW_ENABLE
    uint8_t buf[RAW_EPSIZE] = {0};

    buf[0] = KC_MISC_CMD_GROUP;
    buf[1] = FACTORY_RESET;

    raw_hid_send(buf, RAW_EPSIZE);
#endif
}

#ifdef USB_REPORT_INTERVAL_ENABLE
void usb_report_rate_notify(uint8_t report_rate_div) {
#    ifdef RAW_ENABLE
    uint8_t buf[RAW_EPSIZE] = {0};

    buf[0] = KC_MISC_CMD_GROUP;
    buf[1] = REPORT_RATE_GET;
    buf[2] = 0;
    buf[3] = report_rate_div;
    buf[4] = 0x7F;

    raw_hid_send(buf, RAW_EPSIZE);
#    endif
}
#endif
