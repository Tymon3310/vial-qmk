/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
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

#include "eeconfig_language.h"

#define EECONFIG_BASE_LANGUAGE 37
#define EECONFIG_END_LANGUAGE (EECONFIG_BASE_LANGUAGE + EECONFIG_SIZE_LANGUAGE)

#if defined(USB_REPORT_INTERVAL_ENABLE)
#    define __EECONFIG_SIZE_HSUSB_REPORT_RATE 1
#else
#    define __EECONFIG_SIZE_HSUSB_REPORT_RATE 0
#endif
#define EECONFIG_BASE_HSUSB_REPORT_RATE EECONFIG_END_LANGUAGE
#define EECONFIG_END_HSUSB_REPORT_RATE (EECONFIG_BASE_HSUSB_REPORT_RATE + __EECONFIG_SIZE_HSUSB_REPORT_RATE)

#ifdef DYNAMIC_DEBOUNCE_ENABLE
#    include "eeconfig_debounce.h"
#    define __EECONFIG_SIZE_DEBOUNCE EECONFIG_SIZE_DEBOUNCE
#else
#    define __EECONFIG_SIZE_DEBOUNCE 0
#endif
#define EECONFIG_BASE_DYNAMIC_DEBOUNCE EECONFIG_END_HSUSB_REPORT_RATE
#define EECONFIG_END_DYNAMIC_DEBOUNCE (EECONFIG_BASE_DYNAMIC_DEBOUNCE + __EECONFIG_SIZE_DEBOUNCE)

#if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
#    include "eeconfig_snap_click.h"
#    define __EECONFIG_SIZE_SNAP_CLICK EECONFIG_SIZE_SNAP_CLICK
#else
#    define __EECONFIG_SIZE_SNAP_CLICK 0
#endif
#define EECONFIG_BASE_SNAP_CLICK (EECONFIG_END_DYNAMIC_DEBOUNCE)
#define EECONFIG_END_SNAP_CLICK (EECONFIG_BASE_SNAP_CLICK + __EECONFIG_SIZE_SNAP_CLICK)

#ifdef ANANLOG_MATRIX
#    include "analog_matrix_eeconfig.h"
#    define __EECONFIG_SIZE_ANALOG_MATRIX EECONFIG_SIZE_ANALOG_MATRIX
#else
#    define __EECONFIG_SIZE_ANALOG_MATRIX 0
#endif
#define EECONFIG_BASE_ANALOG_MATRIX EECONFIG_END_SNAP_CLICK
#define EECONFIG_END_ANALOG_MATRIX (EECONFIG_BASE_ANALOG_MATRIX + __EECONFIG_SIZE_ANALOG_MATRIX)

#if defined(KEYCHRON_RGB_ENABLE) && defined(RGB_MATRIX_ENABLE)
#    include "eeconfig_custom_rgb.h"
#    define __EECONFIG_SIZE_CUSTOM_RGB EECONFIG_SIZE_CUSTOM_RGB
#else
#    define __EECONFIG_SIZE_CUSTOM_RGB 0
#endif
#define EECONFIG_BASE_CUSTOM_RGB EECONFIG_END_ANALOG_MATRIX
#define EECONFIG_END_CUSTOM_RGB (EECONFIG_BASE_CUSTOM_RGB + __EECONFIG_SIZE_CUSTOM_RGB)

#if defined(WIRELESS_CONFIG_ENABLE)
#    include "eeconfig_wireless.h"
#    define __EECONFIG_SIZE_WIRELESS_CONFIG EECONFIG_SIZE_WIRELESS_CONFIG
#else
#    define __EECONFIG_SIZE_WIRELESS_CONFIG 0
#endif
#define EECONFIG_BASE_WIRELESS_CONFIG EECONFIG_END_CUSTOM_RGB
#define EECONFIG_END_WIRELESS_CONFIG (EECONFIG_BASE_WIRELESS_CONFIG + __EECONFIG_SIZE_WIRELESS_CONFIG)

#define EECONFIG_KB_DATA_SIZE (EECONFIG_END_WIRELESS_CONFIG - EECONFIG_BASE_LANGUAGE)
