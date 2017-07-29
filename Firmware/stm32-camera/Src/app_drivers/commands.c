/**
 * @file    commands.c
 *
 * @brief   Command line command processors.
 *
 *          Used by tasks like Application Task Monitor to parse and
 *          execute commands.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <inttypes.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "commands.h"
#include "state_event.h"
#include "app_tasks.h"
#include "app_events.h"
#include "event_subscribe.h"
#include "qassert.h"
#include "app_task_camera.h"
#include "app_task_file_system.h"
#include "app_task_ids.h"
#include "app_signals.h"
#include "app_events.h"
#include "auxiliary.h"
#include "board_sensor.h"
#include "config.h"
#include "ff_error_msg.h"
#include "ff.h"
#include "file_util.h"
#include "filesystem.h"
#include "hal_adc.h"
#include "hal_delay.h"
#include "hal_firmware_update.h"
#include "hal_power.h"
#include "hal_sd.h"
#include "hal_uuid.h"
#include "hal_systick.h"
#include "minIni.h"
#include "system_speed.h"
#include "tick_timer.h"

/* ----- Private Functions -------------------------------------------------- */

/** AUXILIARY PORT COMMANDS */
PRIVATE bool command_auxiliary_gpio_out( CmdHandler *me );
PRIVATE bool command_auxiliary_gpio_in( CmdHandler *me );
PRIVATE bool command_auxiliary_gpio_mode( CmdHandler *me );

/** CAMERA COMMANDS */
PRIVATE bool command_camera_flash_level( CmdHandler *me );
PRIVATE bool command_camera_flash_off( CmdHandler *me );
PRIVATE bool command_camera_flash_on( CmdHandler *me );
PRIVATE bool command_camera_flash_timed( CmdHandler *me );
PRIVATE bool command_camera_on( CmdHandler *me );
PRIVATE bool command_camera_off( CmdHandler *me );
PRIVATE bool command_camera_capture( CmdHandler *me );

/** BOARD SENSORS */
PRIVATE bool command_board( CmdHandler *me );

/** CONFIG LOG COMMANDS */
PRIVATE bool command_config_log( CmdHandler *me );
PRIVATE bool command_log( CmdHandler *me );
PRIVATE uint16_t command_log_set_mask( CmdHandler *me, uint16_t system_mask, uint16_t log_mask );

/** DEBUG COMMANDS */
PRIVATE bool command_type( CmdHandler *me );

/** INI COMMANDS */
PRIVATE bool command_ini_browse( CmdHandler *me );
PRIVATE bool command_ini_puts( CmdHandler *me );

/** FILE COMMANDS */
PRIVATE bool command_cd( CmdHandler *me );
PRIVATE bool command_chdrive( CmdHandler *me );
PRIVATE bool command_copy( CmdHandler *me );
PRIVATE bool command_cwd( CmdHandler *me );
PRIVATE bool command_dir( CmdHandler *me );
PRIVATE bool command_del( CmdHandler *me );
PRIVATE bool command_mkdir( CmdHandler *me );
PRIVATE bool command_mv( CmdHandler *me );
PRIVATE bool command_rmdir( CmdHandler *me );

/** SD COMMANDS */
PRIVATE bool command_sd_present( CmdHandler *me );
PRIVATE bool command_sd_mount( CmdHandler *me );
PRIVATE bool command_sd_unmount( CmdHandler *me );

/** SYSTEM COMMANDS */
PRIVATE bool command_system_uuid( CmdHandler *me );
PRIVATE bool command_system_tasks( CmdHandler *me );
PRIVATE bool command_system_speed( CmdHandler *me );
PRIVATE bool command_system_upgrade_firmware( CmdHandler *me );

/* -------------------------------------------------------------------------- */

