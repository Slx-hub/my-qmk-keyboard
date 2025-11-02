// Copyright 2021 Andrzej Kotulski (@akotulski)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define FUNCTION MO(_FUNCTION)
#define SYMBOL MO(_SYMBOL)
#define SPECIAL MO(_SPECIAL)
#define QWERTY MO(_QWERTY)

enum layer_names {
    _BASE,
    _FUNCTION,
    _SYMBOL,
    _SPECIAL,
    _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer - Full Split Keyboard
     * Left Half:                                    Right Half:
     * +-----------------------------------------+    +-----------------------------------------+
     * | ESC  |   q  |   w  |   e  |   r  |   t  |    |   y  |   u  |   i  |   o  |   p  | BSPC |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * | TAB  |   a  |   s  |   d  |   f  |   g  |    |   h  |   j  |   k  |   l  |   ;  |   '  |
     * |------+------+------+------+------+------|    |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |    |   n  |   m  |   ,  |   .  |   /  | SHFT |
     * +------+------+------+------+-------------+    +-------------+------+------+------+------+
     *               |  [   |   ]  |                                |   -  |   =  |
     *               +-------------+-------------+    +-------------+-------------+
     *                             | SPC  | FN   |    | SYM  | ENT  |
     *                             |------+------|    |------+------|
     *                             | BSPC | ALT  |    | ALT  | BSPC |
     *                             +-------------+    +-------------+
     */
    [_BASE] = LAYOUT(
        // Left half
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                          KC_LBRC, KC_RBRC,
                                       KC_SPC,  FUNCTION,  KC_HOME,
                                            KC_BSPC, KC_LALT,
        // Right half
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_MINS, KC_EQL,
        KC_END,  SYMBOL,  KC_ENT,
                 KC_RALT, KC_BSPC
    ),

    [_FUNCTION] = LAYOUT(
        // Left half
        _______, QK_BOOT, _______, _______, _______, KC_LBRC,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN,
        _______, _______, _______, _______, _______, _______,
                          _______, _______,
                                       _______, _______,  _______,
                                            _______, _______,
        // Right half
        KC_RBRC, _______, _______, _______, QK_BOOT, _______,
        KC_RPRN, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,
        _______, _______, _______, _______, _______, _______,
                          _______, _______,
        _______,  _______, _______,
                 _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        // Left half
        _______, _______, _______, _______, _______, KC_LBRC,
        _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END , KC_LPRN,
        _______, _______, _______, _______, _______, _______,
                          _______, KC_PSCR,
                                       _______, _______,  _______,
                                            _______, _______,
        // Right half
        KC_RBRC, _______, _______, _______, _______, _______,
        KC_RPRN, KC_HOME, KC_PGUP, KC_PGDN, KC_END , _______,
        _______, _______, _______, _______, _______, _______,
                          KC_PSCR, _______,
        _______,  _______, _______,
                 _______, _______
    ),

    [_SPECIAL] = LAYOUT(
        // Left half
        _______, QK_BOOT, _______, _______, _______, KC_LBRC,
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN,
        _______, _______, _______, _______, _______, _______,
                          _______, _______,
                                       _______, _______,  _______,
                                            _______, _______,
        // Right half
        KC_RBRC, _______, _______, _______, QK_BOOT, _______,
        KC_RPRN, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, _______,
        _______, _______, _______, _______, _______, _______,
                          _______, _______,
        _______,  _______, _______,
                 _______, _______
    ),

    [_QWERTY] = LAYOUT(
        // Left half
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                          KC_LBRC, KC_RBRC,
                                       KC_SPC,  FUNCTION,  KC_HOME,
                                            KC_BSPC, KC_LALT,
        // Right half
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_MINS, KC_EQL,
        KC_END,  SYMBOL,  KC_ENT,
                 KC_RALT, KC_BSPC
    ),
};
