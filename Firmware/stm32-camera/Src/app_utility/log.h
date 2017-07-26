/**
 * @file      log.h
 *
 * @brief     Debug & Trace Logging System.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef LOG_H
#define	LOG_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>   // For special printf formats

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/** Size of log message output buffer */
#ifndef LOG_MAX_MESSAGE_SIZE
    #define LOG_MAX_MESSAGE_SIZE    255
#endif

/** Maximum number of log output handlers */
#ifndef LOG_MAX_OUTPUTS
    #define LOG_MAX_OUTPUTS         3
#endif

/** Subsystem logging the event. */
typedef enum
{
    FILE_SYSTEM   = _BV(0),
    CONFIG        = _BV(1),
    LOGGING       = _BV(2),
    MENU          = _BV(3),
    LASER         = _BV(4),
    BACKLIGHT     = _BV(5),
    LURE          = _BV(6),
    MONITOR       = _BV(7),
    AUXILIARY     = _BV(8),
    SUPERVISOR    = _BV(9),
    SENSOR        = _BV(10),
    CAMERA        = _BV(11),
    DELIVERY      = _BV(12),
    AUDIO         = _BV(13),
    BATTERY       = _BV(14),
    TEMPERATURE   = _BV(15),
} LOG_SUB_SYSTEM;

#define LOG_SUB_SYSTEM_MASK_ALL     (0xFFFF)

/** Log masks bits for selective logging output. */
typedef enum
{
    LOG_DEBUG     = _BV(0),   // debug-level messages
    LOG_INFO      = _BV(1),   // informational messages
    LOG_NOTICE    = _BV(2),   // normal but significant condition
    LOG_WARN      = _BV(3),   // warning conditions
    LOG_ERROR     = _BV(4),   // error conditions
    LOG_CRITICAL  = _BV(5),   // critical conditions
    LOG_ALERT     = _BV(6),   // action must be taken immediately
    LOG_EMERGENCY = _BV(7),   // system is unusable
} LOG_LEVEL;

#define LOG_MASK_ALL          (0xFF)
#define LOG_MASK_EMERGENCY    (LOG_EMERGENCY)
#define LOG_MASK_ALERT        (LOG_ALERT    | LOG_MASK_EMERGENCY)
#define LOG_MASK_CRITICAL     (LOG_CRITICAL | LOG_MASK_ALERT)
#define LOG_MASK_ERROR        (LOG_ERROR    | LOG_MASK_CRITICAL)
#define LOG_MASK_WARN         (LOG_WARN     | LOG_MASK_ERROR)
#define LOG_MASK_NOTICE       (LOG_NOTICE   | LOG_MASK_WARN)
#define LOG_MASK_INFO         (LOG_INFO     | LOG_MASK_NOTICE)
#define LOG_MASK_DEBUG        (LOG_DEBUG    | LOG_MASK_INFO)

/** Define mask with the log entries that are to be compiled in. */
#define LOG_LEVEL_COMPILE     LOG_MASK_DEBUG

/** Define the default mask of what we use at runtime. */
#define LOG_LEVEL_RUNTIME     LOG_MASK_INFO

/** Logging macro. Depending on the current LOG_PRINT value (see above)
 *  we expect the compiler to eliminate the code for any level for which
 *  LOG_PRINT has not been set. In addition we have a runtime check with
 *  _log_mask_ to allow disabling some logging at runtime.
 */
#define LOG( _sub_system_, _level_, _fmt_, ... )                               \
    do {                                                                       \
        if( LOG_LEVEL_COMPILE & (_level_) & _log_level_mask_ )                   \
        {                                                                      \
            log_printf( _sub_system_, _level_, _fmt_, ## __VA_ARGS__ );        \
        }                                                                      \
    } while(0)

/* ----------------------- Public Variables --------------------------------- */

extern LOG_LEVEL      _log_level_mask_;

/* -------------------------------------------------------------------------- */

typedef void (*LogOutputFunction)( LOG_SUB_SYSTEM system_mask,
                                   LOG_LEVEL      log_mask,
                                   const char     * message,
                                   void           * userdata );

/* ----------------------- Functions Specifications ------------------------- */

PUBLIC void
log_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_set_mask_level( LOG_LEVEL log_mask );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
log_get_mask_level( void );

/* -------------------------------------------------------------------------- */

PUBLIC const char *
log_get_sub_system_label( LOG_SUB_SYSTEM sub_system );

/* -------------------------------------------------------------------------- */

PUBLIC const char *
log_get_mask_level_label( LOG_LEVEL log_mask );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_printf( LOG_SUB_SYSTEM sub_system,
            LOG_LEVEL      log_mask,
            const char *   fmt,
            ... )
            __attribute__ ((format (printf, 3, 4)));

/* -------------------------------------------------------------------------- */

PUBLIC void
log_add_output( LogOutputFunction outfunc,
                void              * userdata );

/* -------------------------------------------------------------------------- */

PUBLIC void
log_clear_output( LogOutputFunction  outfunc,
                  void               * userdata );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

