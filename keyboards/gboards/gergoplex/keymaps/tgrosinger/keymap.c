/* Copyright 2022 Tony Grosinger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum {
  _ALPHA,  // Default
  _SYMB,   // Symbols
  _NUMB,   // Numbers
  _TMUX,   // TMUX Nav layer
};


// Macros
enum custom_keycodes {
  TMUX_NEW = SAFE_RANGE,
  TMUX_ZOOM,
  TMUX_SCROLL,
  TMUX_PN_LT,
  TMUX_PN_UP,
  TMUX_PN_DN,
  TMUX_PN_RT,
  TMUX_WN_LT,
  TMUX_WN_RT,
  TMUX_SP_VT,
  TMUX_SP_HZ,
  VIM_CLIP_CP,
  VIM_CLIP_PST,
  VIM_MACRO,
  VIM_SAVE,
};

// Tap Dance declarations
enum {
  SLSH_BSLS,
  SCLN_COLN,
  NUMB_TMUX,
};

// Tap Dance advanced fn states
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

// Tap Dance state
typedef struct {
  bool is_press_action;
  int state;
} tap;

static tap numb_tmux_state = {
  .is_press_action = true,
  .state = 0
};

static tap scln_coln_state = {
  .is_press_action = true,
  .state = 0
};

// Tap Dance helpers

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

void numb_tmux_finished(qk_tap_dance_state_t *state, void *user_data) {
  numb_tmux_state.state = cur_dance(state);
  switch (numb_tmux_state.state) {
    case SINGLE_TAP:
      set_oneshot_layer(_TMUX, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD:
      layer_on(_NUMB);
      break;
  }
}

void numb_tmux_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (numb_tmux_state.state) {
    case SINGLE_HOLD:
      layer_off(_NUMB);
      break;
  }
  numb_tmux_state.state = 0;
}

void scln_coln_finished(qk_tap_dance_state_t *state, void *user_data) {
  scln_coln_state.state = cur_dance(state);
  switch (scln_coln_state.state) {
    case SINGLE_TAP:
      tap_code(KC_SCLN);
      break;
    case SINGLE_HOLD:
      register_code(KC_LCTL);
      break;
    case DOUBLE_TAP:
      tap_code16(KC_COLN);
      break;
  }
}

void scln_coln_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch(scln_coln_state.state) {
    case SINGLE_HOLD:
      unregister_code(KC_LCTL);
      break;
  }
  scln_coln_state.state = 0;
}


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for "/", twice for "\"
    [SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [SCLN_COLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_coln_finished, scln_coln_reset),
    [NUMB_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numb_tmux_finished, numb_tmux_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(0, KC_H):
      // Override "h" if held
      if (!record->tap.count && record->event.pressed) {
        tap_code16(C(G(KC_LEFT)));
        return false;
      }
      return true;
    case LT(0, KC_L):
      // Override "l" if held
      if (!record->tap.count && record->event.pressed) {
        tap_code16(C(G(KC_RIGHT)));
        return false;
      }
      return true;
    case LT(0, KC_Z):
      // Override "z" if held
      if (!record->tap.count && record->event.pressed) {
        tap_code16(C(S(KC_ESC)));
        return false;
      }
      return true;
    case LT(0, KC_E):
      // Override "e" if held
      if (!record->tap.count && record->event.pressed) {
        tap_code16(G(KC_E));
        return false;
      }
      return true;
    case LT(0, KC_R):
      // Override "r" if held
      if (!record->tap.count && record->event.pressed) {
        tap_code16(G(KC_R));
        return false;
      }
      return true;
    case TMUX_NEW:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("c");
      }
      break;
    case TMUX_ZOOM:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("z");
      }
      break;
    case TMUX_SCROLL:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("[");
      }
      break;
    case TMUX_PN_LT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_LEFT);
      }
      break;
    case TMUX_PN_DN:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_DOWN);
      }
      break;
    case TMUX_PN_UP:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_UP);
      }
      break;
    case TMUX_PN_RT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        tap_code(KC_RIGHT);
      }
      break;
    case TMUX_WN_LT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("p");
      }
      break;
    case TMUX_WN_RT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("n");
      }
      break;
    case TMUX_SP_VT:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("%");
      }
      break;
    case TMUX_SP_HZ:
      if (record->event.pressed) {
        tap_code16(C(KC_B));
        SEND_STRING("\"");
      }
      break;
    case VIM_CLIP_CP:
      if (record->event.pressed) {
        tap_code16(S(KC_QUOTE));
        tap_code16(S(KC_EQUAL));
        tap_code(KC_Y);
      }
      break;
    case VIM_CLIP_PST:
      if (record->event.pressed) {
        tap_code16(S(KC_QUOTE));
        tap_code16(S(KC_EQUAL));
        tap_code(KC_P);
      }
      break;
    case VIM_MACRO:
      if (record->event.pressed) {
        tap_code16(S(KC_2));
        tap_code(KC_Q);
      }
      break;
    case VIM_SAVE:
      if (record->event.pressed) {
        tap_code(KC_ESC);
        tap_code16(KC_COLN);
        tap_code(KC_W);
        tap_code16(KC_ENT);
        tap_code16(C(KC_T));
      }
      break;
    /*
    case LAYRMOD:
      // Act as a mod key if held, or toggle a layer if tapped
      // replace KC_LCTL with desired mod, and _TARGET with desired layer name / number
      if (record->event.pressed) {
        uint8_t key_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
      } else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(key_timer) < 200) {
          layer_invert(_TARGET);
        }
      }
      return false;
      break;
    */
  }
  return true;
}

