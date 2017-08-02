/**
 * @file      OV2640.h
 *
 * @brief     VC0706 Camera Driver
 *
*/

#ifndef OV2640_H
#define OV2640_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_i2c.h"
#include "hal_i2c_master.h"

/* ----- Defines ------------------------------------------------------------ */

#define OV2640_SSCB_WRITE_ADDRESS    0x60
#define OV2640_SSCB_READ_ADDRESS     0x61

/* Command codes */

/* OV2640 Registers for DSP bank (0xFF = 0x00) */
#define OV2640_DSP_R_BYPASS     0x05
#define OV2640_DSP_Qs           0x44
#define OV2640_DSP_CTRL         0x50
#define OV2640_DSP_HSIZE1       0x51
#define OV2640_DSP_VSIZE1       0x52
#define OV2640_DSP_XOFFL        0x53
#define OV2640_DSP_YOFFL        0x54
#define OV2640_DSP_VHYX         0x55
#define OV2640_DSP_DPRP         0x56
#define OV2640_DSP_TEST         0x57
#define OV2640_DSP_ZMOW         0x5A
#define OV2640_DSP_ZMOH         0x5B
#define OV2640_DSP_ZMHH         0x5C
#define OV2640_DSP_BPADDR       0x7C
#define OV2640_DSP_BPDATA       0x7D
#define OV2640_DSP_CTRL2        0x86
#define OV2640_DSP_CTRL3        0x87
#define OV2640_DSP_SIZEL        0x8C
#define OV2640_DSP_HSIZE2       0xC0
#define OV2640_DSP_VSIZE2       0xC1
#define OV2640_DSP_CTRL0        0xC2
#define OV2640_DSP_CTRL1        0xC3
#define OV2640_DSP_R_DVP_SP     0xD3
#define OV2640_DSP_IMAGE_MODE   0xDA
#define OV2640_DSP_RESET        0xE0
#define OV2640_DSP_MS_SP        0xF0
#define OV2640_DSP_SS_ID        0x7F
#define OV2640_DSP_SS_CTRL      0xF8
#define OV2640_DSP_MC_BIST      0xF9
#define OV2640_DSP_MC_AL        0xFA
#define OV2640_DSP_MC_AH        0xFB
#define OV2640_DSP_MC_D         0xFC
#define OV2640_DSP_P_STATUS     0xFE
#define OV2640_DSP_RA_DLMT      0xFF

/* OV2640 Registers for sensor bank (0xFF = 0x01) */
#define OV2640_SENSOR_GAIN       0x00
#define OV2640_SENSOR_COM1       0x03
#define OV2640_SENSOR_REG04      0x04
#define OV2640_SENSOR_REG08      0x08
#define OV2640_SENSOR_COM2       0x09
#define OV2640_SENSOR_PIDH       0x0A
#define OV2640_SENSOR_PIDL       0x0B
#define OV2640_SENSOR_COM3       0x0C
#define OV2640_SENSOR_COM4       0x0D
#define OV2640_SENSOR_AEC        0x10
#define OV2640_SENSOR_CLKRC      0x11
#define OV2640_SENSOR_COM7       0x12
#define OV2640_SENSOR_COM8       0x13
#define OV2640_SENSOR_COM9       0x14
#define OV2640_SENSOR_COM10      0x15
#define OV2640_SENSOR_HREFST     0x17
#define OV2640_SENSOR_HREFEND    0x18
#define OV2640_SENSOR_VSTART     0x19
#define OV2640_SENSOR_VEND       0x1A
#define OV2640_SENSOR_MIDH       0x1C
#define OV2640_SENSOR_MIDL       0x1D
#define OV2640_SENSOR_AEW        0x24
#define OV2640_SENSOR_AEB        0x25
#define OV2640_SENSOR_W          0x26
#define OV2640_SENSOR_REG2A      0x2A
#define OV2640_SENSOR_FRARL      0x2B
#define OV2640_SENSOR_ADDVSL     0x2D
#define OV2640_SENSOR_ADDVHS     0x2E
#define OV2640_SENSOR_YAVG       0x2F
#define OV2640_SENSOR_REG32      0x32
#define OV2640_SENSOR_ARCOM2     0x34
#define OV2640_SENSOR_REG45      0x45
#define OV2640_SENSOR_FLL        0x46
#define OV2640_SENSOR_FLH        0x47
#define OV2640_SENSOR_COM19      0x48
#define OV2640_SENSOR_ZOOMS      0x49
#define OV2640_SENSOR_COM22      0x4B
#define OV2640_SENSOR_COM25      0x4E
#define OV2640_SENSOR_BD50       0x4F
#define OV2640_SENSOR_BD60       0x50
#define OV2640_SENSOR_REG5D      0x5D
#define OV2640_SENSOR_REG5E      0x5E
#define OV2640_SENSOR_REG5F      0x5F
#define OV2640_SENSOR_REG60      0x60
#define OV2640_SENSOR_HISTO_LOW  0x61
#define OV2640_SENSOR_HISTO_HIGH 0x62


