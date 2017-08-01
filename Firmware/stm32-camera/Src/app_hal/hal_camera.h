/**
 * @file      hal_camera.h
 *
 * @brief     Low level interface to the camera.
*/

#ifndef HAL_CAMERA_H
#define HAL_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

    /* Enable/disable 1.3V and 2.5V regulators. */
PUBLIC void
hal_camera_power( bool on );

/* -------------------------------------------------------------------------- */

/* Get the strobe state from the sensor */
PUBLIC bool
hal_camera_strobe( void );

/* -------------------------------------------------------------------------- */

/* Control the reset line */
PUBLIC void
hal_camera_reset( bool on );

/* -------------------------------------------------------------------------- */

/* Control the sensor's snapshot mode */
PUBLIC void
hal_camera_snapshot( bool on );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_CAMERA_H */
