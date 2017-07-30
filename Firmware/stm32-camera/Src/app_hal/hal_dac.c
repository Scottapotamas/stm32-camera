/**
 * @file      hal_flash.c
 *
 * @brief     Low level interface to the camera flash.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_dac.h"
#include "stm32f4xx_hal.h"
#include "hal_gpio.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Private Functions -------------------------------------------------- */

PRIVATE uint32_t
hal_dacp_setting( const float voltage );

PRIVATE void
hal_dacp_init( void  );

PRIVATE void
hal_dacp_deinit( void  );

/* ----- Variables ---------------------------------------------------------- */

PRIVATE float               hal_dac_voltage = 0.0;
PRIVATE DAC_HandleTypeDef   hdac;

/* -------------------------------------------------------------------------- */
/* --- FLASH INTERFACE                                                    --- */
/* -------------------------------------------------------------------------- */

/* Flash initialisation */
PUBLIC void
hal_dac_init( void )
{
    hal_dac( false );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_dac( bool on )
{
    if( on )
    {
        hal_dacp_init();

        HAL_DAC_Start( &hdac, DAC_CHANNEL_2 );

        HAL_DAC_SetValue( &hdac,
                          DAC_CHANNEL_2,
                          DAC_ALIGN_12B_R,
                          hal_dacp_setting( hal_dac_voltage ) );
    }
    else
    {
        /* Reset DAC level to 0 to ensure FLASH is off */
        HAL_DAC_SetValue( &hdac,
                          DAC_CHANNEL_2,
                          DAC_ALIGN_12B_R,
                          0 );

        HAL_DAC_Stop( &hdac, DAC_CHANNEL_2 );

        hal_dacp_deinit();
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_set_dac_voltage( const float voltage )
{
	hal_dac_voltage = CLAMP( voltage, 0.0f, 3.3f );
}

/* -------------------------------------------------------------------------- */

PRIVATE uint32_t
hal_dacp_setting( const float voltage )
{
    uint32_t setting = (voltage / 3.3f ) * 4096;
    return setting;
}

/* -------------------------------------------------------------------------- */

PRIVATE void
hal_dacp_init( void  )
{
    hdac.Instance = DAC;
    HAL_DAC_Init( &hdac );     /* Calls HAL_DAC_MspInit */

    /* DAC channel OUT2 config */
    DAC_ChannelConfTypeDef sConfig;
    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
    HAL_DAC_ConfigChannel( &hdac, &sConfig, DAC_CHANNEL_2 );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
HAL_DAC_MspInit( DAC_HandleTypeDef* dacHandle )
{
    if( dacHandle->Instance == DAC )
    {
        __HAL_RCC_DAC_CLK_ENABLE();
        hal_gpio_init(_AUX_GPIO_2, MODE_ANALOG, 0);
    }
}

/* -------------------------------------------------------------------------- */

PRIVATE void
hal_dacp_deinit( void  )
{
    hdac.Instance = DAC;
    HAL_DAC_DeInit( &hdac ); /* Calls HAL_DAC_MspDeInit */
}

/* -------------------------------------------------------------------------- */

PUBLIC void
HAL_DAC_MspDeInit( DAC_HandleTypeDef* dacHandle )
{
    if( dacHandle->Instance == DAC )
    {
        __HAL_RCC_DAC_CLK_DISABLE();

        /* Switch pin back to output and force low */
        hal_gpio_init(_AUX_GPIO_2, MODE_OUT_PP, 0);
    }
}

/* ----- End ---------------------------------------------------------------- */
