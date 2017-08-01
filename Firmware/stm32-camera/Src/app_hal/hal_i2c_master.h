/**
 * @file      hal_i2c_master.h
 *
 * @brief     Wrapper to allow selection of the hardware or software
 *            based I2C interface.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_I2C_MASTER_H
#define HAL_I2C_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "hal_i2c.h"

/* -------------------------------------------------------------------------- */

#include "hal_i2c_master_sw.h"

#define hal_i2c_master_init(a,b,c)  hal_i2c_master_sw_init(a,b,c)
#define hal_i2c_master_reset        hal_i2c_master_sw_reset
#define hal_i2c_master_clock_speed  hal_i2c_master_sw_clock_speed
#define hal_i2c_master_transmit     hal_i2c_master_sw_transmit
#define hal_i2c_master_receive      hal_i2c_master_sw_receive
#define hal_i2c_master_abort        hal_i2c_master_sw_abort
#define hal_i2c_master_get_state    hal_i2c_master_sw_get_state
#define hal_i2c_master_get_error    hal_i2c_master_sw_get_error
#define hal_i2c_master_set_callback hal_i2c_master_sw_set_callback

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_MASTER_H */
