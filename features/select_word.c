// Copyright 2021 Google LLC
// @filterpaper
// SPDX-License-Identifier: Apache-2.0
// https://getreuer.info/posts/keyboards/select-word

#include "select_word.h"

// Mac users, uncomment this line:
// #define MAC_HOTKEYS

enum { STATE_NONE, STATE_SELECTED, STATE_WORD, STATE_FIRST_LINE, STATE_LINE };

bool process_select_word(uint16_t keycode, keyrecord_t* record, uint16_t sel_keycode) {
	static uint8_t state = STATE_NONE;

	if (keycode == KC_LSFT || keycode == KC_RSFT) { return true; }

	if (keycode == sel_keycode && record->event.pressed) {  // On key press.
		const uint8_t mods = get_mods();
		if (((mods | get_oneshot_mods()) & MOD_MASK_SHIFT) == 0) {  // Select word.
#ifdef MAC_HOTKEYS
			register_code(KC_LALT);
#else
			register_code(KC_LCTL);
#endif
			if (state == STATE_NONE) { SEND_STRING(SS_TAP(X_RGHT) SS_TAP(X_LEFT)); }
			register_code(KC_LSFT);
			register_code(KC_RGHT);
			state = STATE_WORD;
		} else {  // Select line.
			if (state == STATE_NONE) {
				clear_mods();
				clear_oneshot_mods();
#ifdef MAC_HOTKEYS
				SEND_STRING(SS_LCTL("a" SS_LSFT("e")));
#else
				SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)));
#endif
				set_mods(mods);
				state = STATE_FIRST_LINE;
			} else {
				register_code(KC_DOWN);
				state = STATE_LINE;
			}
		}
		return false;
	}

	// `sel_keycode` was released, or another key was pressed.
	switch (state) {
		case STATE_WORD:
			unregister_code(KC_RGHT);
			unregister_code(KC_LSFT);
#ifdef MAC_HOTKEYS
			unregister_code(KC_LALT);
#else
			unregister_code(KC_LCTL);
#endif
			state = STATE_SELECTED;
			break;
		case STATE_FIRST_LINE:
			state = STATE_SELECTED;
			break;
		case STATE_LINE:
			unregister_code(KC_DOWN);
			state = STATE_SELECTED;
			break;
		case STATE_SELECTED:
			if (keycode == KC_ESC) {
				tap_code(KC_RGHT);
				state = STATE_NONE;
				return false;
			}
		default:
			state = STATE_NONE;
	}

	return true;
}
