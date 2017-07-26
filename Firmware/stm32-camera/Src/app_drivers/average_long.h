/**
 * @file      average_long.h
 *
 * @brief     Calculations for long term averaging (bufferless)
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef AVERAGE_LONG_H
#define AVERAGE_LONG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"

/* ----- Defines ------------------------------------------------------------ */

/* ----- Types -------------------------------------------------------------- */

/** Structure to keep track of long term averages
  * (e.g. 60 minutes to 24 hours. Declare the below structure and memset
  * to 0 to initialise. Then call average long with a pointer to the
  * storage struct and the new value to be averaged. New values are to be
  * inserted every minute or so and an approximation (as we don't keep a
  * buffer of historic values) of a running average is calculated.
  *
  * The average from this function almost follows an RC filter type curve
  * with the span value creating 1 RC time = (SPAN/SQRT(2)). A step response
  * then sees the average reach 50% of the step in 1 RC time, the next RC time
  * a further 50% of the difference and reaching 97% after 5 RC times.
  *
  * For example a span of 30 has an RC time of 21 where it reaches 50% and
  * reaches 97% at moment 106.
  */
typedef struct
{
    uint16_t    span;           /* Number of values to average */
    uint16_t    counter;        /* Current number of samples available */
    uint32_t    sum;            /* Sum of samples */
    uint16_t    average;        /* Current average */
} AverageLong_t;

/* -------------------------------------------------------------------------- */

/** Init an AverageLong_t buffer and set the required span (number of values)
 *  over which to average.
 */

PUBLIC void
average_long_init( AverageLong_t * me, uint16_t span );

/* -------------------------------------------------------------------------- */

/** Update the average with a new value and return the average so far returned.
 *
 *  Average is calculated from the sum of all the update values so far
 *  without keeping a buffer. When the max span is reached, the current
 *  average is subtracted from this sum and then the new value is added
 *  again.
 */

PUBLIC uint16_t
average_long_update( AverageLong_t * me, uint16_t new );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
average_long_get_count( const AverageLong_t * me );

/* -------------------------------------------------------------------------- */

/** Get the current average  */

PUBLIC uint16_t
average_long_get_average( const AverageLong_t * me );

/* -------------------------------------------------------------------------- */

/** Hard reset the average value to a new value.
 */

PUBLIC void
average_long_set_average( AverageLong_t * me, uint16_t new_average );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* AVERAGE_LONG_H */
