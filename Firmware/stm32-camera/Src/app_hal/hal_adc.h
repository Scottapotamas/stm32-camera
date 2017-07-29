/**
 * @file      hal_adc.h
 *
 * @brief     ADC Pin Declarations and easy access functions.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_ADC_H
#define HAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "stm32f4xx_hal.h"

/* ----- Types ------------------------------------------------------------- */

typedef enum
{
    HAL_ADC_INPUT_TEMPERATURE,  /* ADC1 - RANK 1 */
    HAL_ADC_INPUT_PHOTOSENSOR,  /* ADC1 - RANK 2 */
    HAL_ADC_INPUT_NUM
} HalAdcInput_t;

/* ------------------------- Functions Prototypes --------------------------- */

PUBLIC void
hal_adc_init( void );

/* -------------------------------------------------------------------------- */

/** Last converted ADC read */

PUBLIC uint32_t
hal_adc_read( HalAdcInput_t input );

/* -------------------------------------------------------------------------- */

/** Averaged ADC read */

PUBLIC uint32_t
hal_adc_read_avg( HalAdcInput_t input );

/* -------------------------------------------------------------------------- */

/** Start DMA based ADC conversions */

PUBLIC void
hal_adc_start( HalAdcInput_t input );

/* -------------------------------------------------------------------------- */

/** Stop DMA based ADC conversions */

PUBLIC void
hal_adc_stop( HalAdcInput_t input );

/* -------------------------------------------------------------------------- */

/** Timer tick to trigger a ADC conversion cycle */

PUBLIC void
hal_adc_tick( void );

/* -------------------------------------------------------------------------- */

/** HAL Functions copied over from adc.h */
//TODO build these functions into init() (if the hal library weak links can be modified?)
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle);

/* ------------------------- End -------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_ADC_H */
