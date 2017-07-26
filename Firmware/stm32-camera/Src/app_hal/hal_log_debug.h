/**
 * @file      hal_log_debug.c
 *
 * @brief     Low level interface to a logger UART.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_LOG_DEBUG_H
#define HAL_LOG_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* -------------------------------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_log_debug_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_log_debug_str( const char * str );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_LOG_DEBUG_H */

