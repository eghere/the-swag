#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
};

// Animation variables
static uint8_t prev_layer = 0;
static bool gradient_anim_active = false;
static uint16_t gradient_anim_start = 0;
static uint8_t gradient_from[RGB_MATRIX_LED_COUNT][3];
static uint8_t gradient_to[RGB_MATRIX_LED_COUNT][3];

enum tap_dance_codes {
  DANCE_0,
};

#define DUAL_FUNC_0 LT(9, KC_L)
#define DUAL_FUNC_1 LT(2, KC_O)
#define DUAL_FUNC_2 LT(9, KC_F3)
#define DUAL_FUNC_3 LT(2, KC_F14)
#define DUAL_FUNC_4 LT(1, KC_F18)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_PSCR,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    CW_TOGG,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           CW_TOGG,        
    KC_ESCAPE,      MT(MOD_LGUI, KC_A),MT(MOD_LALT, KC_S),MT(MOD_LCTL, KC_D),MT(MOD_LSFT, KC_F),KC_G,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_H,           MT(MOD_RSFT, KC_J),MT(MOD_RCTL, KC_K),MT(MOD_RALT, KC_L),MT(MOD_RGUI, KC_SCLN),KC_QUOTE,       
    KC_GRAVE,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_BSLS,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MO(3),          TO(5),                                                                                                          MT(MOD_LCTL, KC_ESCAPE),MO(4),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    LT(1, KC_SPACE),KC_BSPC,        KC_DELETE,                      KC_TRANSPARENT, KC_ENTER,       TD(DANCE_0)
  ),
  [1] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_PGDN,        KC_PAGE_UP,     KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_LEFT_GUI,    KC_LEFT_ALT,    KC_LEFT_CTRL,   KC_LEFT_SHIFT,  KC_NO,          KC_NO,                                                                          KC_NO,          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_HOME,        KC_END,         KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_TRANSPARENT, KC_GRAVE,       KC_LABK,        KC_RABK,        KC_MINUS,       KC_AMPR,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_CIRC,        KC_LCBR,        KC_RCBR,        KC_DQUO,        KC_QUOTE,       KC_F12,         
    KC_TRANSPARENT, DUAL_FUNC_0,    DUAL_FUNC_1,    MT(MOD_LCTL, KC_SLASH),MT(MOD_LSFT, KC_EQUAL),KC_PIPE,        KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_HASH,        DUAL_FUNC_2,    DUAL_FUNC_3,    DUAL_FUNC_4,    MT(MOD_LGUI, KC_SCLN),KC_GRAVE,       
    KC_TRANSPARENT, KC_TILD,        KC_PLUS,        KC_LBRC,        KC_RBRC,        KC_PERC,                                        KC_AT,          KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_CALCULATOR,  KC_SLASH,       KC_ASTR,        KC_BSPC,        KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          DM_REC2,        DM_REC1,        KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_7,           KC_8,           KC_9,           KC_PLUS,        KC_NO,          
    KC_NO,          KC_NO,          DM_RSTP,        DM_PLY2,        DM_PLY1,        KC_NO,          KC_NO,                                                                          KC_NO,          KC_NO,          KC_4,           KC_5,           KC_6,           KC_MINUS,       KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_1,           KC_2,           KC_3,           KC_UNDS,        KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT, KC_NO,                                                                                                          KC_NO,          KC_0,           KC_NO,          KC_DOT,         KC_SPACE,       KC_NO,          
    KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,                          KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,        
    KC_NO,          KC_NO,          KC_NO,          KC_MS_UP,       KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_MS_BTN4,     KC_MS_BTN5,     KC_MS_WH_UP,    KC_NO,          KC_NO,          
    TO(0),          KC_LEFT_SHIFT,  KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_NO,          KC_NO,                                                                          KC_NO,          KC_MS_BTN3,     KC_MS_BTN1,     KC_MS_BTN2,     KC_MS_WH_DOWN,  KC_NO,          KC_NO,          
    KC_NO,          KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_LLCK,        KC_NO,                                                                                                          KC_NO,          KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          
    KC_NO,          KC_NO,          KC_NO,                          KC_NO,          KC_NO,          KC_NO
  ),
  [5] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TAB,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_NO,          KC_A,           KC_S,           KC_D,           KC_F,           KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_TRANSPARENT, 
    KC_LEFT_SHIFT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_RIGHT_SHIFT, 
    KC_LEFT_CTRL,   KC_TRANSPARENT, KC_LEFT_ALT,    KC_LEFT_GUI,    KC_SPACE,       TO(0),                                                                                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_SPACE,       KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TAB
  ),
};