/** AUXILIARY GPIO COMMANDS */
PRIVATE const CmdEntry AuxiliaryGpioCmdTable[] =
{
    CmdEntryAction(  "in",
                     command_auxiliary_gpio_in,
                     "input status" ),
    CmdEntryAction(  "mode",
                     command_auxiliary_gpio_mode,
                     "mode setting" ),
    CmdEntryAction(  "out",
                     command_auxiliary_gpio_out,
                     "output control" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** CAMERA FLASH COMMANDS */
PRIVATE const CmdEntry CameraFlashCmdTable[] =
{
    CmdEntryAction(  "level",
                     command_camera_flash_level,
                     "flash level" ),
    CmdEntryAction(  "off",
                     command_camera_flash_off,
                     "flash OFF" ),
    CmdEntryAction(  "on",
                     command_camera_flash_on,
                     "flash ON" ),
    CmdEntryAction(  "timed",
                     command_camera_flash_timed,
                     "flash on for ms" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** CAMERA COMMANDS */
PRIVATE const CmdEntry CameraCmdTable[] =
{
    CmdEntryAction(  "capture",
                     command_camera_capture,
                     "take picture" ),
    CmdEntrySubMenu( "flash",
                     CameraFlashCmdTable,
                     "flash level, off & on" ),
    CmdEntryAction(  "off",
                     command_camera_off,
                     "camera OFF" ),
    CmdEntryAction(  "on",
                     command_camera_on,
                     "camera ON" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** SYSTEM COMMANDS */
PRIVATE const CmdEntry SystemCmdTable[] =
{
	CmdEntryAction(  "log",
					 command_config_log,
					 "get/set system log level" ),

    CmdEntryAction(  "speed",
                     command_system_speed,
                     "show system speed mode" ),

    CmdEntryAction(  "tasks",
                     command_system_tasks,
                     "show tasks status" ),

    CmdEntryAction(  "upgrade",
                     command_system_upgrade_firmware,
                     "upgrade the firmware" ),

    CmdEntryAction(  "uuid",
                     command_system_uuid,
                     "display system Unique Universal ID" ),

    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** INI COMMANDS */
PRIVATE const CmdEntry IniCmdTable[] =
{
    CmdEntryAction(  "browse",
                     command_ini_browse,
                     "scan the indicated ini file contents" ),
    CmdEntryAction(  "puts",
                     command_ini_puts,
                     "write a section/key/value item to an ini file" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** SD COMMANDS */
PRIVATE const CmdEntry SdCmdTable[] =
{
    CmdEntryAction(  "mount",
                     command_sd_mount,
                     "mount SD file system" ),

    CmdEntryAction(  "present",
                     command_sd_present,
                     "check if an SD card is present" ),

    CmdEntryAction(  "unmount",
                     command_sd_unmount,
                     "unmount SD file system" ),

    CmdEntryTerminator()
};

/** TOP LEVEL COMMANDS - PUBLIC REFERENCE */


PRIVATE const CmdEntry topCmdTable[] =
{
    CmdEntrySubMenu( "auxiliary io",
                     AuxiliaryGpioCmdTable,
                     "control auxiliary port items" ),

    CmdEntryAction(  "board",
                     command_board,
                     "show board sensor data" ),

    CmdEntrySubMenu( "camera",
                     CameraCmdTable,
                     "camera control" ),

    CmdEntryAction(  "cd",
                     command_cd,
                     "change directory" ),

    CmdEntryAction(  "chdrive",
                     command_chdrive,
                     "change drive" ),

    CmdEntryAction(  "copy",
                     command_copy,
                     "copy a file" ),

    CmdEntryAction(  "cwd",
                     command_cwd,
                     "show the current working directory" ),

    CmdEntryAction(  "del",
                     command_del,
                     "delete the indicated file" ),

    CmdEntryAction(  "dir",
                     command_dir,
                     "show the indicated directory" ),

    CmdEntrySubMenu( "ini",
                     IniCmdTable,
                     "manage & view ini files" ),

    CmdEntryAction(  "log",
                     command_log,
                     "set system logging to  terminal" ),

    CmdEntryAction(  "mkdir",
                     command_mkdir,
                     "create the indicated directory" ),

    CmdEntryAction(  "mv",
                     command_mv,
                     "rename a file" ),

    CmdEntryAction(  "rmdir",
                     command_rmdir,
                     "remove the indicated directory" ),

    CmdEntrySubMenu( "sd",
                     SdCmdTable,
                     "manage SD card" ),

    CmdEntrySubMenu( "system",
                     SystemCmdTable,
                     "system control commands" ),

    CmdEntryAction(  "type",
                     command_type,
                     "print the file contents to the terminal" ),

    CmdEntryTerminator()
};


/* -------------------------------------------------------------------------- */

PUBLIC const CmdEntry *commands = topCmdTable;


/* -------------------------------------------------------------------------- */
/* --- AUXILIARY COMMANDS --------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PRIVATE bool command_auxiliary_gpio_out( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 3 )
    {
        uint8_t pin   = (uint8_t)cmd_get_argv_int( me, 1 );
        bool    on    = cmd_get_argv_int( me, 2 ) > 0;
        auxiliary_gpio_out( pin, on );
        cmd_printf( me, "AUX[%d] = %s\r\n",
                        pin,
                        on ? "HIGH" : "LOW");
    }
    else
    {
        cmd_printf( me, "Usage: aux out [pin] [0|1]\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_auxiliary_gpio_in( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        uint8_t pin = (uint8_t)cmd_get_argv_int( me, 1 );
        cmd_printf( me, "AUX[%d] = %s\r\n",
                        pin,
                        auxiliary_gpio_in( pin ) ? "HIGH" : "LOW");
    }
    else
    {
        cmd_printf( me, "Usage: aux in [pin]\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_auxiliary_gpio_mode( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 3 )
    {
        uint8_t pin  = (uint8_t)cmd_get_argv_int( me, 1 );
        uint8_t mode = (uint8_t)cmd_get_argv_int( me, 2 );
        auxiliary_gpio_mode( pin, ( mode == 0 ) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT_PP );
        cmd_printf( me, "AUX[%d] mode %s\r\n",
                        pin,
                        mode == 0 ? "INPUT" : "OUTPUT" );
    }
    else
    {
        cmd_printf( me, "Usage: aux gpio mode [pin] [dir]\r\n" );
    }
    return true;
}


/* -------------------------------------------------------------------------- */
/* --- CAMERA COMMANDS ------------------------------------------------------ */
/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_capture( CmdHandler *me )
{
	cmd_printf( me, "camera capture\r\n" );

	appTaskCameraTakePictureNormal();

    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_level( CmdHandler *me )
{
    uint8_t level = 0;
    if( cmd_get_argc( me ) > 1 )
    {
        level = (uint8_t)cmd_get_argv_int( me, 1 );
    }

    cmd_printf( me, "Camera FLASH level %d%%\r\n", level );
    return true;
}
/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_off( CmdHandler *me )
{
    cmd_printf( me, "Flash OFF\r\n" );
    //TODO Disable flash output
    return true;
}
/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_on( CmdHandler *me )
{
    cmd_printf( me, "Flash ON\r\n" );
    //TODO Enable flash output
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_timed( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        uint16_t flashtime = (uint16_t)cmd_get_argv_int( me, 1 );
        cmd_printf( me, "Flashed for %dms\r\n", flashtime );
        //TODO Enable flash output
        hal_delay_ms( flashtime );
        //TODO Disable flash output
    }
    else
    {
        cmd_printf( me, "Usage: camera flash timed [ms]\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_off( CmdHandler *me )
{
    cmd_printf( me, "Camera OFF\r\n" );
    eventPublish( EVENT_NEW( StateEvent, CAMERA_CMD_OFF ) );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_on( CmdHandler *me )
{
    cmd_printf( me, "Camera ON\r\n" );
    eventPublish( EVENT_NEW( StateEvent, CAMERA_CMD_ON ) );
    return true;
}

/* -------------------------------------------------------------------------- */
/* --- LOG COMMANDS --------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PRIVATE bool
command_config_log( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        config_log_set_level( (LOG_LEVEL)cmd_get_argv_int( me, 1 ) );
    }
    cmd_printf( me, "Current log mask: 0x%04X\r\n",
                                      config_log_level() );
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief  Helper command to print logging messages via the terminal output
 *         channel when the appropriate mask is set.
 * @return void
 */
PRIVATE void
command_log_output( LOG_SUB_SYSTEM system_mask,
                    LOG_LEVEL      log_mask,
                    const char     * message,
                    void           * userdata )
{
    CmdHandler *me = (CmdHandler*)userdata;
    if( ( ( me->LogMask >> 16 ) & system_mask )
        &&
        ( me->LogMask & log_mask ) )
    {
        cmd_printf( me, "%04X-%02X: %s", system_mask, log_mask, message );
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
command_log_set_mask( CmdHandler *me, uint16_t system_mask,
                                      uint16_t log_mask )
{
    me->LogMask   = ( (uint32_t)system_mask << 16 ) | (uint32_t)log_mask;

    if( me->LogMask )
    {
        log_add_output( command_log_output, (void*)me );
    }
    else
    {
        log_clear_output( command_log_output, (void*)me );
    }
    return (uint16_t)me->LogMask;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_log( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        command_log_set_mask( me, 0xFFFF,
                                  (uint16_t)cmd_get_argv_int( me, 1 ) );
    }
    else if( cmd_get_argc( me ) == 3 )
    {
        command_log_set_mask( me, (uint16_t)cmd_get_argv_int( me, 2 ),
                                  (uint16_t)cmd_get_argv_int( me, 1 ) );
    }

    cmd_printf( me,
                "Current terminal log mask: 0x%04lX-0x%04lX\r\n",
                me->LogMask >> 16,
                me->LogMask & 0xFFFF );

    for( uint16_t i = 0; i < 8; i++ )
    {
        uint16_t level = (uint16_t)(me->LogMask & _BV(i));
        if( level )
        {
            cmd_printf( me,
                        " Level   0x%02X - %s\r\n",
                        level,
                        log_get_mask_level_label( level ) );
        }
    }

    for( uint16_t i = 0; i < 16; i++ )
    {
        uint16_t system = (uint16_t)((me->LogMask >> 16) & _BV(i));
        if( system )
        {
            cmd_printf( me,
                        "System 0x%04X - %s\r\n",
                        system,
                        log_get_sub_system_label( system ) );
        }
    }

    return true;
}

/* -------------------------------------------------------------------------- */
/* --- DIRECTORY COMMANDS  -------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/**
 * @brief   Print a textual description of the file I/O result with the
 *          error message is needed.
 * @param   err FRESULT error code.
 * @return  void
 */
PRIVATE void
command_print_fatfs_result( CmdHandler *me, uint16_t err )
{
    if( err == FR_OK )
    {
        cmd_printf( me, "%s", f_error_msg( err ) );
    }
    else
    {
        cmd_printf( me, "ERR %d: %s", err, f_error_msg( err ) );
    }

    cmd_printf( me, "\r\n" );
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Change directory.
 * @return  true when command done.
 */
PRIVATE bool
command_cd( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        FRESULT f_result;
        f_result = f_chdir( (TCHAR*)cmd_get_argv( me, 1 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: cd <filename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Change drive.
 * @return  true when command done.
 */
PRIVATE bool
command_chdrive( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        FRESULT f_result;
        f_result = f_chdrive( (TCHAR*)cmd_get_argv( me, 1 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: chdrive <drive>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Show a directory listing.
 * @return  true when command done.
 */
PRIVATE bool
command_dir( CmdHandler *me )
{
    FRESULT res;
    FILINFO fno;
    static DIR dir;
    TCHAR *fn;   /* This function is assuming non-Unicode cfg. */
    static TCHAR lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
    fno.lfname = lfn;
    fno.lfsize = sizeof lfn;
    static char    path[32];

    if( !me->flags.cmdInitDone )
    {
        if( cmd_get_argc( me ) == 2 )
        {
            strncpy( path,
                     cmd_get_argv( me, 1 ),
                     sizeof( path ) - 1 );
        }
        else
        {
            f_getcwd( (TCHAR*)path, sizeof(path) );
        }

        /* Open the directory */
        res = f_opendir( &dir, (TCHAR*)path );
        me->flags.cmdInitDone = true;
        if( res != FR_OK )
        {
            command_print_fatfs_result( me, res );
            return true;
        }
    }

    /* Read a directory item */
    res = f_readdir(&dir, &fno);

    /* Done on error or end of dir */
    if (res != FR_OK || fno.fname[0] == 0)
    {
        command_print_fatfs_result( me, res );
        return true;
    }

    /* Ignore dot entry */
    if (fno.fname[0] == '.')
    {
        return false;
    }

    fn = *fno.lfname ? fno.lfname : fno.fname;

    // Print date
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    file_util_get_fat_date( fno.fdate, &year, &month, &day );
    cmd_printf( me, "%2d/%02d/%4d ", day, month, year );

    // Print time
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    file_util_get_fat_time( fno.ftime, &hour, &min, &sec );
    cmd_printf( me, "%2d:%02d:%02d ", hour, min, sec );

    // Print attributes
    if( fno.fattrib & AM_RDO )
        cmd_printf( me, "r" );
    else
        cmd_printf( me, "." );

    if( fno.fattrib & AM_HID )
        cmd_printf( me, "h" );
    else
        cmd_printf( me, "." );

    if( fno.fattrib & AM_ARC )
        cmd_printf( me, "a" );
    else
        cmd_printf( me, "." );

    if( fno.fattrib & AM_SYS )
        cmd_printf( me, "s" );
    else
        cmd_printf( me, "." );

    if (fno.fattrib & AM_DIR)
        cmd_printf( me, " <DIR> " );
    else
        cmd_printf( me, "       " );

    cmd_printf( me, "%9ld ", fno.fsize );
    if( path[strlen(path)-1] == '/' )
    {
        cmd_printf( me, "%s%s\r\n", path, (char*)fn);
    }
    else
    {
        cmd_printf( me, "%s/%s\r\n", path, (char*)fn);
    }

    // Go back and do next entry
    return false;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Copy a file
 * @return  true when command done.
 */
PRIVATE bool
command_copy( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 3 )
    {
        FRESULT f_result;
        if( !me->flags.cmdInitDone )
        {
            f_result = filesystem_copy_src( cmd_get_argv( me, 1 ) );
            if ( f_result != FR_OK )
            {
                cmd_printf( me,
                            "Cant't open source file: %s =>" ,
                            cmd_get_argv( me, 1 ));
                command_print_fatfs_result( me, f_result );
                return true;
            }
            f_result = filesystem_copy_dst( cmd_get_argv( me, 2 ) );
            if( f_result != FR_OK )
            {
                cmd_printf( me,
                            "Cant't open destination file: %s => ",
                            cmd_get_argv( me, 2 ) );
                command_print_fatfs_result( me, f_result );
                return true;
            }

            cmd_printf( me,
                        "copying \"%s\" => \"%s\"\r\n",
                        cmd_get_argv( me, 1 ),
                        cmd_get_argv( me, 2 ) );

            me->flags.cmdInitDone = true;
            return false;
        }
        else
        {
            if( filesystem_copy_process() )
            {
                static uint8_t last_progress;
                uint8_t progress = filesystem_copy_progress();
                if( last_progress != progress )
                {
                    cmd_printf( me, "\r%d%%", progress );
                    last_progress = progress;
                }
                return false; /* Still busy */
            }
            else
            {
                cmd_printf( me, "\r    \r" );
                f_result = filesystem_copy_status();
                command_print_fatfs_result( me, f_result );
                return true;
            }
        }
        return true;
    }
    else
    {
        cmd_printf( me, "Usage: copy <srcfile> <dstfile>\r\n" );
        return true;
    }
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Show the current working directory.
 * @return  true when command done.
 */
PRIVATE bool
command_cwd( CmdHandler *me )
{
    FRESULT f_result;
    char    path[64];
    f_result = f_getcwd( (TCHAR*)path, sizeof(path) );
    if( f_result == FR_OK )
        cmd_printf( me, "%s\r\n", path );
    else
        command_print_fatfs_result( me, f_result );
    return true;

}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Create a new directory.
 * @return  true when command done.
 */
PRIVATE bool
command_mkdir( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        FRESULT f_result;
        f_result = f_mkdir( (TCHAR*)cmd_get_argv( me, 1 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: mkdir <filename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Rename a file.
 * @return  true when command done.
 */
PRIVATE bool
command_mv( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 3 )
    {
        FRESULT f_result;
        f_result = f_rename( (TCHAR*)cmd_get_argv( me, 1 ),
                             (TCHAR*)cmd_get_argv( me, 2 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: mv <oldfilename> <newfilename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Delete a directory.
 * @return  true when command done.
 */
PRIVATE bool
command_rmdir( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        FRESULT f_result;
        f_result = f_unlink( (TCHAR*)cmd_get_argv( me, 1 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: rmdir <path>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Deleted the indicated file.e
 * @return  true when command done.

 */
PRIVATE bool
command_del( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        FRESULT f_result;
        f_result = f_unlink( (TCHAR*)cmd_get_argv( me, 1 ) );
        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: del <filename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Type the content of a file.
 * @return  true when command done.
 */
PRIVATE bool
command_type( CmdHandler *me )
{
    static FIL file;
    FRESULT    res;
    char       buffer[80];

    if( !me->flags.cmdInitDone )
    {
        if( cmd_get_argc( me ) == 2 )
        {
            /* Open the file */
            res = f_open( &file,
                          (TCHAR*)cmd_get_argv( me, 1 ),
                          FA_READ | FA_OPEN_EXISTING );
            if ( res != FR_OK )
            {
                command_print_fatfs_result( me, res );
                return true;
            }
            else
            {
                cmd_printf( me, "File %s:\r\n",
                                cmd_get_argv( me, 1 ) );
            }
        }
        else
        {
            cmd_printf( me, "Usage: type <filename>\r\n" );
            return true;
        }
        me->flags.cmdInitDone = true;
    }

    if( f_gets( (TCHAR*)buffer, sizeof(buffer), &file ) != NULL )
    {
        cmd_printf( me, "%s", buffer );
        return false;
    }
    return true;
}

/* -------------------------------------------------------------------------- */
/* --- SD COMMANDS ---------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/**
 * @brief   Request a mount of the USB file system
 * @return  true when command done.
 */
PRIVATE bool
command_sd_mount( CmdHandler *me )
{
    cmd_printf( me, "SD mount TODO!\r\n" );
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Detect SD card
 * @return  true when command done.
 */

PRIVATE bool
command_sd_present( CmdHandler *me )
{
    cmd_printf( me,
                "SD card %s\r\n",
                hal_sd_is_present() ? "DETECTED" : "NOT DETECTED" );
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief   Request a unmount of the SD file system
 * @return  true when command done.
 */
PRIVATE bool
command_sd_unmount( CmdHandler *me )
{
    cmd_printf( me, "SD unmount TODO!\r\n" );
    return true;
}

/* -------------------------------------------------------------------------- */
/* --- INI COMMANDS --------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/**
 * @brief  Support function for Servercommand_ini_browse to show
 *         content of an INI file using the ini_browse function.
 * @param  section  the section being parsed
 * @param  key      the key within that section being read
 * @param  value    the string value of the key in this section
 * @param  userdata pointer to user data passed to the callback. Not used.
 * @return 1 to indicate ini_browse needs to keep going.
 */
PRIVATE int
command_ini_browse_callback( const char * section,
                             const char * key,
                             const char * value,
                             const void * userdata )
{
    CmdHandler *me = (CmdHandler*)userdata;
    cmd_printf( me, "[%s] %s=%s\r\n", section, key, value );
    return 1;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief  Browse the content of an indicated INI file.
 * @return true when command is done.
 */
PRIVATE bool
command_ini_browse( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        ini_browse( command_ini_browse_callback,
                    me,
                    cmd_get_argv( me, 1 ) );
    }
    else
    {
        cmd_printf( me, "Usage: ini browse <filename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/**
 * @brief  Set a string value in an INI file via section / key / value.
 * @return true when command is done.
 */
PRIVATE bool
command_ini_puts( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 5 )
    {
        if( ini_puts( cmd_get_argv( me, 2 ),
                      cmd_get_argv( me, 3 ),
                      cmd_get_argv( me, 4 ),
                      cmd_get_argv( me, 1 ) ) )
        {
           cmd_printf( me, "OK\r\n" );
        }
        else
        {
           cmd_printf( me, "ERROR\r\n" );
        }
    }
    else
    {
        cmd_printf( me, "Usage: ini puts <filename> <section> <key> <value>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */
/* --- SYSTEM COMMANDS ------------------------------------------------------ */
/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_tasks( CmdHandler *me )
{
    cmd_printf( me, " Id:         Name:  St: Burst: Wait:  Que: Max:\r\n" );
    for( uint8_t id = (TASK_MAX-1); id > 0; id-- )
    {
        StateTask *t = app_task_by_id( id );
        if( t )
        {
            cmd_printf( me,
                        "% 3d, %12s,   %s,  % 4ld, % 4ld,  % 3d,  % 3d\r\n",
                        t->id,
                        t->name,
                        t->ready ? "R" : "-",
                        t->burst_max,
                        t->waiting_max,
                        t->eventQueue.used,
                        t->eventQueue.max );
        }
    }
    if( cmd_get_argc( me ) > 1 )
    {
        app_task_clear_statistics();
    }
    return true;
}

/* -------------------------------------------------------------------------- */

/** UUID COMMANDS */
PRIVATE bool command_system_uuid( CmdHandler *me )
{
    cmd_printf( me,
                "UUID: %08lX-%08lX-%08lX\r\n",
                HAL_UUID[0],
                HAL_UUID[1],
                HAL_UUID[2] );

    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_speed( CmdHandler *me )
{
    if( cmd_get_argc( me ) > 1 )
    {
        system_speed_set( ( cmd_get_argv_int( me, 1 ) > 0 )
                          ? SYSTEM_SPEED_FULL
                          : SYSTEM_SPEED_LOW_POWER );
    }
    cmd_printf( me, "System speed: %s\r\n", system_speed_get()
                                            ? "FULL"
                                            : "LOW POWER" );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_upgrade_firmware( CmdHandler *me )
{
	cmd_printf( me, "Firmware upgrade starting...\r\n" );
	hal_firmware_update();

    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_board( CmdHandler *me )
{
    board_sensor_enable();

    hal_delay_ms( 50 );

    cmd_printf( me, "Temp:    % 2.1fC\r\n", board_sensor_temperature_C() );

    return true;
}
/* ----- End ---------------------------------------------------------------- */
