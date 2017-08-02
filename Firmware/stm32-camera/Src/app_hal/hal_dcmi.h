/**
 * @file      hal_mco.h
 *
 * @brief     MCO control.
*/

#ifndef HAL_DCMI_H
#define HAL_DCMI_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include "global.h"

/* ----- Local Includes ----------------------------------------------------- */

#include "stm32f4xx_hal.h"
#include "main.h"

/* -------------------------------------------------------------------------- */

extern DCMI_HandleTypeDef hdcmi;

/* ------------------------- Functions Prototypes --------------------------- */

PUBLIC void
hal_dcmi_init( void );

/* ------------------------- End -------------------------------------------- */

#ifdef __cplusplus
}
#endif
#endif /* HAL_DCMI_H */
