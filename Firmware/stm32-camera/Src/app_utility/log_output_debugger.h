/**
 * @file      log_output_debugger.h
 *
 * @ingroup   utility
 *
 * @brief     Provide log output via the debugger SWO interface.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef LOG_OUTPUT_DEBUGGER_H
#define	LOG_OUTPUT_DEBUGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */


/* ----------------------- Functions Specifications ------------------------- */

PUBLIC void
log_output_debugger_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_output_debugger( LOG_LEVEL log_mask,
                     const char * message );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

