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

#include <string.h>
#include "quantum.h"

enum {
    DFU_INFO_CHIP = 1,
    DFU_INFO_TYPE,
};

enum {
    BL_TYPE_STM32 = 1,
    BL_TYPE_WB32,
};

void dfu_info_rx(uint8_t *data, uint8_t length) {
    uint8_t i = 2;

    data[i++] = 0;  // success
    data[i++] = DFU_INFO_CHIP;
    data[i++] = strlen(STR(QMK_MCU));
    memcpy(&data[i], STR(QMK_MCU), strlen(STR(QMK_MCU)));
    i += strlen(STR(QMK_MCU));
    data[i++] = DFU_INFO_TYPE;
    data[i++] = 1;
    data[i++] =
#if defined(BOOTLOADER_STM32_DFU)
    BL_TYPE_STM32
#elif defined(BOOTLOADER_WB32_DFU)
    BL_TYPE_WB32
#else
    0
#endif
    ;
}
