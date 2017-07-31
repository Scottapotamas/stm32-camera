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

/* ----- System Includes ---------------------------------------------------- */
#include <inttypes.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_system_speed.h"
#include "stm32f4xx_hal.h"
#include "hal_systick.h"
#include "hal_uart.h"

/* ----- Private Types ------------------------------------------------------ */

/* ----- Private Prototypes ------------------------------------------------- */

/* ----- Private Data ------------------------------------------------------- */

volatile uint32_t cc_when_sleeping;		//timestamp when we go to sleep
volatile uint32_t cc_when_woken = 0; 	//timestamp when we wake up
volatile uint32_t cc_awake_time = 0;	//duration of 'active'
volatile uint32_t cc_asleep_time = 0;	//duration of 'sleep'

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
hal_system_speed_init(  )
{
	//Enable the DWT timer
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_sleep( void )
{
	CRITICAL_SECTION_VAR();
	CRITICAL_SECTION_START();

	cc_awake_time += DWT->CYCCNT - cc_when_woken;
	cc_when_sleeping = DWT->CYCCNT;

	//Go to sleep. Wake on interrupt.
    HAL_PWR_EnterSLEEPMode( PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI );

    cc_asleep_time += DWT->CYCCNT - cc_when_sleeping;
	cc_when_woken = DWT->CYCCNT;

	CRITICAL_SECTION_END();
}

/* -------------------------------------------------------------------------- */

//return a 0-100% value for CPU load
PUBLIC float
hal_system_speed_get_load( void )
{
	float cpu_util = (float)cc_awake_time / (float)(cc_asleep_time + cc_awake_time) * 100;
	cc_asleep_time = 0;
	cc_awake_time = 0;

	return cpu_util;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
hal_system_speed_get_speed( void )
{
	return HAL_RCC_GetSysClockFreq();
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_high( void )
{
    /* TODO change clock speed to high speed */
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_system_speed_low( void )
{
    /* TODO change clock speed to low speed */
}

/* ----- End ---------------------------------------------------------------- */

