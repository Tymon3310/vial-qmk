#include QMK_KEYBOARD_H
#include "custom_eeconfig_kb.h"

// Define the snap click configuration
snap_click_config_t snap_click_config = {.enable               = 1, // Enabled by default
                                         .activation_threshold = 30,
                                         .db_threshold         = 5,
                                         .feedback_enable      = 1,
                                         .duration_ms          = 300};
