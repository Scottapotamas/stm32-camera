/**
 * @file    app_task_camera.c
 *
 * @ingroup tasks
 *
 * @brief   Application Task Camera
 *
 *          Management task for the camera. Handles sequencing powering up,
 *          initialisation, idling, signalling a capture and saving the image
 *          to disk.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <event_subscribe.h>
#include <event_subscribe.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "app_task_ids.h"
#include "app_task_file_system.h"   /* f_mount_request/f_unmount_request */
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_tasks.h"

#include "config.h"
#include "ff_error_msg.h"
#include "log.h"

#include "hal_camera.h"
#include "ov2640.h"

#include "app_task_camera.h"
#include "app_task_camera_private.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Defines ------------------------------------------------------------ */

/* ----------------------- Private Functions Declarations ------------------- */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC StateTask *
appTaskCameraCreate( AppTaskCamera *me,
                     StateEvent    *eventQueueData[],
                     const uint8_t eventQueueSize )
{
    // Clear all task data
    memset( me, 0, sizeof(AppTaskCamera) );

    // Initialise State Machine structures
    AppTaskCameraConstructor( me );

    /* Initialise State Machine Task */
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            0,
                            0 );
}

/* -------------------------------------------------------------------------- */

//Simplified helper function for tasks to request taking a picture
PUBLIC bool
appTaskCameraTakePictureNormal()
{
    AppTaskCamera *me = (AppTaskCamera*)app_task_by_id( TASK_CAMERA );

    /* If we are already capturing, ignore this request */
    if( !me->capturing )
    {
        CameraCaptureEvent *cce = EVENT_NEW( CameraCaptureEvent,
                                             CAMERA_CMD_CAPTURE_NORMAL );

        cce->trigger_delay_ms = 0;
        return eventPublish( (StateEvent*)cce );
    }
    return false;
}

/* -------------------------------------------------------------------------- */

// Allow other tasks to checking for camera status.
PUBLIC bool appTaskCameraIsReady( void )
{
    AppTaskCamera *me = (AppTaskCamera*)app_task_by_id( TASK_CAMERA );
    return me->ready;
}

/* ----- Private Functions -------------------------------------------------- */

// State Machine Construction
PRIVATE void AppTaskCameraConstructor( AppTaskCamera *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskCamera_initial );
}

/* -------------------------------------------------------------------------- */

