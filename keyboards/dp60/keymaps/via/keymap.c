/**
 * keymap.c
 *
  Copyright 2020 astro <yuleiz@gmail.com>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
      KC_ESC,       KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_DEL, KC_BSPC,
      KC_TAB,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,
      KC_CAPS,          KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, KC_NUHS,  KC_ENT,
      KC_LSFT, KC_NUBS,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_RSFT,   MO(1),
      KC_LCTL,  KC_LGUI,  KC_LALT,                        KC_SPC,                  KC_RGUI,KC_RALT,  MO(1),   KC_RCTL),

    [1] = LAYOUT_all(
      KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,_______,KC_DEL,
      QK_BOOT,   _______,KC_UP,_______,_______,_______,_______,_______,KC_PAUS,KC_SCRL,KC_PSCR,KC_PGUP,_______,KC_INS,
      _______,        KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,_______,_______, _______,_______,KC_HOME,KC_END,_______, _______,
      _______,_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PGDN,_______,_______,
      _______,_______,_______,                        _______,                        _______,MO(2),TG(0),_______),

    [2] = LAYOUT_all(
      _______, _______,_______,  _______,_______,  _______,_______,  _______,_______,  _______,_______, _______,_______,_______,_______,
      _______,   _______,KC_VOLU,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
      KC_MUTE,        KC_MPRV,KC_VOLD,KC_MNXT,_______,_______,_______,_______, _______,_______,_______,_______,_______, _______,
      _______, _______,       RGB_TOG,RGB_MOD,RGB_RMOD,RGB_VAI,RGB_VAD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,_______,_______,_______,
      _______,_______,_______,                        KC_MPLY,                        _______,_______,_______,_______),

    [3] = LAYOUT_all(
      _______, _______,_______,  _______,_______,  _______,_______,  _______,_______,  _______,_______, _______,_______,_______,_______,
      _______,   _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
      _______,        _______,_______,_______,_______,_______,_______,_______, _______,_______,_______,_______,_______,_______,
      _______, _______,       _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
      _______,_______,_______,                        _______,                        _______,_______,_______,_______)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGBLIGHT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
        case KC_F13: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case KC_F14:
            rgb_matrix_step();
            return false;
        #endif
    #endif
        default:
        break;
    }
  }
  return true;
}
