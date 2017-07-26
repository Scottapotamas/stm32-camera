/**
 * @file      status.h
 *
 * @brief     Access to the two status LED's on the PCB.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include <stdbool.h>

/* -------------------------------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
status_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_red( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_red_toggle( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_green( bool on );

/* -------------------------------------------------------------------------- */

PUBLIC void
status_green_toggle( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* STATUS_H */
