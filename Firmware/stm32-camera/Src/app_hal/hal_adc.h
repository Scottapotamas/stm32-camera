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

/* ----- Types ------------------------------------------------------------- */

typedef enum
{
    HAL_ADC_INPUT_VBACKUPBAT,   /* ADC1 - RANK 1 */
    HAL_ADC_INPUT_VREFINT,      /* ADC1 - RANK 2 */
    HAL_ADC_INPUT_TEMPERATURE,  /* ADC1 - RANK 3 */
    HAL_ADC_INPUT_PWR_I5,       /* ADC1 - RANK 4 */
    HAL_ADC_INPUT_PWR_I3V3,     /* ADC1 - RANK 5 */
    HAL_ADC_INPUT_M1_CURRENT,   /* ADC3 - RANK 1 */
    HAL_ADC_INPUT_M2_CURRENT,   /* ADC3 - RANK 2 */
    HAL_ADC_INPUT_PWR_VBAT,     /* ADC3 - RANK 3 */
    HAL_ADC_INPUT_SPARE,        /* ADC3 - RANK 4 */
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

/* ------------------------- End -------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_ADC_H */
