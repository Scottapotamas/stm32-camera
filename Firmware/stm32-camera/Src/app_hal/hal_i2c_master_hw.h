/**
 * @file      hal_i2c.h
 *
 * @brief     Hardware abstraction interface for I2C interface on STM
 *            Minimalist wrapper to the STM HAL functions to operate I2C
 *            read and write operations under interrupt with callbacks for
 *            the transmit complete, receive complete and error states.
 *            Able to operate on the different available I2C busses in
 *            the STM micro controller.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_I2C_MASTER_HW_H
#define HAL_I2C_MASTER_HW_H

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
/* --- I2C Interface Functions ---------------------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_hw_init( HalI2cBusId_t id );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_hw_reset( HalI2cBusId_t bus_id );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_hw_transmit( HalI2cBusId_t id,
                            uint8_t       address,
                            uint8_t     * buffer,
                            uint8_t       len );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_hw_receive( HalI2cBusId_t id,
                           uint8_t       address,
                           uint8_t     * buffer,
                           uint8_t       len );

/* -------------------------------------------------------------------------- */

PUBLIC HalI2cStatus_t
hal_i2c_master_hw_abort( HalI2cBusId_t id,
                         uint8_t       address );

/* -------------------------------------------------------------------------- */

/** Return state of I2C device / bus transfer */

PUBLIC HalI2cState_t
hal_i2c_master_hw_get_state( HalI2cBusId_t id );

/* -------------------------------------------------------------------------- */

/** Return error status of last I2C transfer */

PUBLIC HalI2cError_t
hal_i2c_master_hw_get_error( HalI2cBusId_t id );

/* -------------------------------------------------------------------------- */

/** Set the callback function to be called when I2C transaction is complete */

PUBLIC void
hal_i2c_master_hw_set_callback( HalI2cBusId_t    id,
                                HalI2cCallback_t callback );

/* ----- End ---------------------------------------------------------------- */

//TODO clean hardware i2c header up
//#include "stm32f4xx_hal.h"
//#include "main.h"
//
///* USER CODE BEGIN Includes */
//
///* USER CODE END Includes */
//
//extern I2C_HandleTypeDef hi2c2;
//
///* USER CODE BEGIN Private defines */
//
///* USER CODE END Private defines */
//
//extern void _Error_Handler(char *, int);
//
//void MX_I2C2_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_MASTER_HW_H */
