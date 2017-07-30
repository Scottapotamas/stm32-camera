/**
 * @file      hal_camera.c
 *
 * @brief     Low level interface to the camera.
 *
*/

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_camera.h"
#include "hal_gpio.h"
#include "hal_power.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Variables ---------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- CAMERA INTERFACE                                                   --- */
/* -------------------------------------------------------------------------- */

/* Enable/disable power to the camera. */

PUBLIC void
hal_camera_power( bool on )
{
	hal_gpio_write_pin( _PWR_EN, on );
}


/* ----- End ---------------------------------------------------------------- */

