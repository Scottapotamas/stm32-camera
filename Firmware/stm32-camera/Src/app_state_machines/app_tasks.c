/**
 * @file      app_tasks.c
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Wrapper
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */
/* Task & State Machine Support */
#include "global.h"
#include "state_task.h"
#include "state_tasker.h"
#include "event_subscribe.h"
#include "qassert.h"
#include "app_config.h"
#include "app_task_ids.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_hardware.h"
#include "app_background.h"

/* Application Tasks */
#include "app_task_supervisor.h"
#include "button.h"
#include "hal_button.h"
#include "hal_systick.h"
#include "hal_delay.h"
#include "app_version.h"
/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* -------------------------------------------------------------------------- */

// ~~~ Event Pool Types ~~~

/** Up to three distinct storage pools. */
EventPool  eventPool[3];

/** @note: Select the following typedefs as approximately the largest
 *         within their group of small, medium and large structures.
 *         You need to make sure that EventsLargeType corresponds to the
 *         biggest event that can be allocated.
 */
typedef ButtonEvent EventsSmallType;

// ~~~ Event Pool Storage ~~~
EventsSmallType  eventsSmall[150];//  __attribute__ ((section (".ccmram")));

// ~~~ Event Subscription Data ~~~
EventSubscribers eventSubscriberList[STATE_MAX_SIGNAL];

// ~~~ Task Control Blocks & Event Queues ~~~
AppTaskSupervisor          appTaskSupervisor;
StateEvent *               appTaskSupervisorEventQueue[60];

// ~~~ Tasker ~~~
PRIVATE StateTasker_t      mainTasker;
        StateTask *        mainTaskTable[TASK_MAX];

/* ----- Public Functions --------------------------------------------------- */

PUBLIC
void app_tasks_init( void )
{
    /* ~~~ Tasker Handling Initialisation ~~~ */
    stateTaskerInit( &mainTasker, mainTaskTable, TASK_MAX );

    /* ~~~ Dynamic Event Pools Initialisation ~~~ */
    eventPoolInit( eventPool,
                   DIM(eventPool) );

    eventPoolAddStorage( (StateEvent*)&eventsSmall,
                                 DIM(eventsSmall),
                                 sizeof(EventsSmallType) );

    /* ~~~ Event Subscription Tables Initialisation ~~~ */
    eventSubscribeInit( eventSubscriberList, STATE_MAX_SIGNAL );

    /* ~~~ Event Timers Initialisation ~~~ */
    eventTimerInit();

    /* ~~~ Init background processes ~~~ */
    app_background_init();

    /* ~~~ State Machines Initialisation ~~~ */
    StateTask *t;

    t = appTaskSupervisorCreate( &appTaskSupervisor,
                                 appTaskSupervisorEventQueue,
                                 DIM(appTaskSupervisorEventQueue) );
    stateTaskerAddTask( &mainTasker, t, TASK_SUPERVISOR, "Super" );
    stateTaskerStartTask( &mainTasker, t );

    hal_systick_hook( eventTimerTick );
}

/* -------------------------------------------------------------------------- */

/* Run a cycle of the application state machine dispatcher. Returns true
 * when there is more events to be processed. False when the state machines
 * are idle.
 */

PUBLIC bool
app_tasks_run( void )
{
    /* Run the background processes. */
    app_background();

    /* Run a single task event. */
    return stateTaskerRunEvent( &mainTasker );
}

/* -------------------------------------------------------------------------- */

/** Return a pointer to the task structure identified by id */

PUBLIC StateTask *
app_task_by_id( uint8_t id )
{
    return stateTaskerGetTaskById( &mainTasker, id );
}

/* -------------------------------------------------------------------------- */

/** Clear the task handling statistics */

PUBLIC void
app_task_clear_statistics( void )
{
    stateTaskerClearStatistics( &mainTasker );
}

/* ----- End ---------------------------------------------------------------- */

