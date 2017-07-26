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

#include "app_config.h" // For MS_TO_TICKS macro

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
};

/* ----------------------- End --------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TIMES_H */
