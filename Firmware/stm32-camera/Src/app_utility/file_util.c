/**
 * @file      file_util.c
 *
 * @brief     Utility functions to parse file and path names.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/*------------------------ System includes ---------------------------------- */

#include <string.h>

/*------------------------ System includes ---------------------------------- */

#include "file_util.h"

/* -------------------------------------------------------------------------- */

PUBLIC const char *
file_util_get_filename( const char *filename )
{
    const char *dot = strrchr(filename, '/');
    
    if( !dot || dot == filename )
        return "";

    return dot + 1;
}

/* -------------------------------------------------------------------------- */

PUBLIC const char *
file_util_get_filename_ext( const char *filename )
{
    const char *dot = strrchr( filename, '.' );

    if( !dot || dot == filename )
        return "";

    return dot + 1;
}

/* -------------------------------------------------------------------------- */
PUBLIC void
file_util_get_fat_date( const uint16_t fatdate,
                        uint16_t *year,
                        uint8_t  *month,
                        uint8_t  *day )
{
    // 111111
    // 5432109876543210
    // yyyyyyymmmmddddd

    *year  = (fatdate >> 9) + 1980;
    *month = (fatdate >> 5) & 0xF;
    *day   = (fatdate & 0x1F);
}

/* -------------------------------------------------------------------------- */

PUBLIC void
file_util_get_fat_time( const uint16_t fattime,
                        uint8_t *hour,
                        uint8_t *min,
                        uint8_t *sec )
{
    // 111111
    // 5432109876543210
    // hhhhhmmmmmmsssss

    *hour = (fattime >> 11)  & 0x1F;
    *min  = (fattime >> 5)   & 0x3F;
    *sec  = (fattime & 0x1F) * 2;
}

/* -------------------------------------------------------------------------- */
