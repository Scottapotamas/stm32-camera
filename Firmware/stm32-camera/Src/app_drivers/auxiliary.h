/**
 * @file      auxiliary.h
 *
 * @brief     Auxiliary port definitions.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef AUXILIARY_H
#define AUXILIARY_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Types -------------------------------------------------------------- */

typedef enum
{
    AUX_GPIO_0 = 0,
    AUX_GPIO_1,
    AUX_GPIO_2,
} AuxiliaryGpio_t;

typedef enum
{
    AUX_GPIO_MODE_INPUT = 0,
    AUX_GPIO_MODE_OUTPUT,
	AUX_GPIO_MODE_SPECIAL
} AuxiliaryGpioMode_t;

typedef enum
{
    AUX_PORT_ANALOG,
	AUX_PORT_EXP_0,
	AUX_PORT_EXP_1
} AuxiliaryPort_t;

typedef enum
{
    AUX_MODE_NONE,
    AUX_MODE_DAC,
	AUX_MODE_PWM,
	AUX_MODE_IO,
} AuxiliaryMode_t;

/* -------------------------------------------------------------------------- */
/* --- DISPLAY NAMING                                                     --- */
/* -------------------------------------------------------------------------- */

PUBLIC const char *
auxiliary_mode_name( AuxiliaryMode_t mode );

/* -------------------------------------------------------------------------- */
/* --- DIGITAL I/O INTERFACE                                              --- */
/* -------------------------------------------------------------------------- */

/** Read the AUX pin input status */

PUBLIC bool
auxiliary_gpio_in( AuxiliaryGpio_t pin );

/* -------------------------------------------------------------------------- */

/** Set the AUX pin direction */

PUBLIC void
auxiliary_gpio_mode( AuxiliaryGpio_t pin, AuxiliaryGpioMode_t mode );

/* -------------------------------------------------------------------------- */

/** Set the AUX pin output status */

PUBLIC void
auxiliary_gpio_out( AuxiliaryGpio_t pin, bool on );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* AUXILIARY_H */
