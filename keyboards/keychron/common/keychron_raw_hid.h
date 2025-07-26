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

#pragma once

#define PROTOCOL_VERSION 0x02
#define MISC_PROTOCOL_VERSION 0x0002
#define QMK_COMMAND_SET 2

enum {
    KC_GET_PROTOCOL_VERSION = 0xA0,
    KC_GET_FIRMWARE_VERSION = 0xA1,
    KC_GET_SUPPORT_FEATURE  = 0xA2,
    KC_GET_DEFAULT_LAYER    = 0xA3,
};

enum {
    FEATURE_DEFAULT_LAYER       = 0x01U << 0,
    FEATURE_BLUETOOTH           = 0x01U << 1,
    FEATURE_P24G                = 0x01U << 2,
    FEATURE_ANALOG_MATRIX       = 0x01U << 3,
    FEATURE_INFO_CHAGNED_NOTIFY = 0x01U << 4,
    FEATURE_DYNAMIC_DEBOUNCE    = 0x01U << 5,
    FEATURE_SNAP_CLICK          = 0x01U << 6,
    FEATURE_KEYCHRON_RGB        = 0x01U << 7,
};

enum {
    MISC_DFU_INFO     = 0x01 << 0,
    MISC_LANGUAGE     = 0x01 << 1,
    MISC_DEBOUNCE     = 0x01 << 2,
    MISC_SNAP_CLICK   = 0x01 << 3,
    MISC_WIRELESS_LPM = 0x01 << 4,
    MISC_REPORT_REATE = 0x01 << 5,
};

enum {
    MISC_GET_PROTOCOL_VER = 0x01,
    DFU_INFO_GET,
    LANGUAGE_GET,
    LANGUAGE_SET,
    DEBOUNCE_GET, // 5
    DEBOUNCE_SET,
    SNAP_CLICK_GET_INFO,
    SNAP_CLICK_GET,
    SNAP_CLICK_SET,
    SNAP_CLICK_SAVE, // A
    WIRELESS_LPM_GET,
    WIRELESS_LPM_SET,
    REPORT_RATE_GET,
    REPORT_RATE_SET,
};
