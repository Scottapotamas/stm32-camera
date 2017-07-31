/**
 * @file    app_task_log.c
 *
 * @ingroup tasks
 *
 * @brief   Application Task Log
 *
 *          Handles writing of log data asynchronously to either the USB
 *          disk or the terminal interface or both.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
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
#include "app_task_ids.h"
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_task_file_system.h"
#include "app_version.h"
#include "config.h"
#include "log_output_buffer.h"
#include "ff_error_msg.h"

#include "app_task_log.h"
#include "app_task_log_private.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Defines ------------------------------------------------------------ */

#define LOG_BUFFER_SIZE            (20*1024)

PRIVATE uint8_t  log_buffer[LOG_BUFFER_SIZE];

/* ----- Public Functions --------------------------------------------------- */

PUBLIC StateTask *
appTaskLogCreate( AppTaskLog    *me,
                  StateEvent    *eventQueueData[],
                  const uint8_t eventQueueSize )
{
    // Clear all task data
    memset( me, 0, sizeof(AppTaskLog) );

    // Initialise State Machine structures
    AppTaskLogConstructor( me );

    /* Initialise State Machine Task */
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            0,
                            0 );
}

/* ----- Private Functions -------------------------------------------------- */

// State Machine Construction
PRIVATE void AppTaskLogConstructor( AppTaskLog *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskLog_initial );
}

/* -------------------------------------------------------------------------- */

