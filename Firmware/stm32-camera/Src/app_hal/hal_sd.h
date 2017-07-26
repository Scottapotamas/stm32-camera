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

#ifndef HAL_SD_H
#define HAL_SD_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local includes ----------------------------------------------------- */

#include "global.h"

/* ----- Types -------------------------------------------------------------- */


/* ----- Public Prototypes -------------------------------------------------- */

/** Return true when SD card is detected */

PUBLIC bool
hal_sd_is_present( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SD_H */
