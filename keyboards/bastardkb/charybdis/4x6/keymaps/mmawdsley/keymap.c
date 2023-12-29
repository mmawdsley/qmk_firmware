/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_GAME,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_DEBUG,
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define DEBUG MO(LAYER_DEBUG)
#define CTL_ESC MT(MOD_LCTL,KC_ESC)
#define MOUSE1 KC_MS_BTN1
#define MOUSE2 KC_MS_BTN2
#define MOUSE3 KC_MS_BTN3
#define DF_BASE DF(LAYER_BASE)
#define DF_GAME DF(LAYER_GAME)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭───────────────────────────────╮ ╭──────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰───────────────────────────────┤ ├──────────────────────────────╯
                                   KC_DEL, RAISE,   KC_LGUI,      KC_RCTL,  KC_RALT,
                                           LOWER,   KC_ENT,       KC_SPC
  //                           ╰────────────────╯ ╰───────────╯
  ),

  [LAYER_GAME] = LAYOUT(
  // ╭───────────────────────────────╮ ╭──────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├───────────────────────────────┤ ├──────────────────────────────┤
        KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  // ╰───────────────────────────────┤ ├──────────────────────────────╯
                                   KC_DEL, RAISE,   KC_LGUI,      KC_RCTL,  KC_RALT,
                                           LOWER,   KC_SPC,       KC_ENT
  //                           ╰────────────────╯ ╰───────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────╮ ╭───────────────────────────────╮
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,      KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_CAPS,    KC_PLUS,   KC_LPRN, KC_RPRN, KC_EQL,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_TRNS, MOUSE2,  MOUSE3,  MOUSE1,  DRGSCRL,    KC_RABK,   KC_MINS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,
  // ╰──────────────────────────────┤ ├───────────────────────────────╯
                                  KC_TRNS, KC_TRNS, KC_TRNS,    KC_RALT, KC_TRNS,
                                           DEBUG,   KC_TRNS,    KC_TRNS
  //                           ╰───────────────╯ ╰───────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────╮ ╭───────────────────────────────╮
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS,    KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS,    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,    KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS, KC_TRNS,
  // ╰──────────────────────────────┤ ├───────────────────────────────╯
                                  KC_TRNS, DEBUG,   KC_TRNS,    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,    KC_TRNS
  //                           ╰───────────────╯ ╰───────────╯
  ),

  [LAYER_DEBUG] = LAYOUT(
  // ╭──────────────────────────────╮ ╭───────────────────────────────╮
       KC_TRNS, DF_BASE, DF_GAME, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS,  KC_TRNS, KC_TRNS,
  // ├──────────────────────────────┤ ├───────────────────────────────┤
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
  // ╰──────────────────────────────┤ ├───────────────────────────────╯
                                  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,    KC_TRNS
  //                           ╰───────────────╯ ╰───────────╯
  ),
};
// clang-format on