// State Machine Initial State
PRIVATE void AppTaskLog_initial( AppTaskLog *me,
                                 const StateEvent *e __attribute__((__unused__)) )
{

    log_output_buffer_init( log_buffer, sizeof( log_buffer ) );
    log_output_buffer_mask_level( config_log_level() );
    log_output_buffer_set_signal_handler( AppTaskLog_log_event_handler );
    log_add_output( log_output_buffer, (void*)me );

    STATE_INIT( &AppTaskLog_main );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

PRIVATE STATE AppTaskLog_main( AppTaskLog *me,
                               const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_INIT_SIGNAL:
            STATE_INIT( AppTaskLog_idle );
            return 0;

        case CONFIG_SETTING_CHANGED_SIGNAL:
            log_output_buffer_mask_level( config_log_level() );
            return 0;
    }
    return (STATE)hsmTop;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

PRIVATE STATE AppTaskLog_idle( AppTaskLog *me,
                               const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            /* Ensure that when there is something already in the log buffer
             * that it will get written eventually.
             */

            if( log_output_buffer_used() > 0 )
            {
                eventTimerStartOnce( &me->flush_delay_timer,
                                     (StateTask* )me,
                                     (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                     MS_TO_TICKS( TIME_LOG_WRITE_DELAY ) );
            }
            return 0;

        case LOG_BUFFER_SIGNAL:
        {
            LogBufferEvent * lbe = (LogBufferEvent*)e;

            if( (lbe->level & LOG_EMERGENCY) || (lbe->percent > 75) )
            {
                /* Flush immediately now */
                STATE_TRAN( AppTaskLog_flushing );
                return 0;
            }
            else
            {
                if( eventTimerIsActive( &me->flush_delay_timer ) )
                {
                    eventTimerRestart( &me->flush_delay_timer,
                                       MS_TO_TICKS( TIME_LOG_WRITE_DELAY ) );
                }
                else
                {
                    eventTimerStartOnce( &me->flush_delay_timer,
                                         (StateTask* )me,
                                         (StateEvent* )&stateEventReserved[ STATE_TIMEOUT1_SIGNAL ],
                                         MS_TO_TICKS( TIME_LOG_WRITE_DELAY ) );
                }
            }
            return 0;
        }

        case STATE_TIMEOUT1_SIGNAL:
            /* Waited long enough */
            STATE_TRAN( AppTaskLog_flushing );
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->flush_delay_timer );
            return 0;

    }
    return (STATE)AppTaskLog_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskLog_flushing( AppTaskLog *me,
                                   const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_INIT_SIGNAL:
            STATE_INIT( AppTaskLog_flush_open );
            return 0;
    }
    return (STATE)AppTaskLog_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskLog_flush_open( AppTaskLog *me,
                                     const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            f_mount_request( (StateTask*)me );
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
            /* Can't mount file system. Go back to idle. Hopefully a little
             * later we can try again.
             */
            eventTimerStopIfActive( &me->timer );
            LOG( LOGGING,
                 LOG_ERROR,
                 "Error mounting file system for log" );

            STATE_TRAN( AppTaskLog_idle );
            return 0;

        case FILE_SYSTEM_MOUNTED:
        {
            eventTimerStopIfActive( &me->timer );

            /* Create a  file name from the current data */
            AppTaskLog_set_log_path_and_filename( me );

            /* Ensure ROOT directory is created  and writable */
            me->f_result = f_mkdir( (TCHAR*)APP_CONFIG_SD_DRIVE
                                    "/"
                                    APP_CONFIG_PATH_LOGS );

            me->f_result = f_chmod( (TCHAR*)APP_CONFIG_SD_DRIVE
                                    "/"
                                    APP_CONFIG_PATH_LOGS, 0, AM_RDO );

            /* Ensure YEAR-MONTH sub directory is created and writable */
            me->f_result = f_mkdir( (TCHAR*)me->log_path_name );

            me->f_result = f_chmod( (TCHAR*)me->log_path_name, 0, AM_RDO );

            /* Open file */
            me->f_result = f_open( &me->log_file,
                                   (TCHAR*)me->log_file_name,
                                   FA_WRITE | FA_OPEN_ALWAYS );

            if( me->f_result == FR_OK )
            {
                /* If file was opened 'fresh', write a line with the
                 * column headings as the first line in the file. */

                if( f_size( &me->log_file ) == 0 )
                {
                    char buffer[ 256 ];
                    uint16_t len;
                    UINT bytes_written = 0;

                    len = snprintf( buffer,
                                    sizeof(buffer),
                                    "Date,Time,Sub System,Log Level,Message\r\n" );

                    me->f_result = f_write( &me->log_file,
                                            buffer,
                                            len,
                                            &bytes_written );
                    STATE_TRAN( AppTaskLog_flush_write );
                }
                else
                {
                    /* File was non-zero length so it already existed.
                     * Seek to end for appending */
                    STATE_TRAN( AppTaskLog_flush_seek );
                }
            }
            else
            {
                /* Can't open log file. Abandon flush and hope to
                 * try again a bit later */
                STATE_TRAN( AppTaskLog_flush_write_finish );
            }
        }
            return 0;

        case STATE_EXIT_SIGNAL:
            eventTimerStopIfActive( &me->timer );
            return 0;
    }
    return (STATE)AppTaskLog_flushing;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskLog_flush_seek( AppTaskLog *me,
                                     const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
        {
            /* Perform the seek in small steps to ensure the f_lseek does
             * block to long to stall the rest of the application. */

            DWORD position = f_tell( &me->log_file );

            if( position < f_size( &me->log_file ) )
            {
                position = MIN( position + _MIN_SS,
                                f_size( &me->log_file ) );

                me->f_result = f_lseek( &me->log_file,
                                        position );
                stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            }
            else
            {
                STATE_TRAN( AppTaskLog_flush_write );
            }
            return 0;
        }
    }
    return (STATE)AppTaskLog_flushing;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskLog_flush_write( AppTaskLog *me,
                                      const StateEvent *e )
{

    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            /* Kick first step */
            LOG( LOGGING,
                 LOG_INFO,
                 "Flushing system log (%.1fKB in use)",
                 (float)(log_output_buffer_used()/1024.0) );
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
        {
            uint32_t bytes_read;
            UINT bytes_written = 0;
            char buffer[ 512 ];

            bytes_read = log_output_buffer_read( buffer, sizeof(buffer) );
            if( bytes_read > 0 )
            {
                me->f_result = f_write( &me->log_file,
                                        buffer,
                                        bytes_read,
                                        &bytes_written );

                /* Loop for another step */
                stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            }
            else
            {
                /* Write an empty line to mark the spot when the buffer
                 * was flushed and closed again. */
                bytes_read = snprintf( buffer, sizeof( buffer ), "\r\n" );
                me->f_result = f_write( &me->log_file,
                                        buffer,
                                        bytes_read,
                                        &bytes_written );
                /* Flush and close */
                f_sync( &me->log_file );
                f_close( &me->log_file );
                STATE_TRAN( AppTaskLog_flush_write_finish );
            }
            return 0;
        }
    }
    return (STATE)AppTaskLog_flushing;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE AppTaskLog_flush_write_finish( AppTaskLog *me,
                                             const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            f_unmount_request( (StateTask*)me );
            stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            return 0;

        case STATE_STEP1_SIGNAL:
            /* If we were also supposed to flush the sensors,
             * go do that now. Otherwise go back to idle.
             */
            STATE_TRAN( AppTaskLog_idle );
            return 0;
    }
    return (STATE)AppTaskLog_flushing;
}

/* ----- Helper Functions --------------------------------------------------- */

PRIVATE void AppTaskLog_log_event_handler( LOG_LEVEL level       __attribute__((__unused__)),
                                           uint32_t used         __attribute__((__unused__)),
                                           uint32_t percent_full __attribute__((__unused__)) )
{
//    LogBufferEvent * lbe = EVENT_NEW( LogBufferEvent, LOG_BUFFER_SIGNAL );
//    /* Failure of EVENT_NEW just results on a log event not coming through
//     * which is not an issue as this event is very repetitive. */
//    if( lbe )
//    {
//        lbe->level = level;
//        lbe->used = used;
//        lbe->percent = percent_full;
//        taskPostFIFO( app_task_by_id( TASK_LOG ), (StateEvent*)lbe );
//    }
}

/* -------------------------------------------------------------------------- */

PRIVATE void AppTaskLog_set_log_path_and_filename( AppTaskLog *me )
{
    snprintf( me->log_path_name,
              MAX_FILE_NAME_LEN,
              APP_CONFIG_SD_DRIVE
              "/"
              APP_CONFIG_PATH_LOGS
              "/%s",
              "testA" );

    snprintf( me->log_file_name,
              MAX_FILE_NAME_LEN,
              "%s/test.csv",
              me->log_path_name
              );
}

/* ----- End ---------------------------------------------------------------- */

