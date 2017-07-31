/**
 * @file      hal_system_speed.h
 *
 * @brief     Low level control of the system clock speed for power saving purposes.
 *            Essentially like the original SystemClock_Config but with two
 *            configurations.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_SYSTEM_SPEED_H
#define HAL_SYSTEM_SPEED_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"


/* ----- Public Functions --------------------------------------------------- */


/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_sleep( void );

/* -------------------------------------------------------------------------- */

PUBLIC float
hal_system_speed_get_load( void );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_system_speed_get_speed( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_high( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_low( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SYSTEM_SPEED_H */
