/**
 * @file      config_ini.c
 *
 * @brief     Configuration data in an INI file on USB memory.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "config_ini.h"
#include "minIni.h"
#include "log.h"

/* ----- Defines ------------------------------------------------------------ */

PRIVATE const char CONFIG_SECTION_AUXILIARY_A[]    	= "auxiliary A";
PRIVATE const char CONFIG_SECTION_AUXILIARY_B[]    	= "auxiliary B";
PRIVATE const char CONFIG_SECTION_AUXILIARY_C[]    	= "auxiliary C";
PRIVATE const char CONFIG_AUXILIARY_MODE[]         	= "mode";
PRIVATE const char CONFIG_AUXILIARY_MODE_NONE[]    	= "none";
PRIVATE const char CONFIG_AUXILIARY_MODE_DAC[] 		= "analog out";
PRIVATE const char CONFIG_AUXILIARY_MODE_PWM[] 		= "pwm out";
PRIVATE const char CONFIG_AUXILIARY_MODE_IO[] 		= "basic io";

PRIVATE const char CONFIG_SECTION_CAMERA[]         	= "camera";

PRIVATE const char CONFIG_SECTION_LOG[]            	= "log";

//PRIVATE const char CONFIG_SECTION_SYSTEM[]         = "system";

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC AuxiliaryMode_t
config_ini_auxiliary_get_mode( AuxiliaryPort_t port,
                               AuxiliaryMode_t default_mode )
{
    char            buffer[25];
    AuxiliaryMode_t mode = default_mode;
    const char * section = port
                           ? CONFIG_SECTION_AUXILIARY_A
                           : CONFIG_SECTION_AUXILIARY_B;

    //TODO Handle AuxC pin in config settings read

    ini_gets( section,
              CONFIG_AUXILIARY_MODE,
              "???",
              buffer,
              sizeof(buffer),
              APP_CONFIG_FILE_CONFIG_INI );

    if( strcasecmp( buffer, "???" ) ) /* Default when no setting */
    {
        mode = default_mode;
    }
    else if( strcasecmp( buffer, CONFIG_AUXILIARY_MODE_NONE ) )
    {
        mode = AUX_MODE_NONE;
    }
    else if( strcasecmp( buffer, CONFIG_AUXILIARY_MODE_DAC ) )
    {
        mode = AUX_MODE_DAC;
    }
    else if( strcasecmp( buffer, CONFIG_AUXILIARY_MODE_PWM ) )
    {
        mode = AUX_MODE_PWM;
    }
    else if( strcasecmp( buffer, CONFIG_AUXILIARY_MODE_IO ) )
    {
        mode = AUX_MODE_IO;
    }
    else /* Unknown / Invalid Setting */
    {
        mode = default_mode;
    }
    return mode;
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_auxiliary_set_mode(  AuxiliaryPort_t port,
                                AuxiliaryMode_t auxiliary_mode )
{
    int status = 0;
    const char * section = port
                           ? CONFIG_SECTION_AUXILIARY_A
                           : CONFIG_SECTION_AUXILIARY_B;

    //TODO Handle AuxC pin in config settings set

    switch( auxiliary_mode )
    {
        case AUX_MODE_NONE:
            status = ini_puts( section,
                               CONFIG_AUXILIARY_MODE,
                               CONFIG_AUXILIARY_MODE_NONE,
                               APP_CONFIG_FILE_CONFIG_INI );
            break;

        case AUX_MODE_DAC:
            status = ini_puts( section,
                               CONFIG_AUXILIARY_MODE,
                               CONFIG_AUXILIARY_MODE_DAC,
                               APP_CONFIG_FILE_CONFIG_INI );
            break;

        case AUX_MODE_PWM:
            status = ini_puts( section,
                               CONFIG_AUXILIARY_MODE,
                               CONFIG_AUXILIARY_MODE_PWM,
                               APP_CONFIG_FILE_CONFIG_INI );
            break;

        case AUX_MODE_IO:
            status = ini_puts( section,
                               CONFIG_AUXILIARY_MODE,
                               CONFIG_AUXILIARY_MODE_IO,
                               APP_CONFIG_FILE_CONFIG_INI );
            break;

    }
    return status > 0;
}

/* -------------------------------------------------------------------------- */
/* --- CAMERA CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
config_ini_camera_get_flash_duration_ms( uint16_t default_flash_duration_ms )
{
    return (uint16_t)ini_getl( CONFIG_SECTION_CAMERA,
                               "flash_time_ms",
                               default_flash_duration_ms,
                               APP_CONFIG_FILE_CONFIG_INI );
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_camera_put_flash_duration_ms( uint16_t flash_duration_ms )
{
    return ini_putl( CONFIG_SECTION_CAMERA,
                     "flash_time_ms",
                     flash_duration_ms,
                     APP_CONFIG_FILE_CONFIG_INI ) > 0;
}

/* -------------------------------------------------------------------------- */

PUBLIC int16_t
config_ini_camera_get_trigger_delay_ms( int16_t default_trigger_delay_ms )
{
    return (int16_t)ini_getl( CONFIG_SECTION_CAMERA,
                              "trigger_delay_ms",
                              default_trigger_delay_ms,
                              APP_CONFIG_FILE_CONFIG_INI );
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_camera_put_trigger_delay_ms( int16_t trigger_delay_ms )
{
    return ini_putl( CONFIG_SECTION_CAMERA,
                     "trigger_delay_ms",
                     trigger_delay_ms,
                     APP_CONFIG_FILE_CONFIG_INI ) > 0;
}

/* -------------------------------------------------------------------------- */
/* --- LOG CONFIGURATION ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
config_ini_log_get_level( uint8_t default_level )
{
    return (LOG_LEVEL)ini_getl( CONFIG_SECTION_LOG,
                                "level",
                                default_level,
                                APP_CONFIG_FILE_CONFIG_INI );
}

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_log_put_level( uint8_t level )
{
    return ini_putl( CONFIG_SECTION_LOG,
                     "level",
                     level,
                     APP_CONFIG_FILE_CONFIG_INI ) > 0;
}


/* ----- End ---------------------------------------------------------------- */
