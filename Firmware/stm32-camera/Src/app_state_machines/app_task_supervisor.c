/**
 * @file      app_task_supervisor.c
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Supervisor
 *
 *            Top level supervisory task for the main trap states and
 *            transitioning between them.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
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

#include "hal_uuid.h"
#include "app_task_supervisor.h"
#include "app_task_supervisor_private.h"

#include "status.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

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

    eventSubscribe( (StateTask*)me, TERMINAL_INPUT_CHAR_SIGNAL );


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

        	//General list of things that need doing

        	//TODO import sd card handling and fatfs management
        	//TODO linkup aux, terminal, fatfs tasks in background/main state machines
        	//TODO cleanup ADC abstraction and readings

        	//TODO flesh out commands interface for terminal use
        	//TODO config handling and cleanup
        	//TODO develop startup sequence for hardware
        	//TODO add dcmi hal code to remove the cubemx one

        	//TODO develop image printout capability

            me->counter = 0;

        	return 0;
        }

        case BUTTON_NORMAL_SIGNAL:
		   switch( ((ButtonPressedEvent*)e)->id )
		   {
			   case BUTTON_0:
				   me->counter++;
		           STATE_TRAN( &AppTaskSupervisor_placeholder );
				   return 0;

			   default:
				   break;
		   }
		   break;

        case STATE_INIT_SIGNAL:
            STATE_INIT( &AppTaskSupervisor_placeholder );
            return 0;

    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskSupervisor_placeholder( AppTaskSupervisor *me,
                                         	 const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:


        	return 0;

        case STATE_EXIT_SIGNAL:



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
