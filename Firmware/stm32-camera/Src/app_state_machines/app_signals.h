/**
 * @file    app_signals.h
 *
 * @brief   Special application level signals for state machine handling.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2013-2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_SIGNALS_H
#define APP_SIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "state_event.h"

/* ----- Types -------------------------------------------------------------- */

enum AppSignals
{
    /* System Command Signals */
    SYSTEM_CMD_POWER_OFF = STATE_USER_SIGNAL, // Signal 8 - First Custom Signal,
    SYSTEM_CMD_ARM,
    SYSTEM_CMD_DISARM,

    /* System Status Signals */

    TERMINAL_INPUT_CHAR_SIGNAL,
	TERMINAL_MODE_SIGNAL,

    AUXILIARY_MODE_SIGNAL,


    SYSTEM_STATUS_ERROR,
    SYSTEM_STATUS_PASSIVE,
    SYSTEM_STATUS_SETUP,

    /* Button Signals */
    BUTTON_EVENT_SIGNAL,            /* Internal button activity event */
    BUTTON_PRESSED_SIGNAL,          /* Key Down Event */
    BUTTON_NORMAL_SIGNAL,           /* Normal Key Press Event */
    BUTTON_LONG_SIGNAL,             /* Long Key Press Event */
    BUTTON_RELEASED_SIGNAL,         /* Key Up Event */

    /* Last Available Signal - Don't Remove This */
    STATE_MAX_SIGNAL
};

/* ----------------------- End --------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_SIGNALS_H */
