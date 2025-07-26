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

# Enable Vial-specific features
SNAP_CLICK_ENABLE = no
VIAL_TAP_DANCE_ENABLE = yes
VIAL_COMBO_ENABLE = yes
VIAL_KEY_OVERRIDE_ENABLE = yes

# Per-key RGB
RGB_MATRIX_ENABLE = yes
# Driver is already defined in the base keyboard config
# RGB_MATRIX_DRIVER = snled27351_spi

# Custom Debounce
DEBOUNCE_TYPE = sym_eager_pk

# Disable features to save space if needed
CONSOLE_ENABLE = no
