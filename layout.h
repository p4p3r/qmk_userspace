// Copyright 2021 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#include "quantum/keycodes.h"

// macOS shortcuts
#define Z_UND	G(KC_Z)
#define Z_CUT	G(KC_X)
#define Z_CPY	G(KC_C)
#define Z_PST	G(KC_V)
#define Z_LOCK	C(G(KC_Q))
#define Z_SLEEP	A(G(KC_PWR))
#define Z_SHUT	C(A(G(KC_PWR)))
#define Z_SSAVE	HYPR(KC_S)
#define Z_FND	G(KC_F)
#define Z_RLD	G(KC_R)

// Shortcuts that will be picked up by a tool like BetterTouchTool
// to set Ploopy Nano Trackball leds and toggle scroll mode or reset
#define PLP_SCR    HYPR(KC_S) // Scroll
#define PLP_RST    HYPR(KC_R) // Reset

// Tap hold macros
#define TH_Q    LT(0,KC_Q)
#define TH_M    LT(0,KC_M)
#define TH_Z    LT(0,KC_Z)
#define TH_X    LT(0,KC_X)
#define TH_C    LT(0,KC_C)
#define TH_COMM    LT(0,KC_COMM)
#define TH_DOT    LT(0,KC_DOT)
#define TH_SLSH    LT(0,KC_SLSH)
#define TH_P_COLN    LT(0,KC_P)
#define TH_QUOT_COLN    LT(0,KC_QUOT)
#define TH_DOT_UNDS    LT(0,KC_DOT)
#define TH_COMM_MINUS    LT(0,KC_COMM)
#define TH_SLSH_EXLM    LT(0,KC_SLSH)
#define TH_SCLN_COLN    LT(0,KC_SCLN)
#define TH(k1,k2,k3,k4) LT(0,k1),LT(0,k2),LT(0,k3),LT(0,k4)


// Home row mod-tap macros
#define HM_A	LSFT_T(KC_A)
#define HM_S	LALT_T(KC_S)
#define HM_D	LCTL_T(KC_D)
#define HM_F	LGUI_T(KC_F)
#define HM_J	LGUI_T(KC_J)
#define HM_K	LCTL_T(KC_K)
#define HM_L	LALT_T(KC_L)
#define HM_QUOT	LSFT_T(KC_QUOT)
#define HRML(k1,k2,k3,k4) LCTL_T(k1),LALT_T(k2),LGUI_T(k3),LSFT_T(k4)
#define HRMR(k1,k2,k3,k4) RSFT_T(k1),RGUI_T(k2),RALT_T(k3),RCTL_T(k4)

// One shot mods
#ifdef NO_ACTION_ONESHOT
#define OSM_SFT KC_LSFT
#define OSM_CTL KC_LCTL
#define OSM_ALT KC_LALc
#define OSM_GUI KC_LGUI
#else
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#endif

// Navigation shortcuts
#define SA_UP S(A(KC_UP))
#define SA_DN S(A(KC_DOWN))

// Layers
enum common_layers { BSE, CMK, SYM, NUM, FNC };

