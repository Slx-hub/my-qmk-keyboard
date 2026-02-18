#pragma once

/* Split keyboard configuration */
#define EE_HANDS

/* I2C communication for split (faster and more reliable than serial) */
#define USE_I2C
#define I2C1_SDA_PIN D1          // Pin 2 on Pro Micro (SDA)
#define I2C1_SCL_PIN D0          // Pin 3 on Pro Micro (SCL)

/* Debug output for split keyboard */
#define DEBUG_MATRIX_SCAN_RATE
#define SPLIT_MAX_CONNECTION_ERRORS 100  // Increased tolerance
#define SPLIT_CONNECTION_CHECK_TIMEOUT 2000  // Longer timeout

/* Vial-specific configuration */

// Unique 8-byte identifier for your keyboard (change this to something unique!)
#define VIAL_KEYBOARD_UID {0x73, 0x6c, 0x61, 0x6b, 0x78, 0x73, 0x69, 0x69}

// Unlock combo: keys you must press together to unlock Vial configuration
// These are matrix positions [row, col]
// Example: top-left key (0,0) and top-right key (0,5)
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }

/* Firmware size reduction */

// How many layers you can configure in Vial (default is often 8+)
// 4 layers = Base, Function, Symbols, Special
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// Disable insecure features that take up space
#undef VIAL_INSECURE
