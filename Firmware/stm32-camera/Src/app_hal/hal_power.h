/**
 * @file      hal_power.h
 *
 * @brief     Hardware abstraction interface for controlling power domains
 *            on PCB. Use the hal_power_for and one of HalPowerDomain_t
 *            to enable the required power bus a requested peripheral like
 *            in:
 *                  hal_power_for( CAMERA, true );
 *                  hal_camera_power( true );
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_POWER_H
#define HAL_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

typedef enum
{
    RESET_REASON_UNKNOWN = 0,
    RESET_REASON_BOR,
    RESET_REASON_PIN,
    RESET_REASON_POR,
    RESET_REASON_SW,
    RESET_REASON_IWDG,
    RESET_REASON_WWDG,
    RESET_REASON_LPWR,
} HalPowerResetReason_t;

/* ----- Public Functions --------------------------------------------------- */

PUBLIC HalPowerResetReason_t
hal_power_reset_reason( void );

/* -------------------------------------------------------------------------- */

PUBLIC const char *
hal_power_reset_reason_description( HalPowerResetReason_t reason );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_POWER_H */
