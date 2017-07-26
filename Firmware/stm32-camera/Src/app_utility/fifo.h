/**
 * @file      fifo.h
 *
 * @ingroup   utility
 *
 * @brief     Basic buffer based FIFO capability.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef FIFO_H
#define FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Types -------------------------------------------------------------- */

typedef struct
{
     uint8_t * buf;
     uint32_t  head;
     uint32_t  tail;
     uint32_t  capacity;
} fifo_t;

/* ----- Public Functions --------------------------------------------------- */

/** This initializes the FIFO structure with the given buffer and size */

PUBLIC void
fifo_init( fifo_t * f, uint8_t * buf, uint32_t buf_size );

/* -------------------------------------------------------------------------- */

/** Reads nbytes bytes from the FIFO. The number of bytes read is returned */

PUBLIC uint32_t
fifo_read( fifo_t * f, void * buf, uint32_t nbytes );

/* -------------------------------------------------------------------------- */

/** Writes up to nbytes bytes to the FIFO
 *  If the head runs in to the tail, not all bytes are written
 *  The number of bytes written is returned
 */

PUBLIC uint32_t
fifo_write( fifo_t * f, const void * buf, uint32_t nbytes );

/* -------------------------------------------------------------------------- */

/** Returns the amount of data used in the fifo. */

PUBLIC uint32_t
fifo_used( fifo_t * f );

/* -------------------------------------------------------------------------- */

/** Returns the amount of free space in the fifo. */

PUBLIC uint32_t
fifo_free( fifo_t * f );

/* ----- End ---------------------------------------------------------------- */

#ifdef    __cplusplus
}
#endif
#endif /* FIFO_H */
