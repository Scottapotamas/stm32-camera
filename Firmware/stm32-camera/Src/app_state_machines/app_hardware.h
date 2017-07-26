/**
 * @file      app_hardware.h
 *
 * @brief     Application Level Hardware Initialisation.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APPLICATION_HARDWARE_H
#define APPLICATION_HARDWARE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>

/* ----- Local Includes ----------------------------------------------------- */


/* ----- Defines ------------------------------------------------------------ */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
app_hardware_init( void );

/* ----- End ------------------------------~--------------------------------- */

#ifdef    __cplusplus
}
#endif
#endif /* APPLICATION_HARDWARE_H */
