/**
 * @file      app_task_terminal_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Auxiliary Private Prototypes
 *            in a separate header file to enable unit testing.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_TERMINAL_PRIVATE_H
#define APP_TASK_TERMINAL_PRIVATE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void
AppTaskTerminalConstructor( AppTaskTerminal *me );

PRIVATE void
AppTaskTerminal_initial( AppTaskTerminal *me, const StateEvent *e );

PRIVATE STATE
AppTaskTerminal_main( AppTaskTerminal *me, const StateEvent *e );

    PRIVATE STATE
	AppTaskTerminal_mode_none( AppTaskTerminal *me, const StateEvent *e );

    PRIVATE STATE
	AppTaskTerminal_mode_active( AppTaskTerminal *me, const StateEvent *e );

/* ----- Private Helper Function Declarations ------------------------------- */

PRIVATE bool
AppTaskTerminal_tx_put_a( uint8_t c );

PRIVATE void
AppTaskTerminal_tx_flush_a( void );

PRIVATE void
AppTaskTerminal_rx_callback( HalUartPort_t port, uint8_t c );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_TERMINAL_PRIVATE_H */
