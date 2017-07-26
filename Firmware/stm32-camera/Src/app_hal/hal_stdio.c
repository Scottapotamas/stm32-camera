/**
 * @file      hal_stdio.c
 *
 * @brief     stdio implementation to use default printf on grooming trap
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ----- System Includes ---------------------------------------------------- */

#include <stdio.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_uart.h"

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_stdio_put( int ch )
{
    hal_uart_put( HAL_UART_PORT_MAIN, ch );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
hal_stdio_flush( void )
{
    hal_uart_flush( HAL_UART_PORT_MAIN );
}

/* -------------------------------------------------------------------------- */

//int __putchar (int ch)
//{
//    hal_uart_put_blocking( HAL_UART_PORT_AUXILIARY_B, ch );
//    return ch;
//}

/* ----- End ---------------------------------------------------------------- */

