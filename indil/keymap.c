#include QMK_KEYBOARD_H
#include <sendstring_german.h>

enum layers {
  _DEFAULT = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAMING,
};
char layer_name_map[5][6] = {
  "DEFAU\0",
  "LOWER\0",
  "RAISE\0",
  "ADJST\0",
  "GAMIN\0",
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
   EUR,
   DLLR,
   PERC,
   TILD,
   ASTX,
   AT,
   DYNENT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // LETTERS AND STUFF
	[_DEFAULT] = LAYOUT(
    KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                            KC_6,       KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,
    KC_TAB,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,                            KC_Y,       KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC,
    KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,                            KC_H,       KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,    KC_B,       KC_MPLY,    KC_MPLY, KC_N,       KC_M,    KC_COMM, KC_DOT, KC_SLSH, TG(_GAMING),
                         KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC,     DYNENT,  MO(_RAISE), KC_BSPC, KC_RGUI),
  // SYMBOLS
	[_LOWER] = LAYOUT(
    ___,     KC_F1,      KC_F2,   KC_F3,      KC_F4,   KC_F5,                KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    ___,     RALT(KC_Q), KC_NUHS, RALT(KC_E), KC_AT,   LBRCK,                RBRCK,         LESS,    KC_AMPR, KC_UNDS, KC_GRV,  KC_F12,
    KC_GRV,  KC_CIRC,    KC_GRV,  DLLR,       KC_PIPE, KC_ASTR,              KC_LPRN,       KC_PEQL, BSLSH,   KC_EXLM, KC_RCBR, KC_TILD,
    ___,     _x_,        _x_,     PERC,       KC_PLUS, LCURL,   ___, ___,    RCURL,         GRTR,    PIPE,    KC_PPLS, TILD,    KC_PIPE,
                                  ___,        ___,     ___,     ___, ___,    MO(_ADJUST),   KC_DEL,  ___),
  // NAVIGATION
	[_RAISE] = LAYOUT(
    ___,    ___,   ___,   ___,    ___,    ___,                    ___,     ___,     ___,    ___,     ___, ___,
    ___,    ___,   ___,   ___,    ___,    ___,                    KC_PSCR, ___,     ___,    ___,     ___, ___,
    KC_F1,  KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,                  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, _x_, _x_,
    KC_F7,  KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,       ___, ___, KC_HOME, KC_END,  ___,    ___,     ___, ___,
                          ___,    ___,    MO(_ADJUST),  ___, ___, ___,     ___,     ___),
  // KEYBOARD SPECIFIC STUFF I GUESS
	[_ADJUST] = LAYOUT(
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, _x_,     _x_,     _x_,     _x_,
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, _x_,     _x_,     _x_,     _x_,
    _x_, _x_, _x_, _x_, _x_, _x_,           _x_, _x_, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, _x_, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                   ___, ___, ___, ___, ___, ___, ___, ___),
  [_GAMING] = LAYOUT(
    KC_ESC, KC_1,    KC_2, KC_3,    KC_4,          KC_5,                    KC_6,  KC_7,    KC_8,    KC_9,   KC_0,    KC_F18,
    KC_F13, KC_TAB,  KC_Q, KC_W,    KC_E,          KC_R,                    KC_T,  KC_Y,    KC_U,    KC_I,   KC_O,    KC_F19,
    KC_F14, KC_LSFT, KC_A, KC_S,    KC_D,          KC_F,                    KC_G,  KC_H,    KC_J,    KC_K,   KC_L,    KC_F20,
    KC_F15, KC_LCTL, KC_Z, KC_X,    KC_C,          KC_V,    KC_F16, KC_F17, KC_B,  KC_N,    KC_COMM, KC_DOT, KC_SLSH, TG(_GAMING),
                           KC_LGUI, LALT(KC_TAB),  KC_TAB,  KC_SPC, DYNENT, MO(_RAISE), KC_BSPC, KC_RGUI),
};

