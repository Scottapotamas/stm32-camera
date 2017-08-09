/**
 * @file      status.h
 *
 * @brief     Access to the two status LED's on the PCB.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef IR_FILTER_H
#define IR_FILTER_H

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
    FILTER_CLEAR = 0,
    FILTER_IR
} FilterPosition_t;

/* -------------------------------------------------------------------------- */

PUBLIC void
ir_filter_init( void );

/* -------------------------------------------------------------------------- */

/** Set the active filter mode */

PUBLIC void
ir_filter_set( uint8_t id, FilterPosition_t mode );

/* -------------------------------------------------------------------------- */

/** Get the current filter mode */

PUBLIC FilterPosition_t
ir_filter_get( void );

/* -------------------------------------------------------------------------- */

/** Process the filter switch state machine */

PUBLIC void
ir_filter_process( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* IR_FILTER_H */
