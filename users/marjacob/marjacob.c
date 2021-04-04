#include "marjacob.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

static userspace_tap lsft_tap_state = { .is_press_action = true, .state = 0 };
static userspace_tap scln_tap_state = { .is_press_action = true, .state = 0 };

qk_tap_dance_action_t tap_dance_actions[] = {
    [TDI_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_finished, lsft_reset),
    [TDI_SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_finished, scln_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed) {
        switch(keycode) {
        case UK_CHKL:
            SEND_STRING(SS_LGUI(" "));
            return false;
        case UK_CTLT:
            SEND_STRING(SS_LCTRL("t"));
            return false;
        case UK_CTLW:
            SEND_STRING(SS_LCTRL("w"));
            return false;
        }
    }

    return true;
}

int cur_dance(qk_tap_dance_state_t *state)
{
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        }

        return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) {
            return DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            return DOUBLE_HOLD;
        }

        return DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) {
            return TRIPLE_TAP;
        }

        return TRIPLE_HOLD;
    }

    return 8;
}

void lsft_finished(qk_tap_dance_state_t *state, void *user)
{
    switch ((lsft_tap_state.state = cur_dance(state))) {
    case DOUBLE_HOLD:
        layer_on(_MOUSE);
        break;
    default:
        register_code(KC_LSFT);
        break;
    }
}

void lsft_reset(qk_tap_dance_state_t *state, void *user)
{
    switch (lsft_tap_state.state) {
    case DOUBLE_HOLD:
        layer_off(_MOUSE);
        break;
    default:
        unregister_code(KC_LSFT);
        break;
    }

    lsft_tap_state.state = 0;
}

void scln_finished(qk_tap_dance_state_t *state, void *user)
{
    switch ((scln_tap_state.state = cur_dance(state))) {
    case SINGLE_HOLD:
        layer_on(_HJKL);
        break;
    default:
        register_code(KC_SCLN);
        break;
    }
}

void scln_reset(qk_tap_dance_state_t *state, void *user)
{
    switch (scln_tap_state.state) {
    case SINGLE_HOLD:
        layer_off(_HJKL);
        break;
    default:
        unregister_code(KC_SCLN);
        break;
    }

    scln_tap_state.state = 0;
}

