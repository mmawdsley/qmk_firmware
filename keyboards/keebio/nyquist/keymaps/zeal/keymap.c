#include QMK_KEYBOARD_H

// This is a one-handed macro pad with keys that are useful for Blender
// Since only one side of the keyboard is used (the left) the right half of the keyboard is not used.

// Compile with:
// bin/qmk compile -kb keebio/nyquist/rev1 -km zeal
// Flash with:
// avrdude -c avr109 -p atmega32u4 -P /dev/ttyACM0 -U flash:w:.build/keebio_nyquist_rev1_zeal.hex

#define MCRO 0
#define LEFT 1
#define RGHT 2

enum custom_keycodes {
    NOOP = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Main Macro Layer
[MCRO] = LEFT_HALF( \
  KC_ESC,   KC_BSPC, KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST, \
  KC_TAB,   KC_NO,   KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, \
  KC_NO,    KC_NO,   KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, \
  KC_LSFT,  KC_NO,   KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, \
  MO(LEFT), KC_LCTL, KC_KP_0, KC_PDOT, KC_LALT, MO(RGHT) \
),

// Left Function Layer
[LEFT] = LEFT_HALF( \
  _______,  _______, KC_F10,  KC_F11,  KC_F12,  _______, \
  _______,  _______, KC_F7,   KC_F8,   KC_F9,   _______, \
  _______,  _______, KC_F4,   KC_F5,   KC_F6,   _______, \
  _______,  _______, KC_F1,   KC_F2,   KC_F3,   _______, \
  MO(LEFT), _______, _______, _______, _______, _______  \
),

// Right Function Layer
[RGHT] = LEFT_HALF( \
  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, MO(RGHT)\
),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NOOP:
      break;
  }
  return true;
}
