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
#include "ir_filter.h"
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
#include "app_version.h"
#include "hal_systick.h"
#include "minIni.h"
#include "cmd.h"
#include "system_speed.h"
#include "hal_system_speed.h"
#include "tick_timer.h"
#include "hal_camera.h"

/* ----- Private Functions -------------------------------------------------- */

/** AUXILIARY PORT COMMANDS */
PRIVATE bool command_aux_gpio_out( CmdHandler *me );
PRIVATE bool command_aux_gpio_in( CmdHandler *me );
PRIVATE bool command_aux_gpio_mode( CmdHandler *me );

/** CAMERA COMMANDS */
PRIVATE bool command_camera_flash_level( CmdHandler *me );
PRIVATE bool command_camera_flash_off( CmdHandler *me );
PRIVATE bool command_camera_flash_on( CmdHandler *me );
PRIVATE bool command_camera_flash_timed( CmdHandler *me );
PRIVATE bool command_camera_on( CmdHandler *me );
PRIVATE bool command_camera_off( CmdHandler *me );
PRIVATE bool command_camera_capture( CmdHandler *me );

PRIVATE bool command_camera_filter( CmdHandler *me );

/** BOARD SENSORS */
PRIVATE bool command_sensor_on( CmdHandler *me );
PRIVATE bool command_sensor_off( CmdHandler *me );
PRIVATE bool command_sensor_read( CmdHandler *me );

/** CONFIG LOG COMMANDS */
PRIVATE bool command_config_log( CmdHandler *me );
PRIVATE bool command_log( CmdHandler *me );
//PRIVATE uint16_t command_log_set_mask( CmdHandler *me, uint16_t system_mask, uint16_t log_mask );

/** DEBUG COMMANDS */
PRIVATE bool command_type( CmdHandler *me );

/** INI COMMANDS */
PRIVATE bool command_config_read( CmdHandler *me );
PRIVATE bool command_config_write( CmdHandler *me );

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
PRIVATE bool command_sd_format( CmdHandler *me );

/** SYSTEM COMMANDS */
PRIVATE bool command_system_uuid( CmdHandler *me );
PRIVATE bool command_system_tasks( CmdHandler *me );
PRIVATE bool command_system_clock( CmdHandler *me );
PRIVATE bool command_system_load( CmdHandler *me );
PRIVATE bool command_system_speed( CmdHandler *me );
PRIVATE bool command_system_upgrade_firmware( CmdHandler *me );
PRIVATE bool command_system_info( CmdHandler *me );
PRIVATE bool command_system_reboot( CmdHandler *me );

/* -------------------------------------------------------------------------- */

