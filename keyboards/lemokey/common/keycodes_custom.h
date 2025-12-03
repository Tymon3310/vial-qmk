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

#include "keycodes.h"

enum custom_keycodes {
    KC_WIN_TASK_VIEW = QK_KB_0,
    KC_WIN_FILE_EXPLORER,
    KC_WIN_LOCK_SCREEN,        // Lock screen
    KC_MAC_MISSION_CONTROL,
    KC_MAC_LAUCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
#ifdef LK_WIRELESS_ENABLE
    BT_HST1,
    BT_HST2,
    BT_HST3,
#if (defined(P24G_MODE_SELECT_PIN) || defined(KEYCOMBO_CONN_SWITCH_ENABLE)) && !defined(KC_BLUETOOTH_ENABLE)
    P2P4G,
    __P2P4G_NEXT,
#else
    __P2P4G_NEXT = BT_HST3 + 1,
#endif
    BAT_LVL = __P2P4G_NEXT,
    __BAT_LVL_NEXT = BAT_LVL + 1,
#else
    BT_HST1 = KC_NO,
    BT_HST2 = KC_NO,
    BT_HST3 = KC_NO,
    P2P4G   = KC_NO,
    BAT_LVL = KC_NO,
    __BAT_LVL_NEXT = KC_RCMMD + 1,
#endif
#ifdef ANANLOG_MATRIX
    PROF1 = __BAT_LVL_NEXT,
    PROF2,
    PROF3,
    __PROF3_NEXT,
#else
    __PROF3_NEXT = __BAT_LVL_NEXT,
#endif
    NEW_SAFE_RANGE = __PROF3_NEXT,
};

#define KC_TASK KC_WIN_TASK_VIEW
#define KC_FILE KC_WIN_FILE_EXPLORER
#define KC_WLCK KC_WIN_LOCK_SCREEN
#define KC_MCTRL KC_MAC_MISSION_CONTROL
#define KC_LNPAD KC_MAC_LAUCHPAD
