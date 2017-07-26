/**
 * @file      file_util.h
 *
 * @brief     Utility functions for manipulating file names
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef FILE_UTIL_H
#define	FILE_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
    
/* -------------------------------------------------------------------------- */

PUBLIC const char *
file_util_get_filename( const char *filename );

PUBLIC const char *
file_util_get_filename_ext( const char *filename );

PUBLIC void
file_util_get_fat_date( const uint16_t fatdate, 
                        uint16_t *year,
                        uint8_t  *month,
                        uint8_t  *day );

PUBLIC void
file_util_get_fat_time( const uint16_t fattime,
                        uint8_t *hour,
                        uint8_t *min,
                        uint8_t *sec );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* FILE_UTIL_H */

