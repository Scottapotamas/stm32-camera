/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define AMBIENT_LIGHT_Pin GPIO_PIN_0
#define AMBIENT_LIGHT_GPIO_Port GPIOC
#define FLASH_OUTPUT_Pin GPIO_PIN_5
#define FLASH_OUTPUT_GPIO_Port GPIOA
#define STATUS0_Pin GPIO_PIN_0
#define STATUS0_GPIO_Port GPIOB
#define STATUS1_Pin GPIO_PIN_1
#define STATUS1_GPIO_Port GPIOB
#define SDIO_DETECT_Pin GPIO_PIN_15
#define SDIO_DETECT_GPIO_Port GPIOE
#define STROBE_Pin GPIO_PIN_14
#define STROBE_GPIO_Port GPIOB
#define EXPST_Pin GPIO_PIN_15
#define EXPST_GPIO_Port GPIOB
#define FREX_Pin GPIO_PIN_8
#define FREX_GPIO_Port GPIOD
#define XCLK_Pin GPIO_PIN_8
#define XCLK_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_11
#define RES_GPIO_Port GPIOA
#define PWDN_Pin GPIO_PIN_12
#define PWDN_GPIO_Port GPIOA
#define REG_EN_Pin GPIO_PIN_15
#define REG_EN_GPIO_Port GPIOA
#define EXP_1_Pin GPIO_PIN_0
#define EXP_1_GPIO_Port GPIOD
#define EXP_0_Pin GPIO_PIN_1
#define EXP_0_GPIO_Port GPIOD
#define BUTTON_0_Pin GPIO_PIN_3
#define BUTTON_0_GPIO_Port GPIOD
#define REBOOT_LATCH_Pin GPIO_PIN_8
#define REBOOT_LATCH_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
