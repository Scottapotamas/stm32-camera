/**
 * @file      hal_solenoid.h
 *
 * @brief     Low level interface to the ir switch driver.
*/

#ifndef HAL_SOLENOID_H
#define HAL_SOLENOID_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_solenoid_init( );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_solenoid_off( );

/* -------------------------------------------------------------------------- */


PUBLIC void
hal_solenoid_activate( bool polarity );


/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SOLENOID_H */
