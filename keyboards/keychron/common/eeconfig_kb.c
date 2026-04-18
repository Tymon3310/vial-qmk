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

#include "eeconfig_kb.h"
#ifdef DYNAMIC_DEBOUNCE_ENABLE
#    include "keychron_debounce.h"
#endif

void eeconfig_init_kb_datablock(void) {
#ifdef DYNAMIC_DEBOUNCE_ENABLE
    extern void debounce_config_reset(void);
    debounce_config_reset();
#endif
#if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
    extern void snap_click_config_reset(void);
    snap_click_config_reset();
#endif
#if defined(KEYCHRON_RGB_ENABLE) && defined(RGB_MATRIX_ENABLE)
    extern void eeconfig_reset_custom_rgb(void);
    eeconfig_reset_custom_rgb();
#endif
#if defined(USB_REPORT_INTERVAL_ENABLE)
    extern void report_rate_reset(void);
    report_rate_reset();
#endif
}
