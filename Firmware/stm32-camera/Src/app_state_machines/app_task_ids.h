/**
 * @file      app_task_ids.h
 *
 * @brief     Enumerates the task ids for inter task communication and
 *            sets task priority
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_IDS_H
#define APP_TASK_IDS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"

/* -------------------------------------------------------------------------- */

/** The enum AppTaskID contains the identifier for all tasks in the system.
 *  Its order specifies the relative priority of tasks. The scheduler will
 *  always process all events from the highest priority task first and only
 *  move down the priority list when there are no higher priority events to
 *  process.
 *
 *  Event processing is blocking, so while an event is processed it runs to
 *  completion and will block all other tasks (even higher priority ones) from
 *  processing their events, so tasks needs to be carefully designed to
 *  avoid long delays in function calls to lower level libraries.
 */

enum AppTaskID
{
    TASK_IDLE = 0, /* Default system IDLE */

	TASK_AUXILIARY_A,
	TASK_AUXILIARY_B,
	TASK_AUXILIARY_C,

    TASK_MONITOR,   /*UART Connection */

	TASK_CAMERA,	/* Camera Handling */

    TASK_FILE_SYSTEM, /* In charge of mounts/dismounting the USB file
     system and powering in the USB as required
     for the mount. Will attempt to power cycle
     the USB to get it to mount if this is taking
     to long. */

    TASK_LOG, /* Monitors the log buffer and when it
     has been idle for some time and there is
     sufficient content, flushes the log to disk.
     Logs are also flushes on certain main
     system events. Also handles the flushing of
     the sensor logs on demand. Mounts the file
     system and opens files. */

	TASK_SUPERVISOR, /* High priority task that manages making
     decisions. In normal operation quite
     busy processing. */

};

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_IDS_H */

