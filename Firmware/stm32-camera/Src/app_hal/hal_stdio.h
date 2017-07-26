/**
 * @file      hal_stdio.h
 *
 * @brief     stdio implementation to use default printf on grooming trap
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_STDIO_H
#define HAL_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_stdio_put( int ch );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_stdio_flush( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_STDIO_H */
