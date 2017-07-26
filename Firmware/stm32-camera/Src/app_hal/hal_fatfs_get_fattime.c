/**
 * @file  hal_fatfs_get_fattime.c
 *
 * @brief Glue function for FAT file system to obtain current time.
 *        Uses the system time as returned from time().
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/*------------------------ System includes -----------------------------------*/

#include <time.h>

/*------------------------ Local includes ------------------------------------*/

#include "global.h"
#include "diskio.h"
#include "ff.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief      Get a current time for use when creating and updating files
 * @param[in]  none
 * @return     DWORD with time stamp encoded as follows:
 *               - bit31:25 => Year from 1980 (0..127)
 *               - bit24:21 => Month (1..12)
 *               - bit20:16 => Day in month(1..31)
 *               - bit15:11 => Hour (0..23)
 *               - bit10:5  => Minute (0..59)
 *               - bit4:0   => Second / 2 (0..29)
 */

//DWORD get_fattime(void)
//{
//	DWORD       fattime = 0;
//    time_t      utc_time = hal_rtc_time( NULL );
//    struct tm * sys_tm = localtime( &utc_time ); // LOCAL TIMEZONE!
//
//    // Only use year when time returned a year later than 1980
//    if( (sys_tm->tm_year + 1900) >= 1980 )
//    {
//        fattime |= (DWORD)(sys_tm->tm_year + 1900 - 1980) << 25;
//    }
//    fattime	|= (DWORD)(sys_tm->tm_mon + 1)  << 21;
//    fattime |= (DWORD)(sys_tm->tm_mday) << 16;
//    fattime |= (DWORD)(sys_tm->tm_hour) << 11;
//    fattime |= (DWORD)(sys_tm->tm_min)  << 5;
//    fattime |= (DWORD)(sys_tm->tm_sec)  >> 1;
//
//	return fattime;
//}

/* -------------------------------------------------------------------------- */
