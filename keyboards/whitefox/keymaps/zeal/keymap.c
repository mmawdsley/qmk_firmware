#include "whitefox.h"

// Helpful defines
#define _______ KC_TRNS

// Layer Ordering:
#define BASE_LAYER 0
#define UPPER_LAYER 1
#define META_LAYER 2

// Layer Modifiers
#define RAISE   MO(UPPER_LAYER)
#define MTA_LYR MO(META_LAYER)

// Shortcuts for more complicated actions
// Copy/paste: used by Fn+C/V
#define TRM_CPY (LCTL(LSFT(KC_C)))
#define TRM_PST (LCTL(LSFT(KC_V)))
// Escape key (or tilde/grave)
#define ACT_ESC F(0)


const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE_LAYER] = LAYOUT( \
    KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_NO,  KC_BSPC,KC_GRV, \
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_PGUP, \
    RAISE,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NO,  KC_ENT,         KC_PGDN,\
    KC_LSFT,KC_NO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,        KC_UP,  KC_DEL,\
    KC_LCTL,KC_LGUI,KC_LALT ,               KC_SPC,                                 KC_RALT,MTA_LYR,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT \
  ),
  [UPPER_LAYER] = LAYOUT( \
    KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,_______,_______,\
    _______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,_______,KC_PGUP,KC_HOME,KC_PGDN,_______,_______,_______,_______,        _______,\
    RAISE,  KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,_______,_______,        _______,\
    _______,_______,_______,_______,TRM_CPY,TRM_PST,_______,KC_END, _______,_______,_______,_______,_______,        _______,_______,\
    _______,_______,_______,                _______,                                _______,_______,_______,_______,_______,_______ \
  ),
  [META_LAYER] = LAYOUT( \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,\
    _______,_______,_______,_______,RESET,  _______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,\
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,_______,\
    _______,_______,_______,                _______,                                _______,MTA_LYR,_______,_______,_______,_______ \
  ),
};

const uint16_t fn_actions[] = {
    [0] = ACTION_FUNCTION(1),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t mods_pressed;
  static bool mod_flag;

  switch (id) {
    case 0:
      /* Handle the combined Grave/Esc key
       */
      // Check to see what mods are pressed
      mods_pressed = get_mods()&(MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)); 

      if (record->event.pressed) {
        /* The key is being pressed.
         */
        if (mods_pressed) {
          mod_flag = true;
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        /* The key is being released.
         */
        if (mod_flag) {
          mod_flag = false;
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    case 1:
      if (!record->event.pressed)
          break;
      if (debug_enable) {
          debug("!debug\n");
          debug_enable = false;
      } else {
          debug_enable = true;
          debug("debug\n");
      }
      break;
  }
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (!record->event.pressed)
        return MACRO_NONE;
    switch(id) {
    case 0:
        SEND_STRING("(y)");
        return false;
    }
    return MACRO_NONE;
}
