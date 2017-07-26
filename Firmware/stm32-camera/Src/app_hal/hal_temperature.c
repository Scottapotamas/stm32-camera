/**
 * @file      hal_temperature.c
 *
 * @brief     Access the ADC with the internal temperature sensor.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "hal_temperature.h"
#include "hal_adc.h"
#include "stm32f4xx_hal.h"

/* -------------------------------------------------------------------------- */

/* Temperature Calibration Values
 * See STM32F429 datasheet page 163
 * */

#define  V25                0.76f       /* V */
#define  AVG_SLOPE          0.0025f     /* 2.5mV/C */

/* -------------------------------------------------------------------------- */

PUBLIC float
hal_temperature_degrees_C( uint32_t raw_adc )
{
    float   Vsense = ( (float)raw_adc * 3.3f ) / 4096.0f;

    return  ( ( ( Vsense - V25 ) / AVG_SLOPE ) + 25.0f );
}

/* ----- End ---------------------------------------------------------------- */
