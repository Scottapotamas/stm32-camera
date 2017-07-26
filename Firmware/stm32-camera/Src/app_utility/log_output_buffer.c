/**
 * @file      log_output_file.c
 *
 * @ingroup   utility
 *
 * @brief     Log output to file interface
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <ctype.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "log.h"
#include "log_output_buffer.h"
#include "fifo.h"

/* ------------------------ Variables --------------------------------------- */

PRIVATE LogBufferSignalCallback_t  log_buffer_signal_callback = NULL;
PRIVATE fifo_t                     log_buffer_fifo;
PRIVATE LOG_LEVEL                  log_buffer_mask;

/* ----------------------- implementation ----------------------------------- */

PUBLIC void
log_output_buffer_init( uint8_t * buffer, size_t buffer_size )
{
    const char * message;
//    bool         message_ok;
    log_buffer_signal_callback = NULL;
    log_buffer_mask = LOG_MASK_ALL;    /* Default accept all */
    fifo_init( &log_buffer_fifo, buffer, buffer_size );

    /* Write a break to the buffer */
    message = "\r\n\r\n";
    fifo_write( &log_buffer_fifo, message, strlen( message ) );

    /* Write a startup message to the crash log. This will append to any
     * other messages that are there and then dump the full crash log
     * (including any faults) to the USB log buffer */

    hal_rtc_backup_enable_ram_access();
    message = hal_rtc_backup_crash_log_get();

//    /* Check if the message makes sense (i.e. not corrupted) */
//    message_ok = true;
//    for( uint16_t i = 0; i < strlen( message ); i++ )
//    {
//        /* Message should be printable and only have \r or \n */
//        if( !isprint( (int)message[i] ) )
//        {
//            if( ( message[i] != '\r' ) && ( message[i] != '\n' ) )
//            {
//                message_ok = false;
//            }
//        }
//    }

    if( strlen( message ) > 0 )
    {
        fifo_write( &log_buffer_fifo, message, strlen( message ) );
    }

    /* Empty out the backup memory log */
    hal_rtc_backup_crash_log_clear();

    /* Write restarting message to initial log */
    char * restart_message = "\r\n*** SYSTEM RESTART ***\r\n\r\n";
    fifo_write( &log_buffer_fifo, restart_message, strlen( restart_message ) );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
log_output_buffer( LOG_SUB_SYSTEM sub_system __attribute__((__unused__)),
                   LOG_LEVEL      log_level,
                   const char     * message,
                   void           * userdata __attribute__((__unused__)) )
{
    if( log_buffer_mask & log_level )
    {
        /* Determine message length */
        uint32_t len = strlen( message );

        fifo_write( &log_buffer_fifo, message, len );

        /* If overflowed we loose log data */

        if( log_buffer_signal_callback )
        {
            uint32_t used = fifo_used( &log_buffer_fifo );
            uint32_t percent = (used * 100) / log_buffer_fifo.capacity;
            log_buffer_signal_callback( log_level, used, percent );
        }
    }
}

/* -------------------------------------------------------------------------- */

/** Set the LOG_LEVEL that this buffer logger is to accept */

PUBLIC void
log_output_buffer_mask_level( LOG_LEVEL log_mask )
{
    log_buffer_mask = log_mask;
}

/* -------------------------------------------------------------------------- */

/** Return how much data is in the log buffer */

PUBLIC uint32_t
log_output_buffer_used( void )
{
    return fifo_used( &log_buffer_fifo );
}

/* -------------------------------------------------------------------------- */

/** Read a chunk of the FIFO buffer */

PUBLIC uint32_t
log_output_buffer_read( char * buffer, uint32_t bytes_to_read )
{
    return fifo_read( & log_buffer_fifo, buffer, bytes_to_read );
}

/* -------------------------------------------------------------------------- */

/** Set callback for buffer activity */

PUBLIC void
log_output_buffer_set_signal_handler( LogBufferSignalCallback_t handler )
{
    log_buffer_signal_callback = handler;
}

/* ----- End ---------------------------------------------------------------- */


