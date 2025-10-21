#include "layer_anim.h"

// Theme definition for gradient mode
typedef struct {
    HSV base;
    HSV accent;
} layer_theme_t;

static const layer_theme_t PROGMEM layer_themes[] = {
    [0] = { .base = {190,176,189}, .accent = {133,223,228} },
    [1] = { .base = {189,175,87},  .accent = {133,224,108} },
    [2] = { .base = {189,175,87},  .accent = {133,224,108} },
    [3] = { .base = {189,175,87},  .accent = {133,224,108} },
    [4] = { .base = {7,255,255},   .accent = {32,226,242} },
    [5] = { .base = {87,255,255},  .accent = {23,255,255} }
};

// Forward declaration of ledmap from keymap.c
extern const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3];

// Active mode (single mode for now)
layer_anim_mode_t current_layer_anim_mode = LAYER_ANIM_SOLID_GRADIENT;

void layer_anim_cycle_mode(void) {
    current_layer_anim_mode = (current_layer_anim_mode + 1) % LAYER_ANIM_MODE_COUNT;
}

// Local hue-aware interpolation for gradient construction
static void hue_interpolate(uint8_t from[3], uint8_t to[3], float t, uint8_t out[3]) {
    int16_t h_from = from[0];
    int16_t h_to   = to[0];
    int16_t dh = h_to - h_from;
    if (dh > 127) dh -= 256;
    else if (dh < -127) dh += 256;
    int16_t h_interp = h_from + (int16_t)(dh * t);
    if (h_interp < 0) h_interp += 256;
    else if (h_interp > 255) h_interp -= 256;
    out[0] = (uint8_t)h_interp;
    for (int i = 1; i < 3; i++) {
        int16_t df = to[i] - from[i];
        out[i] = (uint8_t)(from[i] + (int16_t)(df * t));
    }
}

// Resolver for solid gradient mode
static void resolve_solid_gradient(uint8_t layer, uint8_t out[RGB_MATRIX_LED_COUNT][3]) {
    // Cache max Y once
    static uint8_t max_y = 0;
    if (max_y == 0) {
        for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            if (g_led_config.point[i].y > max_y) {
                max_y = g_led_config.point[i].y;
            }
        }
        if (max_y == 0) max_y = 1;
    }

    layer_theme_t theme = layer_themes[layer];
    HSV base = {
        .h = pgm_read_byte(&theme.base.h),
        .s = pgm_read_byte(&theme.base.s),
        .v = pgm_read_byte(&theme.base.v),
    };
    HSV accent = {
        .h = pgm_read_byte(&theme.accent.h),
        .s = pgm_read_byte(&theme.accent.s),
        .v = pgm_read_byte(&theme.accent.v),
    };

    uint8_t base_arr[3]   = { base.h, base.s, base.v };
    uint8_t accent_arr[3] = { accent.h, accent.s, accent.v };

    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint8_t h = pgm_read_byte(&ledmap[layer][i][0]);
        uint8_t s = pgm_read_byte(&ledmap[layer][i][1]);
        uint8_t v = pgm_read_byte(&ledmap[layer][i][2]);

        if (h || s || v) {
            out[i][0] = h;
            out[i][1] = s;
            out[i][2] = v;
        } else {
            float t = g_led_config.point[i].y / (float)max_y;
            hue_interpolate(base_arr, accent_arr, t, out[i]);
        }
    }
}

void layer_anim_resolve(uint8_t layer, uint8_t out[RGB_MATRIX_LED_COUNT][3]) {
    switch (current_layer_anim_mode) {
        case LAYER_ANIM_SOLID_GRADIENT:
        default:
            resolve_solid_gradient(layer, out);
            break;
    }
}
