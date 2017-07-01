#include QMK_KEYBOARD_H

#define KEYMAP_ZEAL( \
    k00, k01,   k02, k03,   k04, k05,   k06, k07, k50,   k51, k52, k53, k54,          k56,  k57, \
    k10, k11,   k12, k13,   k14, k15,   k16, k17, k60,   k61, k62, k63, k64,   k65,         k67, \
    k20, k21,   k22, k23,   k24, k25,   k26, k27, k70,   k71, k72, k73,        k75,              \
    k30,        k32, k33,   k34, k35,   k36, k37, k80,   k81, k82, k83,        k85,   k86,       \
    k40, k41,   k42,                    k46,             k92, k93, k94, k95,   k96,   k97        \
) KEYMAP( \
    k00, k01,   k02, k03,   k04, k05,   k06, k07, k50,   k51, k52, k53, k54,   KC_NO, k56, k57, \
    k10, k11,   k12, k13,   k14, k15,   k16, k17, k60,   k61, k62, k63, k64,   k65,        k67, \
    k20, k21,   k22, k23,   k24, k25,   k26, k27, k70,   k71, k72, k73, KC_NO, k75,             \
    k30, KC_NO, k32, k33,   k34, k35,   k36, k37, k80,   k81, k82, k83, KC_NO, k85,   k86,      \
    k40, k41,   k42, KC_NO,      KC_NO, k46,      KC_NO, k92, k93, k94, k95,   k96,   k97       \
  )

#define _______ KC_TRNS

// Layer Ordering:
#define BASE_LAYER 0
#define UPPER_LAYER 1
#define META_LAYER 2

// Layer Modifiers
#define UPPER   MO(UPPER_LAYER)
#define MTA_LYR MO(META_LAYER)

// Shortcuts for more complicated actions
// Copy/paste: used by Fn+C/V
#define TRM_CPY (LCTL(LSFT(KC_C)))
#define TRM_PST (LCTL(LSFT(KC_V)))
// Escape key (or UPPER if held)
#define ACT_ESC LT(UPPER_LAYER, KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE_LAYER] = KEYMAP_ZEAL(
  KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,KC_PGUP,       \
  KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,KC_PGDN,       \
  ACT_ESC,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT        ,KC_ENT         ,       \
  KC_LSFT        ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH        ,KC_RSFT,KC_UP  ,       \
  KC_LCTL,KC_LGUI,KC_LALT                        ,KC_SPC                         ,KC_RALT,MTA_LYR,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT),

[UPPER_LAYER] = KEYMAP_ZEAL(
  KC_GRV ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,_______,_______,_______,_______,_______,_______,_______,KC_DEL ,_______,       \
  _______,KC_MPRV,KC_MPLY,KC_MNXT,_______,_______,_______,KC_PGUP,KC_HOME,KC_PGDN,_______,_______,_______,_______,_______,       \
  UPPER  ,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,_______,_______        ,_______        ,       \
  _______        ,_______,_______,TRM_CPY,TRM_PST,_______,KC_END ,_______,_______,_______,_______        ,_______,_______,       \
  _______,_______,_______                        ,_______                        ,_______,_______,_______,_______,_______,_______),

[META_LAYER] = KEYMAP_ZEAL(
  KC_LGUI,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,RGB_TOG,RGB_VAI,       \
  _______,_______,_______,_______,RESET  ,_______,_______,_______,_______,_______,_______,_______,_______,_______,RGB_VAD,       \
  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______        ,_______        ,       \
  _______        ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______        ,_______,RGB_SAI,       \
  _______,MTA_LYR,_______                        ,RGB_MOD                        ,_______,_______,_______,RGB_HUD,RGB_SAD,RGB_HUI),

};
