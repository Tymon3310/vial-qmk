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

#include "rgb_matrix_kb_config.h"

#define OS_INDICATOR_CONFIG_SIZE 4 // sizeof(os_indicator_config_t)

#define RETAIL_DEMO_SIZE 1  // sizeof(retail_demo_enable)

#define PER_KEY_RGB_TYPE_SIZE 1
#define PER_KEY_RGB_LED_COLOR_LIST_SIZE (RGB_MATRIX_LED_COUNT * 3)

#define MIX_RGB_LAYER_FLAG_SIZE RGB_MATRIX_LED_COUNT
#define EFFECT_CONFIG_SIZE 8 // sizeof(effect_config_t)
#define EFFECT_LIST_SIZE (EFFECT_LAYERS * EFFECTS_PER_LAYER * EFFECT_CONFIG_SIZE)

// Clang-format off
#define EECONFIG_SIZE_CUSTOM_RGB (  \
      OS_INDICATOR_CONFIG_SIZE \
    + RETAIL_DEMO_SIZE \
    + PER_KEY_RGB_TYPE_SIZE \
    + PER_KEY_RGB_LED_COLOR_LIST_SIZE \
    + MIX_RGB_LAYER_FLAG_SIZE \
    + EFFECT_LIST_SIZE)
