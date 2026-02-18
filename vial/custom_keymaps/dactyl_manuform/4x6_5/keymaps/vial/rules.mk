# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
NKRO_ENABLE = no           # Enable N-Key Rollover

MOUSEKEY_ENABLE = no        # Disable mouse keys to save space
SPACE_CADET_ENABLE = no     # Disable Space Cadet Shift
MAGIC_ENABLE = no           # Disable Magic keycodes
GRAVE_ESC_ENABLE = no       # Disable Grave Escape

EXTRAKEY_ENABLE = no       # Audio control and System control
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration

BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Split keyboard
SPLIT_KEYBOARD = yes
# I2C is configured in config.h with USE_I2C

# Vial support
VIA_ENABLE = yes
VIAL_ENABLE = yes

# Reduce firmware size
LTO_ENABLE = yes
