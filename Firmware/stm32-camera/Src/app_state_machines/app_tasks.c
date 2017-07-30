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
#include "app_task_file_system.h"
#include "app_task_camera.h"
#include "app_task_auxiliary.h"
#include "app_task_terminal.h"

#include "button.h"
#include "hal_button.h"
#include "hal_systick.h"
#include "hal_delay.h"
#include "app_version.h"
#include "hal_adc.h"
#include "log.h"
#include "config.h"

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
AppTaskFileSystem          appTaskFileSystem;
StateEvent *               appTaskFileSystemEventQueue[20];
StateEvent *               appTaskFileSystemRequestQueue[20];

AppTaskAuxiliary           appTaskAuxiliaryA;
StateEvent *               appTaskAuxiliaryAEventQueue[10];

AppTaskAuxiliary           appTaskAuxiliaryB;
StateEvent *               appTaskAuxiliaryBEventQueue[10];

AppTaskAuxiliary           appTaskAuxiliaryC;
StateEvent *               appTaskAuxiliaryCEventQueue[10];

AppTaskCamera              appTaskCamera;
StateEvent *               appTaskCameraEventQueue[20];

AppTaskTerminal            appTaskTerminal;
StateEvent *               appTaskTerminalEventQueue[20];

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
    eventPoolInit( eventPool, DIM(eventPool) );

    eventPoolAddStorage( (StateEvent*)&eventsSmall,
                                 DIM(eventsSmall),
                                 sizeof(EventsSmallType) );

    /* ~~~ Event Subscription Tables Initialisation ~~~ */
    eventSubscribeInit( eventSubscriberList, STATE_MAX_SIGNAL );

    /* ~~~ Set configuration data to sensible defaults ~~~ */
    config_init();

    /* ~~~ Enable the logging subsystem ~~~ */
    log_init();

    /* ~~~ Event Timers Initialisation ~~~ */
    eventTimerInit();

    /* ~~~ Init background processes ~~~ */
    app_background_init();

    /* ~~~ State Machines Initialisation ~~~ */
    StateTask *t;

    t = appTaskFileSystemCreate( &appTaskFileSystem,
                                 appTaskFileSystemEventQueue,
                                 DIM(appTaskFileSystemEventQueue),
                                 appTaskFileSystemRequestQueue,
                                 DIM(appTaskFileSystemRequestQueue) );
    stateTaskerAddTask( &mainTasker, t, TASK_FILE_SYSTEM, "FileSys" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskAuxiliaryCreate( &appTaskAuxiliaryA,
                                appTaskAuxiliaryAEventQueue,
                                DIM(appTaskAuxiliaryAEventQueue),
								AUX_PORT_ANALOG );
    stateTaskerAddTask( &mainTasker, t, TASK_AUXILIARY_A, "AuxA" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskAuxiliaryCreate( &appTaskAuxiliaryB,
                                appTaskAuxiliaryBEventQueue,
                                DIM(appTaskAuxiliaryAEventQueue),
								AUX_PORT_EXP_0 );
    stateTaskerAddTask( &mainTasker, t, TASK_AUXILIARY_B, "AuxB" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskAuxiliaryCreate( &appTaskAuxiliaryC,
                                appTaskAuxiliaryCEventQueue,
                                DIM(appTaskAuxiliaryBEventQueue),
								AUX_PORT_EXP_1 );
    stateTaskerAddTask( &mainTasker, t, TASK_AUXILIARY_C, "AuxC" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskCameraCreate( &appTaskCamera,
                             appTaskCameraEventQueue,
                             DIM(appTaskCameraEventQueue) );
    stateTaskerAddTask( &mainTasker, t, TASK_CAMERA, "Camera" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskTerminalCreate( &appTaskTerminal,
                             appTaskTerminalEventQueue,
                             DIM(appTaskTerminalEventQueue),
							 HAL_UART_PORT_MAIN );
    stateTaskerAddTask( &mainTasker, t, TASK_TERMINAL, "Terminal" );
    stateTaskerStartTask( &mainTasker, t );

    t = appTaskSupervisorCreate( &appTaskSupervisor,
                                 appTaskSupervisorEventQueue,
                                 DIM(appTaskSupervisorEventQueue) );
    stateTaskerAddTask( &mainTasker, t, TASK_SUPERVISOR, "Super" );
    stateTaskerStartTask( &mainTasker, t );


    hal_systick_hook( eventTimerTick );
    hal_systick_hook( hal_adc_tick );
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

