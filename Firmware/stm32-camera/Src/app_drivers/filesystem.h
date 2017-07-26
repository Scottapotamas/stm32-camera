/**
 * @file      filesystem.h
 *
 * @brief     Defines for the filesystem in use.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/* -------------------------------------------------------------------------- */

#include "global.h"

/* -------------------------------------------------------------------------- */

typedef enum
{
    SD_DRIVE = 0,	//TODO add a ramdisk volume? Support for SDRAM? USB later?
    NUM_FILE_SYSTEMS
} FileSystem_t;


/* -------------------------------------------------------------------------- */

typedef struct
{
    uint32_t   total_KiB;       /**< Mounted volume space total */
    uint32_t   free_KiB;        /**< Mounted volume space available */
} FileSystemSpace_t;

/* -------------------------------------------------------------------------- */

PUBLIC void
filesystem_init( void  );

/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
filesystem_mount( FileSystem_t filesystem );

/* -------------------------------------------------------------------------- */

PUBLIC uint8_t
filesystem_unmount( FileSystem_t filesystem );

/* -------------------------------------------------------------------------- */

PUBLIC const char *
filesystem_path( FileSystem_t filesystem );

/* -------------------------------------------------------------------------- */

PUBLIC uint32_t
filesystem_space( FileSystem_t filesystem );

PUBLIC uint32_t
filesystem_free( FileSystem_t filesystem );

/* -------------------------------------------------------------------------- */

/* File Copy Support */

PUBLIC uint8_t
filesystem_copy_src( const char * sourcefile );

PUBLIC uint8_t
filesystem_copy_dst( const char * dstfile );

PUBLIC bool
filesystem_copy_process( void );

PUBLIC uint8_t
filesystem_copy_progress( void );

PUBLIC uint8_t
filesystem_copy_status( void );

/* -------------------------------------------------------------------------- */



/* ----- End ---------------------------------------------------------------- */

#endif /* FILESYSTEM_H */

