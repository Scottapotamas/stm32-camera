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

    /* System Status Signals */
    SYSTEM_STATUS_ERROR,
    SYSTEM_STATUS_SETUP,

    /* Terminal character received */
    TERMINAL_INPUT_CHAR_SIGNAL,
	TERMINAL_MODE_SIGNAL,

    AUXILIARY_MODE_SIGNAL,

    /* File System Triggers */
    FILE_SYSTEM_CMD_MOUNT,
    FILE_SYSTEM_CMD_UNMOUNT,
    FILE_SYSTEM_MOUNTED,
    FILE_SYSTEM_UNMOUNTED,

    /* Configuration setting changed */
    CONFIG_SETTING_CHANGED_SIGNAL,

    /* Camera */
    CAMERA_CMD_ON,
    CAMERA_CMD_CAPTURE_NORMAL,
    CAMERA_CMD_OFF,
    CAMERA_STATUS_OFF,
    CAMERA_STATUS_ERROR,
    CAMERA_STATUS_READY,
    CAMERA_STATUS_CAPTURING,
    CAMERA_STATUS_CAPTURED,
    CAMERA_STATUS_SAVING,
    CAMERA_STATUS_SAVE_DONE,

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
