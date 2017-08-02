/**
 * @file      hal_mco.c
 *
 * @brief     MCO Handling.
*/

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "hal_mco.h"
#include "hal_gpio.h"

/* ------------------------- Functions -------------------------------------- */

PUBLIC void
hal_mco_init( void )
{
    hal_gpio_init( _CAM_XCLK, MODE_OUT_PP, 0);

    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
    //TODO see how fast we can push the sensor without issue. HSI is 16Mhz
}

/* ----- End ---------------------------------------------------------------- */