/** AUXILIARY GPIO COMMANDS */
PRIVATE const CmdEntry AuxGpioCmdTable[] =
{
    CmdEntryAction(  "in",
                     command_aux_gpio_in,
                     "input status" ),
    CmdEntryAction(  "mode",
                     command_aux_gpio_mode,
                     "mode setting" ),
    CmdEntryAction(  "out",
                     command_aux_gpio_out,
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
    CmdEntryAction( "filter",
                    command_camera_filter,
                    "filter control" ),
    CmdEntryAction(  "off",
                     command_camera_off,
                     "camera OFF" ),
    CmdEntryAction(  "on",
                     command_camera_on,
                     "camera ON" ),
    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** SD COMMANDS */
PRIVATE const CmdEntry SensorCmdTable[] =
{
    CmdEntryAction(  "on",
    				 command_sensor_on,
                     "enable onboard sensors" ),

    CmdEntryAction(  "off",
                     command_sensor_off,
                     "disable onboard sensors" ),

    CmdEntryAction(  "read",
                     command_sensor_read,
                     "print board sensors" ),

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

	CmdEntryAction(  "clock",
					 command_system_clock,
					 "show cpu clock frequency" ),

	CmdEntryAction(  "load",
					 command_system_load,
					 "show cpu utilisation" ),

    CmdEntryAction(  "tasks",
                     command_system_tasks,
                     "show tasks status" ),

    CmdEntryAction(  "upgrade",
                     command_system_upgrade_firmware,
                     "upgrade the firmware" ),

    CmdEntryAction(  "uuid",
                     command_system_uuid,
                     "display system Unique Universal ID" ),

	CmdEntryAction(  "info",
					 command_system_info,
					 "display system version information" ),

	CmdEntryAction(  "reboot",
					 command_system_reboot,
					 "restart the system" ),

    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** INI COMMANDS */
PRIVATE const CmdEntry ConfigCmdTable[] =
{
    CmdEntryAction(  "read",
                     command_config_read,
                     "scan the indicated ini file contents" ),
    CmdEntryAction(  "write",
                     command_config_write,
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

	CmdEntryAction(  "format",
					 command_sd_format,
					 "format the SD card" ),

    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** SD COMMANDS */
PRIVATE const CmdEntry FileCmdTable[] =
{
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

	CmdEntryAction(  "mkdir",
					 command_mkdir,
					 "create the indicated directory" ),

	CmdEntryAction(  "mv",
					 command_mv,
					 "rename a file" ),

	CmdEntryAction(  "rmdir",
					 command_rmdir,
					 "remove the indicated directory" ),

	 CmdEntryAction(  "type",
					  command_type,
					  "print the file contents to the terminal" ),

    CmdEntryTerminator()
};

/* -------------------------------------------------------------------------- */

/** TOP LEVEL COMMANDS - PUBLIC REFERENCE */
PRIVATE const CmdEntry topCmdTable[] =
{
    CmdEntrySubMenu( "aux",
                     AuxGpioCmdTable,
                     "control auxiliary pins" ),

	CmdEntrySubMenu( "sensor",
                     SensorCmdTable,
                     "control/view board sensors" ),

    CmdEntrySubMenu( "camera",
                     CameraCmdTable,
                     "camera control" ),

    CmdEntrySubMenu( "config",
                     ConfigCmdTable,
                     "manage & view configuration files" ),

	CmdEntrySubMenu( "file",
					 FileCmdTable,
					 "filesystem manipulation commands to view/edit/delete" ),

    CmdEntryAction(  "log",
                     command_log,
                     "set system logging to  terminal" ),

    CmdEntrySubMenu( "sd",
                     SdCmdTable,
                     "manage SD card" ),

    CmdEntrySubMenu( "system",
                     SystemCmdTable,
                     "system control commands" ),

    CmdEntryTerminator()
};


/* -------------------------------------------------------------------------- */

PUBLIC const CmdEntry *commands = topCmdTable;

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY COMMANDS --------------------------------------------------- */
/* -------------------------------------------------------------------------- */

PRIVATE bool command_aux_gpio_out( CmdHandler *me )
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

PRIVATE bool command_aux_gpio_in( CmdHandler *me )
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

PRIVATE bool command_aux_gpio_mode( CmdHandler *me )
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
    //Disable flash output
    return true;
}
/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_on( CmdHandler *me )
{
    cmd_printf( me, "Flash ON\r\n" );
    //Enable flash output
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_flash_timed( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        uint16_t flashtime = (uint16_t)cmd_get_argv_int( me, 1 );
        cmd_printf( me, "Flashed for %dms\r\n", flashtime );
        //Enable flash output
        hal_delay_ms( flashtime );
        //Disable flash output
    }
    else
    {
        cmd_printf( me, "Usage: camera flash timed [ms]\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_camera_filter( CmdHandler *me )
{
    if( cmd_get_argc( me ) > 1 )
    {
		ir_filter_set( TASK_AUXILIARY_A,
						  ( cmd_get_argv_int( me, 1 ) > 0 )
						  ? FILTER_IR
						  : FILTER_CLEAR );
    }

    cmd_printf( me, "IR Filter is: %s\r\n", ir_filter_get()
                                            ? "BLOCKING"
                                            : "CLEAR" );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_off( CmdHandler *me )
{
    cmd_printf( me, "Camera OFF\r\n" );
    hal_camera_power(false);
    //eventPublish( EVENT_NEW( StateEvent, CAMERA_CMD_OFF ) );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool command_camera_on( CmdHandler *me )
{
    cmd_printf( me, "Camera ON\r\n" );
    hal_camera_power(true);
    //eventPublish( EVENT_NEW( StateEvent, CAMERA_CMD_ON ) );
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

PRIVATE bool
command_chdrive( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        cmd_printf( me, "chdrive unavailable with one disk\r\n" );

//        FRESULT f_result;
//        f_result = f_chdrive( (TCHAR*)cmd_get_argv( me, 1 ) );
//        command_print_fatfs_result( me, f_result );
    }
    else
    {
        cmd_printf( me, "Usage: chdrive <drive>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

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

PRIVATE bool
command_sd_mount( CmdHandler *me )
{
    cmd_printf( me, "Requesting SD mount!\r\n" );

    if( f_mount_request( (StateTask*)me ) )
	{
		cmd_printf( me, "OK\r\n" );
	}
	else
	{
		cmd_printf( me, "ERROR\r\n" );
	}
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sd_present( CmdHandler *me )
{
    cmd_printf( me,
                "SD card %s\r\n",
                hal_sd_is_present() ? "DETECTED" : "NOT DETECTED" );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sd_unmount( CmdHandler *me )
{
    cmd_printf( me, "Requesting SD unmount!\r\n" );
    if( f_unmount_request( (StateTask*)me ) )
	{
		cmd_printf( me, "OK\r\n" );
	}
	else
	{
		cmd_printf( me, "ERROR\r\n" );
	}
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sd_format( CmdHandler *me )
{
    cmd_printf( me, "SD format TODO!\r\n" );
    return true;
}

/* -------------------------------------------------------------------------- */
/* --- INI COMMANDS --------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

/**
 * @brief  Support function for command_config_read to show
 *         content of an INI file using the ini_browse function.
 * @param  section  the section being parsed
 * @param  key      the key within that section being read
 * @param  value    the string value of the key in this section
 * @param  userdata pointer to user data passed to the callback. Not used.
 * @return 1 to indicate ini_read needs to keep going.
 */
PRIVATE int
command_ini_read_callback( const char * section,
                             const char * key,
                             const char * value,
                             const void * userdata )
{
    CmdHandler *me = (CmdHandler*)userdata;
    cmd_printf( me, "[%s] %s=%s\r\n", section, key, value );
    return 1;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_config_read( CmdHandler *me )
{
    if( cmd_get_argc( me ) == 2 )
    {
        ini_browse( command_ini_read_callback,
                    me,
                    cmd_get_argv( me, 1 ) );
    }
    else
    {
        cmd_printf( me, "Usage: ini read <filename>\r\n" );
    }
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_config_write( CmdHandler *me )
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
        cmd_printf( me, "Usage: config write <filename> <section> <key> <value>\r\n" );
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

PRIVATE bool
command_system_clock( CmdHandler *me )
{
    cmd_printf( me,
                "CPU: %3.2fMHz\r\n",
				(float)hal_system_speed_get_speed() / 1000000
				);
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_load( CmdHandler *me )
{
    cmd_printf( me,
                "CPU: %3.2f%%\r\n",
				hal_system_speed_get_load()
				);
    return true;
}


/* -------------------------------------------------------------------------- */

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

PRIVATE bool command_system_info( CmdHandler *me )
{
    cmd_printf( me,
                "%s\r\nBuild: %s\r\nDate: %s\r\nType: %s\r\n",
                ProgramName,
                ProgramBuildInfo,
                ProgramBuildDate,
                ProgramBuildType );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_speed( CmdHandler *me )
{
    if( cmd_get_argc( me ) > 1 )
    {
        system_speed_set( TASK_AUXILIARY_A,
                          ( cmd_get_argv_int( me, 1 ) > 0 )
                          ? SYSTEM_SPEED_FULL
                          : SYSTEM_SPEED_LOW );
    }
    cmd_printf( me, "System speed: %s\r\n", system_speed_get()
                                            ? "FULL"
                                            : "LOW" );
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_upgrade_firmware( CmdHandler *me )
{
    if( cmd_get_argc( me ) > 1 )
    {
    	cmd_printf( me, "Firmware upgrade starting...\r\n" );

        if( cmd_get_argv_int( me, 1 ) == 0 )
        {

        	cmd_printf( me, "Using hardware method.\r\n" );
        	hal_firmware_update_hardware();
        }
        else if( cmd_get_argv_int( me, 1 ) > 0 )
        {
        	cmd_printf( me, "Using software method.\r\n" );
        	hal_firmware_update_software();
        }
    }
    else
    {
    	cmd_printf( me, "Usage: system upgrade <value>\r\n" );
    	cmd_printf( me, "<hardware reboot>: 0\r\n" );
    	cmd_printf( me, "<software jump>: 1\r\n" );
    }

    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_system_reboot( CmdHandler *me )
{
	cmd_printf( me, "Rebooting microcontroller!\r\n" );
	hal_delay_ms(20);	//enough time to print to serial port
	HAL_NVIC_SystemReset();

    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sensor_on( CmdHandler *me )
{
    board_sensor_enable();
    cmd_printf( me, "SENSORS STARTING\r\n");
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sensor_off( CmdHandler *me )
{
    board_sensor_disable();
    cmd_printf( me, "SENSORS STOPPED\r\n");
    return true;
}

/* -------------------------------------------------------------------------- */

PRIVATE bool
command_sensor_read( CmdHandler *me )
{
    cmd_printf( me, "Temperature: %2.1fC\r\n", board_sensor_temperature_C() );
    cmd_printf( me, "Light: %3.1f\r\n", board_sensor_light() );
    cmd_printf( me, "Vref: %3.1f\r\n", board_sensor_voltage_reference() );

    return true;
}

/* ----- End ---------------------------------------------------------------- */
