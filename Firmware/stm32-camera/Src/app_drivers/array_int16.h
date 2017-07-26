/**
 * @file      array_int16.h
 *
 * @brief     Calculations for short term averaging
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef ARRAY_INT16_H
#define ARRAY_INT16_H

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

typedef struct
{
    uint16_t    size;           /* Number of values to average */
    uint16_t    count;          /* Current number of samples available */
    uint16_t    index;          /* Index in sample buffer */

    uint16_t    average;        /* Current average */
    uint16_t    last;           /* Last added value */
    uint16_t    deviation;      /* Spread between the minimum and maximum values */
    uint32_t    sum;            /* Sum of samples */
    int16_t     *values;
} ArrayInt16_t;

/* -------------------------------------------------------------------------- */

/** Reset an averaging buffer and set the required span (number of values)
 *  over which to average).
 *
 *  Span has to be equal or less than AVERAGE_SHORT_SPAN.
 */

PUBLIC void
array_int16_init( ArrayInt16_t *me,
                  int16_t      *array,
                  uint16_t      size );

/* -------------------------------------------------------------------------- */

PUBLIC void
array_int16_update( ArrayInt16_t * me, int16_t value );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_size( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_count( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_space( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
array_int16_index( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

/** Get the last added value from the samples buffer */

PUBLIC int16_t
array_int16_last( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

/** Get the current average from the actual samples buffer */

PUBLIC int16_t
array_int16_average( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

/** Get the current maximum from the actual samples buffer */

PUBLIC int16_t
array_int16_maximum( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

/** Get the current minimum from the actual samples buffer */

PUBLIC int16_t
array_int16_minimum( ArrayInt16_t * me );

/* -------------------------------------------------------------------------- */

/** Get the deviation from average on the current samples buffer */

PUBLIC int16_t
array_int16_deviation( ArrayInt16_t * me );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_INT16_H */
