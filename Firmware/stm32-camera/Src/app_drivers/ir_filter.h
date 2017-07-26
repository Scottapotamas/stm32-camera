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

//TODO CHANGE THIS FOR IR FILTER
/* ----- Local Includes ----------------------------------------------------- */

#include <stdbool.h>

/* -------------------------------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
filter_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
filter_clear( void);

/* -------------------------------------------------------------------------- */

PUBLIC void
filter_ir( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
filter_toggle( );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* IR_FILTER_H */
