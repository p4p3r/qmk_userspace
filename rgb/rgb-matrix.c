// Copyright @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#include QMK_KEYBOARD_H
#include "rgb-matrix.h"
#include <lib/lib8tion/lib8tion.h>

#ifdef CONVERT_TO_KB2040
// Map keys to KB2040 LEDs on each side
led_config_t g_led_config = { {
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1 }
}, {
    {109, 48}, {115, 48}
}, {
    0x0f, 0xf0 // Flags for masking mod bits
} };
#endif

#if defined(KEYBOARD_splitkb_aurora_sweep_rev1)
led_config_t g_led_config = {{
                                 // Key Matrix to LED Index
                                 {10, 9, 8, 7, 6},
                                 {15, 14, 13, 12, 11},
                                 {20, 19, 18, 17, 16},
                                 {22, 21, NO_LED, NO_LED, NO_LED},
                                 {29, 30, 31, 32, 33},
                                 {34, 35, 36, 37, 38},
                                 {39, 40, 41, 42, 43},
                                 {44, 45, NO_LED, NO_LED, NO_LED},
                             },
                             {// LED Index to Physical Position
                              {71, 15}, {51, 8}, {10, 13}, {10, 42}, {41, 45},
                              {76, 50}, {0, 15}, {20, 5},  {41, 0},  {61, 4},
                              {81, 7},  {0, 31}, {20, 21}, {41, 16}, {61, 20},
                              {81, 23}, {0, 47}, {20, 37}, {41, 32}, {61, 36},
                              {81, 39}, {71, 60}, {92, 64}, {150, 15}, {190, 8},
                              {210, 13}, {220, 42}, {183, 45}, {155, 50}, {143, 7},
                              {163, 20}, {183, 0}, {204, 5}, {224, 15}, {143, 23},
                              {163, 20}, {183, 16}, {204, 21}, {224, 31}, {143, 39},
                              {163, 36}, {183, 32}, {204, 37}, {224, 47}, {132, 64}, {153, 60}
                             },
                             {// LED Index to Flag
                              2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1
                             }};
#endif

layer_state_t layer_state_set_user(layer_state_t const state) {
    rgb_matrix_mode_noeeprom(layer_state_is(CMK) ? CMK_MODE : DEF_MODE);
    return state;
}

/*  filterspace uses transparent keycodes to differentiate layers
static RGB hsv_to_rgb_glow(HSV hsv) {
    // Return glowing RGB values
    hsv.v = scale8(abs8(sin8(scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8)) - 128) * 2, hsv.v);
    return hsv_to_rgb(hsv);
}


bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        RGB const rgb = hsv_to_rgb_glow((HSV){HSV_CAPS});
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
#ifdef SWAP_HANDS_ENABLE
    if (is_swap_hands_on()) {
        RGB const rgb = hsv_to_rgb_glow((HSV){HSV_SWAP});
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
#endif
#ifdef CONVERT_TO_KB2040
    if (get_mods()) {
        uint8_t const mods = get_mods();
        RGB const rgb = hsv_to_rgb((HSV){(mods >> 4 | mods) * 16, 255, rgb_matrix_config.hsv.v});
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (g_led_config.flags[i] & mods) rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
#endif
    if (get_highest_layer(layer_state) > CMK) {
        uint8_t const layer = get_highest_layer(layer_state);
        RGB const rgb = hsv_to_rgb((HSV){(layer - 1) * 80, 255, rgb_matrix_config.hsv.v});
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
    return false;
}
*/

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Modifier keys indicator
    if (get_mods() & MOD_MASK_CSAG) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                if (g_led_config.matrix_co[row][col] & MOD_FLAG) {
                    rgb_matrix_set_color(g_led_config.matrix_co[row][col], RGB_MODS);
                }
            }
        }
    }
    // Layer keys indicator, variation on the examples from the doc:
    // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#examples-idindicator-examples
    uint8_t layer = get_highest_layer(layer_state);
    if (layer > CMK) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
                switch (layer) {
                    case SYM:
                        rgb_matrix_set_color(i, RGB_SPRINGGREEN);
                        break;
                    case NUM:
                        rgb_matrix_set_color(i, RGB_ORANGE);
                        break;
                    case FNC:
                        rgb_matrix_set_color(i, RGB_MAGENTA);
                        break;
                }
            }
        }
    }

    return false;
}

