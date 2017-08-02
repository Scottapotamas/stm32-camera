/**
 * @file      hal_mco.h
 *
 * @brief     MCO control.
*/

#ifndef HAL_MCO_H
#define HAL_MCO_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "stm32f4xx_hal.h"

/* ------------------------- Functions Prototypes --------------------------- */

PUBLIC void
hal_mco_init( void );

/* ------------------------- End -------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_MCO_H */
