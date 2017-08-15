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
#include "dma.h"
#include "hal_adc.h"
#include "hal_gpio.h"
#include "average_long.h"
#include "average_short.h"

/* -------------------------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

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
        average_short_init( &adc_averages[i], 16 );
    }

    //Setup the ADC peripheral and DMA
    ADC_ChannelConfTypeDef sConfig;
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ENABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 3;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;

    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    sConfig.Channel = ADC_CHANNEL_VREFINT;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank = 2;
    sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = 3;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }
}

/* -------------------------------------------------------------------------- */

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
  if(adcHandle->Instance==ADC1)
  {
    __HAL_RCC_ADC1_CLK_ENABLE();

    hal_gpio_init(_AMBIENT_LIGHT, MODE_ANALOG, 0);

    /* ADC1 DMA Init and ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);
  }
}

/* -------------------------------------------------------------------------- */

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
  if(adcHandle->Instance==ADC1)
  {
    __HAL_RCC_ADC1_CLK_DISABLE();

    HAL_GPIO_DeInit(AMBIENT_LIGHT_GPIO_Port, AMBIENT_LIGHT_Pin);
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
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
            HAL_ADC_Start_DMA( &hadc1, &adc_dma[HAL_ADC_INPUT_VREF], 3 );
        }
    }
}

/* -------------------------------------------------------------------------- */

void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
    if( hadc == &hadc1 )
    {
        /* Freeze the DMA collected samples */
        memcpy( &adc_channels[HAL_ADC_INPUT_VREF],
                &adc_dma[HAL_ADC_INPUT_VREF],
                3 * sizeof( adc_channels[0] ) );

        /* Run them though the averaging */
        for( uint8_t chan = HAL_ADC_INPUT_VREF;
                     chan < HAL_ADC_INPUT_NUM;
                     chan++ )
        {
            average_short_update( &adc_averages[chan], adc_channels[chan] );
            adc_peaks[chan] = MAX( adc_peaks[chan], adc_channels[chan] );
        }
    }

}

/* -------------------------------------------------------------------------- */
//TODO remove HAL_ADC_ErrorCallback from hal_adc if nothing breaks
//void HAL_ADC_ErrorCallback( ADC_HandleTypeDef* hadc __attribute__((unused)) )
//{
//    asm("nop");
//}

/* ----- End ---------------------------------------------------------------- */