/* ----- Types ------------------------------------------------------------- */

typedef struct
{
    uint8_t		bus;
} HalCameraSSCBData_t;

//TODO refactor camera settings structures and defines
typedef struct
{
    uint8_t		first_val;
} ov2640SettingSingle;

typedef struct
{
    uint8_t		first_val;
    uint8_t		second_val;
} ov2640SettingPair;

typedef enum
{
    _RESOLUTION_QQVGA,	// 160x120
	_RESOLUTION_QVGA,	//320x240
	//TODO add remaining resolutions to table
} ov2640ModeResolution_t;

typedef enum
{
    _BRIGHTNESS_UP_2,
    _BRIGHTNESS_UP_1,
    _BRIGHTNESS_CENTER,
    _BRIGHTNESS_DOWN_1,
    _BRIGHTNESS_DOWN_2
} ov2640ModeBrightness_t;

typedef enum
{
	_CONTRAST_UP_2,
	_CONTRAST_UP_1,
	_CONTRAST_CENTER,
	_CONTRAST_DOWN_1,
	_CONTRAST_DOWN_2
} ov2640ModeContrast_t;

typedef enum
{
	_EFFECT_ANTIQUE,
	_EFFECT_BLUE,
	_EFFECT_GREEN,
	_EFFECT_RED
} ov2640ModeColourEffect_t;

typedef enum
{
	_EFFECT_BW,
	_EFFECT_NEGATIVE,
	_EFFECT_BW_NEGATIVE,
	_EFFECT_NORMAL
} ov2640ModeGreyscaleEffect_t;



/* -------------------------------------------------------------------------- */

/** Init the camera driver */

PUBLIC void
ov2640_init( void );

/* -------------------------------------------------------------------------- */

/** Stop the camera driver */

PUBLIC void
ov2640_deinit( void );

/* -------------------------------------------------------------------------- */

/** Software reset of the sensor */

PUBLIC void
ov2640_software_reset( void );

/* -------------------------------------------------------------------------- */

/** Read the Omnivision ID */

PUBLIC void
ov2640_uuid_get( void );

/* -------------------------------------------------------------------------- */

/** Configure resolution settings */

PUBLIC void
ov2640_configure_resolution( ov2640ModeResolution_t mode );

/* -------------------------------------------------------------------------- */

/** Configure brightness adjustment */

PUBLIC void
ov2640_configure_brightness( ov2640ModeBrightness_t mode );

/* -------------------------------------------------------------------------- */

/** Configure contrast adjustment */

PUBLIC void
ov2640_configure_contrast( ov2640ModeContrast_t mode );

/* -------------------------------------------------------------------------- */

/** Select active colour post processing filter */

PUBLIC void
ov2640_configure_colour_filter( ov2640ModeColourEffect_t mode );

/* -------------------------------------------------------------------------- */

/** Select active grayscale post processing filter */

PUBLIC void
ov2640_configure_grayscale_filter( ov2640ModeGreyscaleEffect_t mode );

/* -------------------------------------------------------------------------- */

/** SSCB (*cough* i2c *cough*) bit-banged interface for configuration get/set */

PRIVATE void
ov2640_sscb_init( void );

PRIVATE HalI2cStatus_t
ov2640_sscb_register_write( const uint8_t i2c_register,
                            const uint8_t value );

PRIVATE HalI2cStatus_t
ov2640_sscb_register_read( const uint8_t i2c_register,
                           uint8_t       * value );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* OV2640_H */
