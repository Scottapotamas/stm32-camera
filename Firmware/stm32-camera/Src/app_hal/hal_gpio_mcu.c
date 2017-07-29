/**
 * @file      hal_gpio_mcu.c
 *
 * @brief     Internal MCU GPIO pin handling.
 *
 *            For example:
 *
 *                hal_gpio_mcu_init( PORT_A, PIN_12, MODE_INPUT );
 *                hal_gpio_mcu_read_pin( PORT_A, PIN_12 );
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- Module include ----------------------------------------------------- */

#include "hal_gpio_mcu.h"

/* ----- Local Includes ----------------------------------------------------- */

#include "qassert.h"
#include "stm32f4xx_hal.h"

/* ----- Private Function Declarations -------------------------------------- */

/** Map the port nr to a STM32 GPIO_TypeDef */

PRIVATE GPIO_TypeDef *
hal_gpio_mcu_port( HalGpioPortNr_t port_nr );

/** Enable peripheral clock */

PRIVATE void
hal_gpio_mcu_rcc_clock_enable( const HalGpioPortNr_t port_nr );

/** Init as input */

PRIVATE void
hal_gpio_mcu_init_as_input( HalGpioPortNr_t port_nr,
                            HalGpioPinNr_t  pin_nr );

/** Init as input with pullup */

PRIVATE void
hal_gpio_mcu_init_as_input_with_pullup( HalGpioPortNr_t port_nr,
                                        HalGpioPinNr_t  pin_nr );

/** Init as analog */

PRIVATE void
hal_gpio_mcu_init_as_analog( HalGpioPortNr_t port_nr,
        					 HalGpioPinNr_t  pin_nr );

/** Init as open drain output */

PRIVATE void
hal_gpio_mcu_init_as_output_od( HalGpioPortNr_t port_nr,
                                HalGpioPinNr_t  pin_nr,
                                bool            initial_state );

/** Init as push pull output */

PRIVATE void
hal_gpio_mcu_init_as_output_pp( HalGpioPortNr_t port_nr,
                                HalGpioPinNr_t  pin_nr,
                                bool            initial_state );


/* ----- Private Data ------------------------------------------------------- */

DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Public Function Implementations ------------------------------------ */

