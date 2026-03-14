#include QMK_KEYBOARD_H
#include "transactions.h"

enum custom_keycodes {
    SPC_F18 = SAFE_RANGE,
};

static bool spc_f18_pressed = false;
static bool spc_f18_held = false;
static bool spc_f18_used = false;
static uint16_t spc_f18_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != SPC_F18 && record->event.pressed && spc_f18_pressed && !spc_f18_held) {
        register_code(KC_SPC);
        spc_f18_used = true;
    }

    switch (keycode) {
        case SPC_F18:
            if (record->event.pressed) {
                spc_f18_pressed = true;
                spc_f18_held = false;
                spc_f18_used = false;
                spc_f18_timer = timer_read();
            } else {
                spc_f18_pressed = false;
                if (spc_f18_held) {
                    unregister_code(KC_F18);
                } else if (spc_f18_used) {
                    unregister_code(KC_SPC);
                } else {
                    tap_code(KC_SPC);
                }
                spc_f18_held = false;
                spc_f18_used = false;
            }
            return false;
        case KC_LGUI:
            if (!record->event.pressed && keymap_config.swap_lalt_lgui) {
                tap_code(KC_F24);
            }
            return true;
        case KC_F13:
            if (keymap_config.swap_lalt_lgui) {
                if (record->event.pressed) {
                    register_code(KC_LNG1);
                } else {
                    unregister_code(KC_LNG1);
                }
                return false;
            }
            return true;
        case KC_LEFT:
            if (record->event.pressed && keymap_config.swap_lalt_lgui && (get_mods() & MOD_MASK_ALT)) {
                uint8_t mods = get_mods();
                del_mods(MOD_MASK_ALT);
                tap_code(KC_HOME);
                set_mods(mods);
                return false;
            }
            return true;
        case KC_RIGHT:
            if (record->event.pressed && keymap_config.swap_lalt_lgui && (get_mods() & MOD_MASK_ALT)) {
                uint8_t mods = get_mods();
                del_mods(MOD_MASK_ALT);
                tap_code(KC_END);
                set_mods(mods);
                return false;
            }
            return true;
    }
    return true;
}

void matrix_scan_user(void) {
    if (spc_f18_pressed && !spc_f18_held && !spc_f18_used && timer_elapsed(spc_f18_timer) >= 200) {
        spc_f18_held = true;
        register_code(KC_F18);
    }
}

// Combos
const uint16_t PROGMEM combo_esc[]       = {KC_TAB, KC_LCTL, COMBO_END};
const uint16_t PROGMEM combo_esc2[]      = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo_rclick[]    = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_lclick[]    = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_min[]       = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_equal[]     = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_backslash[] = {KC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_quot[]      = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_f6[]        = {KC_LCTL, KC_A, COMBO_END};
const uint16_t PROGMEM combo_f7[]        = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM combo_f8[]        = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_f9[]        = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo_f10[]       = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_f11[]       = {KC_LSFT, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_f12[]       = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_mouse[]      = {MO(1), MO(2), COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_esc2, KC_ESC),
    COMBO(combo_rclick, MS_BTN2),
    COMBO(combo_lclick, MS_BTN1),
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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LEFT_ALT, KC_LGUI, SPC_F18, MO(1), MO(2), KC_F13),
	[1] = LAYOUT_split_3x6_3(KC_GRV, _______, _______, _______, _______, _______, KC_LBRC, KC_UP, KC_RBRC, _______, _______, KC_BSPC, KC_LCTL, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, KC_APP, KC_ENT, KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS, KC_DEL, KC_RSFT, KC_LEFT_ALT, KC_LGUI, SPC_F18, _______, _______, _______),
	[2] = LAYOUT_split_3x6_3(KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_LCTL, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, KC_4, KC_5, KC_6, _______, KC_ENT, KC_LSFT, KC_F11, KC_F12, _______, _______, _______, _______, KC_1, KC_2, KC_3, _______, KC_RSFT, KC_LEFT_ALT, KC_LGUI, SPC_F18, _______, _______, KC_0),
	[3] = LAYOUT_split_3x6_3(QK_BOOT, AG_TOGG, EE_CLR, _______, _______, _______, _______, _______, MS_UP, _______, _______, KC_BSPC, KC_LCTL, _______, _______, _______, _______, _______, _______, MS_LEFT, MS_DOWN, MS_RGHT, _______, KC_ENT, KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_LEFT_ALT, KC_LGUI, SPC_F18, _______, _______, _______)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// Split keyboard sync: MAC/WIN mode from master to slave
static bool slave_win_mode = false;

void user_sync_mode_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const bool* mode = (const bool*)in_data;
    slave_win_mode = *mode;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_MODE, user_sync_mode_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        static bool last_mode = false;
        bool current_mode = keymap_config.swap_lalt_lgui;
        if (current_mode != last_mode || timer_elapsed32(last_sync) > 500) {
            if (transaction_rpc_send(USER_SYNC_MODE, sizeof(current_mode), &current_mode)) {
                last_mode = current_mode;
                last_sync = timer_read32();
            }
        }
    }
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_off();
        return false;
    }
    // Right (slave) OLED: show MAC/WIN mode
    static bool drawn = false;
    static bool last_mode = false;
    bool current_mode = slave_win_mode;
    if (!drawn || current_mode != last_mode) {
        oled_clear();
        oled_set_cursor(0, 7);
        if (current_mode) {
            oled_write_P(PSTR(" WIN"), false);
        } else {
            oled_write_P(PSTR(" MAC"), false);
        }
        drawn = true;
        last_mode = current_mode;
    }
    return false;
}

#endif
