/**
 * @file      hal_fatfs_diskio_ram.h
 *
 * @brief     Low level disk I/O interface for FAT file system in RAM space for
 *            testing purposes. Most likely in the PC environment as the
 *            embedded system is unlikely to have enough RAM to be usefull as
 *            a disk.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_FATFS_DISKIO_RAM_H
#define HAL_FATFS_DISKIO_RAM_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "diskio.h"	    /* FatFs lower layer API */

/* -------------------------------------------------------------------------- */

/**
 * @brief   Initialise the ram disk (nothing really)
 * @return  Status of disk
 */
DSTATUS hal_fatfs_diskio_ram_initialise( void );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Get ram disk status (flagged as Write Protected)
 * @return  Status of disk
 */
DSTATUS hal_fatfs_diskio_ram_status( void );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Read ram disk sectors
 * @param   buff    Data to be store read data
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to read (1..128)
 * @return  Status of read
 */
DRESULT hal_fatfs_diskio_ram_read( BYTE *buff,
                                   DWORD sector,
                                   BYTE count );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Write ram disk sectors (not really. ram is write protected)
 * @param   buff    Data to be written
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to write (1..128)
 * @return  Status of write
 */
DRESULT hal_fatfs_diskio_ram_write( const BYTE *buff,
                                    DWORD sector,
                                    BYTE count );

/* -------------------------------------------------------------------------- */

/**
 * @brief   ram disk IOCTL
 * @param   cmd     Control code
 * @param   buff    Buffer to send/receive control data
 * @return  Status of IOCTL
 */
DRESULT hal_fatfs_diskio_ram_ioctl( BYTE cmd,
                                    void *buff );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_FATFS_DISKIO_RAM_H */
