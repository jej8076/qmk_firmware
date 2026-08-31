/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
Copyright 2025 EPOMAKER <https://github.com/Epomaker>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"
#include "keyboard_common.h"


// Define Combos (Matches ZMK key-positions converted to QMK keycodes)
const uint16_t PROGMEM combo_esc[] = {KC_TAB, KC_LCTL, COMBO_END};
const uint16_t PROGMEM combo_esc2[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_lclick[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_rclick[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_min[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_equal[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_backslash[] = {KC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_f6[] = {KC_LCTL, KC_A, COMBO_END};
const uint16_t PROGMEM combo_f7[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_f8[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_f9[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_f10[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_f11[] = {KC_LSFT, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_f12[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {MO(1), MO(2), COMBO_END};
const uint16_t PROGMEM combo_lclick_l3[] = {KC_E, KC_R, COMBO_END}; // Layer 3 combo2_lclick

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_esc2, KC_ESC),
    COMBO(combo_lclick, MS_BTN1),
    COMBO(combo_rclick, MS_BTN2),
    COMBO(combo_min, KC_MINS),
    COMBO(combo_equal, KC_EQL),
    COMBO(combo_backslash, KC_BSLS),
    COMBO(combo_quot, KC_QUOT),
    COMBO(combo_f6, KC_F6),
    COMBO(combo_f7, KC_F7),
    COMBO(combo_f8, KC_F8),
    COMBO(combo_f9, KC_F9),
    COMBO(combo_f10, KC_F10),
    COMBO(combo_f11, KC_F11),
    COMBO(combo_f12, KC_F12),
    COMBO(combo_mouse, MO(3)),
    COMBO(combo_lclick_l3, MS_BTN1)
};

// Implement conditional combo triggers to mirror ZMK's layers assignment
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case 16: // combo_lclick_l3 (ZMK layers = <3>)
            return IS_LAYER_ON(3);
        case 2: // combo_lclick (ZMK layers = <0> and <4>)
            return (get_highest_layer(layer_state) == 0 || get_highest_layer(layer_state) == 4);
        default:
            return true;
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
             KC_NO,    KC_NO,   KC_NO,  KC_LALT, KC_LGUI,                                KC_SPC,  MO(1),   MO(2),  KC_LNG1,   KC_NO,   KC_NO
    ),

    [1] = LAYOUT_tkl_ansi(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_GRV,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_LBRC,   KC_UP, KC_RBRC,   KC_NO,  KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
             KC_NO,    KC_NO,   KC_NO,  KC_LALT, KC_LGUI,                                KC_SPC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [2] = LAYOUT_tkl_ansi(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_NO,   KC_NO,    KC_7,    KC_8,    KC_9,    KC_0,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                          KC_NO,   KC_NO,    KC_4,    KC_5,    KC_6,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT,  KC_F11,  KC_F12,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,    KC_1,    KC_2,    KC_3, KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
             KC_NO,    KC_NO,   KC_NO,  KC_LALT, KC_LGUI,                                KC_SPC,  KC_NO,   KC_NO,    KC_0,   KC_NO,   KC_NO
    ),

    [3] = LAYOUT_tkl_ansi(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,   KC_NO,   DF(0),   KC_NO,   KC_NO, RM_TOGG,                         KC_NO,   KC_NO,   KC_NO,   MS_UP,   KC_NO,  KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL, RM_NEXT, RM_PREV, RM_VALU, RM_VALD, RM_SPDU,                       RM_SPDD,   KC_NO, MS_LEFT, MS_DOWN, MS_RGHT,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT, MD_BLE1, MD_BLE2, MD_BLE3,  MD_24G,  EE_CLR,                         KC_NO,   DF(4),   KC_NO,   KC_NO,   KC_NO,  KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
             KC_NO,    KC_NO,   KC_NO,  KC_LALT, KC_LGUI,                                KC_SPC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [4] = LAYOUT_tkl_ansi(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
             KC_NO,    KC_NO,   KC_NO,  KC_LALT, KC_LGUI,                                KC_SPC,  MO(1),   MO(2),  KC_F13,   KC_NO,   KC_NO
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [4] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
