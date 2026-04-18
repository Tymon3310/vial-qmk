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
#include <stdbool.h>
#include "matrix.h"

enum {
    DEBOUNCE_SYM_DEFER_GLOBAL,
    DEBOUNCE_SYM_DEFER_PER_ROW,
    DEBOUNCE_SYM_DEFER_PER_KEY,
    DEBOUNCE_SYM_EAGER_PER_ROW,
    DEBOUNCE_SYM_EAGER_PER_KEY,
    DEBOUNCE_ASYM_EAGER_DEFER_PER_KEY,
    DEBOUNCE_NONE,
    DEBOUNCE_MAX,
};

typedef struct {
    void (*debounce_init)(uint8_t);
    bool (*debounce)(matrix_row_t[], matrix_row_t[], uint8_t, bool);
    void (*debounce_free)(void);
} debounce_t;

/**
 * @brief Debounce raw matrix events according to the choosen debounce algorithm.
 *
 * @param raw The current key state
 * @param cooked The debounced key state
 * @param num_rows Number of rows to debounce
 * @param changed True if raw has changed since the last call
 * @return true Cooked has new keychanges after debouncing
 * @return false Cooked is the same as before
 */
bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

void debounce_init(uint8_t num_rows);
void debounce_config_reset(void);

void debounce_free(void);
void debounce_rx(uint8_t *data, uint8_t length);
