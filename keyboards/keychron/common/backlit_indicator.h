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

#if defined(LED_MATRIX_ENABLE) || defined(RGB_MATRIX_ENABLE)

#    ifdef LED_MATRIX_ENABLE
#        define LED_DRIVER led_matrix_driver
#        define LED_INDICATORS_USER led_matrix_indicators_user
#        define LED_NONE_INDICATORS_KB led_matrix_none_indicators_kb
#        define SET_ALL_LED_OFF() led_matrix_set_value_all(0)
#        define SET_LED_OFF(idx) led_matrix_set_value(idx, 0)
#        define SET_LED_ON(idx) led_matrix_set_value(idx, 255)
#        define LED_DRIVER_IS_ENABLED led_matrix_is_enabled
#        define LED_DRIVER_EECONFIG_RELOAD()                                                           \
            eeprom_read_block(&led_matrix_eeconfig, EECONFIG_LED_MATRIX, sizeof(led_matrix_eeconfig)); \
            if (!led_matrix_eeconfig.mode) {                                                           \
                eeconfig_update_led_matrix_default();                                                  \
            }

#        define LED_DRIVER_ENABLE_NOEEPROM led_matrix_enable_noeeprom
#        define LED_DRIVER_DISABLE_NOEEPROM led_matrix_disable_noeeprom

#    endif

#    ifdef RGB_MATRIX_ENABLE
#        define LED_DRIVER rgb_matrix_driver
#        define LED_INDICATORS_USER rgb_matrix_indicators_user
#        define LED_NONE_INDICATORS_KB rgb_matrix_none_indicators_kb
#        define SET_ALL_LED_OFF() rgb_matrix_set_color_all(0, 0, 0)
#        define SET_LED_OFF(idx) rgb_matrix_set_color(idx, 0, 0, 0)
#        define SET_LED_ON(idx) rgb_matrix_set_color(idx, 255, 255, 255)
#        define LED_DRIVER_IS_ENABLED rgb_matrix_is_enabled
#        define LED_DRIVER_EECONFIG_RELOAD()                                                       \
            eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); \
            if (!rgb_matrix_config.mode) {                                                         \
                eeconfig_update_rgb_matrix_default();                                              \
            }

#        define LED_DRIVER_ENABLE_NOEEPROM rgb_matrix_enable_noeeprom
#        define LED_DRIVER_DISABLE_NOEEPROM rgb_matrix_disable_noeeprom

#    endif

void os_state_indicate(void);
void indicator_enable(void);
void indicator_disable(void);
bool indicator_is_enabled(void);
void indicator_eeconfig_reload(void);

#    if defined(RGB_MATRIX_ENABLE)
void backlight_indicator_start(uint16_t on_time, uint16_t off_time, uint8_t repeat_count, RGB color);
#    else
void backlight_indicator_start(uint16_t on_time, uint16_t off_time, uint8_t repeat_count);
#    endif
void backlight_indicator_stop(void);
void backlit_indicator(void);
bool backlight_indicator_is_active(void);

void suspend_power_down_keychron_kb(void);
void suspend_wakeup_init_keychron_kb(void);
#endif
