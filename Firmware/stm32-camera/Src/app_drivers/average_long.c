/**
 * @file      average_long.c
 *
 * @brief     Calculations for long term averaging (bufferless)
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <stdlib.h>
#include <math.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "average_long.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* -------------------------------------------------------------------------- */

/** Init an AverageLong_t buffer and set the required span (number of values)
 *  over which to average.
 */

PUBLIC void
average_long_init( AverageLong_t * me,  uint16_t span )
{
    /* Span must be sensible */
    //REQUIRE( span > 0 );

    /* Clear the structure */
    memset( me, 0 , sizeof(AverageLong_t) );

    /* Init the span */
    me->span = span;
}

/* -------------------------------------------------------------------------- */

/** Update the average with a new value and return the average so far returned.
 *
 *  Average is calculated from the sum of all the update values so far
 *  without keeping a buffer. When the max span is reached, the current
 *  average is subtracted from this sum and then the new value is added
 *  again.
 */

PUBLIC uint16_t
average_long_update( AverageLong_t * me, uint16_t new )
{
    /* Increase the number of samples captured */
    if( me->counter < me->span )
    {
        me->counter++;
    }
    else
    {
        /* We have a full set of samples, subtract the current average
         * from the sum of samples.
         */
        me->sum -= me->average;
    }

    /* Add the new value to the sum */
    me->sum += new;

    /* Calculate new average */
    me->average = me->sum / me->counter;

    return me->average;
}

/* -------------------------------------------------------------------------- */

/** Get the current count  */

PUBLIC uint16_t
average_long_get_count( const AverageLong_t * me )
{
    return me->counter;
}

/* -------------------------------------------------------------------------- */

/** Get the current average  */

PUBLIC uint16_t
average_long_get_average( const AverageLong_t * me )
{
    return me->average;
}

/* -------------------------------------------------------------------------- */

/** Hard reset the average value to a new value.
 */

PUBLIC void
average_long_set_average( AverageLong_t * me, uint16_t new_average )
{
    me->sum = me->counter * new_average;
    me->average = new_average;
}

/* ----- End ---------------------------------------------------------------- */
