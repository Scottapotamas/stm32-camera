/**
 * @file      app_task_supervisor.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Supervisor
*
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_SUPERVISOR_H
#define APP_TASK_SUPERVISOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"
#include "state_task.h"
#include "event_timer.h"

/* ----- State Task Control Block ------------------------------------------- */

/** Application Task Control Block File System */
typedef struct AppTaskSupervisor AppTaskSupervisor;
struct AppTaskSupervisor
{
    // ~~~ Core task structure ~~~
    StateTask             super;                 ///< Core task structure

    // ~~~ Task Timers ~~~
    EventTimer       timer1;                ///< Local state timer 1
    EventTimer       timer2;                ///< Local state timer 2

    // ~~~ Task Variables ~~~
    uint8_t          counter;

    bool              user_interactive;
    float             temperature_C;

};

/* ----- Public Functions --------------------------------------------------- */

/**
 * @brief  Create the supervisor I/O task
 * @param  me             Reference to own task structure
 * @param  priority       Task priority level (fixed at compile time).
 * @param  eventQueueData event queue for this task
 * @param  eventQueueSize size of queue
 * @return StateTask *
 */

PUBLIC StateTask *
appTaskSupervisorCreate( AppTaskSupervisor *me,
                         StateEvent        *eventQueueData[],
                         const uint8_t     eventQueueSize );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_SUPERVISOR_H */
