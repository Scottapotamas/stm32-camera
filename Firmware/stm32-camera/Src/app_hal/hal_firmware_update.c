/**
 * @file      hal_firmware_update.c
 *
 * @brief     Access the ADC with the internal temperature sensor.
 *
 * @author    Scott Rapson <scottr@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "hal_firmware_update.h"
#include "hal_watchdog.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "stm32f4xx_hal.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/* ----- Data --------------------------------------------------------------- */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
hal_firmware_update()
{
    /* Update the watch dog one last time while we have not corrupted any
     * memory yet. This ensure that the watch dog does not kick while we do
     * the reset sequence. */
    hal_watchdog_refresh();

    hal_gpio_write_pin(_REBOOT_LATCH, true);
    hal_delay_ms(20); 	//TODO work out how long we need to power the cap for
    //TODO make reboot_latch a input to hold it high over a reboot maybe?

    /* Go straight to the CORE_CM4 inline function for a reset */
    NVIC_SystemReset();

    /* NO RETURN */
}

/* ----- End ---------------------------------------------------------------- */
