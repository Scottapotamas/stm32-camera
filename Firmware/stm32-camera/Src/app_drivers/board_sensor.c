/**
 * @file      board_sensor.c
 *
 * @brief     Handle access to the PCB sensors for current, voltage and temperature
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "board_sensor.h"
#include "hal_adc.h"
#include "hal_temperature.h"
#include "hal_systick.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/* ------ Private Functions ------------------------------------------------- */

/* ----- Variables ---------------------------------------------------------- */

/* ----- Public Functions --------------------------------------------------- */

/* ----- Public Functions --------------------------------------------------- */

/* Init the hardware for the board sensors */

PUBLIC void
board_sensor_init( void )
{

}

/* -------------------------------------------------------------------------- */

/** Start/Enable board sensors */

PUBLIC void
board_sensor_enable( void )
{
	hal_adc_start( HAL_ADC_INPUT_TEMPERATURE );
	hal_adc_start( HAL_ADC_INPUT_PHOTOSENSOR );

}

/* -------------------------------------------------------------------------- */

/** Stop/Disable board sensors */

PUBLIC void
board_sensor_disable( void )
{
	hal_adc_stop( HAL_ADC_INPUT_TEMPERATURE );
	hal_adc_stop( HAL_ADC_INPUT_PHOTOSENSOR );
}

/* -------------------------------------------------------------------------- */

/** Return temperature */

PUBLIC float
board_sensor_temperature_C( void )
{
    return hal_temperature_degrees_C(
                hal_adc_read_avg( HAL_ADC_INPUT_TEMPERATURE ) );
}

/* -------------------------------------------------------------------------- */

/** Return light reading */

PUBLIC float
board_sensor_light( void )
{
	//TODO normalise light readings into something more sensible
    return hal_adc_read_avg( HAL_ADC_INPUT_PHOTOSENSOR );
}
/* ----- End ---------------------------------------------------------------- */

