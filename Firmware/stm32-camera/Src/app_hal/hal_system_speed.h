/**
 * @file      hal_system_speed.h
 *
 * @brief     Low level control of the system clock speed for power saving purposes.
 *            Essentially like the original SystemClock_Config but with two
 *            configurations.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_SYSTEM_SPEED_H
#define HAL_SYSTEM_SPEED_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"


/* ----- Public Functions --------------------------------------------------- */


/* PLL configuration */
#define RCC_PLLM_MASK    ((uint32_t)0x0000003F)
#define RCC_PLLM_POS     0
#define RCC_PLLN_MASK    ((uint32_t)0x00007FC0)
#define RCC_PLLN_POS     6
#define RCC_PLLP_MASK    ((uint32_t)0x00030000)
#define RCC_PLLP_POS     16
#define RCC_PLLQ_MASK    ((uint32_t)0x0F000000)
#define RCC_PLLQ_POS     24
#define RCC_PLLR_MASK    ((uint32_t)0x70000000)
#define RCC_PLLR_POS     28

typedef struct {
	uint16_t PLLM; // PLL M parameter. Between 2 and 63.
	uint16_t PLLN; // PLL N parameter. Between 192 and 432.
	uint16_t PLLP; // PLL P parameter. Use 2, 4, 6 or 8.
	uint16_t PLLQ; // PLL Q parameter. Between 2 and 15.
	uint16_t PLLR; // PLL R parameter. Between 2 and 7. Only available on STM32F446 devices.
} SystemSpeed_RCC_PLL_t;

PRIVATE SystemSpeed_RCC_PLL_t pll_working;	//TODO rename this local variable

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_set_pll( SystemSpeed_RCC_PLL_t* pll_settings );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_get_pll( SystemSpeed_RCC_PLL_t* pll_settings );

/* -------------------------------------------------------------------------- */

PUBLIC bool
hal_system_speed_pll_ready( void );

/* -------------------------------------------------------------------------- */

PUBLIC bool
hal_system_speed_hsi_ready( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_init( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_sleep( void );

/* -------------------------------------------------------------------------- */

PUBLIC float
hal_system_speed_get_load( void );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_system_speed_get_speed( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_high( void );

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_low( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SYSTEM_SPEED_H */
