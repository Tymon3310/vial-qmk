
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

#include "keychron_debounce.h"
#include "eeprom.h"
#include "raw_hid.h"
#include "quantum.h"
#include "eeconfig.h"
#include "eeconfig_kb.h"
#include "keychron_raw_hid.h"

#ifdef SPLIT_KEYBOARD
#    pragma(error "Split keyboard is not supported")
#endif

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

// Maximum debounce: 255ms
#if DEBOUNCE > UINT8_MAX
#    undef DEBOUNCE
#    define DEBOUNCE UINT8_MAX
#endif

#ifndef DEFAULT_DEBOUNCE_TYPE
#    define DEFAULT_DEBOUNCE_TYPE DEBOUNCE_SYM_EAGER_PER_KEY
#endif

#define DEBOUNCE_SET_QMK 0
#define OFFSET_DEBOUNCE ((uint8_t *)(EECONFIG_BASE_DYNAMIC_DEBOUNCE))

static uint8_t    debounce_type = 0;
uint8_t           debounce_time = 0;
static debounce_t debounce_func = {NULL, NULL, NULL};

extern void sym_defer_g_debounce_init(uint8_t num_rows);
extern bool sym_defer_g_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void sym_defer_g_debounce_free(void);

extern void sym_defer_pr_debounce_init(uint8_t num_rows);
extern bool sym_defer_pr_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void sym_defer_pr_debounce_free(void);

extern void sym_defer_pk_debounce_init(uint8_t num_rows);
extern bool sym_defer_pk_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void sym_defer_pk_debounce_free(void);

extern void sym_eager_pr_debounce_init(uint8_t num_rows);
extern bool sym_eager_pr_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void sym_eager_pr_debounce_free(void);

extern void sym_eager_pk_debounce_init(uint8_t num_rows);
extern bool sym_eager_pk_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void sym_eager_pk_debounce_free(void);

extern void asym_eager_defer_pk_debounce_init(uint8_t num_rows);
extern bool asym_eager_defer_pk_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void asym_eager_defer_pk_debounce_free(void);

extern void none_debounce_init(uint8_t num_rows);
extern bool none_debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);
extern void none_debounce_free(void);

void debounce_set(uint8_t new_debounce_type, uint8_t time, bool force);

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

bool debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    if (debounce_func.debounce) debounce_func.debounce(raw, cooked, num_rows, changed);

    return false;
}

void debounce_init(uint8_t num_rows) {
    debounce_type = 0;

    // debounce_set(DEBOUNCE_SYM_EAGER_PER_KEY, DEBOUNCE);
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    uint8_t type = eeprom_read_byte(OFFSET_DEBOUNCE);
    uint8_t time = eeprom_read_byte(OFFSET_DEBOUNCE + 1);

    if (type >= DEBOUNCE_MAX) type = DEFAULT_DEBOUNCE_TYPE;

    debounce_set(type, time, debounce_type == type);
}

void debounce_free(void) {
    if (debounce_func.debounce_free) debounce_func.debounce_free();
}

static bool debounce_save(void) {
    eeprom_update_byte(OFFSET_DEBOUNCE, debounce_type);
    eeprom_update_byte(OFFSET_DEBOUNCE + 1, debounce_time);
    return true;
}

void debounce_config_reset(void) {
    debounce_set(DEFAULT_DEBOUNCE_TYPE, DEBOUNCE, true);
    debounce_save();
}

void debounce_set(uint8_t new_debounce_type, uint8_t time, bool force) {
    if (new_debounce_type == debounce_type && time == debounce_time && !force) return;

    debounce_free();

    debounce_type = new_debounce_type;
    debounce_time = time;

    if (debounce_time == 0) new_debounce_type = DEBOUNCE_NONE;

    switch (new_debounce_type) {
        case DEBOUNCE_SYM_DEFER_GLOBAL:
            debounce_func.debounce_init = sym_defer_g_debounce_init;
            debounce_func.debounce      = sym_defer_g_debounce;
            debounce_func.debounce_free = sym_defer_g_debounce_free;
            break;

        case DEBOUNCE_SYM_DEFER_PER_ROW:
            debounce_func.debounce_init = sym_defer_pr_debounce_init;
            debounce_func.debounce      = sym_defer_pr_debounce;
            debounce_func.debounce_free = sym_defer_pr_debounce_free;
            break;

        case DEBOUNCE_SYM_DEFER_PER_KEY:
            debounce_func.debounce_init = sym_defer_pk_debounce_init;
            debounce_func.debounce      = sym_defer_pk_debounce;
            debounce_func.debounce_free = sym_defer_pk_debounce_free;
            break;

        case DEBOUNCE_SYM_EAGER_PER_ROW:
            debounce_func.debounce_init = sym_eager_pr_debounce_init;
            debounce_func.debounce      = sym_eager_pr_debounce;
            debounce_func.debounce_free = sym_eager_pr_debounce_free;
            break;

        case DEBOUNCE_SYM_EAGER_PER_KEY:
            debounce_func.debounce_init = sym_eager_pk_debounce_init;
            debounce_func.debounce      = sym_eager_pk_debounce;
            debounce_func.debounce_free = sym_eager_pk_debounce_free;
            break;

        case DEBOUNCE_ASYM_EAGER_DEFER_PER_KEY:
            debounce_func.debounce_init = asym_eager_defer_pk_debounce_init;
            debounce_func.debounce      = asym_eager_defer_pk_debounce;
            debounce_func.debounce_free = asym_eager_defer_pk_debounce_free;
            if (debounce_time > 127) debounce_time = 127;
            break;

        case DEBOUNCE_NONE:
            debounce_func.debounce_init = none_debounce_init;
            debounce_func.debounce      = none_debounce;
            debounce_func.debounce_free = none_debounce_free;
            break;
    }

    if (debounce_func.debounce_init) debounce_func.debounce_init(MATRIX_ROWS);
}

void debounce_time_set(uint8_t time) {
    debounce_time = time;
}

void debounce_rx(uint8_t *data, uint8_t length) {
    uint8_t cmd = data[1];
    switch (cmd) {
        case DEBOUNCE_GET:
            data[2] = 0;
            data[3] = DEBOUNCE_SET_QMK;
            data[4] = debounce_type;
            data[5] = debounce_time;
            break;

        case DEBOUNCE_SET: {
            uint8_t type = data[2];
            uint8_t time = data[3];
            if (type < DEBOUNCE_MAX) {
                data[2] = 0;
                debounce_set(type, time, false);
                debounce_save();
            } else
                data[2] = 1;
        } break;

        default:
            data[0] = 0xFF;
            break;
    }
}
