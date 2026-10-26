/* Copyright 2021 ~ 2025 @ Keychron (https://www.keychron.com)
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

/* Without the knob, cols 10 (A2) and 19 (C14) are GPIO pins and only
 * cols 11-18 are on the shift register. v6/config.h sets 10-19 for the
 * knob layouts. */
#undef HC595_START_INDEX
#undef HC595_END_INDEX
#define HC595_START_INDEX 11
#define HC595_END_INDEX 18

/* Indications */
#define CAPS_LOCK_LED_INDEX 60
#define NUM_LOCK_LED_INDEX 37
