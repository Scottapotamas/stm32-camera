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

/* -------------------------------------------------------------------------- */

PUBLIC void
app_hardware_init( void )
{
	//TODO start the clocks for the GPIO peripherals etc here, instead of the stm32 mx_gpio
    /* Configure internal GPIO pins */
    hal_gpio_configure_mcu_defaults();

    /* Continue basic I/O setup */
    status_green( true );
    status_red( true );

    /* Start the watchdog for around 10s timeout */
    hal_watchdog_init( 20000 );

    /* Configure external I2C pins */
    //hal_gpio_configure_i2c_defaults();
    //TODO init i2c and camera pin states here
    hal_systick_init();
}

/* ----- End ---------------------------------------------------------------- */
