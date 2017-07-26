/**
 * @file    app_events.h
 *
 * @brief   Application Level Custom Event Structures.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2013-2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_EVENTS_H
#define APP_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "app_config.h"
#include "state_task.h"
#include "state_event.h"
#include "button.h"
#include "hal_i2c.h"
#include "auxiliary.h"
#include "hal_uart.h"

/* -------------------------------------------------------------------------- */

/** Internal report of button event */
typedef struct ButtonEvent__
{
    StateEvent        super;             /**< Encapsulated event reference */
    ButtonId_t        id;                /**< ID number of button event */
    ButtonPressType_t press_type;        /**< Type of button event */
} ButtonEvent;

/** Report detected button presses */
typedef struct ButtonPressedEvent__
{
    StateEvent    super;             /**< Encapsulated event reference */
    ButtonId_t    id;                /**< ID number of button event */
} ButtonPressedEvent;

/* -------------------------------------------------------------------------- */

/** Report changes in auxillary mode */
typedef struct AuxiliaryModeEvent__
{
    StateEvent       super;          /**< Encapsulated event reference */
    AuxiliaryPort_t  port;           /**< Aux port for mode switch */
    AuxiliaryMode_t  mode;           /**< Aux mode to switch to */
} AuxiliaryModeEvent;

/* -------------------------------------------------------------------------- */

/** Report changes in terminal mode */
typedef struct TerminalModeEvent__
{
    StateEvent       super;          /**< Encapsulated event reference */
    HalUartPort_t	 port;           /**< terminal port for mode switch */
    //TODO use a mode object here to act as baud rate allowing for event calls on baud change.
} TerminalModeEvent;

/* -------------------------------------------------------------------------- */

typedef struct TerminalCharEvent__
{
    StateEvent    super;
    uint8_t       ch;
} TerminalCharEvent;

/* -------------------------------------------------------------------------- */

/** Report detected button presses */
typedef struct KeyboardEvent__
{
    StateEvent super;             /**< Encapsulated event reference */
    char       key;
} KeyboardEvent;

/* -------------------------------------------------------------------------- */

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_EVENTS_H */
