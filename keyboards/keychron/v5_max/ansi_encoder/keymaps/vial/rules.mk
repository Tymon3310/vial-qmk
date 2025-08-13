VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
QMK_SETTINGS = yes
# VIAL_INSECURE = yes

# Custom Keycodes
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
REPEAT_KEY_ENABLE = yes
KEY_LOCK_ENABLE = yes
# DEFERRED_EXEC_ENABLE = yes # Commented out due to linking error

# Enable additional QMK features
MAGIC_ENABLE = yes        # Magic keycodes
GRAVE_ESC_ENABLE = yes    # Grave Escape
COMBO_ENABLE = yes        # Key combos
MOUSEKEY_ENABLE = yes     # Mouse keys
AUTO_SHIFT_ENABLE = yes   # Auto Shift
ONESHOT_ENABLE = yes      # One-shot keys
SWAP_HANDS_ENABLE = yes   # Enable swap-hands feature


# Enable QMK Settings features
QMK_SETTINGS = yes
CHORDING_ENABLE = yes  # Enable Chordal Hold
FLOW_TAP_ENABLE = yes  # Enable Flow Tap

# Enable Vial-specific features
VIAL_TAP_DANCE_ENABLE = yes
VIAL_COMBO_ENABLE = yes
VIAL_KEY_OVERRIDE_ENABLE = yes

# Per-key RGB - re-enabled
RGB_MATRIX_ENABLE = yes
# Driver is already defined in the base keyboard config
RGB_MATRIX_DRIVER = snled27351_spi

# Custom Debounce
DEBOUNCE_TYPE = sym_eager_pk

# Disable features to save space if needed
CONSOLE_ENABLE = no
LTO_ENABLE = yes