/* Copyright 2025 @ lokher (https://www.keychron.com)
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

#include "wireless.h"
#include "transport.h"
#include "keychron_wireless_common.h"
#include "battery.h"
#include "bat_level_animation.h"
#include "indicator.h"
#include "lpm.h"

#ifdef WIRELESS_ENABLE
#    include "lkbt51.h"
#endif

#ifdef KC_BLUETOOTH_ENABLE
#    include "ckbt51.h"
#endif