// Default 3x5_2 split layout
#define _BASE \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │  Q     │  W     │  E     │  R     │  T     │   │  Y     │  U     │  I     │  O     │  P     │ */\
	TH_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    TH_P_COLN,  \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  A     │  S     │  D     │  F     │  G     │   │  H     │  J     │  K     │  L     │ ' "    │ */\
	KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,    \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  Z     │  X     │  C     │  V     │  B     │   │  N     │  M     │ , <    │ . >    │ / ?    │ */\
	TH_Z,    TH_X,    TH_C,    KC_V,    KC_B,        KC_N,    KC_M,    TH_COMM_MINUS, TH_DOT_UNDS, TH_SLSH_EXLM,    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                  LT(FNC, KC_SPC),    OSM_SFT,     OSM_GUI, TO(SYM)
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */
#define _COLE \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │  Q     │  W     │  F     │  P     │  G     │   │  J     │  L     │  U     │  Y     │ ' "    │ */\
	KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,    \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  A     │  R     │  S     │  T     │  D     │   │  H     │  N     │  E     │  I     │  O     │ */\
	KC_A,    KC_R,    KC_S,    KC_T,    KC_D,        KC_H,    KC_N,    KC_E,    KC_I,    KC_O,       \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  Z     │  X     │  C     │  V     │  B     │   │  K     │  M     │ , <    │ . >    │ / ?    │ */\
	KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                           _______, _______,     _______, _______
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */
#define _COLE_DH \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │  Q     │  W     │  F     │  P     │  G     │   │  J     │  L     │  U     │  Y     │ ' "    │ */\
	KC_Q,    KC_W,    KC_F,  TH_P_COLN, KC_B,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,    \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  A     │  R     │  S     │  T     │  D     │   │  H     │  N     │  E     │  I     │  O     │ */\
	KC_A,    KC_R,    KC_S,    KC_T,    KC_G,        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,       \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  Z     │  X     │  C     │  V     │  B     │   │  K     │  M     │ , <    │ . >    │ / ?    │ */\
	KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,        KC_K,    KC_H,    TH_COMM_MINUS, TH_DOT_UNDS, TH_SLSH_EXLM,    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                           _______, _______,     _______, _______
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */
#define _NUMB \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │ INSERT │  1     │  2     │  3     │ VOL UP │   │ HOME   │ PG DN  │ PG UP  │ END    │  :     │ */\
	QK_GESC, XXXXXXX, KC_VOLD, KC_VOLU, KC_PLUS,     KC_ASTR, KC_7,    KC_8,    KC_9,    KC_BSPC,    \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │ DELETE │  4     │  5     │  6     │ VOL DN │   │ LEFT   │ DOWN   │ UP     │ RIGHT  │  ;     │ */\
	KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS,     KC_EQL,  KC_4,    KC_5,    KC_6,    KC_ENT,     \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │ CAPS   │  7     │  8     │  9     │  0     │   │        │SHFTA DN│SHFTA UP│        │        │ */\
	DF(BSE), DF(CMK), RGB_HUI, RGB_SAI, KC_DOT,      KC_0,    KC_1,    KC_2,    KC_3,    TO(FNC),    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                           TO(BSE), OSM_SFT,     OSM_GUI, TO(SYM)
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */
#define _SYMB \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │        │  [     │  {     │  }     │        │   │  ^     │  (     │  )     │  ]     │  ~     │ */\
	KC_ESC,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, TH_SCLN_COLN, KC_BSPC, \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │  !     │  @     │  #     │  $     │  %     │   │  *     │  -     │  =     │  \     │  `     │ */\
	KC_TAB, KC_EQL,   KC_PLUS, KC_MINS, KC_GRAVE,    KC_BSLS, KC_LCBR, KC_RCBR, KC_PIPE, KC_ENT,     \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │        │        │        │        │        │   │  &     │  _     │  +     │  │     │        │ */\
	KC_BTN1, KC_BTN2, PLP_SCR, KC_WH_U, KC_WH_D,     KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, TO(FNC),    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                           TO(BSE), OSM_SFT,     OSM_GUI, TO(NUM)
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */
#define _FUNC \
/* ╭────────┬────────┬────────┬────────┬────────╮   ╭────────┬────────┬────────┬────────┬────────╮ */\
/* │ BOOT   │  F1    │  F2    │  F3    │ F10    │   │        │ WH UP  │ WH DN  │        │COLEMAK │ */\
	QK_GESC, KC_WH_L, KC_MS_U, KC_WH_R, QK_BOOT,     PLP_RST, KC_HOME, KC_END,  XXXXXXX, KC_BSPC,    \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │        │  F4    │  F5    │  F6    │ F11    │   │ MS LFT │ MS DN  │ MS UP  │ MS RHT │        │ */\
	Z_CUT,   Z_CPY,   Z_PST,   Z_UND, LALT_T(KC_DEL), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  \
/* ├────────┼────────┼────────┼────────┼────────┤   ├────────┼────────┼────────┼────────┼────────┤ */\
/* │ SLEEP  │  F7    │  F8    │  F9    │ F12    │   │        │ BTN 2  │ BTN 1  │        │ SSAVE  │ */\
	KC_BTN1, KC_BTN2, PLP_SCR, KC_WH_U, KC_WH_D,     XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX,    \
/* ╰────────┴────────┴────────┼────────┼────────┤   ├────────┼────────┼────────┴────────┴────────╯ */\
	                           TO(BSE), OSM_CTL,     OSM_GUI, TO(SYM)
