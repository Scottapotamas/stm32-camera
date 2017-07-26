/** @file     minIni_rename.h
 *
 * @brief     minIni support for renaming a file with fatfs.
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef MIN_INI_RENAME_H
#define MIN_INI_RENAME_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------- System includes ----------------------------------*/

#include "minIni.h"

/* ----------------------- Functions Specifications -------------------------*/

/**
* @brief Rename a file. Used when writing ini files that are first copied
*        and then renamed. In FatFs there is a problem in the rename in that
*        it does not allow a drive letter in the destination file.
* @param[in] source   Source file name
* @param[in] dest   Destination file name
* @return int8_t
*/

int ini_rename( TCHAR *source, const TCHAR *dest );

/* ----------------------- End ---------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* MIN_INI_RENAME_H */

