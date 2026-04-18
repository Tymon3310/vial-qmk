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
#include <stdint.h>

typedef struct __attribute__((__packed__)) {
    uint8_t type;
    uint8_t key[2];
} snap_click_config_t;
// size  = 3 bytes

typedef union {
    uint8_t state;
    struct {
        uint8_t state_key_1 : 1;
        uint8_t state_key_2 : 1;
        uint8_t last_single_key_1 : 1;
        uint8_t last_single_key_2 : 1;
        uint8_t reserved : 4;
    };
    struct {
        uint8_t state_keys : 2;
        uint8_t last_single_key : 2;
        uint8_t reserved2 : 4;
    };
} snap_click_state_t;

void snap_click_config_reset(void);
void snap_click_rx(uint8_t *data, uint8_t length);
