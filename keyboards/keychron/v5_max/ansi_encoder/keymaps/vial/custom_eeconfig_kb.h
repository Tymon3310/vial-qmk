#pragma once

/**
 * Custom keyboard eeprom configuration
 * This file defines keyboard-specific EEPROM settings for Vial
 */

// Snap click configuration
typedef union {
    uint32_t raw;
    struct {
        uint8_t  enable : 1;
        uint8_t  activation_threshold : 7;
        uint8_t  db_threshold : 7;
        uint8_t  feedback_enable : 1;
        uint16_t duration_ms;
    };
} snap_click_config_t;
