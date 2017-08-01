/**
 * @file      ov2640.c
 *
 * @brief     ov2640 Camera Driver
 *
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "log.h"

#include "ov2640.h"

#include "hal_camera.h"


//#include "hal_dcmi.h"
//#include "hal_dma.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Types ------------------------------------------------------------- */


/* ------------------------ Variables --------------------------------------- */

PRIVATE HalCameraSSCBData_t hal_gpio_sscb;
PRIVATE HalCameraSSCBData_t *me = &hal_gpio_sscb;

/* ------------------------ Declarations ------------------------------------ */
const ov2640SettingSingle resolutionSettings[] =
{
	  0xff, 0x00,	//TODO actually populate different resolutions, with each full map of settings
	  0x2c, 0xff,
};


const ov2640SettingSingle brightnessSettings[] =
{
		[ _BRIGHTNESS_UP_2 		] = { .first_val = 0x40  },
		[ _BRIGHTNESS_UP_1 		] = { .first_val = 0x30  },
		[ _BRIGHTNESS_CENTER 	] = { .first_val = 0x20  },
		[ _BRIGHTNESS_DOWN_1 	] = { .first_val = 0x10  },
		[ _BRIGHTNESS_DOWN_2 	] = { .first_val = 0x00  }
};

const ov2640SettingPair contrastSettings[] =
{
		[ _CONTRAST_UP_2 	] = { .first_val = 0x28, .second_val = 0x0C },
		[ _CONTRAST_UP_1 	] = { .first_val = 0x24, .second_val = 0x16 },
		[ _CONTRAST_CENTER 	] = { .first_val = 0x20, .second_val = 0x20 },
		[ _CONTRAST_DOWN_1 	] = { .first_val = 0x1C, .second_val = 0x2A },
		[ _CONTRAST_DOWN_2 	] = { .first_val = 0x18, .second_val = 0x34 }
};

const ov2640SettingPair colourFilterSettings[] =
{
		[ _EFFECT_ANTIQUE 	] = { .first_val = 0x40, .second_val = 0xA6 },
		[ _EFFECT_BLUE 		] = { .first_val = 0xA0, .second_val = 0x40 },
		[ _EFFECT_GREEN 	] = { .first_val = 0x40, .second_val = 0x40 },
		[ _EFFECT_RED 		] = { .first_val = 0x40, .second_val = 0xC0 }
};

const ov2640SettingSingle grayscaleFilterSettings[] =
{
		[ _EFFECT_BW 			] = { .first_val = 0x18  },
		[ _EFFECT_NEGATIVE 		] = { .first_val = 0x40  },
		[ _EFFECT_BW_NEGATIVE 	] = { .first_val = 0x58  },
		[ _EFFECT_NORMAL 		] = { .first_val = 0x00  }
};

/* ------------------------ Implementation ---------------------------------- */

/** Init the camera configuration comms */

PUBLIC void
ov2640_configure_SSCB( void )
{
    hal_gpio_i2c_bus_init( I2C_BUS_1, _I2C_SDA, _I2C_SCL );

    memset( &hal_gpio_sscb, 0, sizeof(hal_gpio_sscb) );

    me->bus = I2C_BUS_2;

    hal_i2c_master_init( me->bus, _I2C_SDA, _I2C_SCL );
    hal_i2c_master_clock_speed( me->bus, 100000 );

}

/* -------------------------------------------------------------------------- */

/** Init the camera driver */

PUBLIC void
ov2640_init( void )
{

	//TODO configure DCMI here
	//TODO configure MCO here
	//TODO configure DMA streams here
	//TODO configure peripheral clocks etc
	//TODO use hal_camera hardware to set starting pin state

}

/* -------------------------------------------------------------------------- */

/** Stop the camera driver */

PUBLIC void
ov2640_deinit( void )
{

}

/* -------------------------------------------------------------------------- */

/** Software reset of the sensor */

PUBLIC void
ov2640_software_reset( void )
{
	ov2640_sscb_register_write( OV2640_DSP_RA_DLMT, 0x01 );
	ov2640_sscb_register_write( OV2640_SENSOR_COM7, 0x80 );
}

/* -------------------------------------------------------------------------- */

/** Read the Omnivision ID */

