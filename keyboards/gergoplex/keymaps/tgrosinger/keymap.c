#include QMK_KEYBOARD_H

#define BASE 0    // Default layer
#define WINDOWS 1 // Windows shortcuts layer
#define SYMB 2    // Symbols layer
#define NUMB 3    // Numbers layer
#define ARROWS 4  // Arrows and mouse layer
#define TMUX 5    // TMUX Nav layer

// Combos
enum combos {
  WS,QW,SD,DF,IO,OP,CV,CD,
  HJ,JK,KL,MC,NM,
  FV,GB,HN
};

// NOTE: If you're using MT,LT or anything you must
// define it here. Note this if you change your layout!
/* Keymap 0: Basic layer
 *
 * ,-----------------------------.      ,-----------------------------.
 * |     `     |     |     |     |      |     |    MINS   |    BSLH   |
 * |-----+----ESC----+-----+-----|      |-----+-----------------------|
 * |     |   BSPC   TAB    |     |      |    LES   COLN  GRT    |     |
 * |-----+-----+-----+--RMB+-LMB-|      |-ENT-------------------------|
 * |     |     |    ENT    |     |      |    QUO   UNDR   |     |     |
 * `-----+-----+-----+-----+-----'      `-----------------------------'
 *     .-------------------------.           .-----------------.
 *     |        |       |        |           |        |    |   |
 *     '-------------------------'           '-----------------'
 */
const uint16_t PROGMEM ws_combo[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM cd_combo[] = {KC_C, KC_D, COMBO_END};

const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END}; 
const uint16_t PROGMEM mc_combo[] = {KC_M, KC_COMM, COMBO_END};

