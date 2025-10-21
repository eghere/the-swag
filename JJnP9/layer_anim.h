#pragma once
#include QMK_KEYBOARD_H

// Maximum planned modes (adjust when adding new ones)
typedef enum {
    LAYER_ANIM_SOLID_GRADIENT = 0,
    LAYER_ANIM_MODE_COUNT
} layer_anim_mode_t;

extern layer_anim_mode_t current_layer_anim_mode;

// Cycle to next animation mode (wrap)
void layer_anim_cycle_mode(void);

// Resolve full per-key HSV for given layer into out[LED_COUNT][3].
// Must return final HSV (0,0,0 means "off").
void layer_anim_resolve(uint8_t layer, uint8_t out[RGB_MATRIX_LED_COUNT][3]);