/*                            ╰────────┴────────╯   ╰────────┴────────╯ */

// Mod-tap wrapper
#define HRM(k) HR_MODTAP(k)
#define HR_MODTAP( \
	  l01, l02, l03, l04, l05,   r01, r02, r03, r04, r05, \
	  l06, l07, l08, l09, l10,   r06, r07, r08, r09, r10, \
	  l11, l12, l13, l14, l15,   r11, r12, r13, r14, r15, \
	                 l16, l17,   r16, r17                 \
) \
	  l01, l02, l03, l04, l05,   r01, r02, r03, r04, r05,       \
HRML(l06, l07, l08, l09), l10,   r06, HRMR(r07, r08, r09, r10), \
	  l11, l12, l13, l14, l15,   r11,   TH(r12, r13, r14, r15), \
	                 l16, l17,   r16, r17


// Layout aliases for json keymap
#define LAYOUT_34key_w(...) LAYOUT_split_3x5_2(__VA_ARGS__)
#define LAYOUT_crkbd_w(...) LAYOUT_split_3x6_3(__VA_ARGS__)
#define LAYOUT_ortho_w(...) LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_kyria_w(...) LAYOUT_split_3x6_5(__VA_ARGS__)


// Convert 3x5_2 to 42-key
#define C_42(k) CONV_42(k)
#define CONV_42( \
	     l01, l02, l03, l04, l05,   r01, r02, r03, r04, r05, \
	     l06, l07, l08, l09, l10,   r06, r07, r08, r09, r10, \
	     l11, l12, l13, l14, l15,   r11, r12, r13, r14, r15, \
	                    l16, l17,   r16, r17                 \
) \
PLP_SCR, l01, l02, l03, l04, l05,   r01, r02, r03, r04, r05, Z_CUT, \
KC_BTN2, l06, l07, l08, l09, l10,   r06, r07, r08, r09, r10, Z_CPY, \
KC_BTN1, l11, l12, l13, l14, l15,   r11, r12, r13, r14, r15, Z_PST,  \
	     LSA_T(KC_ESC), l16, l17,   r16, r17, RCS_T(KC_BSPC)

// Convert 3x5_2 to 4x12
#define C_O(k) CONV_4x12(k)
#define CONV_4x12( \
	                      l01, l02, l03, l04, l05, r01, r02, r03, r04, r05, \
	                      l06, l07, l08, l09, l10, r06, r07, r08, r09, r10, \
	                      l11, l12, l13, l14, l15, r11, r12, r13, r14, r15, \
	                                     l16, l17, r16, r17                 \
) \
                 KC_TAB,  l01, l02, l03, l04, l05, r01, r02, r03, r04, r05, KC_BSPC, \
                 QK_GESC, l06, l07, l08, l09, l10, r06, r07, r08, r09, r10, KC_SCLN, \
                 KC_LSFT, l11, l12, l13, l14, l15, r11, r12, r13, r14, r15, KC_ENT,  \
KC_DEL, KC_VOLD, KC_VOLU, RSA_T(KC_ESC), l16, l17, r16, r17, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT

// COnvert 3x5_2 to Kyria
#define C_K(k) CONV_KYRIA(k)
#define CONV_KYRIA( \
	     l01, l02, l03, l04, l05,   r01, r02, r03, r04, r05, \
	     l06, l07, l08, l09, l10,   r06, r07, r08, r09, r10, \
	     l11, l12, l13, l14, l15,   r11, r12, r13, r14, r15, \
	                    l16, l17,   r16, r17                 \
) \
    PLP_SCR, l01, l02, l03, l04, l05,                                 r01, r02, r03, r04, r05, Z_CUT, \
    KC_BTN2, l06, l07, l08, l09, l10,                                 r06, r07, r08, r09, r10, Z_CPY, \
    KC_BTN1, l11, l12, l13, l14, l15, Z_CPY, Z_PST,     Z_FND, Z_RLD, r11, r12, r13, r14, r15, Z_PST, \
	  KC_LBRC, KC_LPRN, LSA_T(KC_ESC),  l16,   l17,       r16,   r17,   RCS_T(KC_BSPC), KC_RPRN, KC_RBRC

