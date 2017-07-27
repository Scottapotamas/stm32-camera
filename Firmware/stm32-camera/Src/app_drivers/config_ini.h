/**
 * @file      config_ini.h
 *
 * @brief     Configuration data in an INI file on USB memory.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef CONFIG_INI_H
#define CONFIG_INI_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "auxiliary.h"
#include "hal_uart.h"
/* ----- Types ------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Get the mode that the auxiliary port is operating in */
PUBLIC AuxiliaryMode_t
config_ini_auxiliary_get_mode( AuxiliaryPort_t port,
                               AuxiliaryMode_t default_auxiliary_mode );

/* -------------------------------------------------------------------------- */

/** Set the mode that the auxiliary port is operating in */
PUBLIC bool
config_ini_auxiliary_set_mode( AuxiliaryPort_t port,
                               AuxiliaryMode_t auxiliary_mode );

/* -------------------------------------------------------------------------- */
/* --- SERIAL CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Get the serial port baudrate to use */
PUBLIC uint32_t
config_ini_terminal_get_baudrate( HalUartPort_t port,
                                   uint32_t        default_baudrate );

/* -------------------------------------------------------------------------- */

/** Set the serial port baudrate to use */
PUBLIC bool
config_ini_terminal_set_baudrate( HalUartPort_t port,
                                   uint32_t        baudrate );

/* -------------------------------------------------------------------------- */
/* --- CAMERA CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/** Time in milliseconds for the flash to be on. */

PUBLIC uint16_t
config_ini_camera_get_flash_duration_ms( uint16_t default_flash_duration_ms );

PUBLIC bool
config_ini_camera_put_flash_duration_ms( uint16_t flash_duration_ms );

/** Extra delay time in milliseconds before flash is triggered. */

PUBLIC int16_t
config_ini_camera_get_trigger_delay_ms( int16_t default_trigger_delay_ms );

PUBLIC bool
config_ini_camera_put_trigger_delay_ms( int16_t trigger_delay_ms );

/* -------------------------------------------------------------------------- */
/* --- LOG CONFIGURATION ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
config_ini_log_get_level( uint8_t default_level );

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_log_put_level( uint8_t level );




/* -------------------------------------------------------------------------- */
/* --- SYSTEM CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */



/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_INI_H */

