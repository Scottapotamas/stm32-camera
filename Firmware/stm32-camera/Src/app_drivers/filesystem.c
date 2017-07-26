/**
 * @file      filesystem.c
 *
 * @brief     Filesystems in use.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* -------------------------------------------------------------------------- */

#include "global.h"
#include "filesystem.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/* -------------------------------------------------------------------------- */

#define BUFFER_SIZE       4096

/* -------------------------------------------------------------------------- */

PRIVATE FATFS             fs_fatfs[ NUM_FILE_SYSTEMS ];
PRIVATE FileSystemSpace_t fs_space[ NUM_FILE_SYSTEMS ];
PRIVATE char              fs_path[ NUM_FILE_SYSTEMS ][ 4 ];

/* -------------------------------------------------------------------------- */

PRIVATE FRESULT   f_result;
PRIVATE FIL       * src    = NULL;
PRIVATE FIL       * dst    = NULL;
PRIVATE uint8_t   * buffer = NULL;

/* -------------------------------------------------------------------------- */

PUBLIC void
filesystem_init( void  )
{
	FATFS_LinkDriver( &SD_Driver, fs_path[ SD_DRIVE ] );
}

/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
filesystem_mount( FileSystem_t filesystem )
{
    FRESULT result = FR_INVALID_PARAMETER;

    if( filesystem < NUM_FILE_SYSTEMS )
    {
        result = f_mount( &fs_fatfs[filesystem],
                          (TCHAR*)fs_path[filesystem],
                          1 );

        if( result == FR_OK )
        {
            DWORD free_clusters;
            FATFS *fs;

            f_chdrive( (TCHAR*)fs_path[filesystem] );

            /* Get total and free space in KiB */
            result = f_getfree( (TCHAR*)fs_path[filesystem],
                                 &free_clusters,
                                 &fs );

            if( result == FR_OK )
            {
                fs_space[filesystem].total_KiB = ((fs->n_fatent - 2) * fs->csize) / 2;
                fs_space[filesystem].free_KiB  = (free_clusters * fs->csize) / 2;
            }
        }
    }

    return result;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
filesystem_unmount( FileSystem_t filesystem )
{
    FRESULT result = FR_INVALID_PARAMETER;

    if( filesystem < NUM_FILE_SYSTEMS )
    {
        result = f_mount( NULL, (TCHAR*)fs_path[filesystem], 0 );
        fs_space[filesystem].total_KiB = 0;
        fs_space[filesystem].free_KiB  = 0;
    }

    return result;
}

/* -------------------------------------------------------------------------- */

PUBLIC const char *
filesystem_path( FileSystem_t filesystem )
{
    char * p = "";
    if( filesystem < NUM_FILE_SYSTEMS )
    {
        p = fs_path[filesystem];
    }
    return p;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
filesystem_space( FileSystem_t filesystem )
{
    uint32_t space = 0;
    if( filesystem < NUM_FILE_SYSTEMS )
    {
        space = fs_space[filesystem].total_KiB;
    }
    return space;
}

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
filesystem_free( FileSystem_t filesystem )
{
    uint32_t free = 0;
    if( filesystem < NUM_FILE_SYSTEMS )
    {
        free = fs_space[filesystem].free_KiB;
    }
    return free;
}

/* -------------------------------------------------------------------------- */

/* File Copy Support */

PUBLIC uint8_t
filesystem_copy_src( const char * sourcefile )
{
    src = (FIL*)malloc( sizeof(FIL) );
    f_result = f_open( src, (TCHAR*)sourcefile, FA_READ | FA_OPEN_EXISTING );
    return f_result;
}

PUBLIC uint8_t
filesystem_copy_dst( const char * dstfile )
{
    dst = (FIL*)malloc( sizeof(FIL) );
    f_result = f_open( dst, (TCHAR*)dstfile, FA_WRITE | FA_CREATE_ALWAYS );
    return f_result;
}

PUBLIC bool
filesystem_copy_process( void )
{
    UINT   bytesread;
    UINT   byteswritten;

    if( !buffer )
    {
        buffer = (uint8_t*)malloc( BUFFER_SIZE );
    }

    if( buffer )
    {
        f_result = f_read( src,
                           buffer,
                           BUFFER_SIZE,
                           &bytesread );

        if( f_result == FR_OK )
        {
            f_result = f_write( dst,
                                buffer,
                                bytesread,
                                &byteswritten );

            f_sync( dst );

            if( f_result == FR_OK )
            {
                if( bytesread != BUFFER_SIZE )
                {
                    f_close( src );
                    free( src );
                    src = NULL;
                    f_close( dst );
                    free( dst );
                    dst = NULL;
                    free( buffer );
                    buffer= NULL;
                    /* Done */
                    return false;
                }
                else
                {
                    /* More to copy */
                    return true;
                }
            }
            else
            {
                /* Fail */
                f_close( src );
                free( src );
                src = NULL;
                f_close( dst );
                free( dst );
                dst = NULL;
                free( buffer );
                buffer= NULL;
                return false;
            }
        }
        else
        {
            /* Fail */
            f_close( src );
            free( src );
            src = NULL;
            f_close( dst );
            free( dst );
            dst = NULL;
            free( buffer );
            buffer= NULL;
            return false;
        }
    }
    return false;
}

PUBLIC uint8_t
filesystem_copy_progress( void )
{
    if( src )
    {
        uint64_t ptr = src->fptr;
        uint64_t size = src->fsize;
        return ptr * 100 / size;
    }
    return 0;
}

PUBLIC uint8_t
filesystem_copy_status( void )
{
    return f_result;
}

/* ----- End ---------------------------------------------------------------- */