int dyn_ent_return_to = _DEFAULT;
void dyn_ent(void) {
  tap_code(KC_ENT);
  switch (get_highest_layer(layer_state)) {
    case _DEFAULT:
      layer_move(dyn_ent_return_to);
      dyn_ent_return_to = _DEFAULT;
      break;
    case _GAMING:
      layer_move(_DEFAULT);
      dyn_ent_return_to = _GAMING;
      break;
    default:
      break;
  }
}

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
  case EUR:
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
  case DYNENT:
    if (record->event.pressed)
      dyn_ent();
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
    [_DEFAULT] =   { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  { ENCODER_CCW_CW(___, ___),            ENCODER_CCW_CW(___, ___)  },
    [_RAISE] =  { ENCODER_CCW_CW(KC_WH_L, KC_WH_R),    ENCODER_CCW_CW(___, ___)  },
    [_ADJUST] = { ENCODER_CCW_CW(___, ___),            ENCODER_CCW_CW(___, ___) },
    [_GAMING] = { ENCODER_CCW_CW(KC_F22, KC_F23),      ENCODER_CCW_CW(___, ___) },
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

static void render_inscription(void) {
  static const char PROGMEM inscription[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x38, 0xFC, 0xFE,
    0xFE, 0xFC, 0x38, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0xA9, 0xFF, 0x57,
    0x57, 0xFF, 0xA9, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x70, 0xF8, 0xF8,
    0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70,
    0x70, 0xFA, 0xFF, 0xF5,
    0xF5, 0xFF, 0xFA, 0x70,
    0x70, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70,
    0xF8, 0xF8, 0x70, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xFF, 0x01,
    0xFF, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xF0, 0xF8, 0xF0, 0x00,
    0x00, 0x3F, 0xFF, 0x80,
    0xFF, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xE1, 0x3F,
    0x30, 0x00, 0x81, 0x8F,
    0x7F, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0x7F, 0x07, 0x00,
    0xE0, 0xFF, 0x01, 0xFF,
    0x3C, 0x19, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0xFF,
    0x00, 0x00, 0xFE, 0xFF,
    0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x1F, 0x8F, 0xE7, 0xE1,
    0x00, 0xF0, 0x1F, 0xFF,
    0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x7F, 0xFF, 0x80, 0xFF,
    0xF0, 0xC1, 0x1F, 0x7F,
    0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFE, 0xFD, 0x03,
    0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x01, 0xFF,
    0xF8, 0xF7, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0x7F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x7F, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0x38, 0x1F,
    0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
  };
  oled_write_raw_P(inscription, sizeof(inscription));
}

static void render_undomiel(void) {
    static const char PROGMEM undomiel[] = {
        192,192,192,192,192,128,128,128,  0,  0,  0,  0,  0, 60,255,231,231,255, 60,  0,  0,  0,  0,  0,128,128,128,192,192,192,192,192,  1,  7, 31,124,225,249,219, 19, 31, 31, 62, 62,127,247,219,157,157,219,247,127, 62, 62, 31, 31, 19,219,249,225,124, 31,  7,  1,  0,  0, 96,240,225,255,255,  7, 14, 28,184,248,240,121,223,207,207,223,121,240,248,184, 28, 14,  7,255,255,225,240, 96,  0,  0,  0,  0,  0,  0,  2,  7, 31,190,252,247,243,249, 24, 60,255,231,231,255, 60, 24,249,243,247,252,190, 31,  7,  2,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  3,  7,255,252, 15,  7, 15,158,253,255,255,253,158, 15,  7, 15,252,255,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 31, 60,120,255,243,192,192,243,255,120, 60, 31,  7,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 44,127,255,225,225,255,127, 44,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(undomiel, sizeof(undomiel));
}

void render_layer(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else if(layer_state_is(_DEFAULT)) {
        oled_write_P(default_layer, false);
    } else {
        oled_write_P(adjust_layer, false);
    }
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  if (is_keyboard_master()) {
    oled_write_ln_P(PSTR(layer_name_map[get_highest_layer(layer_state)]), false);
    render_layer();
    render_undomiel();
    /* oled_write_ln_P(PSTR(" "), false); */
    /* render_layer(); */
    return false;
  } else {
    render_inscription();
    return false;
  }

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
