// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include QMK_KEYBOARD_H

// Dimmer RGB colors
#define RGB_BSTEEL 55, 80, 115
#define RGB_DPURPLE 60, 0, 115
#define RGB_DPINK 115, 20, 45
#define RGB_DTEAL 5, 35, 35
#define RGB_FLUOR 75, 122, 22
#define RGB_GINGER 179, 89, 0
#define RGB_CAPS RGB_FLUOR
#define RGB_MODS RGB_GOLDENROD
#define RGB_LAYER RGB_DPINK

// Custom effects
#ifdef RGB_MATRIX_CUSTOM_USER
# define DEF_MODE RGB_MATRIX_CUSTOM_CANDY_TAP
# define CMK_MODE RGB_MATRIX_CUSTOM_CANDY_RAIN
#else
# define DEF_MODE	RGB_MATRIX_TYPING_HEATMAP
# define CMK_MODE	RGB_MATRIX_TYPING_HEATMAP
#endif

// Custom indicators
#if defined(KEYBOARD_crkbd_rev1) || defined(KEYBOARD_splitkb_aurora_sweep_rev1)
# define MOD_FLAG LED_FLAG_UNDERGLOW
# define CAP_FLAG LED_FLAG_UNDERGLOW
#else
# define MOD_FLAG LED_FLAG_MODIFIER
# define CAP_FLAG LED_FLAG_KEYLIGHT
#endif
