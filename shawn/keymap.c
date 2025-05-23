/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "rgb_matrix_map.h"

enum my_keycodes {
    AP_GLOB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AP_GLOB:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {   // set the keypress (push) in the layout
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return false;
}
#endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
   led_t led_state = host_keyboard_led_state();
      if (led_state.caps_lock) {
            for (uint8_t i = 0; i < 8; i++) {
              rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_MAGENTA); // light up the sidebars when capslocked
              rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_MAGENTA);
            }
            rgb_matrix_set_color(LED_CAPS, RGB_MAGENTA); // also light up capslock key when capslocked
      }
    //if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    //    for (uint8_t i = 0; i < 8; i++) {
    //        rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_MAGENTA); // light up the sidebars when capslocked
    //        rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_MAGENTA);
    //    }
    //    rgb_matrix_set_color(LED_CAPS, RGB_MAGENTA); // also light up capslock key when capslocked
    //}
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(LED_LWIN, RGB_MAGENTA); // light up Win key when disabled
    }
    if (!keymap_config.nkro) {
        rgb_matrix_set_color(LED_N, RGB_MAGENTA); // light up the N key when NKRO is disabled
    }
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 1:
            rgb_matrix_set_color(LED_2, RGB_CYAN); // light up the layer key (2) when dvorak layer (1) is active
            break;
        case 2:
            rgb_matrix_set_color(LED_DEL, RGB_CYAN); // light up fn-shifted keys and media keys on function layer (2)
            rgb_matrix_set_color(LED_END, RGB_CYAN);
            rgb_matrix_set_color(LED_1, RGB_BLUE);  // layers
            rgb_matrix_set_color(LED_2, RGB_BLUE);
            rgb_matrix_set_color(LED_F5, RGB_CYAN); // media
            rgb_matrix_set_color(LED_F6, RGB_CYAN);
            rgb_matrix_set_color(LED_F7, RGB_GREEN);
            rgb_matrix_set_color(LED_F8, RGB_RED);
            rgb_matrix_set_color(LED_BSLS, RGB_YELLOW); // reset
            rgb_matrix_set_color(LED_CAPS, RGB_CYAN);   // caps
            rgb_matrix_set_color(LED_LWIN, RGB_MAGENTA);    // disable win key
            rgb_matrix_set_color(LED_LALT, RGB_CYAN);    // enable win key
            break;
        default:
            break;
    }
    return false;
}
#endif // RGB_MATRIX_ENABLE
// clang-format off

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_MUTE, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
        [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_SLEP, KC_TRNS, TO(0), TO(1), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, AP_GLOB, KC_TRNS, KC_INS, KC_TRNS, KC_TRNS, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_M_P, RGB_TOG, KC_TRNS, QK_BOOT, KC_TRNS, KC_CAPS, KC_TRNS, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, KC_HOME, KC_TRNS, GUI_OFF, GUI_ON, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_RMOD, RGB_SPI),
};

// clang-format on


