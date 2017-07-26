/**
 * @file      hal_terminal.h
 *
 * @brief     Low level interface to the terminal UART.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_TERMINAL_H
#define HAL_TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------ System includes --------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ------------------------ Local includes ---------------------------------- */


/* ------------------------ Types ------------------------------------------- */

typedef void (*HalTerminalRxCallback_t)( uint8_t c );

/* -------------------------------------------------------------------------- */
/* --- UART INTERFACE                                                     --- */
/* -------------------------------------------------------------------------- */

/* Initialise the terminal handler */

void hal_terminal_init( uint32_t baudrate  );

/* -------------------------------------------------------------------------- */

/** Receive some amount of data e.g. through USB CDC */

void hal_terminal_receive( uint8_t * buf, uint32_t len );

/* -------------------------------------------------------------------------- */

/** Background process terminal data */

void hal_terminal_process( void );

/* -------------------------------------------------------------------------- */

/* Non-blocking send for a single character to the UART tx FIFO queue.
 * Returns true when successful. false when queue was full.
 */

bool hal_terminal_put( uint8_t c );

/* -------------------------------------------------------------------------- */

/* Non-blocking send for a number of characters to the UART tx FIFO queue.
 * Returns true when successful. false when queue was full.
 */

uint32_t hal_terminal_write( const uint8_t * data, uint32_t length );

/* -------------------------------------------------------------------------- */

/* Register a receive handler.
 * Called directly from UART ISR. When this is used, there is no buffering
 * available and the hal_terminal_get is no longer functional.
 */

void hal_terminal_set_rx_handler( void (*rxFunc)( uint8_t c) );

/* -------------------------------------------------------------------------- */

/* Returns number of available characters in the RX FIFO queue. */

uint32_t hal_terminal_rx_data_available( void );

/* -------------------------------------------------------------------------- */

/* Retrieve a single byte from the rx FIFO queue.
 * Returns 0 when no data is available or when rx callback is in use.
 */

uint8_t hal_terminal_rx_get( void );

/* -------------------------------------------------------------------------- */

/* Retrieve a number of bytes from the rx FIFO queue up to
 * buffer length. Returns the number of bytes actually read.
 */

uint32_t hal_terminal_read( uint8_t * buffer, uint32_t bufferlen );

/* -------------------------------------------------------------------------- */

/* Blocking printf to the UART.
 * To be used within assert and fault handlers to print fault
 * information.
 */

void hal_terminal_printf_direct( const char * format, ... );

/* -------------------------------------------------------------------------- */

void hal_terminal_printf( const char * format, ... );

bool hal_terminal_tx_todo(void);
/* ----------------------- End ---------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_TERMINAL_H */