const uint16_t PROGMEM combo0[] = { KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo2[] = { MT(MOD_LSFT, KC_F), MT(MOD_RSFT, KC_J), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_MINUS),
    COMBO(combo1, KC_MINUS),
    COMBO(combo2, KC_CAPS),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_SPACE):
            return TAPPING_TERM -50;
        case TD(DANCE_0):
            return TAPPING_TERM -100;
        default:
            return TAPPING_TERM;
    }
}


extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {190,176,189}, {170,137,199}, {152,168,209}, {128,247,242}, {128,247,242}, {128,247,242}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {133,223,228}, {190,176,189}, {170,137,199}, {152,168,209}, {141,197,218}, {190,176,189}, {170,137,199}, {152,168,209}, {128,247,242}, {128,247,242}, {128,247,242}, {133,223,228} },

    [1] = { {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,0,255}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,0,255}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,0,255}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,0,255}, {139,203,150}, {133,224,108}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,0,255}, {141,198,103}, {133,224,108}, {189,175,87}, {0,0,255}, {0,0,255}, {0,0,255}, {133,224,108}, {189,175,87}, {0,0,255}, {0,0,255}, {0,0,255}, {132,226,162}, {189,175,87}, {169,138,92}, {0,0,255}, {141,198,103}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108} },

    [2] = { {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {39,255,255}, {216,255,255}, {181,218,204}, {23,255,255}, {133,224,108}, {39,255,255}, {181,218,204}, {0,218,204}, {0,218,204}, {133,224,108}, {39,255,255}, {181,218,204}, {0,218,204}, {84,218,204}, {133,224,108}, {39,255,255}, {0,218,204}, {181,218,204}, {84,218,204}, {133,224,108}, {39,255,255}, {23,255,255}, {23,255,255}, {23,255,255}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108}, {39,255,255}, {39,255,255}, {216,255,255}, {0,0,255}, {133,224,108}, {39,255,255}, {216,255,255}, {172,255,255}, {0,218,204}, {133,224,108}, {39,255,255}, {216,255,255}, {172,255,255}, {172,255,255}, {133,224,108}, {39,255,255}, {84,218,204}, {84,218,204}, {172,255,255}, {133,224,108}, {39,255,255}, {84,218,204}, {84,218,204}, {0,0,0}, {133,224,108}, {39,255,255}, {23,255,255}, {0,0,0}, {0,0,0}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108} },

    [3] = { {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {189,175,87}, {169,138,92}, {0,255,255}, {141,198,103}, {133,224,108}, {189,175,87}, {86,255,255}, {0,0,255}, {141,198,103}, {133,224,108}, {189,175,87}, {86,255,255}, {0,0,255}, {141,198,103}, {0,0,255}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {133,224,108}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {133,224,108}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {189,175,87}, {169,138,92}, {152,170,97}, {141,198,103}, {189,175,87}, {169,138,92}, {152,170,97}, {128,248,115}, {128,248,115}, {128,248,115}, {133,224,108} },

    [4] = { {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {7,255,255}, {12,249,252}, {16,243,250}, {32,226,242}, {32,226,242}, {32,226,242}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {26,232,245}, {7,255,255}, {12,249,252}, {16,243,250}, {21,238,247}, {7,255,255}, {12,249,252}, {16,243,250}, {32,226,242}, {32,226,242}, {32,226,242}, {26,232,245} },

    [5] = { {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {87,255,255}, {77,246,232}, {65,247,209}, {23,255,255}, {23,255,255}, {23,255,255}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {34,252,204}, {87,255,255}, {77,246,232}, {65,247,209}, {50,249,186}, {87,255,255}, {77,246,232}, {65,247,209}, {23,255,255}, {23,255,255}, {23,255,255}, {34,252,204} },

};

extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void interpolate_color(uint8_t from[3], uint8_t to[3], float t, uint8_t out[3]) {
  for (int i = 0; i < 3; i++) {
    out[i] = from[i] + (to[i] - from[i]) * t;
  }
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}
void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  uint8_t curr_layer = biton32(layer_state);

  if (!keyboard_config.disable_layer_led) {
    if (curr_layer != prev_layer) {
      for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        gradient_from[i][0] = pgm_read_byte(&ledmap[prev_layer][i][0]);
        gradient_from[i][1] = pgm_read_byte(&ledmap[prev_layer][i][1]);
        gradient_from[i][2] = pgm_read_byte(&ledmap[prev_layer][i][2]);

        gradient_to[i][0] = pgm_read_byte(&ledmap[curr_layer][i][0]);
        gradient_to[i][1] = pgm_read_byte(&ledmap[curr_layer][i][1]);
        gradient_to[i][2] = pgm_read_byte(&ledmap[curr_layer][i][2]);
      }
      gradient_anim_active = true;
      gradient_anim_start  = timer_read();
      prev_layer = curr_layer;
    }

    if (gradient_anim_active) {
      uint16_t elapsed = timer_elapsed(gradient_anim_start);
      float t = (elapsed >= 250) ? 1.0f : (elapsed / 250.0f);

      if (t >= 1.0f) {
        gradient_anim_active = false;
        set_layer_color(curr_layer);
      } else {
        for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
          uint8_t interp_hsv[3];
          interpolate_color(gradient_from[i], gradient_to[i], t, interp_hsv);
          if (!gradient_to[i][0] && !gradient_to[i][1] && !gradient_to[i][2]) {
            if (t > 0.98f) {
              rgb_matrix_set_color(i, 0, 0, 0);
              continue;
            }
          }
          if (!interp_hsv[0] && !interp_hsv[1] && !interp_hsv[2]) {
            rgb_matrix_set_color(i, 0, 0, 0);
          } else {
            HSV hsv = { .h = interp_hsv[0], .s = interp_hsv[1], .v = interp_hsv[2] };
            RGB rgb = hsv_to_rgb_with_value(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
          }
        }
      }
    } else {
      set_layer_color(curr_layer);
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}



typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[1];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_TAB); break;
        case SINGLE_HOLD: layer_on(2); break;
        case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
        case DOUBLE_HOLD: register_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_TAB); break;
        case SINGLE_HOLD:
          if(!is_layer_locked(2)) {
            layer_off(2);
          }
        break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_HOLD: unregister_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
    }
    dance_state[0].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QK_MODS ... QK_MODS_MAX: 
    // Mouse keys with modifiers work inconsistently across operating systems, this makes sure that modifiers are always
    // applied to the mouse key that was pressed.
    if (IS_MOUSE_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
    if (record->event.pressed) {
        add_mods(QK_MODS_GET_MODS(keycode));
        send_keyboard_report();
        wait_ms(2);
        register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
        return false;
      } else {
        wait_ms(2);
        del_mods(QK_MODS_GET_MODS(keycode));
      }
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_EXLM);
        } else {
          unregister_code16(KC_EXLM);
        }
      } else {
        if (record->event.pressed) {
          register_mods(MOD_LGUI);
        } else {
          unregister_mods(MOD_LGUI);
        }  
      }  
      return false;
    case DUAL_FUNC_1:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_ASTR);
        } else {
          unregister_code16(KC_ASTR);
        }
      } else {
        if (record->event.pressed) {
          register_mods(MOD_LALT);
        } else {
          unregister_mods(MOD_LALT);
        }  
      }  
      return false;
    case DUAL_FUNC_2:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_LPRN);
        } else {
          unregister_code16(KC_LPRN);
        }
      } else {
        if (record->event.pressed) {
          register_mods(MOD_RSFT);
        } else {
          unregister_mods(MOD_RSFT);
        }  
      }  
      return false;
    case DUAL_FUNC_3:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_RPRN);
        } else {
          unregister_code16(KC_RPRN);
        }
      } else {
        if (record->event.pressed) {
          register_mods(MOD_RCTL);
        } else {
          unregister_mods(MOD_RCTL);
        }  
      }  
      return false;
    case DUAL_FUNC_4:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_COLN);
        } else {
          unregister_code16(KC_COLN);
        }
      } else {
        if (record->event.pressed) {
          register_mods(MOD_RALT);
        } else {
          unregister_mods(MOD_RALT);
        }  
      }  
      return false;
    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
  }
  return true;
}

