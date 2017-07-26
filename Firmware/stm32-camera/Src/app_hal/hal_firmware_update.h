/**
 * @file      hal_firmware_update.h
 *
 * @brief     Interface to the boot loader to start firmware update.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_FIRMWARE_UPDATE_H
#define HAL_FIRMWARE_UPDATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

/** Function to trigger a firmware update.
 */
PUBLIC void
hal_firmware_update();

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_FIRMWARE_UPDATE_H */