// State Machine Initial State
PRIVATE void AppTaskCamera_initial( AppTaskCamera *me,
                                    const StateEvent *e __attribute__((__unused__)) )
{
    eventSubscribe( (StateTask*)me, CAMERA_CMD_ON );
    eventSubscribe( (StateTask*)me, CAMERA_CMD_CAPTURE_NORMAL );
    eventSubscribe( (StateTask*)me, CAMERA_CMD_OFF );
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_MOUNTED );
    eventSubscribe( (StateTask*)me, FILE_SYSTEM_UNMOUNTED );

    STATE_INIT( &AppTaskCamera_off );
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_off( AppTaskCamera *me,
                                 const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( CAMERA, LOG_INFO, "OFF" );
            if( me->camera_was_init )
            {
            	//deinit camera
                me->camera_was_init = false;
            }
            //disable flash
            eventPublish( EVENT_NEW( StateEvent, CAMERA_STATUS_OFF ) );
            return 0;

        case CAMERA_CMD_OFF:
            eventPublish( EVENT_NEW( StateEvent, CAMERA_STATUS_OFF ) );
            return 0;

        case CAMERA_CMD_CAPTURE_NORMAL:
            LOG( CAMERA, LOG_WARN, "Camera is OFF - No image captured" );
            return 0;

        case CAMERA_CMD_ON:
            STATE_TRAN( AppTaskCamera_on );
            return 0;
    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on( AppTaskCamera *me,
                                const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_INIT_SIGNAL:
            STATE_INIT( AppTaskCamera_on_init );
            return 0;

        case STATE_ENTRY_SIGNAL:
            LOG( CAMERA, LOG_INFO, "ON" );
            return 0;

        case CAMERA_CMD_OFF:
            STATE_TRAN( AppTaskCamera_off );
            return 0;
    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_init( AppTaskCamera *me,
                                     const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( CAMERA, LOG_DEBUG, "INIT" );

            //TODO camera init here
            me->camera_was_init = true;
            eventTimerStartOnce( &me->timer,
                                 (StateTask* )me,
                                 (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                 MS_TO_TICKS( TIME_CAMERA_POWER_UP_DELAY ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            STATE_TRAN( AppTaskCamera_on_init_reset );
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskCamera_on;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_init_reset( AppTaskCamera *me,
                                           const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            //TODO camera reset/retry here
            me->retry = 0;
            eventTimerStartEvery( &me->timer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( TIME_CAMERA_RESET_TIMEOUT ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:

            LOG( CAMERA, LOG_WARN, "TIMEOUT on RESET" );

            STATE_TRAN( AppTaskCamera_error );

            return 0;

        case STATE_TIMEOUT2_SIGNAL:
            LOG( CAMERA, LOG_DEBUG, "RESET" );
            //TODO handle state where camera doesn't come up on retry
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskCamera_on_init;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_ready( AppTaskCamera *me,
                                      const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            eventPublish( EVENT_NEW( StateEvent, CAMERA_STATUS_READY ) );
            me->capturing = false;
            return 0;

        case STATE_INIT_SIGNAL:

            return 0;

        case CAMERA_CMD_CAPTURE_NORMAL:
        {

            STATE_TRAN( AppTaskCamera_on_capture_normal );
            return 0;
        }

    }
    return (STATE)AppTaskCamera_on;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_capture_normal( AppTaskCamera *me,
                                               const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            me->shutter_time_ms = config_camera_flash_duration_ms();

            LOG( CAMERA, LOG_INFO, "Shutter @ %dms (normal mode)",
                                   me->shutter_time_ms );

            me->trigger_delay_ms = 0; /* No extra delay */

            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
            STATE_TRAN( AppTaskCamera_on_capture );
            return 0;
    }
    return (STATE)AppTaskCamera_on;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_capture( AppTaskCamera *me,
                                        const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            me->capturing = true;

            eventTimerStartOnce( &me->timer,
                                 (StateTask* )me,
                                 (StateEvent* )&stateEventReserved[ STATE_STEP1_SIGNAL ],
                                 MS_TO_TICKS( me->shutter_time_ms ) );

            eventPublish( EVENT_NEW( StateEvent, CAMERA_STATUS_CAPTURING ) );
            return 0;

        case STATE_STEP1_SIGNAL:
        	//TODO setup to take a picture
            LOG( CAMERA, LOG_INFO, "Freeze Frame" );
            eventTimerStartEvery( &me->timer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( TIME_CAMERA_RESPONSE_TIMEOUT ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            LOG( CAMERA, LOG_WARN, "TIMEOUT on FREEZE" );
            //TODO Take image function call
            me->retry++;
            if( me->retry > 3 )
            {
                STATE_TRAN( AppTaskCamera_error );
            }
            return 0;

        case STATE_TIMEOUT2_SIGNAL:
            LOG( CAMERA, LOG_INFO, "Flash OFF" );

            STATE_TRAN( AppTaskCamera_on_save );
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskCamera_on;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_save( AppTaskCamera *me,
                                     const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

            LOG( CAMERA, LOG_INFO, "Saving photo" );
            return 0;

        case STATE_INIT_SIGNAL:
            STATE_INIT( AppTaskCamera_on_save_get_size );
            return 0;
    }
    return (STATE)AppTaskCamera_on;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_save_get_size( AppTaskCamera *me,
                                              const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

            me->retry = 0;
            eventTimerStartEvery( &me->timer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( TIME_CAMERA_RESPONSE_TIMEOUT ) );

            //TODO calculate image size and then save the file
            STATE_TRAN( AppTaskCamera_on_save_open_file );

            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            LOG( CAMERA, LOG_WARN, "TIMEOUT on GET IMAGE SIZE" );

            me->retry++;
            if( me->retry > 3 )
            {
                STATE_TRAN( AppTaskCamera_error );
            }
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskCamera_on_save;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_on_save_open_file( AppTaskCamera *me,
                                               const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            f_mount_request( (StateTask*)me );
            LOG( CAMERA,
                 LOG_INFO,
                 "Request to mount USB file system to save photo" );
            eventTimerStartEvery( &me->timer,
                                  (StateTask* )me,
                                  (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                  MS_TO_TICKS( TIME_APPLICATION_SD_MOUNT_POLL ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            /* No response. Re-request mount */
            f_mount_request( (StateTask*)me );
            return 0;

        case FILE_SYSTEM_UNMOUNTED:
            eventTimerStopIfActive( &me->timer );

            /* Unable to open file system. Abort play */
            LOG( CAMERA,
                 LOG_ERROR,
                 "Unable to mount USB file system. Image save aborted." );
            STATE_TRAN( AppTaskCamera_on_ready );
            return 0;

        case FILE_SYSTEM_MOUNTED:
            eventTimerStopIfActive( &me->timer );

            set_capture_path_and_file_name( me );

            /* Ensure ROOT directory exists */
            me->f_result = f_mkdir( APP_CONFIG_SD_DRIVE
                                    "/"
                                    APP_CONFIG_PATH_PHOTOS );
            if( ( me->f_result != FR_OK ) && ( me->f_result != FR_EXIST ) )
            {
                LOG( CAMERA,
                     LOG_ERROR, "Error creating directory '%s' - %s",
					 APP_CONFIG_SD_DRIVE
                                 "/"
                                 APP_CONFIG_PATH_PHOTOS,
                                 f_error_msg( me->f_result ) );
            }

            /* Ensure ROOT directory is writable */
            me->f_result = f_chmod( APP_CONFIG_SD_DRIVE
                                    "/"
                                    APP_CONFIG_PATH_PHOTOS,
                                    0, AM_RDO );
            if( ( me->f_result != FR_OK ) )
            {
                LOG( CAMERA,
                     LOG_ERROR, "Error removing read only from directory '%s' - %s",
					 	 	 	APP_CONFIG_SD_DRIVE
                                "/"
                                APP_CONFIG_PATH_PHOTOS,
                                f_error_msg( me->f_result ) );
            }

            /* Ensure YEAR-MONTH sub directory is created */
            me->f_result = f_mkdir( (TCHAR*)me->capture_path_name );
            if( ( me->f_result != FR_OK ) && ( me->f_result != FR_EXIST ) )
            {
                LOG( CAMERA,
                     LOG_ERROR, "Error creating directory '%s' - %s",
                                 me->capture_path_name,
                                 f_error_msg( me->f_result ) );
            }

            /* Ensure YEAR-MONTH directory is writable */
            me->f_result = f_chmod( (TCHAR*)me->capture_path_name,
                                    0, AM_RDO );
            if( ( me->f_result != FR_OK ) )
            {
                LOG( CAMERA,
                     LOG_ERROR, "Error removing read only from directory '%s' - %s",
                                 me->capture_path_name,
                                 f_error_msg( me->f_result ) );
            }

            /* Open file */
            me->f_result = f_open( &me->capture_file,
                                   (TCHAR*)me->capture_file_name,
                                   FA_WRITE | FA_CREATE_ALWAYS );
            if( me->f_result == FR_OK )
            {
                LOG( CAMERA,
                     LOG_NOTICE,
                     "Saving photo: '%s' - %s",
                     me->capture_file_name,
                     f_error_msg( me->f_result ) );
                //TODO Save the image
            }
            else
            {
                LOG( CAMERA,
                     LOG_ERROR,
                     "Unable to save photo: '%s' - %s",
                     me->capture_file_name,
                     f_error_msg( me->f_result ) );
                STATE_TRAN( AppTaskCamera_on_ready );
            }
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskCamera_on_save;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskCamera_error( AppTaskCamera *me,
                                   const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( CAMERA, LOG_ERROR, "Camera ERROR - No response" );
            eventPublish( EVENT_NEW( StateEvent, CAMERA_STATUS_ERROR ) );

            eventTimerStartOnce( &me->timer,
                                 (StateTask* )me,
                                 (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                 MS_TO_TICKS( TIME_APPLICATION_STEP ) );
            return 0;

        case STATE_TIMEOUT1_SIGNAL:
            STATE_TRAN( AppTaskCamera_off );
            return 0;

        case CAMERA_CMD_CAPTURE_NORMAL:
            LOG( CAMERA, LOG_WARN, "Camera in error state - No image captured" );
            return 0;

        case CAMERA_CMD_OFF:
            STATE_TRAN( AppTaskCamera_off );
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)hsmTop;
}

/* ----- Helper Functions --------------------------------------------------- */

PRIVATE void set_capture_path_and_file_name( AppTaskCamera *me )
{
    snprintf( me->capture_path_name,
              MAX_FILE_NAME_LEN,
              APP_CONFIG_SD_DRIVE
              "/"
              APP_CONFIG_PATH_PHOTOS
              );
}

/* ----- End ---------------------------------------------------------------- */

