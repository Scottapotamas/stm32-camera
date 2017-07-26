/**
 * @file      log_output_terminal.h
 *
 * @ingroup   utility
 *
 * @brief     Provide log output via the terminal interface.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef LOG_OUTPUT_TERMINAL_H
#define	LOG_OUTPUT_TERMINAL_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "log.h"

/* ----- Types -------------------------------------------------------------- */


/* ----------------------- Functions Specifications --------------------------*/

PUBLIC void
log_output_terminal_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_output_terminal( const LOG_LEVEL log_level,
                     const char * message );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_OUTPUT_TERMINAL_H */

