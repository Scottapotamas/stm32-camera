/**
 * @file      app_task_log.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Log
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_LOG_H
#define APP_TASK_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"
#include "state_task.h"
#include "event_timer.h"
#include "fifo.h"
#include "ff.h"

/* ----- State Task Control Block ------------------------------------------- */

/** Application Task Control Block Sensor */
typedef struct AppTaskLog AppTaskLog;
struct AppTaskLog
{
    // ~~~ Core task structure ~~~
    StateTask                    super;

    // ~~~ Task Timers ~~~
    EventTimer                   timer;
    EventTimer                   flush_delay_timer;

    // ~~~ Task Variables ~~~
    char                         log_path_name[ MAX_FILE_NAME_LEN ];
    char                         log_file_name[ MAX_FILE_NAME_LEN ];
    FIL                          log_file;
    FRESULT                      f_result;
};

/* ----- Public Functions --------------------------------------------------- */

/**
 * @brief  Create the Log task
 * @param  me             Reference to own task structure
 * @param  priority       Task priority level (fixed at compile time).
 * @param  eventQueueData event queue for this task
 * @param  eventQueueSize size of queue
 * @return StateTask *
 */
PUBLIC StateTask *
appTaskLogCreate( AppTaskLog    *me,
                  StateEvent    *eventQueueData[],
                  const uint8_t eventQueueSize );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_LOG_H */
