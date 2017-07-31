/**
 * @file      hal_firmware_update.c
 *
 */

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "hal_firmware_update.h"
#include "hal_watchdog.h"
#include "hal_gpio.h"
#include "hal_delay.h"
#include "stm32f4xx_hal.h"
#include "app_times.h"
#include "hal_systick.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/* ----- Data --------------------------------------------------------------- */

/* ----- Public Functions --------------------------------------------------- */

PUBLIC void
hal_firmware_update_hardware()
{
    /* This ensure that the watch dog does not kick while reset. */
    hal_watchdog_refresh();

    //Charge the cap on the BOOT0 pin and then ensure the output doesn't drain it during reboot
    hal_gpio_write_pin(_REBOOT_LATCH, true);
    hal_delay_ms( TIME_REBOOT_CAP_CHARGE );
    hal_gpio_init(_REBOOT_LATCH, MODE_ANALOG, 0);

    /* Go straight to the CORE_CM4 inline function for a reset */
    NVIC_SystemReset();

    /* NO RETURN */
}

PUBLIC void
hal_firmware_update_software()
{
    /* This ensure that the watch dog does not kick while reset. */
    hal_watchdog_refresh();

	void (*SysMemBootJump)(void);

	//Address of boot program in memory (only applies to F429, see AN2606 table 110).
	volatile uint32_t addr = 0x1FFF0000;

	//Disable RCC and set to defaults
	HAL_RCC_DeInit();

	//Disable systick and set to defaults
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	__disable_irq();

	//Remap memory to address 0x00000000 in address space.
	__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();

	// Set the jump location
	SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));

	//Set the stack pointer
	__set_MSP(*(uint32_t *)addr);

    //aaand JUMP!
	SysMemBootJump();

    /* NO RETURN */
}

/* ----- End ---------------------------------------------------------------- */
