/**
 * @file    app_task_terminal.c
 *
 * @ingroup tasks
 *
 * @brief   blah
 *
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <ctype.h>
#include <string.h>
#include <event_subscribe.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "app_tasks.h"
#include "app_task_ids.h"
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_version.h"

#include "app_task_terminal.h"
#include "app_task_terminal_private.h"
#include "commands.h"
#include "hal_uart.h"
#include "hal_systick.h"
#include "config.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----------------------- Public Functions --------------------------------- */

PUBLIC StateTask *
appTaskTerminalCreate( AppTaskTerminal   *me,
                        StateEvent         *eventQueueData[ ],
                        const uint8_t      eventQueueSize,
						HalUartPort_t      instance )
{
    /* Clear all task data */
    memset( me, 0, sizeof(AppTaskTerminal) );

    /* Initialise State Machine structures */
    AppTaskTerminalConstructor( me );

    /* Which uart are we talking about */
    me->instance = instance;

    /* Initialise State Machine Task */
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            0,
                            0 );
}

/* ----- Private Functions -------------------------------------------------- */

/* State Machine Construction */
PRIVATE void AppTaskTerminalConstructor( AppTaskTerminal *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskTerminal_initial );
}

/* -------------------------------------------------------------------------- */

/*  State Machine Initial State */
PRIVATE void AppTaskTerminal_initial( AppTaskTerminal *me,
                                       const StateEvent *e __attribute__((__unused__)) )
{
    eventSubscribe( (StateTask*)me, TERMINAL_MODE_SIGNAL );
    STATE_INIT( &AppTaskTerminal_main );
}

/* -------------------------------------------------------------------------- */

/* State Machine Initial State */
PRIVATE STATE
AppTaskTerminal_main( AppTaskTerminal *me,
                       const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
        	//TODO put some logging here or something
            return 0;

        case STATE_INIT_SIGNAL:
            switch( config_terminal_baudrate( me->instance ) )
            {
            //TODO Handle a 'disabled' uart port
                case HAL_UART_PORT_MAIN:
                    STATE_INIT( AppTaskTerminal_mode_active );
                    break;

                case HAL_UART_PORT_SECONDARY:
                    STATE_INIT( AppTaskTerminal_mode_active );
                    break;
            }
            return 0;

        case TERMINAL_MODE_SIGNAL:
            {
                TerminalModeEvent *ame = (TerminalModeEvent*)e;
                if( ame->port == me->instance )
                {
                    //TODO Handle a 'disabled' uart port
                    STATE_TRAN_DYN( AppTaskTerminal_mode_active );
                }
            }
            return 0;

    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

/* State Machine Mode None */
PRIVATE STATE
AppTaskTerminal_mode_none( AppTaskTerminal *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
        	//TODO set instance to uninitialised

            return 0;
    }
    return (STATE)AppTaskTerminal_main;
}

/* -------------------------------------------------------------------------- */

/* State Machine Mode Monitor */
PRIVATE STATE
AppTaskTerminal_mode_active( AppTaskTerminal *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            cmd_init( &me->monitor, commands );

            if( me->instance == HAL_UART_PORT_MAIN || me->instance == HAL_UART_PORT_SECONDARY)
            {
                hal_uart_init( me->instance );

                hal_uart_baudrate( me->instance, config_terminal_baudrate( me->instance ) );
                hal_uart_set_rx_handler( me->instance, AppTaskTerminal_rx_callback );

                cmd_set_output_put( &me->monitor, AppTaskTerminal_tx_put_a );
                cmd_set_output_flush( &me->monitor,  AppTaskTerminal_tx_flush_a );
            }



            cmd_set_echo( &me->monitor, true );
            cmd_printf( &me->monitor,
                        "\r\n*** %s - %s (%s) %s ***\r\n\r\n",
                        ProgramName,
                        ProgramBuildInfo,
                        ProgramBuildDate,
                        ProgramBuildType );
            cmd_input_func( &me->monitor, '\r' );
            return 0;

        case TERMINAL_INPUT_CHAR_SIGNAL:
            cmd_input_func( &me->monitor, ((TerminalCharEvent*)e)->ch );
            //no break

        case STATE_STEP1_SIGNAL:
            me->monitor.flags.cmdDone = cmd_main_loop( &me->monitor );
            if( !me->monitor.flags.cmdDone )
            {
                /* Repeat until done */
                stateTaskPostReservedEvent( STATE_STEP1_SIGNAL );
            }
            return 0;
    }
    return (STATE)AppTaskTerminal_main;
}

/* -------------------------------------------------------------------------- */


/* ----- Callback Helper Functions ------------------------------------------ */

PRIVATE bool
AppTaskTerminal_tx_put_a( uint8_t c )
{
    return hal_uart_put( HAL_UART_PORT_MAIN, c );
}

/* -------------------------------------------------------------------------- */

PRIVATE void
AppTaskTerminal_tx_flush_a( void )
{
    hal_uart_flush( HAL_UART_PORT_MAIN );
}

/* -------------------------------------------------------------------------- */

/* Simple callback for received characters */
PRIVATE void
AppTaskTerminal_rx_callback( HalUartPort_t port, uint8_t c )
{
    if( port == HAL_UART_PORT_MAIN )
    {
        TerminalCharEvent *e = EVENT_NEW( TerminalCharEvent, TERMINAL_INPUT_CHAR_SIGNAL );

        // Failure of EVENT_NEW allocate results in a corrupted input message
        if( e )
        {
            e->ch = c;
            if( port == HAL_UART_PORT_MAIN )
            {
                stateTaskPostFIFO( app_task_by_id( TASK_MONITOR ),
                                   (StateEvent*)e );
            }

        }
    }
    else
    {
    	//handle other uart ports here if future boards need them
    }
}

/* ----- End ---------------------------------------------------------------- */
