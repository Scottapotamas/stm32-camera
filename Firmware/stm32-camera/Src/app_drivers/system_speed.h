/**
 * @file      system_speed.h
 *
 * @brief     Control the system clock speed for power saving purposes.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef SYSTEM_SPEED_H
#define SYSTEM_SPEED_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include <stdbool.h>

/* ----- Public Functions --------------------------------------------------- */

#include "global.h"

typedef enum
{
    SYSTEM_SPEED_LOW_POWER = 0,
    SYSTEM_SPEED_FULL
} SystemSpeed_t;

/* -------------------------------------------------------------------------- */

PUBLIC void
system_speed_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
system_speed_set( SystemSpeed_t speed );

/* -------------------------------------------------------------------------- */

PUBLIC SystemSpeed_t
system_speed_get( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
system_speed_cleanup( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_SPEED_H */
