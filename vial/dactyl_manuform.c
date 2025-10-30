// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    // Initialize any hardware-specific features
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // Post-init actions
    keyboard_post_init_user();
}
