/**
 * @file      status.h
 *
 * @brief     Access to the two status LED's on the PCB.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "status.h"
#include "hal_gpio.h"

/* -------------------------------------------------------------------------- */
/* --- INIT                                                               --- */
/* -------------------------------------------------------------------------- */

PUBLIC void
status_init( void )
{

}

/* -------------------------------------------------------------------------- */
/* --- RED                                                                --- */
/* -------------------------------------------------------------------------- */

PUBLIC void
status_red( bool on )
{
    hal_gpio_write_pin( _STATUS_1, on );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
status_red_toggle( void )
{
    hal_gpio_toggle_pin( _STATUS_1 );
}

/* -------------------------------------------------------------------------- */
/* --- GREEN                                                              --- */
/* -------------------------------------------------------------------------- */

PUBLIC void
status_green( bool on )
{
    hal_gpio_write_pin( _STATUS_0, on );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
status_green_toggle( void )
{
    hal_gpio_toggle_pin( _STATUS_0 );
}

/* ----- End ---------------------------------------------------------------- */

