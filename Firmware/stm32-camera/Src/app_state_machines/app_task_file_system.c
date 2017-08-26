/**
 * @file    app_task_file_system.c
 *
 * @ingroup tasks
 *
 * @brief   Application Task File System
 *
 *          Management of the file system on the USB memory device. Handles
 *          powering on and off of the USB memory as required as well as the
 *          mounting and unmounting of the file system.
 *
 *          Provides a wrapper around the FatFs file system functions that
 *          uses event messages to signal when a file is ready to be accessed,
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <inttypes.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_tasks.h"
#include "app_config.h"
#include "app_task_ids.h"
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "event_pool.h"
#include "event_subscribe.h"
#include "log.h"
#include "ff.h"
#include "ff_error_msg.h"
#include "hal_power.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "hal_sd.h"
#include "filesystem.h"

#include "app_task_file_system.h"
#include "app_task_file_system_private.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Defines ------------------------------------------------------------ */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC StateTask *
appTaskFileSystemCreate( AppTaskFileSystem *me,
                         StateEvent        *eventQueueData[ ],
                         const uint8_t     eventQueueSize,
                         StateEvent        *requestQueue[ ],
                         const uint8_t     requestQueueSize )
{
    // Clear all task data
    memset( me, 0, sizeof(AppTaskFileSystem) );

    // Initialise State Machine State
    AppTaskFileSystemConstructor( me );

    // Initialise State Machine Task
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            requestQueue,
                            requestQueueSize );
}

/* -------------------------------------------------------------------------- */

/* Simplified helper function for tasks to request file system mount.
 * This file system task will then mount and responds with a event signal
 * posted directly to the requesting task. Returns true when mount
 * request was successfully send.
 */

PUBLIC bool
f_mount_request( StateTask *me )
{
    FileSystemRequestEvent *fsre = EVENT_NEW( FileSystemRequestEvent,
                                              FILE_SYSTEM_CMD_MOUNT );
    if( fsre )
    {
        /* Grab the task id from the calling task priority level */
        fsre->task = me;

        /* Post just to this task */
        return stateTaskPostFIFO( app_task_by_id( TASK_FILE_SYSTEM ), (StateEvent*)fsre );
    }
    return false;
}

/* -------------------------------------------------------------------------- */

/* Simplified helper function for tasks to request file system mount.
 * This file system task will then mount and responds with a event signal
 * posted directly to the requesting task. Returns true when unmount
 * request was successful.
 */
