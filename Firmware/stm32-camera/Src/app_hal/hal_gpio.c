/**
 * @file      hal_gpio.c
 *
 * @brief     GPIO Pin Declarations. Should be the only central definition
 *            of GPIO output and input names and the physical mapping to I/O.
 *            Application code to use the NAME.port and NAME.pin values when
 *            using the HAL GPIO functions.
 *
 *            For example:
 *
 *                hal_gpio_write_pin( _STATUS_0, on );
 *
 *                hal_gpio_read_pin( _AUX_IN_0 );
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
*/

#include "hal_gpio.h"

#include "hal_gpio_types.h"
#include "hal_gpio_mcu.h"
#include "hal_delay.h"
#include "qassert.h"

//Note: removed i2c expander handling functionality. Otherwise leaving hardware map structures intact incase i2c IO is added later.

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/** For our own HAL GPIO layer, define enum labels that incorporate
 *  port and pin numbers combined in the one enum label.
 *  Port numbers are in the high byte and pin number are in the low byte
 */
const HalGpioDef_t HalGpioHardwareMap[] =
{
	/* --- BUTTONS --- */
	[ _BTN             ] = { .mode = MODE_INPUT_PU, .port = PORT_D, .pin = PIN_3 },

    /* --- STATUS Indication --- */
    [ _STATUS_0        ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_0, .initial = 0 },
    [ _STATUS_1        ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_1, .initial = 0 },

    /* --- Aux IO --- */
    [ _AUX_GPIO_2      ] = { .mode = MODE_INPUT, .port = PORT_A, .pin = PIN_5 },	//High performance DAC/Timer/Etc label A
    [ _AUX_GPIO_0      ] = { .mode = MODE_INPUT, .port = PORT_D, .pin = PIN_1 },	//Label E0
    [ _AUX_GPIO_1      ] = { .mode = MODE_INPUT, .port = PORT_D, .pin = PIN_0 },	//Label E1

	[ _SD_DETECT       ] = { .mode = MODE_INPUT_PU, .port = PORT_E, .pin = PIN_15 },

	[ _AMBIENT_LIGHT   ] = { .mode = MODE_ANALOG, .port = PORT_C, .pin = PIN_0 },
    [ _REBOOT_LATCH    ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_8, .initial = 0 },

	/* --- I2C Sensor Control --- */
    [ _I2C_SDA      ] = { .mode = MODE_OUT_OD, .port = PORT_B, .pin = PIN_11, .initial = 1 },
    [ _I2C_SCL      ] = { .mode = MODE_OUT_OD, .port = PORT_B, .pin = PIN_10, .initial = 1 },

    /* --- Camera Control --- */
    [ _PWR_EN     	] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_15, .initial = 0 },
    [ _CAM_STROBE  	] = { .mode = MODE_INPUT,  .port = PORT_B, .pin = PIN_14, },
    [ _CAM_EXPST  	] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_15, .initial = 0 },
    [ _CAM_FREX  	] = { .mode = MODE_OUT_PP, .port = PORT_D, .pin = PIN_8,  .initial = 0 },
    [ _CAM_XCLK  	] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_8,  .initial = 0 },
    [ _CAM_RESET  	] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_11, .initial = 0 },
    [ _CAM_PWDN  	] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_12, .initial = 0 },

    [ _CAM_HSYNC     ] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_4, .initial = 0 },
    [ _CAM_PIXCK     ] = { .mode = MODE_OUT_PP, .port = PORT_A, .pin = PIN_6, .initial = 0 },
    [ _CAM_VSYNC     ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_7, .initial = 0 },
    [ _CAM_D0        ] = { .mode = MODE_OUT_PP, .port = PORT_C, .pin = PIN_6, .initial = 0 },
    [ _CAM_D1        ] = { .mode = MODE_OUT_PP, .port = PORT_C, .pin = PIN_7, .initial = 0 },
    [ _CAM_D2        ] = { .mode = MODE_OUT_PP, .port = PORT_E, .pin = PIN_0, .initial = 0 },
    [ _CAM_D3        ] = { .mode = MODE_OUT_PP, .port = PORT_E, .pin = PIN_1, .initial = 0 },
    [ _CAM_D4        ] = { .mode = MODE_OUT_PP, .port = PORT_E, .pin = PIN_4, .initial = 0 },
    [ _CAM_D5        ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_6, .initial = 0 },
    [ _CAM_D6        ] = { .mode = MODE_OUT_PP, .port = PORT_E, .pin = PIN_5, .initial = 0 },
    [ _CAM_D7        ] = { .mode = MODE_OUT_PP, .port = PORT_B, .pin = PIN_9, .initial = 0 },

};

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_gpio_configure_mcu_defaults( void )
{
    for( HalGpioPortPin_t portpin = 0;
                          portpin < _NUMBER_OF_GPIO_PORT_PINS;
                          portpin++ )
    {
        const HalGpioDef_t m = HalGpioHardwareMap[portpin];

        hal_gpio_mcu_init( m.port, m.pin, m.mode, m.initial );
    }
}

/* -------------------------------------------------------------------------- */

/** @brief Configure mode of pin */

PUBLIC void
hal_gpio_init( HalGpioPortPin_t gpio_port_pin_nr,
               HalGpioMode_t    mode,
               bool             initial_state )
{
    const HalGpioDef_t m = HalGpioHardwareMap[gpio_port_pin_nr];

    hal_gpio_mcu_init( m.port, m.pin, mode, initial_state );
}

PUBLIC void
hal_gpio_deinit( HalGpioPortPin_t gpio_port_pin_nr )
{
    const HalGpioDef_t m = HalGpioHardwareMap[gpio_port_pin_nr];

    hal_gpio_mcu_deinit( m.port, m.pin );
}

/* -------------------------------------------------------------------------- */

/** @brief read the I/O pin. Return true when pin is high */

PUBLIC bool
hal_gpio_read_pin( HalGpioPortPin_t gpio_port_pin_nr )
{
    const HalGpioDef_t m = HalGpioHardwareMap[gpio_port_pin_nr];

    return hal_gpio_mcu_read_pin( m.port, m.pin );
}

/* -------------------------------------------------------------------------- */

/** @brief Write the I/O pin. Pin is set high when 'on' == true */

PUBLIC void
hal_gpio_write_pin( HalGpioPortPin_t gpio_port_pin_nr, bool on )
{
    const HalGpioDef_t m = HalGpioHardwareMap[gpio_port_pin_nr];

    hal_gpio_mcu_write_pin( m.port, m.pin, on );
}

/* -------------------------------------------------------------------------- */

/** @brief Toggle the I/O pin */

PUBLIC void
hal_gpio_toggle_pin( HalGpioPortPin_t gpio_port_pin_nr )
{
    const HalGpioDef_t m = HalGpioHardwareMap[gpio_port_pin_nr];

    hal_gpio_mcu_toggle_pin( m.port, m.pin );
}

/* ----- End ---------------------------------------------------------------- */
