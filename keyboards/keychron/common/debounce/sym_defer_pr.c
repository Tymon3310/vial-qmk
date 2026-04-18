/*
Copyright 2021 Chad Austin <chad@chadaustin.me>
Copyright 2024 ~ 2025 @ keychron (https://www.keychron.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*
Symmetric per-row debounce algorithm. Changes only apply when
DEBOUNCE milliseconds have elapsed since the last change.
*/

#include "debounce.h"
#include "timer.h"
#include <stdlib.h>

extern uint8_t debounce_time;

static uint16_t last_time;
// [row] milliseconds until key's state is considered debounced.
static uint8_t* countdowns = NULL;
// [row]
static matrix_row_t* last_raw = NULL;

void sym_defer_pr_debounce_init(uint8_t num_rows) {
    countdowns = (uint8_t*)calloc(num_rows, sizeof(uint8_t));
    last_raw   = (matrix_row_t*)calloc(num_rows, sizeof(matrix_row_t));
    last_time  = timer_read();
}

void sym_defer_pr_debounce_free(void) {
    if (countdowns != NULL) {
        free(countdowns);
        countdowns = NULL;
    }
    if (last_raw != NULL) {
        free(last_raw);
        last_raw = NULL;
    }
}

bool sym_defer_pr_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    uint16_t now           = timer_read();
    uint16_t elapsed16     = TIMER_DIFF_16(now, last_time);
    last_time              = now;
    uint8_t elapsed        = (elapsed16 > 255) ? 255 : elapsed16;
    bool    cooked_changed = false;

    uint8_t* countdown = countdowns;

    for (uint8_t row = 0; row < num_rows; ++row, ++countdown) {
        matrix_row_t raw_row = raw[row];

        if (raw_row != last_raw[row]) {
            *countdown    = debounce_time;
            last_raw[row] = raw_row;
        } else if (*countdown > elapsed) {
            *countdown -= elapsed;
        } else if (*countdown) {
            cooked_changed |= cooked[row] ^ raw_row;
            cooked[row] = raw_row;
            *countdown  = 0;
        }
    }

    return cooked_changed;
}

bool debounce_active(void) {
    return true;
}
