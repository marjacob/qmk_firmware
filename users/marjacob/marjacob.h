// vim:et:ts=4:sw=4:sts=4:
#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

#define FN_BASE TO(_BASE)
#define FN_HHKB MO(_HHKB)
#define FN_HJKL MO(_HJKL)
#define FN_MOUS TO(_MOUSE)
#define TD_LSFT TD(TDI_LSFT)
#define TD_SCLN TD(TDI_SCLN)
#define XXXXXXX KC_NO
#define _______ KC_TRNS

enum userspace_action {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5,
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
};

enum userspace_keycode {
    UK_CHKL = SAFE_RANGE,
    UK_CTLT,
    UK_CTLW,
    NEW_SAFE_RANGE
};

enum userspace_layer {
    _BASE = 0,
    _HHKB,
    _HJKL,
    _MOUSE,
    _EMPTY
};

enum userspace_tapdance {
    TDI_LSFT = 0,
    TDI_SCLN
};

typedef struct {
    bool is_press_action;
    int state;
} userspace_tap;

int cur_dance(qk_tap_dance_state_t *state);

void lsft_finished(qk_tap_dance_state_t *state, void *user);

void lsft_reset(qk_tap_dance_state_t *state, void *user);

void scln_finished(qk_tap_dance_state_t *state, void *user);

void scln_reset(qk_tap_dance_state_t *state, void *user);