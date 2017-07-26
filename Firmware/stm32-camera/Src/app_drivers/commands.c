/**
 * @file    commands.c
 *
 * @brief   Command line command processors.
 *
 *          Used by tasks like Application Task Monitor to parse and
 *          execute commands.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <inttypes.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "commands.h"
#include "state_event.h"
#include "app_tasks.h"
#include "app_events.h"
#include "event_subscribe.h"
#include "qassert.h"
#include "app_task_ids.h"
#include "app_signals.h"
#include "app_events.h"
#include "hal_delay.h"
#include "hal_uuid.h"
#include "file_util.h"
#include "tick_timer.h"



/* ----- Private Functions -------------------------------------------------- */

/** CURRENT SENSING COMMANDS */
PRIVATE bool command_test_power( CmdHandler *me );
PRIVATE bool command_test_delivery( CmdHandler *me );
PRIVATE bool command_test_audio( CmdHandler *me );
PRIVATE bool command_test_sensors( CmdHandler *me );
PRIVATE bool command_test_camera( CmdHandler *me );

/** SYSTEM COMMANDS */
PRIVATE bool command_system_uuid( CmdHandler *me );
PRIVATE bool command_system_tasks( CmdHandler *me );

/* -------------------------------------------------------------------------- */

/** CURRENT SENSING TRACK COMMANDS */
PRIVATE const CmdEntry LoomTestingCmdTable[] =
{
    CmdEntryAction(  "power loom",
                     command_test_power,
                     "Battery ring terminals and solar connector" ),
    CmdEntryAction(  "delivery loom",
                     command_test_delivery,
                     "magazine and piston motor, magazine and trigger solenoid" ),
    CmdEntryAction(  "audio loom",
                     command_test_audio,
                     "stereo speakers" ),
	CmdEntryAction(  "sensor loom",
					 command_test_sensors,
					 "top, left and right LiDAR sensors" ),
	CmdEntryAction(  "camera loom",
					 command_test_camera,
					 "Camera, laser, IR flash, bottom LiDAR" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** SYSTEM COMMANDS */
PRIVATE const CmdEntry SystemCmdTable[] =
{
    CmdEntryAction(  "tasks",
                     command_system_tasks,
                     "show tasks status" ),

    CmdEntryAction(  "uuid",
                     command_system_uuid,
                     "display system Unique Universal ID" ),

    CmdEntryTerminator()
};

/** TOP LEVEL COMMANDS - PUBLIC REFERENCE */

PRIVATE const CmdEntry topCmdTable[] =
{

    CmdEntrySubMenu( "test",
                     LoomTestingCmdTable,
                     "run test on a loom" ),
	CmdEntrySubMenu( "system",
					 SystemCmdTable,
					 "rename this later" ),

    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

PUBLIC const CmdEntry *commands = topCmdTable;

/* -------------------------------------------------------------------------- */
/* --- TESTING COMMANDS ----------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PRIVATE bool
command_test_power( CmdHandler *me )
{



    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_test_delivery( CmdHandler *me )
{


    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_test_audio( CmdHandler *me )
{


    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_test_sensors( CmdHandler *me )
{


    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_test_camera( CmdHandler *me )
{


    return true;
}

/* -------------------------------------------------------------------------- */
/* --- SYSTEM COMMANDS ------------------------------------------------------ */
/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_tasks( CmdHandler *me )
{
    cmd_printf( me, " Id:         Name:  St: Burst: Wait:  Que: Max:\r\n" );
    for( uint8_t id = (TASK_MAX-1); id > 0; id-- )
    {
        StateTask *t = app_task_by_id( id );
        if( t )
        {
            cmd_printf( me,
                        "% 3d, %12s,   %s,  % 4ld, % 4ld,  % 3d,  % 3d\r\n",
                        t->id,
                        t->name,
                        t->ready ? "R" : "-",
                        t->burst_max,
                        t->waiting_max,
                        t->eventQueue.used,
                        t->eventQueue.max );
        }
    }
    if( cmd_get_argc( me ) > 1 )
    {
        app_task_clear_statistics();
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

/** UUID COMMANDS */
PRIVATE bool command_system_uuid( CmdHandler *me )
{
    cmd_printf( me,
                "UUID: %08lX-%08lX-%08lX\r\n",
                HAL_UUID[0],
                HAL_UUID[1],
                HAL_UUID[2] );

    return true;
}

/* ----- End ---------------------------------------------------------------- */
