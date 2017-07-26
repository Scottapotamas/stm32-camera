///**
// * @file      hal_i2c.c
// *
// * @brief     Wrapper around the HAL_I2C functions from CubeMX.
// *
// * @author    Marco Hess <marco.hess@through-ip.com>
// *
// * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
// */
//
///* -------------------------------------------------------------------------- */
//
//#include <ctype.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
//
///* -------------------------------------------------------------------------- */
//
//#include "global.h"
//#include "qassert.h"
//#include "stm32f4xx_hal.h"
//#include "hal_delay.h"
//#include "hal_i2c_master_hw.h"
//#include "i2c.h"
//
///* -------------------------------------------------------------------------- */
//
//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */
//
///* ----- Types -------------------------------------------------------------- */
//
///* ----- Private Function Prototypes ---------------------------------------- */
//
//PRIVATE I2C_HandleTypeDef *
//hal_i2c_master_hw_bus_handle( HalI2cBusId_t bus_id );
//
//PRIVATE HalI2cBusId_t
//hal_i2c_master_hw_bus_id( I2C_HandleTypeDef * handle );
//
///* ----- Private Variables -------------------------------------------------- */
//
//PRIVATE HalI2cCallback_t hal_i2c_master_hw_callback;
//
///* -------------------------------------------------------------------------- */
///* ----- I2C Interface Functions -------------------------------------------- */
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cStatus_t
//hal_i2c_master_hw_init( HalI2cBusId_t bus_id )
//{
//    switch( bus_id )
//    {
//        case I2C_BUS_1:
//            MX_I2C1_Init();
//            break;
//        case I2C_BUS_2:
//            MX_I2C2_Init();
//            break;
//        default:
//            return I2C_STATUS_ERROR;
//    }
//    return I2C_STATUS_OK;
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cStatus_t
//hal_i2c_master_hw_reset( HalI2cBusId_t bus_id )
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    I2C_HandleTypeDef *hi2c = hal_i2c_master_hw_bus_handle( bus_id );
//
//    /* Assert software reset on the I2C */
//    hi2c->Instance->CR1 |= I2C_CR1_SWRST;
//    hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;
//
//    __HAL_RCC_I2C2_FORCE_RESET();
//    __HAL_RCC_I2C2_RELEASE_RESET();
//
//    HAL_I2C_DeInit( hi2c );
//
//    GPIO_InitStruct.Pin = SENSOR_I2C_SDA_Pin|SENSOR_I2C_SCL_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
//
//    HAL_GPIO_WritePin( SENSOR_I2C_SDA_GPIO_Port,
//                       SENSOR_I2C_SDA_Pin, GPIO_PIN_SET );
//    HAL_GPIO_WritePin( SENSOR_I2C_SCL_GPIO_Port,
//                       SENSOR_I2C_SCL_Pin, GPIO_PIN_SET );
//
//    if( HAL_GPIO_ReadPin( SENSOR_I2C_SDA_GPIO_Port,
//                          SENSOR_I2C_SDA_Pin ) == GPIO_PIN_RESET )
//    {
//        for( uint8_t i = 0; i <= 9; i++ )
//        {
//            HAL_GPIO_WritePin( SENSOR_I2C_SCL_GPIO_Port,
//                               SENSOR_I2C_SCL_Pin, GPIO_PIN_RESET );
//            hal_delay_us(5);
//            HAL_GPIO_WritePin( SENSOR_I2C_SCL_GPIO_Port,
//                               SENSOR_I2C_SCL_Pin, GPIO_PIN_SET );
//            hal_delay_us(5);
//            if( HAL_GPIO_ReadPin( SENSOR_I2C_SDA_GPIO_Port,
//                                  SENSOR_I2C_SDA_Pin ) == GPIO_PIN_SET )
//            {
//                break;
//            }
//        }
//    }
//
//    HAL_GPIO_DeInit(GPIOF, SENSOR_I2C_SDA_Pin|SENSOR_I2C_SCL_Pin);
//
//    hal_i2c_master_hw_init( bus_id );
//
//    /* Clear software reset on the I2C */
//    hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;
//
//    return I2C_STATUS_OK;
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cStatus_t
//hal_i2c_master_hw_transmit( HalI2cBusId_t bus_id,
//                            uint8_t       address,
//                            uint8_t     * buffer,
//                            uint8_t       len )
//{
//    return (HalI2cStatus_t)HAL_I2C_Master_Transmit_IT( hal_i2c_master_hw_bus_handle( bus_id ),
//                                                       address << 1,
//                                                       buffer,
//                                                       len );
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cStatus_t
//hal_i2c_master_hw_receive( HalI2cBusId_t bus_id,
//                           uint8_t       address,
//                           uint8_t     * buffer,
//                           uint8_t       len )
//{
//    return (HalI2cStatus_t)HAL_I2C_Master_Receive_IT( hal_i2c_master_hw_bus_handle( bus_id ),
//                                                      address << 1,
//                                                      buffer,
//                                                      len );
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cStatus_t
//hal_i2c_master_hw_abort( HalI2cBusId_t bus_id,
//                         uint8_t       address )
//{
//    return (HalI2cStatus_t)HAL_I2C_Master_Abort_IT( hal_i2c_master_hw_bus_handle( bus_id ),
//                                                    address << 1 );
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC HalI2cState_t
//hal_i2c_master_hw_get_state( HalI2cBusId_t bus_id )
//{
//    return (HalI2cState_t)HAL_I2C_GetState( hal_i2c_master_hw_bus_handle( bus_id ) );
//}
//
///* -------------------------------------------------------------------------- */
//
///** Return error status of last I2C transfer */
//
//PUBLIC HalI2cError_t
//hal_i2c_master_hw_get_error( HalI2cBusId_t bus_id )
//{
//    return (HalI2cError_t)HAL_I2C_GetError( hal_i2c_master_hw_bus_handle( bus_id ) );
//}
//
///* -------------------------------------------------------------------------- */
//
//PUBLIC void
//hal_i2c_master_hw_set_callback( HalI2cBusId_t    id,
//                                HalI2cCallback_t callback )
//{
//    hal_i2c_master_hw_callback = callback;
//}
//
///* -------------------------------------------------------------------------- */
///* ----- Private Functions -------------------------------------------------- */
///* -------------------------------------------------------------------------- */
//
///** Return the STM I2C handle using the generic Bus ID */
//
//PRIVATE I2C_HandleTypeDef *
//hal_i2c_master_hw_bus_handle( HalI2cBusId_t bus_id )
//{
//    switch( bus_id )
//    {
//        case I2C_BUS_1:
//            return &hi2c1;
//        case I2C_BUS_2:
//            return &hi2c2;
//        default:
//            ASSERT( false );
//    }
//    return NULL;
//}
//
///* -------------------------------------------------------------------------- */
//
///** Return the generic Bus ID based on the the STM I2C handle */
//
//PRIVATE HalI2cBusId_t
//hal_i2c_master_hw_bus_id( I2C_HandleTypeDef * handle )
//{
//    if( handle == &hi2c1 )
//    {
//        return I2C_BUS_1;
//    }
//    else if( handle == &hi2c2 )
//    {
//        return I2C_BUS_2;
//    }
//    else
//    {
//        ASSERT( false );
//    }
//    return 0;
//}
//
///* -------------------------------------------------------------------------- */
///* ----- HAL_I2C Callback Functions ----------------------------------------- */
///* -------------------------------------------------------------------------- */
//
///** STM HAL layer callback when transmit completes */
//
//PUBLIC void
//HAL_I2C_MasterTxCpltCallback( I2C_HandleTypeDef *hi2c )
//{
//    if( hal_i2c_master_hw_callback )
//    {
//        (*hal_i2c_master_hw_callback)( hal_i2c_master_hw_bus_id( hi2c ),
//                                       I2C_CALLBACK_TX_COMPLETE );
//    }
//}
//
///* -------------------------------------------------------------------------- */
//
///** STM HAL layer callback when receive completes */
//
//PUBLIC void
//HAL_I2C_MasterRxCpltCallback( I2C_HandleTypeDef *hi2c )
//{
//    if( hal_i2c_master_hw_callback )
//    {
//        (*hal_i2c_master_hw_callback)( hal_i2c_master_hw_bus_id( hi2c ),
//                                       I2C_CALLBACK_RX_COMPLETE );
//    }
//}
//
///* -------------------------------------------------------------------------- */
//
///** STM HAL layer callback when error occurred */
//
//PUBLIC void
//HAL_I2C_ErrorCallback( I2C_HandleTypeDef *hi2c )
//{
//    if( hal_i2c_master_hw_callback )
//    {
//        /* The STM32F40x Errata indicate that the chip is erroneously
//         * generating BERR errors in master transmit mode and should be
//         * ignored.
//         */
////        if( hi2c->ErrorCode & HAL_I2C_STATUS_ERROR_BERR )
////        {
////            hi2c->ErrorCode &= ~HAL_I2C_STATUS_ERROR_BERR;
////        }
//
//        if( hi2c->ErrorCode )
//        {
//            (*hal_i2c_master_hw_callback)( hal_i2c_master_hw_bus_id( hi2c ),
//                                           I2C_CALLBACK_ERROR );
//        }
//    }
//}
//
///* ----- End ---------------------------------------------------------------- */
//