PUBLIC bool
f_unmount_request( StateTask *me )
{
    FileSystemRequestEvent *fsre = EVENT_NEW( FileSystemRequestEvent,
                                              FILE_SYSTEM_CMD_UNMOUNT );
    /* Failure of EVENT_NEW would result in application needing to retry */
    if( fsre )
    {
        /* Grab the task reference from the calling task priority level */
        fsre->task = me;

        /* Post just to this task */
        return stateTaskPostFIFO( app_task_by_id( TASK_FILE_SYSTEM ), (StateEvent*)fsre );
    }
    return false;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t AppTaskFileSystemGetAvailableKB( void )
{
    return filesystem_space( SD_DRIVE );
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t AppTaskFileSystemGetFreeKB( void )
{
    return filesystem_free( SD_DRIVE );
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
AppTaskFileSystemIsMounted( void )
{
    AppTaskFileSystem * me = (AppTaskFileSystem*)app_task_by_id( TASK_FILE_SYSTEM );
    return me->mounted;
}


/* ----- Private Functions -------------------------------------------------- */

// State Machine Construction
PRIVATE void AppTaskFileSystemConstructor( AppTaskFileSystem *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskFileSystem_initial );
}

/* -------------------------------------------------------------------------- */

// State Machine Initial State
PRIVATE void AppTaskFileSystem_initial( AppTaskFileSystem *me,
                                        const StateEvent *e __attribute__((__unused__)) )
{
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_CMD_MOUNT );
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_CMD_UNMOUNT );
    // Warning. Take care not to do the FATFS_LinkDriver
    // more than once or it will corrupt the driver structure
    // data!
    //FATFS_LinkDriver( &USBH_Driver, APP_CONFIG_USB_DRIVE );
    STATE_INIT( &AppTaskFileSystem_main );
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_main( AppTaskFileSystem *me,
                                      const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_INIT_SIGNAL:
            STATE_INIT( AppTaskFileSystem_unmounted );
            return 0;

        case STATE_ENTRY_SIGNAL:
            if( hal_sd_is_present() )
            {
                FRESULT fresult = filesystem_mount( SD_DRIVE );
                LOG( FILE_SYSTEM,
                     LOG_INFO,
                     "SD Card detected. Status = %s",
                     f_error_msg( fresult ) );

                if( fresult == FR_OK )
                {
                    LOG( FILE_SYSTEM,
                         LOG_INFO,
                         "SD Card size %luMB (%luMB free)",
                         filesystem_space( SD_DRIVE ) / 1024,
                         filesystem_free( SD_DRIVE ) / 1024 );
                }
            }
            return 0;
    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_unmounted( AppTaskFileSystem *me,
                                           const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            return 0;

        case FILE_SYSTEM_CMD_MOUNT:
        {
            /* Record task Id for mount and start mounting. Don't send
             * the status until we are properly mounted */
            me->retry = 0;
            FileSystemRequestEvent *fsre = (FileSystemRequestEvent*)e;
            me->mount_task = fsre->task;
            if( !me->requested[ me->mount_task->id ] )
            {
                me->requested[ me->mount_task->id ] = true;
                LOG( FILE_SYSTEM,
                     LOG_INFO,
                     "USB Media mounted requested for task %d (%s)",
                     me->mount_task->id, me->mount_task->name );
            }
            STATE_TRAN( AppTaskFileSystem_mount );
            return 0;
        }

        case FILE_SYSTEM_CMD_UNMOUNT:
        {
            FileSystemRequestEvent *fsre = (FileSystemRequestEvent*)e;
            me->requested[ fsre->task->id ] = false;
            me->mounts[ fsre->task->id ] = false;
            AppTaskFileSystemHelper_send_unmounted_status( me, fsre->task );
            return 0;
        }
    }
    return (STATE)AppTaskFileSystem_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_mount( AppTaskFileSystem *me,
                                       const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            me->mounted = true;
            return 0;

        case STATE_INIT_SIGNAL:
            me->retry = 0;
            STATE_INIT( AppTaskFileSystem_mounting );
            return 0;

        case FILE_SYSTEM_CMD_MOUNT:
            /* While mounting queue further requests until we are
             * fully mounted */
            eventQueuePutFIFO( &me->super.requestQueue, (StateEvent*)e );
            return 0;

        case FILE_SYSTEM_CMD_UNMOUNT:
            /* While mounting queue further requests until we are
             * fully mounted */
            eventQueuePutFIFO( &me->super.requestQueue, (StateEvent*)e );
            return 0;
    }
    return (STATE)AppTaskFileSystem_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_mounting( AppTaskFileSystem *me,
                                          const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

           eventTimerStartOnce( &me->timer,
                                 (StateTask* )me,
                                 (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                 MS_TO_TICKS( TIME_APPLICATION_SD_MOUNT_POLL ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            /* No response from device. Retry */
            LOG( FILE_SYSTEM,
                 LOG_ERROR,
                 "SD Not responding (timeout %ds)",
                 500 );
            STATE_TRAN( AppTaskFileSystem_mounting_retry );
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskFileSystem_mount;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_mounting_retry( AppTaskFileSystem *me,
                                                const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( FILE_SYSTEM, LOG_ERROR, "Retry to mount SD" );

            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            me->retry++;
            if( me->retry < 5 )
            {
                STATE_TRAN( AppTaskFileSystem_mounting );
            }
            else
            {
                LOG( FILE_SYSTEM, LOG_ERROR, "Media not detected!" );

                /* Signal that we have a problem to the first requesting task */
                AppTaskFileSystemHelper_send_unmounted_status( me,
                                                               me->mount_task );

                /** Loop any other requests and tell them the bad news */
                FileSystemRequestEvent * next = (FileSystemRequestEvent*)eventQueueGet( &me->super.requestQueue );
                while( next )
                {
                    AppTaskFileSystemHelper_send_unmounted_status( me,
                                                                   next->task );
                    eventPoolGarbageCollect( (StateEvent*)next );
                    next = (FileSystemRequestEvent*)eventQueueGet( &me->super.requestQueue );
                }
                STATE_TRAN( AppTaskFileSystem_unmounted );
            }
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskFileSystem_mount;
}

/* -------------------------------------------------------------------------- */
//TODO work out how we go from mounting to mounted.
PRIVATE STATE AppTaskFileSystem_mounted( AppTaskFileSystem *me,
                                         const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            /* See if there were any events queued */
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
            /* Device ready to communicate. Mount file system */
            me->f_result = f_mount( &me->fs[SD_DRIVE], (TCHAR*)APP_CONFIG_SD_DRIVE, 1 );
            if( me->f_result == FR_OK )
            {
                DWORD free_clusters;
                FATFS *fs;

                f_chdrive( (TCHAR*)APP_CONFIG_SD_DRIVE );

                /* Get total and free space in KiB */
                me->f_result = f_getfree( (TCHAR*)APP_CONFIG_SD_DRIVE,
                                          &free_clusters,
                                          &fs );

                if( me->f_result == FR_OK )
                {
                    me->space[SD_DRIVE].total_KiB = ((fs->n_fatent - 2) * fs->csize) / 2;
                    me->space[SD_DRIVE].free_KiB = (free_clusters * fs->csize) / 2;
                    LOG( FILE_SYSTEM,
                         LOG_INFO,
                         "SD Media mounted with %"PRIu32"MB (%"PRIu32"MB free)",
                         me->space[SD_DRIVE].total_KiB/1024,
                         me->space[SD_DRIVE].free_KiB/1024 );

                    /* We are mounted. Send ACK back to original requesting task */
                    me->mounts[ me->mount_task->id ] = true;
                    AppTaskFileSystemHelper_send_mounted_status( me,
                                                                 me->mount_task );

                    STATE_TRAN( AppTaskFileSystem_mounted_standby );
                }
                else
                {
                    me->space[SD_DRIVE].total_KiB = 0;
                    me->space[SD_DRIVE].free_KiB = 0;

                    LOG( FILE_SYSTEM,
                         LOG_ERROR,
                         "Unable to get free space info from media: %s",
                         f_error_msg( me->f_result ) );

                    /* Retry the mount ? */
                    STATE_TRAN( AppTaskFileSystem_mounting_retry );
                }
            }
            else
            {
                LOG( FILE_SYSTEM,
                     LOG_ERROR,
                     "Unable to mount media: %s",
                     f_error_msg( me->f_result ) );

                /* Retry the mount ? */
                STATE_TRAN( AppTaskFileSystem_mounting_retry );
            }
            return 0;
    }
    return (STATE)AppTaskFileSystem_mount;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_mounted_standby( AppTaskFileSystem *me,
                                                 const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            eventTimerStartEvery( &me->timer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( 500 ) );

            /* See if there were any events queued */
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
        {
            /** See if there were more requests */
            StateEvent * next = eventQueueGet( &me->super.requestQueue );
            if( next )
            {
                /* Post the event to ourselves */
                eventQueuePutFIFO( &me->super.eventQueue, next );
                eventPoolGarbageCollect( next );

                /* Loop around until the queue is empty */
                stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            }
            return 0;
        }

        case STATE_TIMEOUT1_SIGNAL:
            /* Any mounts remaining? */
            if( AppTaskFileSystemHelper_num_mounted( me ) == 0 )
            {
                STATE_TRAN( AppTaskFileSystem_unmounting );
            }
            else
            {
                eventTimerRestart( &me->timer,
                                   MS_TO_TICKS( 500 ) );
            }
            return 0;

        case FILE_SYSTEM_CMD_MOUNT:
        {
            /* Still mounted. ACK request directly. */
            eventTimerRestart( &me->timer,
                               MS_TO_TICKS( 500 ) );
            FileSystemRequestEvent *fsre = (FileSystemRequestEvent*)e;
            me->mounts[ fsre->task->id ] = true;
            AppTaskFileSystemHelper_send_mounted_status( me, fsre->task );
            return 0;
        }

        case FILE_SYSTEM_CMD_UNMOUNT:
        {
            FileSystemRequestEvent *fsre = (FileSystemRequestEvent*)e;
            me->mounts[ fsre->task->id ] = false;
            AppTaskFileSystemHelper_send_unmounted_status( me, fsre->task );
            eventTimerRestart( &me->timer,
                               MS_TO_TICKS( 500 ) );
            return 0;
        }

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskFileSystem_mount;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskFileSystem_unmounting( AppTaskFileSystem *me,
                                            const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
            me->mounted = false;
            f_mount( NULL, (TCHAR*)APP_CONFIG_SD_DRIVE, 0 );
            me->space[SD_DRIVE].free_KiB = 0;
            me->space[SD_DRIVE].total_KiB = 0;
            LOG( FILE_SYSTEM, LOG_INFO, "USB Media unmounted for ALL tasks" );

            STATE_TRAN( AppTaskFileSystem_unmounted );
            return 0;
    }
    return (STATE)AppTaskFileSystem_mount;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Send mounted status back to just the requesting task. */

PRIVATE void AppTaskFileSystemHelper_send_mounted_status( AppTaskFileSystem *me,
                                                          StateTask * requesting_task )
{
    REQUIRE( requesting_task );

    FileSystemStatusEvent *fsse = EVENT_NEW( FileSystemStatusEvent,
                                             FILE_SYSTEM_MOUNTED );
    if( fsse )
    {
        LOG( FILE_SYSTEM,
             LOG_DEBUG,
             "USB Media mounted for task %d (%s)",
             requesting_task->id,
             requesting_task->name );

        fsse->f_result = me->f_result;
        fsse->number_of_mounts = AppTaskFileSystemHelper_num_mounted( me );
        fsse->space_total_KiB = me->space[SD_DRIVE].total_KiB;
        fsse->space_free_KiB = me->space[SD_DRIVE].free_KiB;

        eventQueuePutFIFO( &requesting_task->eventQueue, (StateEvent*)fsse );
    }
}

/* -------------------------------------------------------------------------- */

/** Send unmounted status back to just the requesting task. */

PRIVATE void AppTaskFileSystemHelper_send_unmounted_status( AppTaskFileSystem *me __attribute__((unused)),
                                                            StateTask * requesting_task )
{
    REQUIRE( requesting_task );

    if( me->requested[ requesting_task->id ] )
    {
        LOG( FILE_SYSTEM,
             LOG_DEBUG,
             "USB Media unmounted for task %d (%s)",
             requesting_task->id,
             requesting_task->name );
        me->requested[ requesting_task->id ] = false;
    }

    StateEvent *e = EVENT_NEW( StateEvent, FILE_SYSTEM_UNMOUNTED );
    if( e )
    {
        eventQueuePutFIFO( &requesting_task->eventQueue, e );
    }
}

/* -------------------------------------------------------------------------- */

/* Return true when any of the tasks have an active mount requested */
PRIVATE uint8_t AppTaskFileSystemHelper_num_mounted( AppTaskFileSystem *me )
{
    uint8_t mounts = 0;
    for( uint8_t task = 0; task < TASK_MAX; task++ )
    {
        if( me->mounts[ task ] )
            mounts++;
    }
    return mounts;
}

/* ----- End ---------------------------------------------------------------- */

