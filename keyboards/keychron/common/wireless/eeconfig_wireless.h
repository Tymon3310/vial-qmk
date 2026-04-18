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

#pragma once

#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
#    define EECONFIG_SIZE_TRANSPORT 1
#else
#    define EECONFIG_SIZE_TRANSPORT 0
#endif

// EECONFIG_SIZE_TRANSPORT = sizeof(backlit_disable_time) + sizeof (connected_idle_time) = 4
#define EECONFIG_SIZE_WIRELESS_CONFIG    (4 + EECONFIG_SIZE_TRANSPORT)

#ifdef KEYCOMBO_CONN_SWITCH_ENABLE
#    define OFFSET_TRANSPORT    4
#endif
