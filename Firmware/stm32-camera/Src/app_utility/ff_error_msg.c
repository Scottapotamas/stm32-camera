/**
 * @file      ff_error_msg.c
 *
 * @brief     print FatFs error codes as messages.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- Local Includes ----------------------------------------------------- */

#include "ff_error_msg.h"

/* -------------------------------------------------------------------------- */

/** Message strings corresponding to the FRESULT codes */
PRIVATE const char *    fresult_messages[] =
{
    "OK",                       //   0: FR_OK
    "Disk I/O Error",           //   1: FR_DISK_ERR
    "Internal Error",           //   2: FR_INT_ERR
    "Not Ready",                //   3: FR_NOT_READY
    "File Not Found",           //   4: FR_NO_FILE
    "Path Not Found",           //   5: FR_NO_PATH
    "Invalid Path",             //   6: FR_INVALID_NAME
    "Access Denied",            //   7: FR_DENIED
    "Already Exist",            //   8: FR_EXIST
    "Invalid Object",           //   9: FR_INVALID_OBJECT
    "Write Protected",          //  10: FR_WRITE_PROTECTED
    "Invalid Drive Number",     //  11: FR_INVALID_DRIVE
    "No Volume Work Area",      //  12: FR_NOT_ENABLED
    "No Valid FAT Volume",      //  13: FR_NO_FILESYSTEM
    "MKFS Aborted",             //  14: FR_MKFS_ABORTED
    "Timeout",                  //  15: FR_TIMEOUT
    "Locked",                   //  16: FR_LOCKED
    "Not Enough Buffers",       //  17: FR_NOT_ENOUGH_CORE
    "Too Many Open Files",      //  18: FR_TOO_MANY_OPEN_FILES
    "Invalid Parameter",        //  19: FR_INVALID_PARAMETER
};

/* -------------------------------------------------------------------------- */

/**
 * @brief  Returns a pointer to a text message representing the err code.
 * @param  err FRESULT code
 * @return const string pointer with error message.
 */
PUBLIC const char *
f_error_msg( FRESULT err )
{
    // Return valid error message when in range
    if( err <= FR_INVALID_PARAMETER )
    {
        return fresult_messages[ err ];
    }

    // Return default "Internal Error" message when err not in range.
    return fresult_messages[ FR_INT_ERR ];
}

/* ----- End ---------------------------------------------------------------- */

