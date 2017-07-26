/**
 * @file    hal_fatfs_diskio_ram.c
 *
 * @brief   Low level disk I/O for FAT file system in code space.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright
 *          (c) 2013-2014 EnviroVision Pty. Ltd. - All rights reserved.
 */

/*------------------------ System includes ---------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*------------------------ Local Includes ----------------------------------- */

#include "global.h"
#include "hal_fatfs_diskio_ram.h"

/* -------------------------------------------------------------------------- */

#define HAL_RAM_DISK_SECTOR_SIZE    (512)
#define HAL_RAM_DISK_1MB            (1024*2*HAL_RAM_DISK_SECTOR_SIZE)
#define HAL_RAM_DISK_SIZE           (HAL_RAM_DISK_1MB*10)   /* 10 MB */

/* -------------------------------------------------------------------------- */

 /* Disk Status */
PRIVATE volatile DSTATUS ram_disk_status = STA_NOINIT;
//PRIVATE uint8_t *ram_disk_buffer;
PRIVATE uint32_t ram_disk_size;

/* -------------------------------------------------------------------------- */

DSTATUS hal_fatfs_diskio_ram_initialise( void )
{
    if( ram_disk_status != STA_NOINIT )
    {
        return ram_disk_status;     /* Mem variables already set */
    }

    /* Reset */
    ram_disk_status = STA_NOINIT;

//    ram_disk_buffer = malloc( HAL_RAM_DISK_SIZE );
//    ram_disk_size   = HAL_RAM_DISK_SIZE;
//
//    /* Check if we got a valid, atleast 4K sized buffer */
//    if( !ram_disk_buffer || ram_disk_size < 4096 )
//    {
//        return ram_disk_status;
//    }
//
//    ram_disk_status &= ~STA_NOINIT;

    return ram_disk_status;
}

/* -------------------------------------------------------------------------- */

DSTATUS hal_fatfs_diskio_ram_status( void )
{
    return ram_disk_status;
}

/* -------------------------------------------------------------------------- */

DRESULT hal_fatfs_diskio_ram_read( BYTE *buff  __attribute__((__unused__)),
                                   DWORD sector  __attribute__((__unused__)),
                                   BYTE count )
{
    if( ! (count > 0) )
    {
        return RES_PARERR;
    }

    if( ram_disk_status & STA_NOINIT )
    {
        return RES_NOTRDY;
    }

//    memcpy( buff, ram_disk_buffer + (sector * HAL_RAM_DISK_SECTOR_SIZE), HAL_RAM_DISK_SECTOR_SIZE * count );

    return RES_OK;
}

/* -------------------------------------------------------------------------- */

DRESULT hal_fatfs_diskio_ram_write( const BYTE *buff  __attribute__((__unused__)),
                                    DWORD      sector __attribute__((__unused__)),
                                    BYTE       count )
{
    if( ! (count > 0) )
    {
        return RES_PARERR;
    }

    if (ram_disk_status & STA_NOINIT)
    {
        return RES_NOTRDY;
    }

//    memcpy( ram_disk_buffer + (sector * HAL_RAM_DISK_SECTOR_SIZE), buff, HAL_RAM_DISK_SECTOR_SIZE * count );

    return RES_OK;
}

/* -------------------------------------------------------------------------- */

DRESULT hal_fatfs_diskio_ram_ioctl(	BYTE cmd,
                                    void *buff )
{
    DRESULT res;

    if( ram_disk_status & STA_NOINIT )
    {
        return RES_NOTRDY;
    }

    res = RES_ERROR;

    switch( cmd )
    {
        case CTRL_SYNC: /* Make sure that no pending write process */
            res = RES_OK;
            break;

        case GET_SECTOR_COUNT: /* Get number of sectors on the disk (DWORD) */
            *(DWORD *) buff = ram_disk_size / HAL_RAM_DISK_SECTOR_SIZE;
            res = RES_OK;
            break;

        case GET_SECTOR_SIZE: /* Get R/W sector size (WORD) */
            *(WORD *) buff = HAL_RAM_DISK_SECTOR_SIZE; // 512;
            res = RES_OK;
            break;

        case GET_BLOCK_SIZE:/* Get erase block size in unit of sector (DWORD) */
            *(DWORD *) buff = HAL_RAM_DISK_SECTOR_SIZE; // FIXED:
            res = RES_OK;
            break;

        default:
            res = RES_PARERR;
            break;
    }
    return res;
}

/* -------------------------------------------------------------------------- */
