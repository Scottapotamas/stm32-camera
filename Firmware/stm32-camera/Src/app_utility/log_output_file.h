/**
 * @file      log_output_file.h
 *
 * @ingroup   utility
 *
 * @brief     Provide log output to a file.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef LOG_OUTPUT_FILE_H
#define	LOG_OUTPUT_FILE_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "log.h"

/* ----- Types -------------------------------------------------------------- */


/* ----------------------- Functions Specifications -------------------------*/

PUBLIC void
log_output_file_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_output_file( const LOG_LEVEL log_level,
                 const char * message );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_OUTPUT_FILE_H */

