/**
 * @file      hal_sd.c
 *
 * @brief     Low level interface to the detect if an SD is present
 *            Only works on MkIII hardware. On MkII it always returns false.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "hal_sd.h"
#include "hal_gpio.h"

/* -------------------------------------------------------------------------- */


/* ----- Defines ------------------------------------------------------------ */


/* ------------------------ Variables --------------------------------------- */


/* ----- Public Functions --------------------------------------------------- */

PUBLIC bool
hal_sd_is_present( void )
{
	/* Active low when SD card inserted */
	return hal_gpio_read_pin( _SD_DETECT ) == false;
}

/* ----- End ---------------------------------------------------------------- */