// TODO: Add a back and forward button for use in the browser?

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x5_3(
      KC_Q,        KC_W, LT(0, KC_E), LT(0, KC_R), KC_T,      KC_Y,        KC_U,        KC_I,        KC_O,        KC_P, 
      CTL_T(KC_A), KC_S, KC_D,        KC_F,        KC_G,      LT(0, KC_H), GUI_T(KC_J), ALT_T(KC_K), LT(0, KC_L), TD(SCLN_COLN),
      LT(0, KC_Z), KC_X, KC_C,        KC_V,        KC_B,      KC_N,        KC_M,        KC_COMM,     KC_DOT,      TD(SLSH_BSLS),
          KC_NO, TD(NUMB_TMUX), KC_LSFT,                              KC_SPC, MO(_SYMB), KC_NO
      ),
  [_NUMB] = LAYOUT_split_3x5_3(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,  KC_7, KC_8, KC_9,  KC_0,
      KC_LCTL, KC_LT,   KC_LPRN, KC_RPRN, KC_GT,        KC_NO, KC_4, KC_5, KC_6,  KC_NO,
      KC_LSFT, KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR,      KC_NO, KC_1, KC_2, KC_3,  KC_DOT,
          KC_NO, KC_TRNS, DF(_ALPHA),                       DF(_NUMB), KC_0, KC_NO
      ),
  [_SYMB] = LAYOUT_split_3x5_3(
      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,
      KC_LCTL, KC_NO,   KC_NO,   KC_HOME, KC_PGUP,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
      KC_NO,   KC_NO,   KC_NO,   KC_END,  KC_PGDN,     KC_F1,   KC_F2,   KC_F4,   KC_F5,   KC_F12,
          KC_NO, KC_NO, DF(_ALPHA),                        DF(_SYMB),  KC_TRNS, KC_NO
      ),
  [_TMUX] = LAYOUT_split_3x5_3(
      VIM_MACRO, VIM_SAVE,    KC_NO,    KC_NO,      TMUX_SP_VT,      VIM_CLIP_CP, KC_NO,      KC_NO,      KC_NO,      VIM_CLIP_PST,
      KC_NO,     TMUX_SCROLL, KC_NO,    C(KC_TILD), KC_NO,           TMUX_PN_LT,  TMUX_PN_DN, TMUX_PN_UP, TMUX_PN_RT, TMUX_SP_HZ,
      TMUX_ZOOM, KC_NO,       TMUX_NEW, KC_NO,      KC_NO,           TMUX_WN_LT,  KC_NO,      KC_NO,      TMUX_WN_RT, KC_NO,
          KC_NO, KC_DEL, DF(_ALPHA),                                     DF(_TMUX), KC_TRNS, KC_NO
      ),
};
