/**
 * @file      log_output_debugger.c
 *
 * @ingroup   utility
 *
 * @brief     Log output via debugger IDE window
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "log.h"
#include "log_output_debugger.h"
#include "hal_log_debug.h"

/* ----------------------- Start implementation ----------------------------- */

PUBLIC void
log_output_debugger_init( void )
{
    hal_log_debug_init();
}

/* -------------------------------------------------------------------------- */

PUBLIC void
log_output_debugger( LOG_LEVEL log_mask __attribute__((unused)),
                     const char *  message )
{
    hal_log_debug_str( message );
}

/* ----- End ---------------------------------------------------------------- */


