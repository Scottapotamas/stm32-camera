/**
 * @file      board_sensor.h
 *
 * @brief     Handle access to the PCB mounted sensors
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef BOARD_SENSOR_H
#define BOARD_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Public Functions --------------------------------------------------- */

/* Init the hardware for the board sensors */

PUBLIC void
board_sensor_init( void );

/* -------------------------------------------------------------------------- */

/** Start/Enable board sensors */

PUBLIC void
board_sensor_enable( void );

/* -------------------------------------------------------------------------- */

/** Stop/Disable board sensors */

PUBLIC void
board_sensor_disable( void );

/* -------------------------------------------------------------------------- */

/** Return reference voltage */

PUBLIC float
board_sensor_voltage_reference( void );

/* -------------------------------------------------------------------------- */

/** Return temperature */

PUBLIC float
board_sensor_temperature_C( void );

/* -------------------------------------------------------------------------- */

/** Return light value from phototransistor */

PUBLIC float
board_sensor_light( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* BOARD_SENSOR_H */
