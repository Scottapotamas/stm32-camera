/**
 * @file      hal_power.c
 *
 * @brief     Hardware abstraction interface for controlling power on PCB
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_power.h"
#include "hal_gpio.h"
#include "stm32f4xx_hal.h"

/* -------------------------------------------------------------------------- */

PUBLIC HalPowerResetReason_t
hal_power_reset_reason( void )
{
    HalPowerResetReason_t reason = RESET_REASON_UNKNOWN;

    if( __HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET )
    {
      reason = RESET_REASON_BOR;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET )
    {
        reason = RESET_REASON_POR;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET )
    {
        reason = RESET_REASON_SW;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET )
    {
        reason = RESET_REASON_IWDG;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET )
    {
        reason =  RESET_REASON_WWDG;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) != RESET )
    {
        reason =  RESET_REASON_LPWR;
    }
    else if( __HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET )
    {
        reason = RESET_REASON_PIN;
    }
    __HAL_RCC_CLEAR_RESET_FLAGS();

    return reason;
}

/* -------------------------------------------------------------------------- */

PUBLIC const char *
hal_power_reset_reason_description( HalPowerResetReason_t reason )
{
    switch( reason )
    {
        case RESET_REASON_BOR:  return "BROWN OUT";
        case RESET_REASON_PIN:  return "RESET PIN";
        case RESET_REASON_POR:  return "POWER ON";
        case RESET_REASON_SW:   return "SOFTWARE";
        case RESET_REASON_IWDG: return "INDEPENDENT WATCHDOG";
        case RESET_REASON_WWDG: return "WINDOW WATCHDOG";
        case RESET_REASON_LPWR: return "LOW POWER";
        default:                return "?";
    }

    return "?";
}

/* ----- End ---------------------------------------------------------------- */