PUBLIC void
hal_gpio_mcu_init( const HalGpioPortNr_t port_nr,
                   const HalGpioPinNr_t  pin_nr,
                   const HalGpioMode_t   mode,
                   const bool            initial_state )
{
    ENSURE( port_nr <= PORT_H );
    ENSURE( pin_nr <= PIN_15 );

    hal_gpio_mcu_rcc_clock_enable( port_nr );

    switch( mode )
    {
        case MODE_INPUT:
            hal_gpio_mcu_init_as_input( port_nr, pin_nr );
            break;

        case MODE_INPUT_PU:
            hal_gpio_mcu_init_as_input_with_pullup( port_nr, pin_nr );
            break;

        case MODE_ANALOG:
            hal_gpio_mcu_init_as_analog( port_nr, pin_nr );
            break;

        case MODE_OUT_OD:
            hal_gpio_mcu_init_as_output_od( port_nr, pin_nr, initial_state );
            break;

        case MODE_OUT_PP:
            hal_gpio_mcu_init_as_output_pp( port_nr, pin_nr, initial_state );
            break;
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_gpio_mcu_deinit( const HalGpioPortNr_t port_nr,
                     const HalGpioPinNr_t  pin_nr )
{
    ENSURE( port_nr <= PORT_H );
    ENSURE( pin_nr <= PIN_15 );

	HAL_GPIO_DeInit( hal_gpio_mcu_port(port_nr),
					 HAL_GPIO_PIN_MASK(pin_nr) );
}

/* -------------------------------------------------------------------------- */

/** @brief read the I/O pin. Return true when pin is high */

PUBLIC bool
hal_gpio_mcu_read_pin( const HalGpioPortNr_t port_nr,
                       const HalGpioPinNr_t  pin_nr )
{
    return HAL_GPIO_ReadPin( hal_gpio_mcu_port( port_nr ),
                             HAL_GPIO_PIN_MASK( pin_nr ) ) == GPIO_PIN_SET;
}

/* -------------------------------------------------------------------------- */

/** @brief Write the I/O pin. Pin is set high when 'on' == true */

PUBLIC void
hal_gpio_mcu_write_pin( const HalGpioPortNr_t port_nr,
                        const HalGpioPinNr_t  pin_nr,
                        const bool            on )
{
    HAL_GPIO_WritePin( hal_gpio_mcu_port( port_nr ),
                       HAL_GPIO_PIN_MASK( pin_nr ),
                       on ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/* -------------------------------------------------------------------------- */

/** @brief Toggle the I/O pin */

PUBLIC void
hal_gpio_mcu_toggle_pin( const HalGpioPortNr_t port_nr,
                         const HalGpioPinNr_t  pin_nr )
{
    HAL_GPIO_TogglePin( hal_gpio_mcu_port( port_nr ),
                        HAL_GPIO_PIN_MASK( pin_nr ) );
}

/* ----- Private Function Implementations ----------------------------------- */

/** Map the port nr to a STM32 GPIO_TypeDef */

PRIVATE GPIO_TypeDef *
hal_gpio_mcu_port( HalGpioPortNr_t port_nr )
{
    GPIO_TypeDef * port = 0;

    switch( port_nr )
    {
        case PORT_A: port = GPIOA; break;
        case PORT_B: port = GPIOB; break;
        case PORT_C: port = GPIOC; break;
        case PORT_D: port = GPIOD; break;
        case PORT_E: port = GPIOE; break;
        case PORT_F: port = GPIOF; break;
        case PORT_G: port = GPIOG; break;
        case PORT_H: port = GPIOH; break;
        default:     ASSERT( false );
    }
    return port;
}

/* -------------------------------------------------------------------------- */

PRIVATE void
hal_gpio_mcu_rcc_clock_enable( const HalGpioPortNr_t port_nr )
{
    switch( port_nr )
    {
        case PORT_A: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
        case PORT_B: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
        case PORT_C: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
        case PORT_D: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
        case PORT_E: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
        case PORT_F: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
        case PORT_G: __HAL_RCC_GPIOG_CLK_ENABLE(); break;
        case PORT_H: __HAL_RCC_GPIOH_CLK_ENABLE(); break;
        default:                                   break;
    }
}

/* -------------------------------------------------------------------------- */

/** @brief Configure Input pin without pull up */

PRIVATE void
hal_gpio_mcu_init_as_input( HalGpioPortNr_t port_nr,
                            HalGpioPinNr_t  pin_nr )
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin  = HAL_GPIO_PIN_MASK( pin_nr );
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init( hal_gpio_mcu_port( port_nr ),
                   &GPIO_InitStruct );
}

/* -------------------------------------------------------------------------- */

/** @brief Configure as Input pin with pullups */

PRIVATE void
hal_gpio_mcu_init_as_input_with_pullup( HalGpioPortNr_t port_nr,
                                        HalGpioPinNr_t  pin_nr )
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin  = HAL_GPIO_PIN_MASK( pin_nr );
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init( hal_gpio_mcu_port( port_nr ),
                   &GPIO_InitStruct );
}

/* -------------------------------------------------------------------------- */

/** @brief Configure as analog pin */

PRIVATE void
hal_gpio_mcu_init_as_analog( HalGpioPortNr_t port_nr,
                            HalGpioPinNr_t  pin_nr )
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin  = HAL_GPIO_PIN_MASK( pin_nr );
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init( hal_gpio_mcu_port( port_nr ),
                   &GPIO_InitStruct );
}

/* -------------------------------------------------------------------------- */

/** @brief Configure as output */

PRIVATE void
hal_gpio_mcu_init_as_output_od( HalGpioPortNr_t port_nr,
                                HalGpioPinNr_t  pin_nr,
                                bool            initial_state )
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin   = HAL_GPIO_PIN_MASK( pin_nr );
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( hal_gpio_mcu_port( port_nr ),
                   &GPIO_InitStruct);

    hal_gpio_mcu_write_pin( port_nr, pin_nr, initial_state );
}

/* -------------------------------------------------------------------------- */

/** @brief Configure as output */

PRIVATE void
hal_gpio_mcu_init_as_output_pp( HalGpioPortNr_t port_nr,
                                HalGpioPinNr_t  pin_nr,
                                bool            initial_state )
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin   = HAL_GPIO_PIN_MASK( pin_nr );
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( hal_gpio_mcu_port( port_nr ),
                   &GPIO_InitStruct);

    hal_gpio_mcu_write_pin( port_nr, pin_nr, initial_state );
}


/* ----- End ---------------------------------------------------------------- */


