/**
 * @file      hal_delay.c
 *
 * @brief     Delay functions using background timers for accurate timing.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_DELAY_H
#define HAL_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

/** Delay time in milli seconds. Uses a background timer for timing. */

PUBLIC void
hal_delay_ms( uint32_t delay_ms );

/* -------------------------------------------------------------------------- */

/** Delay time in micro seconds. Uses a background timer for timing. */

PUBLIC void
hal_delay_us( uint32_t delay_us );

/* -------------------------------------------------------------------------- */

/** Delay time in nano seconds. Uses a background timer for timing. */

PUBLIC void
hal_delay_ns( uint32_t delay_ns );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_DELAY_H */
