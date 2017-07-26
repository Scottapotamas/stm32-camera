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

#ifndef HAL_I2C_H
#define HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/** Enum to map a generic ID number to the actual I2C handle pointer in use */

typedef enum
{
    I2C_BUS_1,          /* I/O Expanders */
    I2C_BUS_2,          /* LIDAR's */
    I2C_BUS_MAX,
} HalI2cBusId_t;

/** Enum mapping to equivalent numbers as in HAL_StatusTypeDef */

typedef enum
{
    I2C_STATUS_OK      = 0,
    I2C_STATUS_ERROR   = 1,
    I2C_STATUS_BUSY    = 2,
    I2C_STATUS_TIMEOUT = 3
} HalI2cStatus_t;

/** Enum mapping for callback event types */

typedef enum
{
    I2C_CALLBACK_TX_COMPLETE = 0,
    I2C_CALLBACK_RX_COMPLETE,
    I2C_CALLBACK_ERROR,
} HalI2cCallbackEventType_t;

/** Enum mapping to equivalent numbers as in HAL_I2C_StateTypeDef */

typedef enum
{
    I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialised         */
    I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialised and ready for use  */
    I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
    I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
    I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
    I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
    I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
                                                 process is ongoing                       */
    I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
                                                 process is ongoing                       */
    I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
    I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
    I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */
} HalI2cState_t;

typedef enum /* See stm32f4xx_hal_i2c.h */
{
    I2C_ERROR_NONE              = 0x00U,   /*!< No error           */
    I2C_ERROR_BERR              = 0x01U,   /*!< BERR error         */
    I2C_ERROR_ARLO              = 0x02U,   /*!< ARLO error         */
    I2C_ERROR_AF                = 0x04U,   /*!< AF error           */
    I2C_ERROR_OVR               = 0x08U,   /*!< OVR error          */
    I2C_ERROR_DMA               = 0x10U,   /*!< DMA transfer error */
    I2C_ERROR_TIMEOUT           = 0x20U,   /*!< Timeout Error      */
} HalI2cError_t;

/** Callback prototype for Tx, Rx and Error callbacks */

typedef void (*HalI2cCallback_t)( HalI2cBusId_t bus_id, HalI2cCallbackEventType_t event_type );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_I2C_H */
