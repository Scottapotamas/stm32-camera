/**
 * @file      hal_flash.h
 *
 * @brief     Low level interface to the camera flash.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_DAC_H
#define HAL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */
/* --- FLASH INTERFACE                                                    --- */
/* -------------------------------------------------------------------------- */

/* DAC initialisation */
PUBLIC void
hal_dac_init( void );

/* -------------------------------------------------------------------------- */

/* DAC On/Off */
PUBLIC void
hal_dac( bool on );

/* -------------------------------------------------------------------------- */

/* DAC output voltage */
PUBLIC void
hal_dac_set_dac_voltage( const float voltage );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_FLASH_H */
