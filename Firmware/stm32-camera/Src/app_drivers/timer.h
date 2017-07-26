/**
 * @file      timer.h
 *
 * @brief     Lightweight wrappers around hal_tick_get_ms() to
 *            manage timeouts and stop watches with ms resolution. Using
 *            functions instead of macros to allow for stronger typing.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ---- Local Includes ------------------------------------------------------ */

#include "global.h"

/* ---- Types --------------------------------------------------------------- */

//! to declare timer variables in your code
typedef uint32_t timer_t;

/* ---- Public Functions ---------------------------------------------------- */

//! Start a timer for a particular timeout.
PUBLIC void
timerStart( timer_t * timer, timer_t delay_ms );

/* -------------------------------------------------------------------------- */

//! Stop the timer from expiring.
PUBLIC void
timerStop( timer_t * timer );

/* -------------------------------------------------------------------------- */

//! Return true when timer is running and has expired.
PUBLIC bool
timerIsExpired( timer_t * timer );

/* -------------------------------------------------------------------------- */

//! Start a stopwatch to measure time
PUBLIC void
timerStopwatchStart( timer_t * timer );

/* -------------------------------------------------------------------------- */

//! Return the current stopwatch time.
PUBLIC timer_t
timerStopwatchLap( timer_t * timer );

/* -------------------------------------------------------------------------- */

//! Return the current stopwatch time.
PUBLIC timer_t
timerStopwatchStop( timer_t * timer );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
