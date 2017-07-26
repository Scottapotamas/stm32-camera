/**
 * @file      hal_gpio_mcu.h
 *
 * @brief     Thin interface layer to access GPIO for internal MCU pins.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_GPIO_MCU_H
#define HAL_GPIO_MCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_gpio.h"
#include "hal_gpio_types.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_gpio_mcu_init( const HalGpioPortNr_t port_nr,
                   const HalGpioPinNr_t  pin_nr,
                   const HalGpioMode_t   mode,
                   const bool            initial_state );

/* -------------------------------------------------------------------------- */

/** Return true when input pin is high, false when input is low */

PUBLIC bool
hal_gpio_mcu_read_pin( const HalGpioPortNr_t port_nr,
                       const HalGpioPinNr_t  pin_nr );

/* -------------------------------------------------------------------------- */

/** Set output pin high when on = true, low when on = false */

PUBLIC void
hal_gpio_mcu_write_pin( const HalGpioPortNr_t port_nr,
                        const HalGpioPinNr_t  pin_nr,
                        const bool            on );

/* -------------------------------------------------------------------------- */

/** Toggle the current output state */

PUBLIC void
hal_gpio_mcu_toggle_pin( const HalGpioPortNr_t port_nr,
                         const HalGpioPinNr_t  pin_nr );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_GPIO_MCU_H */
