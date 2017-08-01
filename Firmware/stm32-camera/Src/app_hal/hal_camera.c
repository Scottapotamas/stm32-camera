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

/* ----- Defines ------------------------------------------------------------ */

/* ----- Variables ---------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- CAMERA HARDWARE CONTROL                                            --- */
/* -------------------------------------------------------------------------- */

/* Enable/disable 1.3V and 2.5V regulators. */

PUBLIC void
hal_camera_power( bool on )
{
	hal_gpio_write_pin( _PWR_EN, on );
//    hal_gpio_write_pin( _CAM_PWDN, on );
	//TODO work out CAM_PWDN integration with regulator startup. Or split into different function
}

/* -------------------------------------------------------------------------- */

/* Get the strobe state from the sensor */
PUBLIC bool
hal_camera_strobe( void )
{
    return hal_gpio_read_pin( _CAM_STROBE );
}

/* -------------------------------------------------------------------------- */

/* Control the reset line */
PUBLIC void
hal_camera_reset( bool on )
{
    hal_gpio_write_pin( _CAM_RESET, on );
    //TODO add reset timing and/or power cycling
}

/* -------------------------------------------------------------------------- */

/* Control the sensor's snapshot mode */
PUBLIC void
hal_camera_snapshot( bool on )
{
    hal_gpio_write_pin( _CAM_FREX, on );
    //TODO include snapshot modes which use the _CAM_EXPST pin
}

/* ----- End ---------------------------------------------------------------- */

