/**
 * @file      auxiliary.c
 *
 * @brief     Auxiliary port control and support.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "auxiliary.h"
#include "hal_power.h"
#include "hal_gpio.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* -------------------------------------------------------------------------- */

PRIVATE const char * aux_mode_names[] =
{
   [ AUX_MODE_NONE ]        = "OFF",
   [ AUX_MODE_DAC ]      	= "ANALOG OUT",
   [ AUX_MODE_PWM ]      	= "PWM OUT",
   [ AUX_MODE_IO ]      	= "BASIC IO",

};

/* -------------------------------------------------------------------------- */
/* --- DISPLAY NAMING                                                     --- */
/* -------------------------------------------------------------------------- */

PUBLIC const char *
auxiliary_mode_name( AuxiliaryMode_t mode )
{
    return aux_mode_names[ mode ];
}

/* -------------------------------------------------------------------------- */
/* --- DIGITAL I/O INTERFACE                                              --- */
/* -------------------------------------------------------------------------- */

PUBLIC bool
auxiliary_gpio_in( AuxiliaryGpio_t pin )
{
    bool status = false;
    switch( pin )
    {
        case AUX_GPIO_0:
            status = hal_gpio_read_pin( _AUX_GPIO_0 );
            break;
        case AUX_GPIO_1:
            status = hal_gpio_read_pin( _AUX_GPIO_1 );
            break;
        case AUX_GPIO_2:
            status = hal_gpio_read_pin( _AUX_GPIO_2 );
            break;
    }
    return status;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
auxiliary_gpio_mode( AuxiliaryGpio_t pin, AuxiliaryGpioMode_t mode )
{
    const HalGpioMode_t gpio_mode = ( mode == AUX_GPIO_MODE_INPUT )
                                    ? MODE_INPUT : MODE_OUT_PP;
    //TODO support special output modes on aux 2
    switch( pin )
    {
        case AUX_GPIO_0:
            hal_gpio_init( _AUX_GPIO_0, gpio_mode, 0 );
            break;
        case AUX_GPIO_1:
            hal_gpio_init( _AUX_GPIO_1, gpio_mode, 0 );
            break;
        case AUX_GPIO_2:
            hal_gpio_init( _AUX_GPIO_2, gpio_mode, 0 );
            break;
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
auxiliary_gpio_out( AuxiliaryGpio_t pin, bool on )
{
    switch( pin )
    {
        case AUX_GPIO_0:
            hal_gpio_write_pin( _AUX_GPIO_0, on );
            break;
        case AUX_GPIO_1:
            hal_gpio_write_pin( _AUX_GPIO_1, on );
            break;
        case AUX_GPIO_2:
            hal_gpio_write_pin( _AUX_GPIO_2, on );
            break;
    }
}

/* ----- End ---------------------------------------------------------------- */
