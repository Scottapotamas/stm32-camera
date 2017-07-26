/**
 * @file      hal_i2c_master_sw.h
 *
 * @brief     Abstraction interface for I2C interface on STM.
 *            Pure software based I2C operation for read and write operations
 *            using a timer tick or software loop based controlled state
 *            machine.
 *
 *            Requires just access to any I/O lines and a optionally a
 *            timer tick to operate.
 *
 *            Designed to be operationally similar to the STM hardware
 *            variant.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_I2C_MASTER_SW_H
#define HAL_I2C_MASTER_SW_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_gpio.h"
#include "hal_i2c.h"

/* ----- Defines ------------------------------------------------------------ */

//#define HAL_I2C_MASTER_SW_USE_TICKS

/* ----- Types -------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- I2C Interface Functions ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_init( HalI2cBusId_t          bus_id,
                        const HalGpioPortPin_t sda,
                        const HalGpioPortPin_t scl );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_i2c_master_sw_clock_speed( HalI2cBusId_t bus_id,  uint32_t bus_speed );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_reset( HalI2cBusId_t bus_id );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_transmit( HalI2cBusId_t id,
                            uint8_t       address,
                            uint8_t     * buffer,
                            uint8_t       len );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_receive( HalI2cBusId_t id,
                           uint8_t       address,
                           uint8_t     * buffer,
                           uint8_t       len );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_sw_abort( HalI2cBusId_t id,
                         uint8_t       address );

/* -------------------------------------------------------------------------- */

/** Return state of I2C device / bus transfer */

PUBLIC HalI2cState_t
hal_i2c_master_sw_get_state( HalI2cBusId_t id );

/* -------------------------------------------------------------------------- */

/** Return error status of last I2C transfer */

PUBLIC HalI2cError_t
hal_i2c_master_sw_get_error( HalI2cBusId_t id );

/* -------------------------------------------------------------------------- */

/** Set the callback function to be called when I2C transaction is complete */

PUBLIC void
hal_i2c_master_sw_set_callback( HalI2cBusId_t    bus_id,
                                HalI2cCallback_t callback_handler );

/* -------------------------------------------------------------------------- */

/** Tick processor to advance the internal state machine on a timer tick
 *  basis. Tick time equals to half the I2C clock period. */

PUBLIC void
hal_i2c_master_sw_tick( HalI2cBusId_t bus_id );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_MASTER_SW_H */
