/**
 * @file      app_config.h
 *
 * @brief     Application level configuration options and definitions.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APPLICATION_CONFIG_H
#define APPLICATION_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

/* ----- Local Includes ----------------------------------------------------- */

/* ----- Defines ------------------------------------------------------------ */

#define APPLICATION_VERSION      0

//! Hardware Version - Currently a static fixed value.
#define HARDWARE_VERSION         0

//! Manufacturer name
#define MANUFACTURER_NAME        "Scott Rapson"

//! Max File Name Length
#define MAX_FILE_NAME_LEN        128

#define APP_CONFIG_FILE_CONFIG_INI         "config.ini"

/* -------------------------------------------------------------------------- */
/* --- Serial I/O Baudrates                                               --- */
/* -------------------------------------------------------------------------- */

/** Monitor/Terminal Interface Default Baudrate */
#define APP_CONFIG_BAUDRATE_MONITOR       115200

/* -------------------------------------------------------------------------- */
/* --- File System Paths                                                  --- */
/* -------------------------------------------------------------------------- */

/** Drive Name */
#define APP_CONFIG_SD_DRIVE                "0:"

/** Directory Paths */
#define APP_CONFIG_PATH_PHOTOS             "Photos"
#define APP_CONFIG_PATH_LOGS               "Logs"

/** File Names */
#define APP_CONFIG_FILE_CONFIG_INI         "config.ini"


/* -------------------------------------------------------------------------- */
/* --- Tick Timer Conversion Macros                                       --- */
/* -------------------------------------------------------------------------- */

#ifdef STM32F429xx
//! Application uses 1ms timer ticks on the ARM platform with SysTick
#define MS_PER_TICK             1U
#else
//! Application uses 10ms timer ticks on the PC
#define MS_PER_TICK             10UL
#endif

// Convert a ms time into timer ticks. Ensure that we round up when needed.
#define MS_TO_TICKS(_ms_)  (((_ms_) + (MS_PER_TICK-1)) / MS_PER_TICK)

/* ----- End ---------------------------------------------------------------- */

#ifdef    __cplusplus
}
#endif
#endif /* APPLICATION_CONFIG_H */
