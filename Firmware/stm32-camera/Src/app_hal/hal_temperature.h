/**
 * @file      hal_temperature.h
 *
 * @brief     Access the ADC with the internal temperature sensor.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_TEMPERATURE_H
#define HAL_TEMPERATURE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

/** Return a ADC sample of the internal temperature sensor converted in
  * tents of degrees C. Note the function can return values below 0 degrees!
  */
PUBLIC float
hal_temperature_degrees_C( uint32_t raw_adc );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_TEMPERATURE_H */
