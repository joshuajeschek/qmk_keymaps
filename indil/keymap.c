#include QMK_KEYBOARD_H
#include <sendstring_german.h>

enum layers {
  _DEFAULT = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};
enum helpers {
  ___ = KC_TRNS,
  _x_ = KC_NO,
};
enum custom_keycodes {
   LCURL = SAFE_RANGE,
   RCURL,
   LBRCK,
   RBRCK,
   PIPE,
   BSLSH,
   LESS,
   GRTR,
   EURO,
   DLLR,
   PERC,
   TILD,
   ASTX,
   AT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // LETTERS AND STUFF
	[_DEFAULT] = LAYOUT(
    KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,   KC_0,    KC_GRV,
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                    KC_Y,  KC_U,    KC_I,    KC_O,   KC_P,    KC_MINS,
    KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,                    KC_H,  KC_J,    KC_K,    KC_L,   KC_SCLN, KC_RSFT,
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,    KC_B,  KC_LBRC, KC_MPLY, KC_N,  KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RALT,
                         KC_LALT, KC_LGUI, MO(1), KC_SPC,  KC_ENT,  MO(2), KC_BSPC, KC_RGUI),
  // SYMBOLS
	[_LOWER] = LAYOUT(
    ___,     KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,                KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    ___,     AT,      KC_NUHS, EURO,  KC_AT,   LBRCK,                RBRCK,   GRTR,    KC_AMPR, KC_UNDS, KC_GRV,  KC_F12,
    KC_GRV,  KC_CIRC, KC_GRV,  DLLR,  KC_PIPE, KC_ASTR,              KC_LPRN, KC_PEQL, BSLSH,   KC_EXLM, KC_RCBR, KC_TILD,
    ___,     _x_,     _x_,     PERC,  KC_PLUS, LCURL,   ___, ___,    RCURL,   LESS,    PIPE,    KC_PPLS, TILD,    KC_PIPE,
                               ___,   ___,     ___,     ___, ___,    MO(3),   KC_DEL,  ___),
  // NAVIGATION
	[_RAISE] = LAYOUT(
    ___,    ___,   ___,   ___,    ___,    ___,              ___,     ___,     ___,    ___,     ___,     ___,
    KC_GRV, KC_1,  KC_2,  KC_3,   KC_4,   KC_5,             KC_PSCR, KC_7,    KC_8,   KC_9,    KC_0,    ___,
    KC_F1,  KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,            KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, _x_,     _x_,
    KC_F7,  KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ___, ___, KC_PLUS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
                          ___,    ___,    MO(3),  ___, ___, ___,     ___,     ___),
  // KEYBOARD SPECIFIC STUFF I GUESS
	[_ADJUST] = LAYOUT(
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, _x_,     _x_,     _x_,     _x_,
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, _x_,     _x_,     _x_,     _x_,
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                   ___, ___, ___, ___, ___, ___, ___, ___)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LCURL:
    if (record->event.pressed)
      SEND_STRING("{");
    break;
  case RCURL:
    if (record->event.pressed)
      SEND_STRING("}");
    break;
  case LBRCK:
    if (record->event.pressed)
      SEND_STRING("[");
    break;
  case RBRCK:
    if (record->event.pressed)
      SEND_STRING("]");
    break;
  case PIPE:
    if (record->event.pressed)
      SEND_STRING("|");
    break;
  case BSLSH:
    if (record->event.pressed)
      SEND_STRING("\\");
    break;
  case LESS:
    if (record->event.pressed)
      SEND_STRING("<");
    break;
  case GRTR:
    if (record->event.pressed)
      SEND_STRING(">");
    break;
  case EURO:
    if (record->event.pressed)
      SEND_STRING("€");
    break;
  case DLLR:
    if (record->event.pressed)
      SEND_STRING("$");
    break;
  case PERC:
    if (record->event.pressed)
      SEND_STRING("%");
    break;
  case TILD:
    if (record->event.pressed)
      SEND_STRING("~");
    break;
  case ASTX:
    if (record->event.pressed)
      SEND_STRING("*");
    break;
  case AT:
    if (record->event.pressed)
      SEND_STRING("@");
    break;
  }
  return true;
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  return false;
}
#endif
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  { ENCODER_CCW_CW(___, ___),                      ENCODER_CCW_CW(___, ___)  },
    [_RAISE] =  { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT), ENCODER_CCW_CW(___, ___)  },
    [_ADJUST] = { ENCODER_CCW_CW(___, ___),                      ENCODER_CCW_CW(___, ___) },
};
#endif
#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}
bool oled_task_user(void) {
  // Host Keyboard Layer Status
  return true;
  render_logo();
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _DEFAULT:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("FN\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("ADJ\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  return false;
}
#endif
