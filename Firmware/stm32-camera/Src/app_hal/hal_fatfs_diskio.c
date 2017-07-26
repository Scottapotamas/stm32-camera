/**
* @file       hal_fatfs_diskio.c
 *
 * @brief     Custom fatfs diskio.c for supporting both a ROM based
 *            READ-ONLY FAT file system for internal files and a USB based file
 *            system for when we have the UBS stick inserted.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----------------------- Local includes -----------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */

#define FATFS_RAM_DISK_ENABLED
#define FATFS_ROM_DISK_ENABLED
#define FATFS_USB_DISK_ENABLED

/* Drive Numbers For Media */
#define ROM_DISK		0
#define USB_DISK		1
#define RAM_DISK		2

#ifdef FATFS_RAM_DISK_ENABLED
#include "hal_fatfs_diskio_ram.h"	/* RAM disk */
#endif

#ifdef FATFS_USB_DISK_ENABLED
#include "hal_fatfs_diskio_usb.h"	/* USB disk */
#endif

/* -------------------------------------------------------------------------- */

/**
 * @brief   Initialise the disk
 * @param   pdrv    Physical drive number (0..)
 * @return  Status of disk
 */
//DSTATUS disk_initialize( BYTE pdrv )
//{
//    DSTATUS stat;
//    int result;
//
//    switch (pdrv)
//    {
//#ifdef FATFS_RAM_DISK_ENABLED
//        case RAM_DISK :
//            result = hal_fatfs_diskio_ram_initialise();
//            stat = result;
//            break;
//#endif
//#ifdef FATFS_ROM_DISK_ENABLED
//        case ROM_DISK :
//            result = hal_fatfs_diskio_rom_initialise();
//            stat = result;
//            break;
//#endif
//#ifdef FATFS_USB_DISK_ENABLED
//        case USB_DISK :
//            result = hal_fatfs_diskio_usb_initialise();
//            stat = result;
//            break;
//#endif
//        default:
//            stat = STA_NODISK;
//            break;
//    }
//    return stat;
//}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Get disk status
 * @param   pdrv    Physical drive number (0..)
 * @return  Status of disk
 */
//DSTATUS disk_status( BYTE pdrv )
//{
//    DSTATUS stat;
//    int result;
//
//    switch (pdrv)
//    {
//#ifdef FATFS_RAM_DISK_ENABLED
//        case RAM_DISK:
//            result = hal_fatfs_diskio_ram_status();
//            stat = result;
//            break;
//#endif
//#ifdef FATFS_ROM_DISK_ENABLED
//        case ROM_DISK:
//            result = hal_fatfs_diskio_rom_status();
//            stat = result;
//            break;
//#endif
//#ifdef FATFS_USB_DISK_ENABLED
//        case USB_DISK:
//            result = hal_fatfs_diskio_usb_status();
//            stat = result;
//            break;
//#endif
//        default:
//            stat = STA_NOINIT;
//    }
//    return stat;
//}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Read disk sectors
 * @param   pdrv    Physical drive number (0..)
 * @param   buff    Data to be store read data
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to read (1..128)
 * @return  Status of read
 */

//DRESULT disk_read( BYTE pdrv,
//                   BYTE *buff,
//                   DWORD sector,
//                   UINT count )
//{
//    DRESULT res;
//    int result;
//
//    switch (pdrv)
//    {
//#ifdef FATFS_RAM_DISK_ENABLED
//        case RAM_DISK :
//            result = hal_fatfs_diskio_ram_read(buff, sector, count);
//            res = result;
//            break;
//#endif
//#ifdef FATFS_ROM_DISK_ENABLED
//        case ROM_DISK :
//            result = hal_fatfs_diskio_rom_read(buff, sector, count);
//            res = result;
//            break;
//#endif
//#ifdef FATFS_USB_DISK_ENABLED
//        case USB_DISK :
//            result = hal_fatfs_diskio_usb_read(buff, sector, count);
//            res = result;
//            break;
//#endif
//        default:
//            res = RES_PARERR;
//            break;
//    }
//    return res;
//}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Write disk sectors
 * @param   pdrv    Physical drive number (0..)
 * @param   buff    Data to be written
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to write (1..128)
 * @return  Status of write
 */
//DRESULT disk_write( BYTE       pdrv,
//                    const BYTE *buff,
//                    DWORD      sector,
//                    UINT       count )
//{
//    DRESULT res;
//    int result;
//
//    switch( pdrv )
//    {
//#ifdef FATFS_RAM_DISK_ENABLED
//        case RAM_DISK :
//            result = hal_fatfs_diskio_ram_write( buff, sector, count );
//            res = result;
//            break;
//#endif
//#ifdef FATFS_ROM_DISK_ENABLED
//        case ROM_DISK :
//            result = hal_fatfs_diskio_rom_write( buff, sector, count );
//            res = result;
//            break;
//#endif
//#ifdef FATFS_USB_DISK_ENABLED
//        case USB_DISK :
//            result = hal_fatfs_diskio_usb_write( buff, sector, count );
//            res = result;
//            break;
//#endif
//        default:
//            res = RES_PARERR;
//            break;
//    }
//    return res;
//}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Disk IOCTL
 * @param   pdrv    Physical drive number (0..)
 * @param   cmd     Control code
 * @param   buff    Buffer to send/receive control data
 * @return  Status of IOCTL
 */
//DRESULT disk_ioctl ( BYTE pdrv,
//                     BYTE cmd,
//                     void *buff	)
//{
//    DRESULT res;
//    int result;
//
//    switch (pdrv)
//    {
//#ifdef FATFS_RAM_DISK_ENABLED
//        case RAM_DISK:
//            result = hal_fatfs_diskio_ram_ioctl(cmd, buff);
//            res = result;
//            break;
//#endif
//#ifdef FATFS_ROM_DISK_ENABLED
//        case ROM_DISK:
//            result = hal_fatfs_diskio_rom_ioctl(cmd, buff);
//            res = result;
//            break;
//#endif
//#ifdef FATFS_USB_DISK_ENABLED
//        case USB_DISK :
//            result = hal_fatfs_diskio_usb_ioctl(cmd, buff);
//            res = result;
//            break;
//#endif
//        default:
//            res = RES_PARERR;
//            break;
//    }
//    return res;
//}

/* -------------------------------------------------------------------------- */
