/**
 * @file      hal_systick.h
 *
 * @brief     Hooks into the STM HAL_SYSTICK_Callback().
 *            This is the 1ms system tick. Use this module to hook
 *            additional application tick handlers into this
 *            interrrupt.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_SYSTICK_H
#define HAL_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

/* Up to 5 hooks can be used. Ensure this is big enough for the number used */
#define HAL_SYSTICK_MAX_HOOKS           5

/* -------------------------------------------------------------------------- */

typedef void (*voidTickHookFuncPtr)(void);

/* -------------------------------------------------------------------------- */

/** Ensure that the timer needed for the delay measurement is started */

PUBLIC void
hal_systick_init( void );

/* -------------------------------------------------------------------------- */

/** Provides a tick value in millisecond.*/

PUBLIC uint32_t
hal_systick_get_ms( void );

/* -------------------------------------------------------------------------- */

// Add a callback function to the 1ms tick timer. Returns true when
// hook was successfully added.

PUBLIC bool
hal_systick_hook( voidTickHookFuncPtr hookfunc );

/* -------------------------------------------------------------------------- */

// Remove a callback function from the 1ms tick timer

PUBLIC void
hal_systick_unhook( voidTickHookFuncPtr hookfunc );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SYSTICK_H */
