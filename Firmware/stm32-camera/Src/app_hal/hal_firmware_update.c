/**
 * @file      hal_firmware_update.c
 *
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
#include "app_times.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/* ----- Data --------------------------------------------------------------- */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
hal_firmware_update()
{
    /* This ensure that the watch dog does not kick while reset. */
    hal_watchdog_refresh();

    //Charge the cap on the BOOT0 pin and then ensure the output doesn't drain it during reboot
    hal_gpio_write_pin(_REBOOT_LATCH, true);
    hal_delay_ms( TIME_REBOOT_CAP_CHARGE );
    hal_gpio_init(_REBOOT_LATCH, MODE_ANALOG, 0);

    /* Go straight to the CORE_CM4 inline function for a reset */
    NVIC_SystemReset();

    /* NO RETURN */
}

/* ----- End ---------------------------------------------------------------- */
