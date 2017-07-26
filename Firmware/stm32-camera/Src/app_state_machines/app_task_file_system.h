/**
 * @file      app_task_file_system.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task File System
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_FILE_SYSTEM_H
#define APP_TASK_FILE_SYSTEM_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "ff.h"
#include "state_task.h"
#include "event_timer.h"
#include "filesystem.h"

/* ----- State Task Control Block ------------------------------------------- */


/** Application Task Control Block File System */
typedef struct AppTaskFileSystem AppTaskFileSystem;
struct AppTaskFileSystem
{
    // ~~~ Core task structure ~~~
    StateTask  super;                /**<  Core task structure */

    // ~~~ Task Timers ~~~
    EventTimer timer;                /**<  Task State timer */

    // ~~~ File System Mounted ~~~
    uint8_t    retry;                 /**< Last task performing request */
    StateTask  *mount_task;           /**< Last task performing request */
    uint8_t    last_unmount_request;  /**< Last task performing request */
    bool       requested[ TASK_MAX ]; /**< Mount request flags for each task */
    bool       mounts[ TASK_MAX ];    /**< Mounted flags for each task */
    bool       mounted;               /**< Overall mounted */
    uint8_t    f_result;              /**< F_RESULT from last mount/unmount */

    // ~~~ File System ~~~
    FATFS             fs[ NUM_FILE_SYSTEMS ];
    FileSystemSpace_t space[ NUM_FILE_SYSTEMS ];
};

/* ----- Public Functions --------------------------------------------------- */

/**
 * @brief  Create the File System task
 * @param  me             Reference to own task structure
 * @param  priority       Task priority level (fixed at compile time).
 * @param  eventQueueData event queue for this task
 * @param  eventQueueSize size of queue
 * @return StateTask *
 */

PUBLIC StateTask *
appTaskFileSystemCreate( AppTaskFileSystem *me,
                         StateEvent        *eventQueueData[ ],
                         uint8_t           eventQueueSize,
                         StateEvent        *requestQueue[ ],
                         uint8_t           requestQueueSize );

/* ----- Helpers ------------------------------------------------------------ */

/* Simplified helper function for tasks to request file system mount.
 * This file system task will then mount and responds with a event signal
 * posted directly to the requesting task. Returns true when mount
 * request was successfully send.
 */

PUBLIC bool
f_mount_request( StateTask *me );

/* -------------------------------------------------------------------------- */

/* Simplified helper function for tasks to request file system mount.
 * This file system task will then mount and responds with a event signal
 * posted directly to the requesting task. Returns true when unmount
 * request was successful.
 */
PUBLIC bool
f_unmount_request( StateTask *me );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
AppTaskFileSystemGetAvailableKB( void );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
AppTaskFileSystemGetFreeKB( void );

/* -------------------------------------------------------------------------- */

PUBLIC bool
AppTaskFileSystemIsMounted( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_FILE_SYSTEM_H */