//I2C_HandleTypeDef hi2c2;
//
///* I2C2 init function */
//void MX_I2C2_Init(void)
//{
//
//  hi2c2.Instance = I2C2;
//  hi2c2.Init.ClockSpeed = 100000;
//  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
//  hi2c2.Init.OwnAddress1 = 0;
//  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//  hi2c2.Init.OwnAddress2 = 0;
//  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
//  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }
//
//}
//
//void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct;
//  if(i2cHandle->Instance==I2C2)
//  {
//  /* USER CODE BEGIN I2C2_MspInit 0 */
//
//  /* USER CODE END I2C2_MspInit 0 */
//
//    /**I2C2 GPIO Configuration
//    PB10     ------> I2C2_SCL
//    PB11     ------> I2C2_SDA
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//    /* Peripheral clock enable */
//    __HAL_RCC_I2C2_CLK_ENABLE();
//  /* USER CODE BEGIN I2C2_MspInit 1 */
//
//  /* USER CODE END I2C2_MspInit 1 */
//  }
//}
//
//void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
//{
//
//  if(i2cHandle->Instance==I2C2)
//  {
//  /* USER CODE BEGIN I2C2_MspDeInit 0 */
//
//  /* USER CODE END I2C2_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_I2C2_CLK_DISABLE();
//
//    /**I2C2 GPIO Configuration
//    PB10     ------> I2C2_SCL
//    PB11     ------> I2C2_SDA
//    */
//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);
//
//  /* USER CODE BEGIN I2C2_MspDeInit 1 */
//
//  /* USER CODE END I2C2_MspDeInit 1 */
//  }
//}


