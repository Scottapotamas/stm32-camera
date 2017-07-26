/**
 * @file      app_background.c
 *
 * @brief     Application main loop background processes
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "app_background.h"
#include "event_subscribe.h"
#include "app_signals.h"
#include "button.h"
#include "hal_button.h"
#include "hal_terminal.h"
#include "timer.h"

/* -------------------------------------------------------------------------- */

PRIVATE timer_t button_timer = 0;

/* -------------------------------------------------------------------------- */

PUBLIC void
app_background_init( void )
{
    timerStart( &button_timer, 50 );
    hal_terminal_init( 115200 );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
app_background( void )
{
    if( timerIsExpired( &button_timer ) )
    {
        timerStart( &button_timer, 50 );
    }

    /* Scan buttons */
    button_process();
    hal_terminal_process();
}

/* ----- End ---------------------------------------------------------------- */

