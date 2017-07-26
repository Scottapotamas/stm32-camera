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

/** Get the serial port baudrate to use on the auxiliary port */
PUBLIC uint32_t
config_ini_auxiliary_get_baudrate( AuxiliaryPort_t port,
                                   uint32_t        default_baudrate );

/* -------------------------------------------------------------------------- */

/** Set the serial port baudrate to use on the auxiliary port */
PUBLIC bool
config_ini_auxiliary_set_baudrate( AuxiliaryPort_t port,
                                   uint32_t        baudrate );

/* -------------------------------------------------------------------------- */
/* --- BATTERY CONFIGURATION ------------------------------------------------ */
/* -------------------------------------------------------------------------- */

/** Get the percentage of battery state of charge to go to hibernation */
PUBLIC uint8_t
config_ini_battery_get_critical( uint8_t default_critical_level );

/* -------------------------------------------------------------------------- */

/** Get the percentage of battery state of charge to start shutdown things */
PUBLIC uint8_t
config_ini_battery_get_low( uint8_t default_low_level );

/* -------------------------------------------------------------------------- */

/** Return the minutes from midnight to wakeup from hibernation */
PUBLIC uint16_t
config_ini_battery_get_wakeup_time( uint16_t default_wakeup_time );

/* -------------------------------------------------------------------------- */

/** Set the percentage of battery state of charge to go into hibernation */
PUBLIC bool
config_ini_battery_set_critical( uint8_t hibernate_level );

/* -------------------------------------------------------------------------- */

/** Set the percentage of battery state of charge to start shutdown things */
PUBLIC bool
config_ini_battery_set_low( uint8_t low_level );

/* -------------------------------------------------------------------------- */

/** Set the number of minutes from start of day to wakeup from hybernation */
PUBLIC bool
config_ini_battery_set_wakeup_time( uint16_t wakeup_time );

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
/* --- CONTACT CONFIGURATION ------------------------------------------------ */
/* -------------------------------------------------------------------------- */

PUBLIC void
config_ini_contact_get_line( uint8_t line,
                             char *  buffer,
                             uint8_t buffer_len,
                             const char * default_message );

/* -------------------------------------------------------------------------- */
/* --- FACTORY CONFIGURATION ------------------------------------------------ */
/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
config_ini_factory_get_enable( const uint16_t default_enable_mask );

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_factory_put_enable( const uint16_t enable_mask );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
config_ini_factory_get_serial_number( const uint32_t default_serial_number );

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_factory_put_serial_number( const uint32_t serial_number );

/* -------------------------------------------------------------------------- */
/* --- LOG CONFIGURATION ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
config_ini_log_get_level( uint8_t default_level );

/* -------------------------------------------------------------------------- */

PUBLIC bool
config_ini_log_put_level( uint8_t level );

/* -------------------------------------------------------------------------- */
/* --- LURE CONFIGURATION --------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/* Return true when lure playing is enabled */
PUBLIC bool
config_ini_lure_get_enable( bool default_enable );

PUBLIC bool
config_ini_lure_put_enable( bool enable );

PUBLIC void
config_ini_lure_get_track( char * buffer, uint16_t buffer_len, const char * default_track );

PUBLIC bool
config_ini_lure_put_track( const char * track );

/* -------------------------------------------------------------------------- */
/* --- SENSOR CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
config_ini_sensor_get_averaging_count( uint16_t default_averaging_count );

PUBLIC bool
config_ini_sensor_put_averaging_count( uint16_t averaging_count );

PUBLIC bool
config_ini_sensor_get_bottom_enable( bool default_enable );

PUBLIC bool
config_ini_sensor_put_bottom_enable( bool on );

PUBLIC uint16_t
config_ini_sensor_get_margin_min_cm( uint16_t default_min_margin );

PUBLIC bool
config_ini_sensor_put_margin_min_cm( uint16_t min_margin );

PUBLIC uint16_t
config_ini_sensor_get_margin_delta_cm( uint16_t default_delta_margin );

PUBLIC bool
config_ini_sensor_put_margin_delta_cm( uint16_t delta_margin );

PUBLIC uint16_t
config_ini_sensor_get_margin_max_cm( uint16_t default_max_margin );

PUBLIC bool
config_ini_sensor_put_margin_max_cm( uint16_t max_margin );

PUBLIC uint16_t
config_ini_sensor_get_range_max_cm( uint16_t default_max_range );

PUBLIC bool
config_ini_sensor_put_range_max_cm( uint16_t max_range );

PUBLIC uint16_t
config_ini_sensor_get_sleep_time_sec( uint16_t default_sleep_time );

PUBLIC bool
config_ini_sensor_put_sleep_time_sec( uint16_t sleep_time );

PUBLIC uint16_t
config_ini_sensor_get_sensor_hold_time_ms( uint16_t default_sensor_hold_time_ms );

PUBLIC bool
config_ini_sensor_put_sensor_hold_time_ms( uint16_t sensor_hold_time_ms );

PUBLIC uint16_t
config_ini_sensor_get_target_hold_time_ms( uint16_t default_target_hold_time_ms );

PUBLIC bool
config_ini_sensor_put_target_hold_time_ms( uint16_t target_hold_time_ms );

PUBLIC uint16_t
config_ini_sensor_get_target_linger_time_s( uint16_t default_target_linger_time_s );

PUBLIC bool
config_ini_sensor_put_target_linger_time_s( uint16_t target_linger_time_s );

PUBLIC uint16_t
config_ini_sensor_get_top_hold_time_ms( uint16_t default_top_hold_time_ms );

PUBLIC bool
config_ini_sensor_put_top_hold_time_ms( uint16_t top_hold_time_ms );

/* -------------------------------------------------------------------------- */
/* --- SYSTEM CONFIGURATION ------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
config_ini_system_get_volume_percent( uint8_t default_volume_percent );

PUBLIC bool
config_ini_system_put_volume( uint8_t volume_percent );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_INI_H */

