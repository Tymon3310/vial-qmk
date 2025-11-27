/* Copyright 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "keychron_common.h"
#include "keychron_task.h"
#include "backlit_indicator.h"

#ifdef LANGUAGE_ENABLE
#    include "language.h"
#endif

#if defined(SNAP_CLICK_ENABLE) && !defined(ANANLOG_MATRIX)
#    include "snap_click.h"
#endif

#ifdef ANALOG_MATRIX_ENABLE
#    include "analog_matrix.h"
#    include "profile.h"
#endif

#if defined(LK_WIRELESS_ENABLE) || defined(KC_BLUETOOTH_ENABLE)
#    include "wireless_include.h"
#endif

#ifdef STATE_NOTIFY_ENABLE
#    include "state_notify.h"
#endif

#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
