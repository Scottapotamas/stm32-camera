/**
 * @file      hal_systick.c
 *
 * @brief     Hooks into the STM HAL_SYSTICK_Callback()
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* -------------------------------------------------------------------------- */

#include <string.h>

/* -------------------------------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "hal_systick.h"
#include "stm32f4xx_hal.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* -------------------------------------------------------------------------- */

/* Ensure the hook pointers are all init before main starts */

PRIVATE voidTickHookFuncPtr  tick_hooks[HAL_SYSTICK_MAX_HOOKS] = { 0 };

/* -------------------------------------------------------------------------- */

/** Enable and init system tick. Configure for the current system clock */

PUBLIC void
hal_systick_init( void )
{
    /* Use systick as time base source and configure 1ms tick
     * (default clock after Reset is HSI) */
    HAL_InitTick(TICK_INT_PRIORITY);
}

/* -------------------------------------------------------------------------- */

/** Provides a tick value in millisecond.*/

PUBLIC uint32_t
hal_systick_get_ms( void )
{
    return HAL_GetTick();
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
hal_systick_hook( voidTickHookFuncPtr hookfunc )
{
    // Make sure it is not already in the list
    hal_systick_unhook( hookfunc );

    bool empty_available = false;

    // Add the output function in the list
    for( uint8_t handler = 0; handler < HAL_SYSTICK_MAX_HOOKS; handler++ )
    {
        if( tick_hooks[handler] == NULL )
        {
            empty_available = true;
            CRITICAL_SECTION_VAR();
            CRITICAL_SECTION_START();
            tick_hooks[handler] = hookfunc;
            CRITICAL_SECTION_END();
            break;
        }
    }
    ENSURE( empty_available );

    return empty_available;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_systick_unhook( voidTickHookFuncPtr hookfunc )
{
    for( uint8_t handler = 0; handler < HAL_SYSTICK_MAX_HOOKS; handler++ )
    {
        if( tick_hooks[handler] == hookfunc )
        {
            CRITICAL_SECTION_VAR();
            CRITICAL_SECTION_START();
            tick_hooks[handler] = NULL;
            CRITICAL_SECTION_END();
            break;
        }
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
HAL_SYSTICK_Callback(void)
{
    for( uint8_t handler = 0; handler < HAL_SYSTICK_MAX_HOOKS; handler++ )
    {
        if( tick_hooks[handler] != NULL )
        {
            (tick_hooks[handler])();
        }
    }
}

/* ----- End ---------------------------------------------------------------- */
