// Copyright 2021 Andrzej Kotulski (@akotulski)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define FUNCTION MO(_FUNCTION)
#define SYMBOL MO(_SYMBOL)
#define SPECIAL MO(_SPECIAL)

enum layer_names {
    _BASE,
    _FUNCTION,
    _SYMBOL,
    _SPECIAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)qweertyasdfgYXcVBü+Ü*[]{}
     * +-----------------------------------------+            
     * | ESC  |   q  |   w  |   e  |   r  |   t  |            
     * |------+------+------+------+------+------|            
     * | TAB  |   a  |   s  |   d  |   f  |   g  |            
     * |------+------+------+------+------+------|            
     * | SHFT |   z  |   x  |   c  |   v  |   b  |            
     * +------+------+------+------+-------------+            
     *               |  [   |   ]  |                          
     *               +-------------+-------------+            
     *                             |      |      |            
     *                             |------+------|            
     *                             |      |      |            
     *                             +-------------+            
     *                                           +------------
     *                                           |      |     
     *                                           |------+-----
     *                                           |      |     
     *                                           +------------
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    
                          KC_LBRC, KC_RBRC,                   
                                       KC_SPC,  FUNCTION,   KC_HOME,  
                                            KC_BSPC, KC_LALT
    ),

    [_FUNCTION] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______, KC_LBRC,      
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN,      
        _______, _______, _______, _______, _______, _______,      
                          _______, _______,                        
                                  _______, _______,  _______,      
                                            _______, _______
    ),

    [_SYMBOL] = LAYOUT(
        _______, _______, _______, _______, _______, KC_LBRC,      
        _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END , KC_LPRN,      
        _______, _______, _______, _______, _______, _______,      
                          _______, KC_PSCR,                        
                                  _______, _______,  _______,      
                                            _______, _______
    ),

    [_SPECIAL] = LAYOUT(
        _______, QK_BOOT, _______, _______, _______, KC_LBRC,      
        _______, KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, KC_LPRN,      
        _______, _______, _______, _______, _______, _______,      
                          _______, _______,                        
                                  _______, _______,  _______,      
                                            _______, _______
    )
};

