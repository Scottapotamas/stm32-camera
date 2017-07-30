/**
 * @file      OV2640.h
 *
 * @brief     VC0706 Camera Driver
 *
*/

#ifndef OV2640_H
#define OV2640_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/* Command codes */



/* ----- Types ------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */

/** Init the camera driver */

PUBLIC void
ov2640_init( void );

/* -------------------------------------------------------------------------- */

/** Stop the camera driver */

PUBLIC void
ov2640_deinit( void );



/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* OV2640_H */
