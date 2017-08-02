/**
 * @file      hal_dcmi.h
 *
 * @brief     DCMI Peripheral control.
*/
/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "hal_dcmi.h"
#include "dma.h"

/* -------------------------------------------------------------------------- */

DCMI_HandleTypeDef hdcmi;
DMA_HandleTypeDef hdma_dcmi;

/* ------------------------- Functions -------------------------------------- */

/* DCMI init function */

PUBLIC void
hal_dcmi_init(void)
{
  hdcmi.Instance = DCMI;
  hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;

  hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
  hdcmi.Init.PCKPolarity = DCMI_PCKPOLARITY_RISING; //changed to rising
  hdcmi.Init.VSPolarity = DCMI_VSPOLARITY_HIGH;     //changed to high
  hdcmi.Init.HSPolarity = DCMI_HSPOLARITY_LOW;      //low
  hdcmi.Init.CaptureRate = DCMI_CR_ALL_FRAME;       // all frames, instead of every second or 4th
  hdcmi.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
  hdcmi.Init.JPEGMode = DCMI_JPEG_ENABLE;
//        DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot; //DCMI_CaptureMode_SnapShot

  if (HAL_DCMI_Init(&hdcmi) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* -------------------------------------------------------------------------- */

void HAL_DCMI_MspInit(DCMI_HandleTypeDef* dcmiHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(dcmiHandle->Instance==DCMI)
  {
    /* Peripheral clock enable */
    __HAL_RCC_DCMI_CLK_ENABLE();
  
    /**DCMI GPIO Configuration    
    PE4     ------> DCMI_D4
    PE5     ------> DCMI_D6
    PA4     ------> DCMI_HSYNC
    PA6     ------> DCMI_PIXCK
    PC6     ------> DCMI_D0
    PC7     ------> DCMI_D1
    PB6     ------> DCMI_D5
    PB7     ------> DCMI_VSYNC
    PB9     ------> DCMI_D7
    PE0     ------> DCMI_D2
    PE1     ------> DCMI_D3 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* DCMI DMA Init */
    hdma_dcmi.Instance = DMA2_Stream1;
    hdma_dcmi.Init.Channel = DMA_CHANNEL_1;
    hdma_dcmi.Init.Direction = DMA_PERIPH_TO_MEMORY;

    hdma_dcmi.Init.Mode = DMA_NORMAL;   //CHANGED TO NORMAL FROM CIRCULAR
    hdma_dcmi.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_dcmi.Init.FIFOMode = DMA_FIFOMODE_ENABLE;  //CHANGED TO ENABLE
    hdma_dcmi.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;  //ADDED

    hdma_dcmi.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dcmi.Init.PeriphBurst = DMA_PBURST_SINGLE;    //ADDED
    hdma_dcmi.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;

    hdma_dcmi.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dcmi.Init.MemBurst = DMA_MBURST_SINGLE;    //ADDED
    hdma_dcmi.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;

    if (HAL_DMA_Init(&hdma_dcmi) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    //TODO put dcmi into DCMI_MODE_SNAPSHOT

    //TODO interrupt handling from DCMI x3

    __HAL_LINKDMA(dcmiHandle,DMA_Handle,hdma_dcmi);

    /* DCMI interrupt Init */
    HAL_NVIC_SetPriority(DCMI_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(DCMI_IRQn);
  }
}

/* -------------------------------------------------------------------------- */

void HAL_DCMI_MspDeInit(DCMI_HandleTypeDef* dcmiHandle)
{
  if(dcmiHandle->Instance==DCMI)
  {
    /* Peripheral clock disable */
    __HAL_RCC_DCMI_CLK_DISABLE();
  
    /**DCMI GPIO Configuration    
    PE4     ------> DCMI_D4
    PE5     ------> DCMI_D6
    PA4     ------> DCMI_HSYNC
    PA6     ------> DCMI_PIXCK
    PC6     ------> DCMI_D0
    PC7     ------> DCMI_D1
    PB6     ------> DCMI_D5
    PB7     ------> DCMI_VSYNC
    PB9     ------> DCMI_D7
    PE0     ------> DCMI_D2
    PE1     ------> DCMI_D3 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_0|GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9);

    /* DCMI DMA DeInit */
    HAL_DMA_DeInit(dcmiHandle->DMA_Handle);

    /* DCMI interrupt Deinit */
    HAL_NVIC_DisableIRQ(DCMI_IRQn);
  }
} 

/* ----- End ---------------------------------------------------------------- */

