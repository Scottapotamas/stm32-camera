/**
 * @file      log.c
 *
 * @brief     Logging & Trace Support
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2013-2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "log.h"
#include "config.h"

/* ----------------------- Public Variables ---------------------------------*/

PUBLIC LOG_LEVEL      _log_level_mask_;

/* ----------------------- Local Variables --------------------------------- */

PRIVATE LogOutputFunction   log_outputs[LOG_MAX_OUTPUTS];
PRIVATE void *              log_userdata[LOG_MAX_OUTPUTS];

PRIVATE void(*log_output)( const LOG_LEVEL priority, const char * message );

/* ----------------------- Start implementation ---------------------------- */

PUBLIC void
log_init( void )
{
    log_output = NULL;
    memset( &log_outputs,  0, sizeof( log_outputs ) );
    memset( &log_userdata, 0, sizeof( log_userdata ) );

   _log_level_mask_ = LOG_LEVEL_RUNTIME;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
log_set_mask_level( LOG_LEVEL log_mask )
{
    _log_level_mask_ = log_mask;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
log_get_mask_level( void )
{
    return _log_level_mask_;
}

/* -------------------------------------------------------------------------- */

PUBLIC const char *
log_get_sub_system_label( LOG_SUB_SYSTEM sub_system )
{
    if( sub_system & FILE_SYSTEM ) return "FILE";
    if( sub_system & CONFIG      ) return "CONFIG";
    if( sub_system & LOGGING     ) return "LOG";
    if( sub_system & TERMINAL    ) return "TERMINAL";
    if( sub_system & AUXILIARY   ) return "AUXILIARY";
    if( sub_system & SUPERVISOR  ) return "SYSTEM";
    if( sub_system & CAMERA      ) return "CAMERA";
    if( sub_system & TEMPERATURE ) return "TEMPERATURE";

    return "???";
}

/* -------------------------------------------------------------------------- */

PUBLIC const char *
log_get_mask_level_label( LOG_LEVEL log_mask )
{
    if( log_mask & LOG_EMERGENCY ) return "EMERGENCY";
    if( log_mask & LOG_ALERT     ) return "ALERT";
    if( log_mask & LOG_CRITICAL  ) return "CRITICAL";
    if( log_mask & LOG_ERROR     ) return "ERROR";
    if( log_mask & LOG_WARN      ) return "WARNING";
    if( log_mask & LOG_NOTICE    ) return "NOTICE";
    if( log_mask & LOG_INFO      ) return "INFO";
    if( log_mask & LOG_DEBUG     ) return "DEBUG";
    return "???";
}

/* -------------------------------------------------------------------------- */

/** @fn     log_printf()
 *  @brief  Top level logging printf for use in the LOG macro
 *  @param  log_mask  the current mask to be forwarded to the output function
 *  @param  format    printf style format string
 *  @param  ...       variable number of arguments for the format
 *  @return void
 */

PUBLIC void
log_printf( LOG_SUB_SYSTEM sub_system, LOG_LEVEL log_mask, const char * format, ... )
{
    uint16_t milli_seconds = 0;	//TODO replace milliseconds with a 'time since boot'?

    va_list args;
    char message[LOG_MAX_MESSAGE_SIZE];
    char print_message[LOG_MAX_MESSAGE_SIZE];
    uint8_t handler;
    int len;

    /* Format the printf part */
    va_start( args, format );
    len = vsnprintf( print_message, sizeof(print_message), format, args );
    va_end( args );


    /* Extend with the data time stamp and log level name */
    snprintf( message, sizeof(message),
              "%03d,%s,%s,\"%s\"\r\n",
              milli_seconds,
              log_get_sub_system_label( sub_system ),
              log_get_mask_level_label( log_mask ),
              print_message );

    /* Send message to all available output functions */
    if( len )
    {
        for( handler = 0; handler < LOG_MAX_OUTPUTS; handler++ )
        {
            if( log_outputs[handler] != NULL )
            {
                (log_outputs[handler])( sub_system,
                                        log_mask,
                                        message,
                                        log_userdata[handler] );
            }
        }
    }
}

/* -------------------------------------------------------------------------- */

/** @fn     log_add_output()
 *  @brief  Add the indicated output function to the logger ouputs
 *  @param  outfunc    the output function to be cleared
 *  @return void
 */

PUBLIC void
log_add_output( LogOutputFunction outfunc,
                void              * userdata )
{
    uint8_t handler;

    // Make sure it is not already in the list
    log_clear_output( outfunc, userdata );

    // Add the output function in the list
    for( handler = 0; handler < LOG_MAX_OUTPUTS; handler++ )
    {
        if( log_outputs[handler] == NULL )
        {
            log_outputs[handler]  = outfunc;
            log_userdata[handler] = userdata;
            break;
        }
    }
}

/* -------------------------------------------------------------------------- */

/** @fn     log_clear_output()
 *  @brief  Remove the indicated output function from the logger ouputs
 *  @param  outfunc    the output function to be cleared
 *  @return void
 */

PUBLIC void
log_clear_output( LogOutputFunction outfunc,
                  void              * userdata )
{
    uint8_t handler;

    for( handler = 0; handler < LOG_MAX_OUTPUTS; handler++ )
    {
        if( ( log_outputs[handler] == outfunc )
            &&
            ( log_userdata[handler] == userdata ) )
        {
            log_outputs[handler] = NULL;
            log_userdata[handler] = NULL;
        }
    }
}

/* ----- End ---------------------------------------------------------------- */


