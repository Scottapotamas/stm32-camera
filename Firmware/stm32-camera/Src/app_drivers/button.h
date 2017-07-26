/**
 * @file      button.h
 *
 * @brief     Provide button detection handling.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef BUTTON_H
#define BUTTON_H

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_button.h"

/* ----- Defines ------------------------------------------------------------ */


/* ----- Types ------------------------------------------------------------- */

typedef enum
{
    BUTTON_PRESS_TYPE_DOWN = 0x00, /*!< Button pressed */
    BUTTON_PRESS_TYPE_NORMAL,      /*!< Normal press type, released */
    BUTTON_PRESS_TYPE_LONG,        /*!< Long press type */
    BUTTON_PRESS_TYPE_UP           /*!< Button released */
} ButtonPressType_t;

typedef void (*ButtonHandler_t)( ButtonId_t id, ButtonPressType_t press_type );

/* ----- Public Functions --------------------------------------------------- */

/* Configure the given button and set the call back handler
 * Returns true when the button is already pressed
 */

PUBLIC bool
button_init( ButtonId_t id, ButtonHandler_t handler );

/* -------------------------------------------------------------------------- */

/* Background process checking button presses */

PUBLIC void
button_process( void );

/* -------------------------------------------------------------------------- */

#endif /* BUTTON_H */
