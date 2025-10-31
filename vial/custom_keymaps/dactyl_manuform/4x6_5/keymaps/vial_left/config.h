#pragma once

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
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// Tap Dance: Press a key multiple times for different actions
// Example: Tap once = 'a', Tap twice = 'A', Hold = Ctrl
// Set to 4 if you'll use a few, or 0 to disable completely
// !disabled in rules.mk!
// #define VIAL_TAP_DANCE_ENTRIES 4

// Combos: Press multiple keys simultaneously for an action
// Example: Press 'j'+'k' together = Escape
// Set to 4 for basic use, or 0 to disable
// !disabled in rules.mk!
// #define VIAL_COMBO_ENTRIES 4

// Key Overrides: Override key behavior based on modifiers
// Example: Shift+Backspace = Delete
// Set to 0 to disable if you don't need it
// !disabled in rules.mk!
// #define VIAL_KEY_OVERRIDE_ENTRIES 4

// Disable insecure features that take up space
#undef VIAL_INSECURE