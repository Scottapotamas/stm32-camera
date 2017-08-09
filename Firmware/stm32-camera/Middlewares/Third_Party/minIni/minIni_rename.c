/**
 * @file        minIni_rename.c
 *
 * @brief       minINi support for renaming a file with fatfs.
 *
 * @author      Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright   (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----------------------- System includes ---------------------------------- */

#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/* ----------------------- Local Includes ----------------------------------- */

#include "minIni_rename.h"

/* ----------------------- Start implementation ----------------------------- */

int ini_rename(TCHAR *source, const TCHAR *dest)
{
  TCHAR *drive = (TCHAR*)strchr((char*)dest, ':');
  drive = (drive == NULL) ? (TCHAR*)dest : drive + 1;
  return (f_rename(source, drive) == FR_OK);
}

/* ----------------------- End ---------------------------------------------- */

