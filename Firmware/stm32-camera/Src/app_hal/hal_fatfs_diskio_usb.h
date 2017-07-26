/**
 * @file      hal_fatfs_diskio_usb.h
 *
 * @brief     Low level disk I/O for FAT file system in USB memory.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef HAL_FATFS_DISKIO_USB_H
#define HAL_FATFS_DISKIO_USB_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----------------------- Local includes -----------------------------------*/

#include "diskio.h"

/* -------------------------------------------------------------------------- */

/**
 * @brief   Initialise the USB disk
 * @return  Status of disk
 */
DSTATUS
hal_fatfs_diskio_usb_initialise( void );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Get USB disk status
 * @return  Status of disk
 */
DSTATUS
hal_fatfs_diskio_usb_status( void );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Read USB disk sectors
 * @param   buff    Data to be store read data
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to read (1..128)
 * @return  Status of read
 */
DRESULT
hal_fatfs_diskio_usb_read( BYTE *buff,
                           DWORD sector,
                           BYTE count );

/* -------------------------------------------------------------------------- */

/**
 * @brief   Wite USB disk sectors
 * @param   buff    Data to be written
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to write (1..128)
 * @return  Status of write
 */
DRESULT
hal_fatfs_diskio_usb_write( const BYTE *buff,
                            DWORD sector,
                            BYTE count );

/* -------------------------------------------------------------------------- */

/**
 * @brief   USB disk IOCTL
 * @param   pdrv    Physical drive number (0..)
 * @param   cmd     Control code
 * @param   buff    Buffer to send/receive control data
 * @return  Status of IOCTL
 */
 DRESULT
 hal_fatfs_diskio_usb_ioctl( BYTE ctrl,
                             void *buff );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_FATFS_DISKIO_USB_H */
