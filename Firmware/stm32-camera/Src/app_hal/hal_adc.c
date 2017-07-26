/**
 * @file      hal_adc.c
 *
 * @brief     ADC Pin Declarations and easy access functions.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/


/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "adc.h"
#include "hal_adc.h"
#include "average_long.h"
#include "average_short.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ------------------------- Average ---------------------------------------- */

PRIVATE bool           adc_running;
PRIVATE uint8_t        adc_tick;
PRIVATE uint8_t        adc_enabled[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_dma[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_channels[HAL_ADC_INPUT_NUM];
PRIVATE uint32_t       adc_peaks[HAL_ADC_INPUT_NUM];
PRIVATE AverageShort_t adc_averages[HAL_ADC_INPUT_NUM];

/* ------------------------- Functions -------------------------------------- */

PUBLIC void
hal_adc_init( void )
{
    adc_running = false;
    memset( &adc_peaks,    0, sizeof( adc_peaks ) );
    memset( &adc_enabled,  0, sizeof( adc_enabled ) );
    memset( &adc_dma,      0, sizeof( adc_dma ) );
    memset( &adc_channels, 0, sizeof( adc_channels ) );
    memset( &adc_averages, 0, sizeof( adc_averages ) );

    for( uint8_t i = 0; i < HAL_ADC_INPUT_NUM; i++ )
    {
        average_short_init( &adc_averages[i], 32 );
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return adc_channels[input];
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read_avg( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return average_short_get_average( &adc_averages[input] );
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_adc_read_peak( HalAdcInput_t input )
{
    REQUIRE( input < HAL_ADC_INPUT_NUM );
    return adc_peaks[input];
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_adc_start( HalAdcInput_t input )
{
    /* Increment reference count for this input */
    adc_enabled[input] += 1;

    /* Clear the peak history */
    adc_peaks[input] = 0;

    /* If enabled and was not running before, turn on the sampling DMA
     * the tick handler will turn it on */
    adc_running = true;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_adc_stop( HalAdcInput_t input )
{
    bool enabled = false;

    REQUIRE( input < HAL_ADC_INPUT_NUM );

    /* Decrement reference count for this input */
    if( adc_enabled[input] > 0 )
    {
        adc_enabled[input] -= 1;
    }

    /* Check if any sensors are still enabled */
    for( uint8_t i = 0; i < HAL_ADC_INPUT_NUM; i++ )
    {
        if( adc_enabled[i] > 0 )
        {
            enabled = true;
            break;
        }
    }

    /* If no longer enabled, turn off the sampling DMA */
    if( !enabled )
    {
        adc_running = false;
        HAL_ADC_Stop_DMA( &hadc1 );
    }
}

/* -------------------------------------------------------------------------- */

/** Timer tick to trigger a ADC conversion cycle */

PUBLIC void
hal_adc_tick( void )
{
    if( adc_running )
    {
        adc_tick++;
        if( adc_tick > 20 )
        {
            adc_tick = 0;
            HAL_ADC_Stop_DMA( &hadc1 );
            HAL_ADC_Start_DMA( &hadc1, &adc_dma[HAL_ADC_INPUT_VBACKUPBAT], 5 );
//            HAL_ADC_Start_DMA( &hadc3, &adc_dma[HAL_ADC_INPUT_M1_CURRENT], 3 );
        }
    }
}

/* -------------------------------------------------------------------------- */

void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
    if( hadc == &hadc1 )
    {
        /* Freeze the DMA collected samples */
        memcpy( &adc_channels[HAL_ADC_INPUT_VBACKUPBAT],
                &adc_dma[HAL_ADC_INPUT_VBACKUPBAT],
                5 * sizeof( adc_channels[0] ) );

        /* Run them though the averaging */
        for( uint8_t chan = HAL_ADC_INPUT_VBACKUPBAT;
                     chan < HAL_ADC_INPUT_M1_CURRENT;
                     chan++ )
        {
            average_short_update( &adc_averages[chan], adc_channels[chan] );
            adc_peaks[chan] = MAX( adc_peaks[chan], adc_channels[chan] );
        }
    }
    /*
    if( hadc == &hadc3 )
    {
        // Freeze the DMA collected samples
        memcpy( &adc_channels[HAL_ADC_INPUT_M1_CURRENT],
                &adc_dma[HAL_ADC_INPUT_M1_CURRENT],
                4 * sizeof( adc_channels[0] ) );

        // Run them though the averaging
        for( uint8_t chan = HAL_ADC_INPUT_M1_CURRENT;
                     chan < HAL_ADC_INPUT_NUM;
                     chan++ )
        {
            average_short_update( &adc_averages[chan], adc_channels[chan] );
            adc_peaks[chan] = MAX( adc_peaks[chan], adc_channels[chan] );
        }
    }
	*/
}

/* -------------------------------------------------------------------------- */

void HAL_ADC_ErrorCallback( ADC_HandleTypeDef* hadc __attribute__((unused)) )
{
    asm("nop");
}

/* ----- End ---------------------------------------------------------------- */