PUBLIC void
ov2640_uuid_get( void )
{
	uint8_t Manufacturer_ID1 = 0;
	uint8_t Manufacturer_ID2 = 0;
	uint8_t PIDH = 0;
	uint8_t PIDL = 0;

	ov2640_sscb_register_write( OV2640_DSP_RA_DLMT, 0x01 );

	ov2640_sscb_register_read( OV2640_SENSOR_MIDH, &Manufacturer_ID1 );
	ov2640_sscb_register_read( OV2640_SENSOR_MIDL, &Manufacturer_ID2);
	ov2640_sscb_register_read( OV2640_SENSOR_PIDH, &PIDH );
	ov2640_sscb_register_read( OV2640_SENSOR_PIDL, &PIDL );

	//TODO return a value or struct with the sensor manf info
}

/* -------------------------------------------------------------------------- */

/** Configure resolution settings */

PUBLIC void
ov2640_configure_resolution( ov2640ModeResolution_t mode )
{
    const ov2640SettingPair setting = resolutionSettings[mode];

    //consider rebooting the camera to ensure we are in a known state?

    //TODO iterate through settings for the requested resolution

}

/* -------------------------------------------------------------------------- */

/** Configure brightness adjustment */

PUBLIC void
ov2640_configure_brightness( ov2640ModeBrightness_t mode )
{
    const ov2640SettingSingle setting = brightnessSettings[mode];

	ov2640_sscb_register_write( 0xFF, 0x00 );
	ov2640_sscb_register_write( 0x7C, 0x00 );
	ov2640_sscb_register_write( 0x7D, 0x04 );
	ov2640_sscb_register_write( 0x7C, 0x09 );
	ov2640_sscb_register_write( 0x7D, setting.first_val );
	ov2640_sscb_register_write( 0x7D, 0x00 );
}

/* -------------------------------------------------------------------------- */

/** Configure contrast adjustment */

PUBLIC void
ov2640_configure_contrast( ov2640ModeContrast_t mode )
{
    const ov2640SettingPair setting = contrastSettings[mode];

	ov2640_sscb_register_write( 0xFF, 0x00 );
	ov2640_sscb_register_write( 0x7C, 0x00 );
	ov2640_sscb_register_write( 0x7D, 0x04 );
	ov2640_sscb_register_write( 0x7C, 0x07 );
	ov2640_sscb_register_write( 0x7D, 0x20 );
	ov2640_sscb_register_write( 0x7D, setting.first_val);
	ov2640_sscb_register_write( 0x7D, setting.second_val );
	ov2640_sscb_register_write( 0x7D, 0x06 );
}

/* -------------------------------------------------------------------------- */

/** Select active colour post processing filter */

PUBLIC void
ov2640_configure_colour_filter( ov2640ModeColourEffect_t mode )
{
    const ov2640SettingPair setting = colourFilterSettings[mode];

	ov2640_sscb_register_write( 0xFF, 0x00 );
	ov2640_sscb_register_write( 0x7c, 0x00 );
	ov2640_sscb_register_write( 0x7d, 0x18 );
	ov2640_sscb_register_write( 0x7c, 0x05 );
	ov2640_sscb_register_write( 0x7D, setting.first_val);
	ov2640_sscb_register_write( 0x7D, setting.second_val );
}

/* -------------------------------------------------------------------------- */

/** Select active grayscale post processing filter */

PUBLIC void
ov2640_configure_grayscale_filter( ov2640ModeGreyscaleEffect_t mode )
{
    const ov2640SettingSingle setting = grayscaleFilterSettings[mode];

	ov2640_sscb_register_write( 0xFF, 0x00 );
	ov2640_sscb_register_write( 0x7C, 0x00 );
	ov2640_sscb_register_write( 0x7D, setting.first_val );
	ov2640_sscb_register_write( 0x7C, 0x05 );
	ov2640_sscb_register_write( 0x7D, 0x80 );
	ov2640_sscb_register_write( 0x7D, 0x80 );
}

/* -------------------------------------------------------------------------- */

PRIVATE HalI2cStatus_t
ov2640_sscb_register_read( const uint8_t i2c_register,
                           uint8_t       * value )
{
    uint8_t buffer[1];
    buffer[0] = i2c_register;

    hal_i2c_master_transmit( me->bus, OV2640_SSCB_READ_ADDRESS, buffer, 1 );
    hal_i2c_master_receive( me->bus, OV2640_SSCB_READ_ADDRESS, buffer,  1 );

    *value = buffer[0];

    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */

PRIVATE HalI2cStatus_t
ov2640_sscb_register_write( const uint8_t i2c_register,
                            const uint8_t value )
{
    uint8_t buffer[2];
    buffer[0] = i2c_register;
    buffer[1] = value;
    return hal_i2c_master_transmit( me->bus, OV2640_SSCB_WRITE_ADDRESS, buffer, 2 );
}


/* ----- End ---------------------------------------------------------------- */
