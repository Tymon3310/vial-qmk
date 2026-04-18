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
#include "game_controller_common.h"
//#include "eeconfig.h"
#include "eeprom.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "analog_matrix.h"

uint8_t      game_controller_mode;
point_t      curve[CURVE_POINTS_COUNT];
float        slope[CURVE_POINTS_COUNT - 1];
matrix_row_t game_controller_matrix[MATRIX_ROWS] = {0};

void game_controller_curve_init(point_t *pt) {
    memcpy(curve, pt, CURVE_POINTS_COUNT * SIZE_OF_POINT_T);

    if (curve[0].y == 0 && curve[1].y == 0 && curve[2].y == 0 && curve[3].y == 0) {
        point_t default_curve[CURVE_POINTS_COUNT] = {{0, 0}, {10, 31}, {30, 95}, {40, 127}};
        memcpy(curve, default_curve, sizeof(default_curve));
        slope[0] = slope[1] = slope[2] = 3.175f;
    }
}

void game_controller_mode_init(uint8_t mode) {
    game_controller_mode = mode;
}

bool game_controller_mode_get(uint8_t *data) {
    data[1] = game_controller_mode;
    return true;
}

bool game_controller_mode_set(uint8_t mode) {
    if (game_controller_mode == mode) return false;

    game_controller_mode = mode;

    // Save
    if (!eeconfig_is_kb_datablock_valid()) eeprom_update_dword(EECONFIG_KEYBOARD, (EECONFIG_KB_DATA_VERSION));

    analog_matrix_eeprom_update(&game_controller_mode, (uint8_t *)OFFSET_GAME_CONTROLLER_MODE_START, 1);
    // usbDisconnectBus(&USBD1);
    // usbStop(&USBD1);
    // wait_ms(1000);
    // usb_start(&USBD1);

    return true;
}

bool game_controller_set_curve(point_t *pt) {
    if (curve[0].x > curve[1].x || curve[1].x > curve[2].x || curve[2].x > curve[3].x) return false;

    memcpy(curve, pt, sizeof(curve));
    if (curve[0].x != curve[1].x) slope[0] = (float)(curve[1].y - curve[0].y) / (curve[1].x - curve[0].x);
    if (curve[1].x != curve[2].x) slope[1] = (float)(curve[2].y - curve[1].y) / (curve[2].x - curve[1].x);
    if (curve[2].x != curve[3].x) slope[2] = (float)(curve[3].y - curve[2].y) / (curve[3].x - curve[2].x);

    analog_matrix_eeprom_update(curve, (uint8_t *)OFFSET_CURVE_PTS_START, CURVE_POINTS_COUNT * SIZE_OF_POINT_T);

    return true;
}

bool game_controller_get_curve(uint8_t *data) {
    memcpy(data, curve, sizeof(curve));
    return true;
}

bool game_controller_xinput_enabled(void) {
    return game_controller_mode & GC_MASK_XINPUT;
}

bool game_controller_type_enabled(void) {
    return game_controller_mode & GC_MASK_TYPING;
}

void game_controller_clear(void) {
    memset(game_controller_matrix, 0, sizeof(game_controller_matrix));

#ifdef JOYSTICK_ENABLE
#    ifdef XINPUT_ENABLE
    if (!game_controller_xinput_enabled())
#    endif
    {
        extern void joystick_clear(void);
        joystick_clear();
    }
#endif
#ifdef XINPUT_ENABLE
#    ifdef JOYSTICK_ENABLE
    if (game_controller_xinput_enabled())
#    endif
    {
        extern void xinput_clear(void);
        xinput_clear();
    }
#endif
}
