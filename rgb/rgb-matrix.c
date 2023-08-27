// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#include "rgb-matrix.h"

// Assign left and right keys to KB2040 LEDs on each side
#ifdef CONVERT_TO_KB2040
led_config_t g_led_config = {{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}}, {{111, 48}, {113, 48}}, {255, 255}};
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
                              {71, 15}, {51, 8}, {10, 13}, {10, 42}, {41, 45}, {76, 50}, {0, 15}, {20, 5}, {41, 0}, {61, 4}, {81, 7}, {0, 31}, {20, 21}, {41, 16}, {61, 20}, {81, 23}, {0, 47}, {20, 37}, {41, 32}, {61, 36}, {81, 39}, {71, 60}, {92, 64}, {150, 15}, {190, 8}, {210, 13}, {220, 42}, {183, 45}, {155, 50}, {143, 7}, {163, 20}, {183, 0}, {204, 5}, {224, 15}, {143, 23}, {163, 20}, {183, 16}, {204, 21}, {224, 31}, {143, 39}, {163, 36}, {183, 32}, {204, 37}, {224, 47}, {132, 64}, {153, 60}},
                             {// LED Index to Flag
                              2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1}};
#endif

layer_state_t layer_state_set_user(layer_state_t const state) {
    switch (get_highest_layer(state)) {
        case CMK:
            rgb_matrix_mode_noeeprom(CMK_MODE);
            break;
        default:
            rgb_matrix_mode_noeeprom(DEF_MODE);
    }
    return state;
}

#ifdef __AVR__

/*  filterspace uses transparent keycodes to differentiate layers
bool rgb_matrix_indicators_user(void) {
    // Caps lock
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (g_led_config.flags[i] & CAP_FLAG) {
                rgb_matrix_set_color(i, RGB_CAPS);
            }
        }
    }
    // Modifier keys
    if (get_mods() & MOD_MASK_CSAG) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (g_led_config.flags[i] & MOD_FLAG) {
                rgb_matrix_set_color(i, RGB_MODS);
            }
        }
    }
    // Layer keys indicator by @rgoulter
    if (get_highest_layer(layer_state) > CMK) {
        uint8_t layer = get_highest_layer(layer_state);
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t  index_led     = g_led_config.matrix_co[row][col];
                uint16_t index_keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                if (index_led != NO_LED && index_keycode > KC_TRNS) {
                    rgb_matrix_set_color(index_led, RGB_LAYER);
                }
            }
        }
    }
#	ifdef SWAP_HANDS_ENABLE
    if (is_swap_hands_on()) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (g_led_config.flags[i] & CAP_FLAG) {
                rgb_matrix_set_color(i, RGB_TEAL);
            }
        }
    }
#	endif
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

#else

#    include "lib/lib8tion/lib8tion.h"
static inline RGB hsv_to_rgb_glow(HSV hsv) {
    hsv.v = scale8(abs8(sin8(scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8)) - 128) * 2, hsv.v);
    return hsv_to_rgb(hsv);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps lock
    if (host_keyboard_led_state().caps_lock) {
        RGB rgb = hsv_to_rgb_glow((HSV){HSV_RED});
        for (uint8_t i = led_min; i <= led_max; ++i) {
            if (g_led_config.flags[i] & CAP_FLAG) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    // Modifier keys
    if (get_mods() & MOD_MASK_CSAG) {
        for (uint8_t i = led_min; i <= led_max; ++i) {
            if (g_led_config.flags[i] & MOD_FLAG) {
                rgb_matrix_set_color(i, RGB_MODS);
            }
        }
    }
    // Layer active keys indicator by @rgoulter
    if (get_highest_layer(layer_state) > CMK) {
        uint8_t layer = get_highest_layer(layer_state);
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t  index_led     = g_led_config.matrix_co[row][col];
                uint16_t index_keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});
                if (led_min <= index_led && index_led <= led_max && index_keycode > KC_TRNS) {
                    rgb_matrix_set_color(index_led, RGB_LAYER);
                }
            }
        }
    }
#    ifdef SWAP_HANDS_ENABLE
    if (is_swap_hands_on()) {
        RGB rgb = hsv_to_rgb_glow((HSV){HSV_TEAL});
        for (uint8_t i = led_min; i <= led_max; ++i) {
            if (g_led_config.flags[i] & CAP_FLAG) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    }
#    endif
    return false;
}

#endif // __AVR__
