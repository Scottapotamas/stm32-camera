/**
 * @file      system_speed.h
 *
 * @brief     Control the system clock speed for power saving purposes.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "system_speed.h"
#include "simple_state_machine.h"
#include "hal_system_speed.h"

#include "hal_systick.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "stm32f4xx_hal.h"

/* ----- Private Types ------------------------------------------------------ */

typedef enum
{
   SYSTEM_SPEED_STATE_LOW,
   SYSTEM_SPEED_STATE_HIGH
} SystemSpeedStates_t;

typedef struct
{
    SystemSpeedStates_t previousState;
    SystemSpeedStates_t currentState;
    SystemSpeedStates_t nextState;
    uint32_t            high_speed_requested;
} SystemSpeedStateVars_t;

/* ----- Private Data ------------------------------------------------------- */

SystemSpeedStateVars_t system_speed_state_machine;
SystemSpeedStateVars_t *me = &system_speed_state_machine;

/* ----- Public Functions --------------------------------------------------- */

/** Init the system clock to a default level */

PUBLIC void
system_speed_init( void )
{
    memset( &system_speed_state_machine, 0, sizeof(system_speed_state_machine) );

    hal_system_speed_low();

    STATE_INIT_INITIAL( SYSTEM_SPEED_STATE_LOW );
}

/* -------------------------------------------------------------------------- */

/** Set the system clock speed to a different level */

PUBLIC void
system_speed_set( SystemSpeed_t speed )
{
    switch( me->currentState )
    {
       case SYSTEM_SPEED_STATE_LOW:
           STATE_ENTRY_ACTION
               me->high_speed_requested = 0;
               hal_system_speed_low();
               hal_uart_reinit( HAL_UART_PORT_MAIN );

           STATE_TRANSITION_TEST
                if( speed == SYSTEM_SPEED_FULL )
                {
                    me->high_speed_requested++;
                    STATE_NEXT( SYSTEM_SPEED_STATE_HIGH );
                }
            STATE_EXIT_ACTION
            STATE_END
            break;

       case SYSTEM_SPEED_STATE_HIGH:
           STATE_ENTRY_ACTION
               hal_system_speed_high();
               hal_uart_reinit( HAL_UART_PORT_MAIN );

            STATE_TRANSITION_TEST
                if( speed == SYSTEM_SPEED_FULL )
                {
                    me->high_speed_requested++;
                }
                if( speed == SYSTEM_SPEED_LOW_POWER )
                {
                    if( --me->high_speed_requested == 0 )
                    {
                        STATE_NEXT( SYSTEM_SPEED_STATE_LOW );
                    }
                }
            STATE_EXIT_ACTION
            STATE_END
            break;
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC SystemSpeed_t
system_speed_get( void )
{
    SystemSpeed_t speed = SYSTEM_SPEED_LOW_POWER;

    switch( me->currentState )
    {
        case SYSTEM_SPEED_STATE_LOW:
            speed = SYSTEM_SPEED_LOW_POWER;
            break;

        case SYSTEM_SPEED_STATE_HIGH:
            speed = SYSTEM_SPEED_FULL;
            break;
    }
    return speed;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
system_speed_cleanup( void )
{
	//Re-initalise the clocks for the various peripherals affected by clock change
	hal_systick_init();

	__HAL_RCC_USART1_CLK_ENABLE();

	//hal_uart_init(HAL_UART_PORT_MAIN);

}


/* ----- End ---------------------------------------------------------------- */

