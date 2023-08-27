// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#include "filterpaper.h"

#if (defined TAPPING_TERM_PER_KEY || defined PERMISSIVE_HOLD_PER_KEY)
static uint_fast16_t tap_timer = 0;
#endif


#ifdef TAPPING_TERM_PER_KEY
// Scale tapping term to short key press interval to avoid false trigger.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	return IS_HOME_ROW() && IS_TYPING() ? IS_TYPING_TERM : TAPPING_TERM;
}
#endif


#ifdef QUICK_TAP_TERM_PER_KEY
// Reduce quick tap term for thumb keys
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
	return IS_THUMB_ROW() ? QUICK_TAP_TERM / 2 : QUICK_TAP_TERM;
}
#endif


#ifdef PERMISSIVE_HOLD_PER_KEY
// Select Shift mod tap immediately when another key is pressed and released.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
	return MODTAP_BIT(keycode) & MOD_MASK_SHIFT && !IS_TYPING() ? true : false;
}
#endif


#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
// Select hold immediately with another key for layer tap 1 and higher.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
	return IS_LAYER_TAP(keycode) ? true : false;
}
#endif


// Send custom hold keycode for mod tap.
static inline bool process_tap_hold(uint16_t hold_keycode, keyrecord_t *record) {
	if (!record->tap.count) {
		tap_code16(hold_keycode);
		return false;
	}
	return true;
}


bool process_record_user(uint16_t const keycode, keyrecord_t *record) {
	if (record->event.pressed) {
#if (defined TAPPING_TERM_PER_KEY || defined PERMISSIVE_HOLD_PER_KEY)
		tap_timer = timer_read();
#endif
#if (defined OLED_ENABLE && !defined WPM_ENABLE)
		extern uint32_t oled_tap_timer;
		oled_tap_timer = timer_read32();
#endif
#ifdef AUTO_CORRECT
		extern bool process_autocorrect(uint16_t keycode, keyrecord_t* record);
		if (!process_autocorrect(keycode, record)) {
			return false;
		}
#endif
#ifdef CAPS_UNLOCK
		extern bool process_caps_unlock(uint16_t keycode, keyrecord_t *record);
		if (!process_caps_unlock(keycode, record)) {
			return false;
		}
#endif
		// Clipboard shortcuts.
		switch(keycode) {
			// case TH_SLSH: return process_tap_hold(Z_UND, record);
			// case TH_DOT:  return process_tap_hold(Z_CUT, record);
			// case TH_COMM: return process_tap_hold(Z_CPY, record);
			// case TH_M:    return process_tap_hold(Z_PST, record);
			case TH_Q:    return process_tap_hold(KC_ESC, record);
			case TH_Z:    return process_tap_hold(KC_BTN1, record);
			case TH_X:    return process_tap_hold(KC_BTN2, record);
			case TH_C:    return process_tap_hold(PLP_SCR, record);
  		case TH_QUOT_COLN: return process_tap_hold(KC_COLN, record);
  		case TH_P_COLN: return process_tap_hold(KC_COLN, record);
      case TH_DOT_UNDS: return process_tap_hold(KC_UNDS, record);
      case TH_COMM_MINUS: return process_tap_hold(KC_MINUS, record);
      case TH_SLSH_EXLM: return process_tap_hold(KC_EXLM, record);
      case TH_SCLN_COLN: return process_tap_hold(KC_COLN, record);
    }
  }
	return true;
}

// void keyboard_post_init_user(void) {
// #if defined(KEYBOARD_splitkb_aurora_sweep_rev1)
//   g_led_config.flags[21] = LED_FLAG_MODIFIER;
//   g_led_config.flags[22] = LED_FLAG_MODIFIER;
//   g_led_config.flags[44] = LED_FLAG_MODIFIER;
//   g_led_config.flags[45] = LED_FLAG_MODIFIER;
// }
// #endif

