/**
 * @file      hal_button.c
 *
 * @brief     Low level GPIO interface to the buttons.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "hal_button.h"
#include "hal_gpio.h"

/* -------------------------------------------------------------------------- */


/* ----- Defines ------------------------------------------------------------ */


/* ------------------------ Variables --------------------------------------- */


/* ----- Public Functions --------------------------------------------------- */

PUBLIC bool
hal_button_is_pressed( ButtonId_t id )
{
    bool pressed = false;
    switch( id )
    {
        case BUTTON_0:
            pressed = hal_gpio_read_pin(_BTN);
            break;

        default:
            break;
    }
    return pressed;
}

/* ----- End ---------------------------------------------------------------- */

