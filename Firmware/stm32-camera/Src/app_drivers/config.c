/**
 * @file      config.c
 *
 * @brief     Configuration data.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "config.h"
#include "config_ini.h"
#include "config_signal.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----- Defines ------------------------------------------------------------ */

/* Default Auxiliary Configuration A */
#define CONFIG_DEFAULT_AUXILIARY_A_MODE           AUX_MODE_NONE

/* Default Auxiliary Configuration B */
#define CONFIG_DEFAULT_AUXILIARY_B_MODE           AUX_MODE_NONE

/* Default Auxiliary Configuration C */
#define CONFIG_DEFAULT_AUXILIARY_C_MODE           AUX_MODE_NONE


/* Default camera configuration */
#define CONFIG_DEFAULT_CAMERA_FLASH_TIME_MS                 100 /* ms */
#define CONFIG_DEFAULT_CAMERA_TRIGGER_DELAY_MS              (0) /* ms */


/* Default factory configuration - nothing enabled */
#define CONFIG_DEFAULT_FACTORY_MASK                         (0) /* All Off */

/* Default Lure Configuration */
#define CONFIG_DEFAULT_LURE_ENABLE                         true /* enabled */

/* Default Log Level Configuration */
#define CONFIG_DEFAULT_LOG_LEVEL                  LOG_MASK_ALL  /* all levels incl. LOG_DEBUG */

/* ----- Types -------------------------------------------------------------- */

typedef struct ConfigAuxiliary__
{
    AuxiliaryMode_t     mode;
} ConfigAuxiliary_t;

typedef struct ConfigCamera__
{
    uint16_t            flash_time_ms;
    int16_t             trigger_delay_ms;
} ConfigCamera_t;

typedef struct ConfigLog__
{
    uint8_t             level;
} ConfigLog_t;


typedef struct ConfigSystem__
{
    uint8_t             volume;
} ConfigSystem_t;


typedef struct Config__
{
    bool                loaded;
    ConfigAuxiliary_t   auxiliary[3];
    ConfigCamera_t      camera;
    ConfigLog_t         log;
    ConfigSystem_t      system;
} Config_t;


/* ----- Variables ---------------------------------------------------------- */

PRIVATE Config_t    config;

/* -------------------------------------------------------------------------- */
/* --- CONFIGURATION INIT & LOAD -------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC void
config_init( void )
{
    memset( &config, 0, sizeof( config ) );
    config_defaults();
}

/* -------------------------------------------------------------------------- */

PUBLIC void
config_defaults( void )
{
    /* AUXILIARY */
    config.auxiliary[AUX_PORT_ANALOG].mode    = CONFIG_DEFAULT_AUXILIARY_A_MODE;
	config.auxiliary[AUX_PORT_EXP_0].mode     = CONFIG_DEFAULT_AUXILIARY_B_MODE;
	config.auxiliary[AUX_PORT_EXP_1].mode     = CONFIG_DEFAULT_AUXILIARY_B_MODE;

    /* CAMERA */

    config.camera.flash_time_ms = CONFIG_DEFAULT_CAMERA_FLASH_TIME_MS;
    config.camera.trigger_delay_ms = CONFIG_DEFAULT_CAMERA_TRIGGER_DELAY_MS;

    /* LOG */

    config.log.level = CONFIG_DEFAULT_LOG_LEVEL;

    /* SYSTEM */


}

/* -------------------------------------------------------------------------- */

PUBLIC void
config_load( void )
{
    /* AUXILIARY */

    config.auxiliary[ AUX_PORT_ANALOG ].mode =
       config_ini_auxiliary_get_mode( AUX_PORT_ANALOG,
                                      CONFIG_DEFAULT_AUXILIARY_A_MODE );

	config.auxiliary[ AUX_PORT_EXP_0 ].mode =
	   config_ini_auxiliary_get_mode( AUX_PORT_EXP_0,
									  CONFIG_DEFAULT_AUXILIARY_B_MODE );

	config.auxiliary[ AUX_PORT_EXP_1 ].mode =
	   config_ini_auxiliary_get_mode( AUX_PORT_EXP_1,
									  CONFIG_DEFAULT_AUXILIARY_C_MODE );

    /* CAMERA INFORMATION */

    config.camera.flash_time_ms =
            CLAMP( config_ini_camera_get_flash_duration_ms( CONFIG_DEFAULT_CAMERA_FLASH_TIME_MS ),
                   10,
                   1000 );

    config.camera.trigger_delay_ms =
            CLAMP( config_ini_camera_get_trigger_delay_ms( CONFIG_DEFAULT_CAMERA_TRIGGER_DELAY_MS ),
                   0,
                   1000 );

    /* LOG */

    config.log.level =
            CLAMP( config_ini_log_get_level( CONFIG_DEFAULT_LOG_LEVEL ),
                   0,
                   255 );

    /* SYSTEM */


}

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Get the mode that the auxiliary port is operating in */
PUBLIC AuxiliaryMode_t
config_auxiliary_mode( AuxiliaryPort_t port )
{
    return config.auxiliary[port].mode;
}

/* -------------------------------------------------------------------------- */

/** Set the mode that the auxiliary port is operating in */
PUBLIC void
config_auxiliary_set_mode( AuxiliaryPort_t port,
                           AuxiliaryMode_t auxiliary_mode )
{
    config.auxiliary[port].mode = auxiliary_mode;
    config_ini_auxiliary_set_mode( port, auxiliary_mode );
    config_signal_auxiliary_set_mode( port, auxiliary_mode );
}

/* -------------------------------------------------------------------------- */
/* --- TERMINAL ------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
PUBLIC uint32_t
config_terminal_baudrate( HalUartPort_t port )
{
	//TODO actually read baudrate from config file
	return (uint32_t)115200;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
config_terminal_set_baudrate( HalUartPort_t port,
        						uint32_t baudrate )
{
	//TODO actually set baudrate in config file
}

/* -------------------------------------------------------------------------- */
/* --- CAMERA --------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Return the camera trigger delay ins ms */

PUBLIC uint16_t
config_camera_flash_duration_ms( void )
{
    return config.camera.flash_time_ms;
}

/* -------------------------------------------------------------------------- */

/** Set the camera trigger delay in ms */

PUBLIC void
config_camera_set_flash_duration_ms( uint16_t flash_time_ms )
{
    config.camera.flash_time_ms = flash_time_ms;
    config_ini_camera_put_flash_duration_ms( config.camera.flash_time_ms );
}

/* -------------------------------------------------------------------------- */

/** Return the camera trigger delay ins ms */

PUBLIC int16_t
config_camera_trigger_delay_ms( void )
{
    return config.camera.trigger_delay_ms;
}

/* -------------------------------------------------------------------------- */

/** Set the camera trigger delay in ms */

PUBLIC void
config_camera_set_trigger_delay_ms( int16_t trigger_delay_ms )
{
    config.camera.trigger_delay_ms = trigger_delay_ms;
    config_ini_camera_put_trigger_delay_ms( config.camera.trigger_delay_ms );
}

/* -------------------------------------------------------------------------- */
/* --- LOG CONFIGURATION ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Return the configured logging level */

PUBLIC LOG_LEVEL
config_log_level( void )
{
    return config.log.level;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
config_log_set_level( LOG_LEVEL level )
{
    config.log.level = level;
    config_ini_log_put_level( level );
}


/* -------------------------------------------------------------------------- */
/* --- SYSTEM CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */




/* ----- End ---------------------------------------------------------------- */


