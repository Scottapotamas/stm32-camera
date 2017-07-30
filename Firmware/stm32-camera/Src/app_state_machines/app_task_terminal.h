/**
 * @file      app_task_terminal.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task auxiliary
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_TERMINAL_H
#define APP_TASK_TERMINAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- System Includes ---------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "state_task.h"
#include "event_timer.h"
#include "hal_uart.h"
#include "cmd.h"

/* ----- State Task Control Block ------------------------------------------- */

/** Application Task Control Block File System */
typedef struct AppTaskTerminal AppTaskTerminal;
struct AppTaskTerminal
{
    // ~~~ Core task structure ~~~
    StateTask       super;           // Core task structure

    // ~~~ Task Timers ~~~
    EventTimer      timer;           // Task State timer

    // ~~~ Task Variable ~~~
    HalUartPort_t   instance;           // Which uart to use
    CmdHandler      monitor;            // Command parser
    char            buffer[80];
    uint8_t         buffer_index;
};

/* ----- Public Functions --------------------------------------------------- */

/**
 * @brief  Create the terminal task
 * @param  me             Reference to own task structure
 * @param  priority       Task priority level (fixed at compile time).
 * @param  eventQueueData event queue for this task
 * @param  eventQueueSize size of queue
 * @return StateTask *
 */

PUBLIC StateTask *
appTaskTerminalCreate( AppTaskTerminal   *me,
                        StateEvent         *eventQueueData[ ],
                        uint8_t             eventQueueSize,
						HalUartPort_t     instance );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_TERMINAL_H */
