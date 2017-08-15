/**
 * @file      app_task_supervisor.c
 *
 * @ingroup   tasks
 *

 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <event_subscribe.h>

/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_version.h"

#include "app_task_supervisor.h"
#include "app_task_supervisor_private.h"

#include "app_task_file_system.h"
#include "app_task_camera.h"
#include "log.h"

#include "hal_power.h"
#include "hal_uuid.h"
#include "cmd_config.h"
#include "board_sensor.h"
#include "status.h"
#include "config.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC StateTask *
appTaskSupervisorCreate( AppTaskSupervisor *me,
                         StateEvent        *eventQueueData[ ],
                         const uint8_t     eventQueueSize )
{
    // Clear all task data
    memset( me, 0, sizeof(AppTaskSupervisor) );

    // Initialise State Machine State
    AppTaskSupervisorConstructor( me );

    /* Initialise State Machine Task */
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            0,
                            0 );
}

/* ----- Private Functions -------------------------------------------------- */


/* ----- Private Functions -------------------------------------------------- */

// State Machine Construction
PRIVATE void AppTaskSupervisorConstructor( AppTaskSupervisor *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskSupervisor_initial );
}

/* -------------------------------------------------------------------------- */

// State Machine Initial State
PRIVATE void AppTaskSupervisor_initial( AppTaskSupervisor *me,
                                        const StateEvent *e __attribute__((__unused__)) )
{
	button_init( BUTTON_0, AppTaskSupervisorButtonEvent );

    /* Detect user activities */
    eventSubscribe( (StateTask*)me, BUTTON_NORMAL_SIGNAL );

    /* File System Status Responses */
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_MOUNTED );
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_UNMOUNTED );

    /* High Level Commands */

    STATE_INIT( &AppTaskSupervisor_main );
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskSupervisor_main( AppTaskSupervisor *me,
                                      const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
        {

            //Todo actually do something in the supervisor state
            status_green(false);

        	return 0;
        }

        case BUTTON_NORMAL_SIGNAL:
		   switch( ((ButtonPressedEvent*)e)->id )
		   {
			   case BUTTON_0:

				   return 0;

			   default:
				   break;
		   }
		   break;

        case STATE_INIT_SIGNAL:
            STATE_INIT( &AppTaskSupervisor_load_config );
            return 0;

    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskSupervisor_load_config( AppTaskSupervisor *me,
                                         	 const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            config_defaults();

            f_mount_request( (StateTask*)me );

            eventTimerStartEvery( &me->cardTimer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( 500 ) );
            //TODO decide on a consistent SD timeout

        	return 0;

        case STATE_TIMEOUT1_SIGNAL:
			//Mount timed out
			f_mount_request( (StateTask*)me );
			return 0;

		case FILE_SYSTEM_UNMOUNTED:
			eventTimerStopIfActive( &me->cardTimer );
			LOG( SUPERVISOR, LOG_NOTICE, "System using default config data" );
			STATE_TRAN( AppTaskSupervisor_check_camera );
			return 0;

		case FILE_SYSTEM_MOUNTED:
			eventTimerStopIfActive( &me->cardTimer );
			LOG( SUPERVISOR, LOG_NOTICE, "System loading config data" );
			config_load();
			STATE_TRAN( AppTaskSupervisor_check_camera );
			return 0;

		case STATE_EXIT_SIGNAL:
			eventTimerStopIfActive( &me->cardTimer );

			f_unmount_request( (StateTask*)me );
			return 0;
    }
    return (STATE)AppTaskSupervisor_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskSupervisor_check_camera( AppTaskSupervisor *me,
                                              const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( SUPERVISOR, LOG_NOTICE, "Camera check starting..." );
            eventPublish( EVENT_NEW( StateEvent, CAMERA_CMD_ON ) );
            //publish/request a camera check event or something
            return 0;


        case CAMERA_STATUS_READY:
            LOG( SUPERVISOR, LOG_INFO, "Camera OK" );

            return 0;

        case CAMERA_STATUS_ERROR:
            LOG( SUPERVISOR, LOG_ERROR, "Camera ERROR" );

            return 0;

        case STATE_EXIT_SIGNAL:
            LOG( SUPERVISOR, LOG_NOTICE, "Check complete." );

            return 0;
    }
    return (STATE)AppTaskSupervisor_main;
}

/* -------------------------------------------------------------------------- */

/*
 * Button handling publishes event
 */

PRIVATE void AppTaskSupervisorButtonEvent( ButtonId_t button,
                                          ButtonPressType_t press_type )
{
	if(press_type == BUTTON_PRESS_TYPE_NORMAL)
	{
	    ButtonEvent *be = EVENT_NEW( ButtonEvent, BUTTON_NORMAL_SIGNAL );
	    if( be )
	    {
	        be->id = button;
	        be->press_type = press_type;
	        eventPublish( (StateEvent*)be );
	    }
	}

}
/* ----- End ---------------------------------------------------------------- */
