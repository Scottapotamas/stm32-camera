/**
 * @file      log_output_buffer.h
 *
 * @ingroup   utility
 *
 * @brief     Provide log output to a buffer fifo in RAM.
 *            To be used with asynchronously writing to a file.
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

/** Callback function prototype signalling something got deposited in the
 * log buffer. Reports the current buffer used and the % full.
 */
typedef void (*LogBufferSignalCallback_t)( LOG_LEVEL level,
                                           uint32_t  used,
                                           uint32_t  percent_full );

/* ----------------------- Functions Specifications -------------------------*/

/** Init the log message internal buffer. */

PUBLIC void
log_output_buffer_init( uint8_t * buffer, size_t buffer_size );

/* -------------------------------------------------------------------------- */

/** Writes a log message to the internal buffer. */

PUBLIC void
log_output_buffer( LOG_SUB_SYSTEM sub_system,
                   LOG_LEVEL      log_level,
                   const char     * message,
                   void           * userdata );

/* -------------------------------------------------------------------------- */

/** Set the LOG_LEVEL that this buffer logger is to accept */

PUBLIC void
log_output_buffer_mask_level( LOG_LEVEL log_mask );

/* -------------------------------------------------------------------------- */

/** Return how much data is in the log buffer */

PUBLIC uint32_t
log_output_buffer_used( void );

/* -------------------------------------------------------------------------- */

/** Read a chunk of the FIFO buffer */

PUBLIC uint32_t
log_output_buffer_read( char * buffer, uint32_t bytes_to_read );

/* -------------------------------------------------------------------------- */

/** Set callback for buffer activity */

PUBLIC void
log_output_buffer_set_signal_handler( LogBufferSignalCallback_t handler );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_OUTPUT_FILE_H */

