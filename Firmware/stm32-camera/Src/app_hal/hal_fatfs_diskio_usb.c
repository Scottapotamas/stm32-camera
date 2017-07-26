/**
 * @file  hal_diskio_usb.c
 *
 * @brief Low level disk I/O for FAT file system on USB media.
 *        Uses the low level STM USB Host interfaces.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

//#include "USB/usb.h"
//#include "USB/usb_host_msd.h"
//#include "USB/usb_host_msd_scsi.h"
//#include "ff.h"
#include "hal_fatfs_diskio_usb.h"
//#include "hardware/led.h"

/* -------------------------------------------------------------------------- */

DSTATUS hal_fatfs_diskio_usb_initialise( void )
{
//    if( !USBHostMSDSCSIMediaInitialize() )
//    {
        return STA_NODISK;
//    }
//    return 0;
}

/* -------------------------------------------------------------------------- */

DSTATUS hal_fatfs_diskio_usb_status ( void )
{
//    if( !USBHostMSDSCSIMediaDetect() )
//    {
        return STA_NODISK;
//    }
//    return 0;
}

/* -------------------------------------------------------------------------- */

DRESULT hal_fatfs_diskio_usb_read( BYTE *buff   __attribute__((__unused__)),
                                   DWORD sector __attribute__((__unused__)),
                                   BYTE count   __attribute__((__unused__)) )
{
//    int     nSector;
    DRESULT status = RES_OK;

//    uint16_t oldLedLevel = ledGetCurrentPWM( LED_USB );
//    ledSetCurrentPWM( LED_USB, LED_PWM_MAX );
//
//    for( nSector = 0; nSector < count; nSector++ )
//    {
//        if( !USBHostMSDSCSISectorRead(sector, buff) )
//        {
            status = RES_NOTRDY;
//            break;
//        }
//        sector++;
//        buff += 512;
//    }
//
//    ledSetCurrentPWM( LED_USB, oldLedLevel );

    return status;
 }

/* -------------------------------------------------------------------------- */

/**
 * @brief   Wite USB disk sectors
 * @param   buff    Data to be written
 * @param   sector  Sector address (LBA)
 * @param   count   Number of sectors to write (1..128)
 * @return  Status of write
 */
 DRESULT hal_fatfs_diskio_usb_write( const BYTE *buff  __attribute__((__unused__)),
                                     DWORD sector      __attribute__((__unused__)),
                                     BYTE count        __attribute__((__unused__)) )
 {
//    int     nSector;
    DRESULT status = RES_OK;

//    uint16_t oldLedLevel = ledGetCurrentPWM( LED_USB );
//    ledSetCurrentPWM( LED_USB, LED_PWM_MAX );
//
//    for( nSector = 0; nSector < count; nSector++ )
//    {
//        if( !USBHostMSDSCSISectorWrite(sector, (BYTE *)buff,0) )
//        {
            status = RES_NOTRDY;
//            break;
//        }
//        sector++;
//        buff += 512;
//    }
//
//    ledSetCurrentPWM( LED_USB, oldLedLevel );

    return status;
}

/* -------------------------------------------------------------------------- */

DRESULT hal_fatfs_diskio_usb_ioctl ( BYTE ctrl,
                                     void *buff )
{
    switch(ctrl)
    {
        case GET_SECTOR_SIZE:
            *(WORD *)buff = 512;
            return RES_OK;

        case CTRL_SYNC:
            return RES_OK;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = 0; // Number of sectors on the volume
            return RES_OK;

        case GET_BLOCK_SIZE:
            return RES_OK;
    }
    return RES_PARERR;
}

/* ----- End ---------------------------------------------------------------- */