const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM hn_combo[] = {KC_H, KC_N, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  // Horizontal Chords
  [QW] = COMBO(qw_combo, KC_GRV),
  [SD] = COMBO(sd_combo, KC_BSPC),
  [DF] = COMBO(df_combo, KC_TAB),
  [CV] = COMBO(cv_combo, KC_ENT),
  [CD] = COMBO(cd_combo, KC_ENT),

  [IO] = COMBO(io_combo, KC_MINS),
  [OP] = COMBO(op_combo, KC_BSLS),
  [HJ] = COMBO(hj_combo, KC_LT),
  [JK] = COMBO(jk_combo, KC_COLN),
  [KL] = COMBO(kl_combo, KC_GT),
  [MC] = COMBO(mc_combo, KC_UNDS), // m,
  [NM] = COMBO(nm_combo, KC_QUOT),
  
  // Vertical
  [WS] = COMBO(ws_combo, KC_ESC),
  [GB] = COMBO(gb_combo, KC_BTN1),
  [FV] = COMBO(fv_combo, KC_BTN2),
  [HN] = COMBO(hn_combo, KC_ENT)
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
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default layer
 * ,-----------------------------.       ,----------------------------------.
 * |  Q   |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |   O   |    P   |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-------+--------|
 * |CTRL/A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |   L   | CTRL/; |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-------+--------|
 * |SHFT/Z|ALT/X|  C  |  V  |  B  |      |  N  |  M  |  <  | ALT/> | SHFT/? |
 * `------+-----+-----+------+----'      `----------------------------------'
 *           .-----------------.             .----------------------.
 *           |GUI|SHFT|SPC(NUM)|             |SPC(SYM)|TMUX |WINDOWS|
 *           '-----------------'             '----------------------'
 */
[BASE] = LAYOUT_gergoplex(
    KC_Q,              KC_W,               KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P, 
    MT(MOD_LCTL, KC_A),KC_S,               KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   MT(MOD_LCTL, KC_SCLN),
    MT(MOD_LSFT, KC_Z),MT(MOD_LALT, KC_X), KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, MT(MOD_LALT, KC_DOT), MT(MOD_RSFT, KC_SLSH),
            
    KC_LGUI, KC_LSFT, LT(NUMB, KC_SPC),       // Left
    LT(SYMB, KC_SPC), MO(TMUX), MO(WINDOWS)   // Right
    ),

/* Keymap 1: Windows layer
 * ,------------------------------.       ,----------------------------------.
 * |      |      |     |     |     |      |     |     |      |      |        |
 * |------+------+-----+-----+-----|      |-----+-----+------+------+--------|
 * |      |SCNSHT|     |     |     |      |D-Lft|W-Lft|W-Rght|D-Rght|        |
 * |------+------+-----+-----+-----|      |-----+-----+------+------+--------|
 * |      |      |     |     |     |      |     |     |      |      |        |
 * `------+------+-----+------+----'      `----------------------------------'
 *           .-----------------.             .---------------------.
 *           |   |SHFT|        |             |        |     | HLD  |
 *           '-----------------'             '---------------------'
 */
[WINDOWS] = LAYOUT_gergoplex(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, G(S(KC_S)), KC_NO, KC_NO, KC_NO,    G(C(KC_LEFT)), S(A(KC_TAB)), A(KC_TAB), G(C(KC_RGHT)), KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
            
    KC_NO, KC_LSFT, KC_NO,    // Left
    KC_NO, KC_NO,   KC_NO   // Right
    ),

/* Keymap 2: Symbols layer
 * ,-----------------------------.       ,-------------------------------.
 * |  !   |  @  |  #  |  $  |  %  |      |  ^  |  &  |  *  |  +  |   =   |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
 * |  F1  | F2  | F3  | F4  | F5  |      | F6  | F7  | F8  | F9  |  F10  |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
 * |      |     |     |     |     |      |     |     |     | F11 |  F12  |
 * `------+-----+-----+-----+-----'      `-------------------------------'
 *        .-----------------.                  .-----------------.
 *        |     | DEL | MO3 |                  | HLD | SPC |     |
 *        '-----------------'                  '-----------------'
 */
[SYMB] = LAYOUT_gergoplex(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_F11,  KC_F12,
                   KC_NO, KC_DEL, MO(ARROWS),        KC_TRNS,  KC_SPC, KC_NO
    ),

/* Keymap 3: Number layer
 * ,-----------------------------.       ,-------------------------------.
 * |  1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
 * | CTRL |     |  (  |  )  |     |      |     |  4  |  7  |  6  |       |
 * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
 * | SHFT |     |  [  |  ]  |     |      |     |  1  |  2  |  3  |   .   |
 * `------+-----+-----+-----+-----'      `-------------------------------'
 *        .-----------------.                  .-----------------.
 *        |     |     | HLD |                  | MO3 |  0  |     |
 *        '-----------------'                  '-----------------'
 */
[NUMB] = LAYOUT_gergoplex(
    KC_1,    KC_2,  KC_3,    KC_4,    KC_5,       KC_6,  KC_7, KC_8, KC_9,  KC_0,
    KC_LCTL,   KC_NO, KC_LPRN, KC_RPRN, KC_NO,      KC_NO, KC_4, KC_5, KC_6,  KC_NO,
    KC_LSFT, KC_NO, KC_LBRC, KC_RBRC, KC_NO,      KC_NO, KC_1, KC_2, KC_3, KC_DOT,
                 KC_NO,KC_NO,KC_TRNS,             MO(ARROWS),KC_0,KC_NO
    ),

/* Keymap 4: Arrows and mouse layer
 * ,-----------------------------.       ,-------------------------------------------.
 * |      |     |     |     |     |      | SS PGDN | S PGDN | S PGUP | SS PGUP |     |
 * |------+-----+-----+-----+-----|      |---------+--------+--------+---------+-----|
 * | CTRL |HOME | PUP | M1  | M2  |      |   LEFT  |  DOWN  |   UP   |  RIGHT  |     |
 * |------+-----+-----+-----+-----|      |---------+--------+--------+---------+-----|
 * | SHFT |END  | PDN |     | M3  |      |   M LT  |  M DN  |  M UP  |  M RT   |     |
 * `------+-----+-----+-----+-----'      `-------------------------------------------'
 *        .-----------------.                   .-----------------.
 *        |     |     | HLD |                   | HLD |     |     |
 *        '-----------------'                   '-----------------'
 */
[ARROWS] = LAYOUT_gergoplex(
    KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,     SGUI(KC_PGDN),LGUI(KC_PGDN), LGUI(KC_PGUP), SGUI(KC_PGUP), KC_NO,
    KC_LCTL, KC_HOME, KC_PGUP, KC_BTN1, KC_BTN2,   KC_LEFT,      KC_DOWN,       KC_UP,         KC_RGHT,       KC_NO,
    KC_LSFT, KC_END,  KC_PGDN, KC_NO,   KC_BTN3,   KC_MS_L,      KC_MS_D,       KC_MS_U,       KC_MS_R,       KC_NO,
                 KC_NO,KC_NO,KC_TRNS,              KC_TRNS,KC_NO,KC_NO
    ),
    
/* Keymap 5: Tmux navigation layer
 * ,--------------------------------.      ,---------------------------------------.
 * | Vi Mcr |     |     |     | SP VT |      | Vi Ynk|       |       |       | Vi PT |
 * |--------+-----+-----+-----+-------|      |-------+-------+-------+-------+-------|
 * |        | SCRL|     |     |       |      | PN LT | PN DN | PN UP | PN RT | SP HZ |
 * |--------+-----+-----+-----+-------|      |-------+-------+-------+-------+-------|
 * |  ZOOM  | KILL| NEW |     |       |      | W LT  |       |       | W RT  |       |
 * `--------+-----+-----+-----+-------'      `---------------------------------------'
 *          .-----------------.                   .-----------------.
 *          |     | HLD |     |                   |     |     |     |
 *          '-----------------'                   '-----------------'
 */
[TMUX] = LAYOUT_gergoplex(
    VIM_MACRO, KC_NO,       KC_NO,    KC_NO, TMUX_SP_VT,      VIM_CLIP_CP, KC_NO,      KC_NO,      KC_NO,      VIM_CLIP_PST,
    KC_NO,     TMUX_SCROLL, KC_NO,    KC_NO, KC_NO,           TMUX_PN_LT,  TMUX_PN_DN, TMUX_PN_UP, TMUX_PN_RT, TMUX_SP_HZ,
    TMUX_ZOOM, KC_NO,       TMUX_NEW, KC_NO, KC_NO,           TMUX_WN_LT,  KC_NO,      KC_NO,      TMUX_WN_RT, KC_NO,
                 KC_NO,KC_TRNS,KC_NO,                              KC_NO,KC_NO,KC_NO
    )
};
