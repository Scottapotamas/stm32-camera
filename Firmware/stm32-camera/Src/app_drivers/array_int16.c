/**
 * @file      array_int16.c
 *
 * @brief     Special array/buffer handling that operate like a FIFO and
 *            allows collecting avg, min, max and deviations from that FIFO.
 *            Only operates on actual values in the FIFO and rotates when it
 *            full.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <stdlib.h>
#include <math.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "array_int16.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* -------------------------------------------------------------------------- */

PUBLIC void
array_int16_init( ArrayInt16_t * me, int16_t *array, uint16_t size )
{
    /* Clear the structure */
    memset( me, 0 , sizeof(ArrayInt16_t) );

    /* Init the buffer reference and the size */
    me->values = array;
    me->size   = size;

    /* Clear the array */
    memset( me->values, 0 , sizeof(int16_t) * size );
}

/* -------------------------------------------------------------------------- */

PUBLIC void
array_int16_update( ArrayInt16_t * me, int16_t value )
{
    me->last = value;

    /* Add new value to index */
    me->values[ me->index ] = value;

    /* Loop index */
    if( ++me->index >= me->size )
    {
        me->index = 0;
    }

    /* Update count up to size */
    if( me->count < me->size )
    {
        me->count++;
    }
}

/* -------------------------------------------------------------------------- */

/** Get the size of the array */

PUBLIC uint16_t
array_int16_size( ArrayInt16_t * me )
{
    return me->size;
}

/* -------------------------------------------------------------------------- */

/** Get the number of elements currently in the array */

PUBLIC uint16_t
array_int16_count( ArrayInt16_t * me )
{
    return me->count;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_space( ArrayInt16_t * me )
{
    return me->size - me->count;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_index( ArrayInt16_t * me )
{
    return me->index;
}

/* -------------------------------------------------------------------------- */

/** Get the last added value from the samples buffer */

PUBLIC int16_t
array_int16_last( ArrayInt16_t * me )
{
    return me->last;
}

/* -------------------------------------------------------------------------- */

/** Get the last added value from the samples buffer */

PUBLIC int16_t
array_int16_average( ArrayInt16_t * me )
{
    if( me->count )
    {
        int32_t sum = 0;
        for( uint16_t i = 0; i < me->count; i++ )
        {
            sum += me->values[i];
        }
        return sum / me->count;
    }
    else
    {
        return 0;
    }
}

/* -------------------------------------------------------------------------- */

/** Get the current maximum from the actual samples buffer */

PUBLIC int16_t
array_int16_maximum( ArrayInt16_t * me )
{
    if( me->count )
    {
        int16_t max = INT16_MIN;
        for( uint16_t i = 0; i < me->count; i++ )
        {
            max = MAX( max, me->values[i] );
        }
        return max;
    }
    else
    {
        return 0;
    }
}

/* -------------------------------------------------------------------------- */

/** Get the current minimum from the actual samples buffer */

PUBLIC int16_t
array_int16_minimum( ArrayInt16_t * me )
{
    if( me->count )
    {
        int16_t min = INT16_MAX;
        for( uint16_t i = 0; i < me->count; i++ )
        {
            min = MIN( min, me->values[i] );
        }
        return min;
    }
    else
    {
        return 0;
    }
}

/* -------------------------------------------------------------------------- */

/** Get the deviation from average on the current samples buffer */

PUBLIC int16_t
array_int16_deviation( ArrayInt16_t * me )
{
    if( me->count )
    {
        int32_t tmp = 0;
        int16_t avg = array_int16_average( me );
        for( uint16_t i = 0; i < me->count; i++ )
        {
            int32_t diff = me->values[i] - avg;
            tmp += (diff * diff);
        }
        return sqrt( tmp );
    }
    else
    {
        return 0;
    }
}

/* ----- End ---------------------------------------------------------------- */
