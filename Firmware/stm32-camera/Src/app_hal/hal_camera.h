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

/* Enable power to the camera */
PUBLIC void
hal_camera_power( bool on );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_CAMERA_H */
