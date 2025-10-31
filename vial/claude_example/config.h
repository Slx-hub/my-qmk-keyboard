// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameters */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Custom
#define PRODUCT         Dactyl Manuform

/* Key matrix size */
#define MATRIX_ROWS 10  // 5 rows per half, 2 halves
#define MATRIX_COLS 6   // 6 columns per half

/* Matrix row/column pin configuration */
/* Change these to match your actual wiring */
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }      // Left half rows
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }  // Left half columns

/* Split keyboard configuration */
#define SOFT_SERIAL_PIN D0
#define MASTER_LEFT  // Define which half is master (use MASTER_LEFT or MASTER_RIGHT)

/* Debounce reduces chatter (unintended double-presses) */
#define DEBOUNCE 5

/* Vial-specific settings */
#define VIAL_KEYBOARD_UID {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }

/* Optional: Enable tap dance */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Handedness detection */
#define SPLIT_HAND_PIN F4
