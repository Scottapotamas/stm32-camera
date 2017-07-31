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

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_system_speed.h"
#include "stm32f4xx_hal.h"

/* ----- Private Types ------------------------------------------------------ */

/* ----- Private Prototypes ------------------------------------------------- */

/* ----- Private Data ------------------------------------------------------- */

volatile uint32_t cc_when_sleeping;
volatile uint32_t cc_when_woken = 0;
volatile uint32_t cc_awake_time = 0;
volatile uint32_t cc_asleep_time = 0;

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
hal_system_speed_init(  )
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;


}

PUBLIC void
hal_system_speed_sleep( void )
{
	CRITICAL_SECTION_VAR();
	CRITICAL_SECTION_START();

	/* Add to working time */
	cc_awake_time += DWT->CYCCNT - cc_when_woken;

	/* Save count cycle time */
	cc_when_sleeping = DWT->CYCCNT;

	/* Go to sleep mode */
    HAL_PWR_EnterSLEEPMode( PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI );

	/* Increase number of sleeping time in CPU cycles */
    cc_asleep_time += DWT->CYCCNT - cc_when_sleeping;

	/* Save current time to get number of working CPU cycles */
	cc_when_woken = DWT->CYCCNT;

	CRITICAL_SECTION_END();
}

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

