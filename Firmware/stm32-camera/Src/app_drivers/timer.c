/**
 * @file      timer.c
 *
 * @brief     Lightweight functions around hal_systick_get_ms() to
 *            manage timeouts and stop watches with ms resolution. Using
 *            functions instead of macros to allow for stronger typing.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

/* ---- Local Includes ------------------------------------------------------ */

#include "timer.h"
#include "hal_systick.h"

/* ---- Public Functions ---------------------------------------------------- */

//! Start a timer for a particular timeout.
PUBLIC void
timerStart( timer_t * timer, timer_t delay_ms )
{
    *timer = hal_systick_get_ms() + delay_ms;
}

/* -------------------------------------------------------------------------- */

//! Stop the timer from expiring.
PUBLIC void
timerStop( timer_t * timer )
{
    *timer = 0;
}

/* -------------------------------------------------------------------------- */

//! Return true when timer is running and has expired.
PUBLIC bool
timerIsExpired( timer_t * timer )
{
    return (*timer) && (hal_systick_get_ms() >= *timer);
}

/* -------------------------------------------------------------------------- */

//! Start a stopwatch to measure time
PUBLIC void
timerStopwatchStart( timer_t * timer )
{
    *timer = hal_systick_get_ms();
}

/* -------------------------------------------------------------------------- */

//! Return the current stopwatch time.
PUBLIC timer_t
timerStopwatchLap( timer_t * timer )
{
    return hal_systick_get_ms() - *timer;
}

/* -------------------------------------------------------------------------- */

//! Return the current stopwatch time.
PUBLIC timer_t
timerStopwatchStop( timer_t * timer )
{
    return hal_systick_get_ms() - *timer;
}

/* ----- End ---------------------------------------------------------------- */
