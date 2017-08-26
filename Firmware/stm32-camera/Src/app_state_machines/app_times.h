/**
 * @file    app_times.h
 *
 * @brief   Definitions of various application timeouts.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2013-2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TIMES_H
#define APP_TIMES_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- Types -------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */

enum AppTimeoutsMs
{
  TIME_APPLICATION_STEP               =    200, /* ms */
  TIME_APPLICATION_TICK               =     20, /* ms */

  TIME_MENU_TIMEOUT                   = (2*60*1000), /* ms */
  TIME_MENU_REFRESH                   =   1000, /* ms */
  TIME_MENU_REFRESH_FAST              =    300, /* ms */
  TIME_MINUTE_TICK                    =  60000, /* ms */

  TIME_BUTTON_POLL_MS                 =    200, /* ms */
  TIME_BUTTON_DEFAULTS_ACTIVATE_MS    =   5000, /* ms */
  TIME_BUTTON_NORMAL_PRESS            =     50, /* ms */
  TIME_BUTTON_LONG_PRESS              =   1500, /* ms */

  TIME_APPLICATION_SD_MOUNT_POLL 	  = 500,

  TIME_REBOOT_CAP_CHARGE			  = 200, /* ms */

  //TODO set reasonable timeouts
  TIME_CAMERA_RESPONSE_TIMEOUT 		  = 500,
  TIME_CAMERA_POWER_UP_DELAY		  = 500,
  TIME_CAMERA_RESET_TIMEOUT			  = 500,

  TIME_LOG_WRITE_DELAY                = 300000, /* 5 minutes */
  TIME_LOG_WRITE_DELAY_SHORT          =  20000, /* 20 seconds */


};

/* -------------------------------------------------------------------------- */

enum AppCounters
{
    COUNT_CAMERA_RETRIES                =     2,
    COUNT_POWER_OFF                     =    10,
};

/* ----------------------- End --------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TIMES_H */
