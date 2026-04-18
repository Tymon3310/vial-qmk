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

#include <string.h>
#include "quantum.h"
#include "keychron_raw_hid.h"

void nkro_rx(uint8_t *data, uint8_t length) {
    if (data[0] != KC_MISC_CMD_GROUP) return;

    uint8_t cmd = data[1];
    switch (cmd) {
        case NKRO_GET:
            data[2] = KC_SUCCESS;
            data[3] = ((keymap_config.nkro ? 0x01 : 0x00) << 0)
#if defined(NKRO_ENABLE) && !defined(APDAPTIVE_NKRO_ENABLE)
                      | (0x01 << 1)
#endif
#ifdef APDAPTIVE_NKRO_ENABLE
                      | (0x01 << 2)
#endif
                      ;
            break;

        case NKRO_SET:
            if (data[2] > 1) {
                data[2] = KC_FAIL;
            } else {
#if defined(NKRO_ENABLE) && !defined(APDAPTIVE_NKRO_ENABLE)
                keymap_config.nkro = data[2];
                eeconfig_update_keymap(keymap_config.raw);
                data[2] = KC_SUCCESS;
#else
                data[2] = KC_FAIL;
#endif
            }
            break;

        default:
            data[0] = 0xFF;
            break;
    }
}
