/**
 * @file      config.h
 *
 * @brief     Configuration data.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "log.h"
#include "auxiliary.h"
#include "hal_uart.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- CONFIGURATION INIT & LOAD -------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Clear the internal configuration data.
 */

PUBLIC void
config_init( void );

/* -------------------------------------------------------------------------- */

/** Init all config data with sensible defaults */

PUBLIC void
config_defaults( void );

/* -------------------------------------------------------------------------- */

/** (Re)Load the configuration data from USB memory. Ensure that the
 *  USB device is present and enabled.
 */
PUBLIC void
config_load( void );

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Get the mode that the auxiliary port is operating in */
PUBLIC AuxiliaryMode_t
config_auxiliary_mode( AuxiliaryPort_t port );

/* -------------------------------------------------------------------------- */

/** Set the mode that the auxiliary port is operating in */
PUBLIC void
config_auxiliary_set_mode( AuxiliaryPort_t port,
                           AuxiliaryMode_t auxiliary_mode );

/* -------------------------------------------------------------------------- */
/* --- TERMINAL CONFIGURATION ----------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Get the serial port baudrate to use */
PUBLIC uint32_t
config_terminal_baudrate( HalUartPort_t port );

/* -------------------------------------------------------------------------- */

/** Set the serial port baudrate to use on the auxiliary port */
PUBLIC void
config_terminal_set_baudrate( HalUartPort_t port,
                               uint32_t        baudrate );

/* -------------------------------------------------------------------------- */
/* --- CAMERA --------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Return the camera flash time in ms */

PUBLIC uint16_t
config_camera_flash_duration_ms( void );

/* -------------------------------------------------------------------------- */

/** Set the camera flash time in ms */

PUBLIC void
config_camera_set_flash_duration_ms( uint16_t flash_time_ms );

/* -------------------------------------------------------------------------- */

/** Return the camera trigger delay in ms */

PUBLIC int16_t
config_camera_trigger_delay_ms( void );

/* -------------------------------------------------------------------------- */

/** Set the camera trigger delay in ms */

PUBLIC void
config_camera_set_trigger_delay_ms( int16_t triger_delay_ms );

/* -------------------------------------------------------------------------- */
/* --- LOG CONFIGURATION ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Return the configured logging level */

PUBLIC LOG_LEVEL
config_log_level( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
config_log_set_level( LOG_LEVEL enable_bits );


/* -------------------------------------------------------------------------- */
/* --- SYSTEM CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */


/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_H */

