/**
 * @file      hal_terminal.c
 *
 * @brief     Low level interface to the terminal UART.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

/* ------------------------ System includes --------------------------------- */

#include <stdlib.h>
#include <stdarg.h>

/* ------------------------ Local includes ---------------------------------- */

#include "hal_terminal.h"
#include "fifo.h"
#include "stm32f4xx_hal.h"
//#include "usbd_cdc_if.h"

//#define HAL_TERMINAL_USE_USB_CDC

//#ifdef HAL_TERMINAL_USE_USB_CDC
//extern USBD_HandleTypeDef hUsbDeviceFS;
//#endif

/* ------------------------ Defines ----------------------------------------- */

/** Tx is buffered output */
#define  TERMINAL_RX_FIFO_SIZE       32
#define  TERMINAL_TX_FIFO_SIZE       256
#define  TERMINAL_TX_SEND_SIZE       32

/* ------------------------ Variables --------------------------------------- */

fifo_t                  hal_terminal_tx_fifo;
uint8_t                 hal_terminal_tx_buffer[TERMINAL_TX_FIFO_SIZE];

fifo_t                  hal_terminal_rx_fifo;
uint8_t                 hal_terminal_rx_buffer[TERMINAL_RX_FIFO_SIZE];

uint8_t                 hal_terminal_send_buffer[TERMINAL_TX_SEND_SIZE];

HalTerminalRxCallback_t hal_terminal_rx_callback = 0;

uint8_t                 hal_terminal_buffer[64];

/* -------------------------------------------------------------------------- */
/* --- UART INTERFACE                                                     --- */
/* -------------------------------------------------------------------------- */

/* Initialise the UART */

void hal_terminal_init( uint32_t baudrate )
{
    /* Setup FIFO buffer for terminal output */
    fifo_init( &hal_terminal_tx_fifo,
               hal_terminal_tx_buffer,
               sizeof( hal_terminal_tx_buffer ) );

    fifo_init( &hal_terminal_rx_fifo,
               hal_terminal_rx_buffer,
               sizeof( hal_terminal_rx_buffer ) );

}

/* -------------------------------------------------------------------------- */

/* Non-blocking send for a single character to the UART tx FIFO queue.
 * Returns true when successful. false when queue was full.
 */

bool hal_terminal_put( uint8_t ch )
{
    uint32_t sent = fifo_write( &hal_terminal_tx_fifo, &ch, 1 );

    return (sent == 1);
}

/* -------------------------------------------------------------------------- */

/* Blocking printf to the UART.
 * To be used within assert and fault handlers to print fault
 * information.
 */


void hal_terminal_printf_direct( const char * format, ... )
{
    uint32_t len;
    va_list  args;

    va_start( args, format );
    len = vsnprintf( (char*)hal_terminal_buffer, sizeof(hal_terminal_buffer), format, args );
    va_end( args );

//    CDC_Transmit_FS( (uint8_t*)hal_terminal_buffer, len );

}

/* -------------------------------------------------------------------------- */

void hal_terminal_printf( const char * format, ... )
{
    uint8_t len;
    va_list args;

    va_start( args, format );
    len = vsnprintf( (char*)hal_terminal_buffer, sizeof(hal_terminal_buffer), format, args );
    va_end( args );

    hal_terminal_write( hal_terminal_buffer, len );
}

/* -------------------------------------------------------------------------- */

/* Non-blocking send for a number of characters to the UART tx FIFO queue.
 * Returns the number of characters written to the queue. When less than
 * length, characters were dropped.
 */

uint32_t hal_terminal_write( const uint8_t * data, uint32_t length )
{
    uint32_t sent = fifo_write( &hal_terminal_tx_fifo, data, length );

    return sent;
}

/* -------------------------------------------------------------------------- */

/* Register a receive handler.
 * Called directly from UART ISR. When this is used, there is no buffering
 * available and the hal_terminal_get is no longer functional.
 */

void hal_terminal_set_rx_handler( HalTerminalRxCallback_t handler )
{
    hal_terminal_rx_callback = handler;
}

/* -------------------------------------------------------------------------- */

/* Returns number of available characters in the RX FIFO queue. */

uint32_t hal_terminal_rx_data_available( void )
{
    uint32_t dataAvail;
    __disable_irq();
    dataAvail = fifo_used( &hal_terminal_rx_fifo );
    __enable_irq();
    return dataAvail;
}

/* -------------------------------------------------------------------------- */

/* Retrieve a single byte from the rx FIFO queue.
 * Returns 0 when no data is available or when rx callback is in use.
 */

uint8_t hal_terminal_rx_get( void )
{
    uint8_t c = 0;
    __disable_irq();
    fifo_read( &hal_terminal_rx_fifo, &c, 1 );
    __enable_irq();
    return c;
}

/* -------------------------------------------------------------------------- */

/* Retrieve a number of bytes from the rx FIFO queue up to
 * buffer length. Returns the number of bytes actually read.
 */

uint32_t hal_terminal_read( uint8_t * data, uint32_t maxlength )
{
    return fifo_read( &hal_terminal_rx_fifo, data, maxlength );
}

/* -------------------------------------------------------------------------- */

void hal_terminal_receive( uint8_t * buf, uint32_t len )
{
    fifo_write( &hal_terminal_rx_fifo, buf, len );
}

/* -------------------------------------------------------------------------- */

uint32_t hal_terminal_process_timer = 0;

bool hal_terminal_tx_todo(void)
{
    return fifo_used( &hal_terminal_tx_fifo );
}

void hal_terminal_process( void )
{
    if( ( HAL_GetTick() - hal_terminal_process_timer ) > 10 )
    {
        hal_terminal_process_timer = HAL_GetTick();


        /* Transmit FIFO to CDC */
        uint32_t available = fifo_used( &hal_terminal_tx_fifo );
        if( available )
        {
//            USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
//            if (hcdc->TxState == 0)
//            {
//                uint32_t len = fifo_read( &hal_terminal_tx_fifo,
//                                          hal_terminal_send_buffer,
//                                          sizeof(hal_terminal_send_buffer) );
//                USBD_CDC_SetTxBuffer(&hUsbDeviceFS, hal_terminal_send_buffer, len);
//                USBD_CDC_TransmitPacket(&hUsbDeviceFS);
//            }
        }

        __disable_irq();
        /* Receive FIFO from USB CDC */
        available = fifo_used( &hal_terminal_rx_fifo );
        if( available )
        {
            if( hal_terminal_rx_callback )
            {
                uint8_t c;
                fifo_read( &hal_terminal_rx_fifo, &c, 1 );
                (*hal_terminal_rx_callback)( c );
            }
        }
        __enable_irq();
    }
}

/* ----------------------- End ---------------------------------------------- */
