/**
 * @file        minGlue.h
 *
 * @brief       Glue functions for the minIni library, allows to compile
 *              for FatFs (default) or with stdio for use on PC when
 *              __USE_PC_FILE_II is defined.
 *
 * @author      Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright   (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef MIN_INI_GLUE_H
#define	MIN_INI_GLUE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------- Defines ------------------------------------------ */

#define INI_BUFFERSIZE  256      /* maximum line length, maximum path length */

/* ----------------------- Mapping Functions -------------------------------- */

#ifdef __USE_PC_FILE_IO

    /* ------------------- Stdio Glue Mapping ------------------------------- */

    #include <stdio.h>

    #define INI_FILETYPE                  FILE*
    #define ini_openread(filename,file)   ((*(file) = fopen((filename),"rb")) != NULL)
    #define ini_openwrite(filename,file)  ((*(file) = fopen((filename),"wb")) != NULL)
    #define ini_close(file)               (fclose(*(file)) == 0)
    #define ini_read(buffer,size,file)    (fgets((buffer),(size),*(file)) != NULL)
    #define ini_write(buffer,file)        (fputs((buffer),*(file)) >= 0)
    #define ini_rename(source,dest)       (rename((source), (dest)) == 0)
    #define ini_remove(filename)          (remove(filename) == 0)

    #define INI_FILEPOS                   fpos_t
    #define ini_tell(file,pos)            (fgetpos(*(file), (pos)) == 0)
    #define ini_seek(file,pos)            (fsetpos(*(file), (pos)) == 0)

    // Ensure that minIni uses a line termination that
    // is MS-Windows notepad friendly.
    #define INI_LINETERM                  "\r\n"

    /* for floating-point support, define additional types and functions */
    #define INI_REAL                      float
    #define ini_ftoa(string,value)        sprintf((string),"%f",(value))
    #define ini_atof(string)              (INI_REAL)strtod((string),NULL)

#else

    /* ------------------- FatFs Glue Mapping ------------------------------- */

    #include "ff.h"
    #include "ff_gen_drv.h"
    #include "sd_diskio.h"
    #include "minIni_rename.h"

    #define INI_FILETYPE                  FIL
    #define ini_openread(filename,file)   (f_open((file), ((TCHAR*)filename), FA_READ|FA_OPEN_EXISTING) == FR_OK)
    #define ini_openwrite(filename,file)  (f_open((file), ((TCHAR*)filename), FA_WRITE|FA_CREATE_ALWAYS) == FR_OK)
    #define ini_close(file)               (f_close(file) == FR_OK)
    #define ini_read(buffer,size,file)    f_gets(((TCHAR*)buffer), (size),(file))
    #define ini_write(buffer,file)        f_puts(((TCHAR*)buffer), (file))
    #define ini_remove(filename)          (f_unlink((TCHAR*)filename) == FR_OK)

    #define INI_FILEPOS                   DWORD
    #define ini_tell(file,pos)            (*(pos) = f_tell((file)))
    #define ini_seek(file,pos)            (f_lseek((file), *(pos)) == FR_OK)

    // Enable rational number support
    #define INI_REAL                      float
    #define ini_ftoa(string,value)        sprintf((string),"%f",(double)(value))
    #define ini_atof(string)              (INI_REAL)strtod((string),NULL)

    // Ensure that minIni uses a line termination that
    // is MS-Windows notepad friendly. FatFS is configured with _USE_STRFUNC 1
    // which does not do the "\n" to "\r\n" translation so we only need "\r\n" here.
    #define INI_LINETERM                  "\r\n"

    // Enable custom version of 'strnicmp' as it does not exist in PIC32 libs.
    #define PORTABLE_STRNICMP

#endif

/* ----------------------- End ---------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* MIN_INI_GLUE_H */

