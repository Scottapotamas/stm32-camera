/**
 * @file      app_hardware.c
 *
 * @ingroup   tasks
 *
 * @brief     Application Level Hardware Initialisation
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "hal_systick.h"
#include "status.h"
#include "hal_gpio.h"
#include "hal_watchdog.h"
#include "hal_adc.h"
#include "system_speed.h"
#include "ir_filter.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
app_hardware_init( void )
{
	system_speed_init();		//setup state machine for clock changes

    /* Configure internal GPIO pins */
    hal_gpio_configure_mcu_defaults();

    /* Continue basic I/O setup */
    status_green( true );
    status_red( true );

    hal_adc_init();
    //ir_filter_init();

    /* Start the watchdog for around 10s timeout */
    hal_watchdog_init( 20000 );

    //TODO init i2c and camera pin states here
    hal_systick_init();
}

/* ----- End ---------------------------------------------------------------- */
