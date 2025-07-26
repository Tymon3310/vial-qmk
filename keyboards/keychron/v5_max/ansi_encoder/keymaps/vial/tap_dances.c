#include QMK_KEYBOARD_H
#include "tap_dance.h"

// Initialize a global to track the tap dance state
typedef enum { TD_NONE, TD_SINGLE_TAP, TD_DOUBLE_TAP, TD_TRIPLE_TAP } td_state_t;

// Example tap dance state
static td_state_t tap_state = TD_NONE;

// Example tap dance function - this will be available in Vial
void example_tap_dance(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_state = TD_SINGLE_TAP;
    } else if (state->count == 2) {
        tap_state = TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        tap_state = TD_TRIPLE_TAP;
    }
}

// Define a sample tap dance
tap_dance_action_t tap_dance_actions[] = {[0] = ACTION_TAP_DANCE_FN(example_tap_dance)};
