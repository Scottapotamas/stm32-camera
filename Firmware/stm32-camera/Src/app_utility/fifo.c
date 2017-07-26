/**
 * @file      fifo.c
 *
 * @ingroup   utility
 *
 * @brief     Basic buffer based FIFO facility
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "fifo.h"

/* ----- Public Functions --------------------------------------------------- */

/** This initializes the FIFO structure with the given buffer and size */

PUBLIC void
fifo_init( fifo_t * f, uint8_t * buf, uint32_t buf_size )
{
     f->head = 0;
     f->tail = 0;
     f->capacity = buf_size;
     f->buf = buf;
}

/* -------------------------------------------------------------------------- */

/** Reads nbytes bytes from the FIFO. The number of bytes read is returned */

PUBLIC uint32_t
fifo_read( fifo_t * f, void * buf, uint32_t nbytes )
{
     uint32_t i;
     char * p;
     p = buf;
     for(i=0; i < nbytes; i++)
     {
          if( f->tail != f->head )
          { //see if any data is available
               *p++ = f->buf[f->tail];  //grab a byte from the buffer
               f->tail++;  //increment the tail
               if( f->tail == f->capacity )
               {  //check for wrap-around
                    f->tail = 0;
               }
          }
          else
          {
               return i; //number of bytes read
          }
     }
     return nbytes;
}

/* -------------------------------------------------------------------------- */

/** Writes up to nbytes bytes to the FIFO
 *  If the head runs in to the tail, not all bytes are written
 *  The number of bytes written is returned
 */

PUBLIC uint32_t
fifo_write( fifo_t * f, const void * buf, uint32_t nbytes )
{
    uint32_t i;
    const char * p;
    p = buf;
    for( i = 0; i < nbytes; i++ )
    {
        //first check to see if there is space in the buffer
        if( ( f->head + 1 == f->tail )
            ||
            ( (f->head + 1 == f->capacity) && (f->tail == 0) ) )
        {
            return i; //no more room
        }
        else
        {
            f->buf[f->head] = *p++;
            f->head++;  //increment the head
            if( f->head == f->capacity )
            {  //check for wrap-around
                f->head = 0;
            }
        }
    }
    return nbytes;
}

/* -------------------------------------------------------------------------- */

/** Returns the amount of data in use in the fifo.
  * This can be at max the capacity less 1
  */

PUBLIC uint32_t
fifo_used( fifo_t * f )
{
    int32_t used = (int32_t)f->head - (int32_t)f->tail;
    if( used >= 0 )
    {
        return (uint32_t)used;
    }
    else
    {
        return (uint32_t)(used + f->capacity);
    }
}

/* -------------------------------------------------------------------------- */

/** Returns the amount of data free in the fifo. */

PUBLIC uint32_t
fifo_free( fifo_t * f )
{
    int32_t used = (int32_t)f->head - (int32_t)f->tail;
    if( used < 0 )
    {
        used += f->capacity;
    }
    return f->capacity - used - 1;
}

/* ----- End ---------------------------------------------------------------- */
