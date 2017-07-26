/**
 * @file      app_version.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Version & Build Information
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_VERSION_H
#define APP_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"

/* ----- Public Functions --------------------------------------------------- */

extern const char *   ProgramName;        ///< Application Name
extern const char *   ProgramBuildType;   ///< Build Type e.g. DEBUG, RELEASE
extern const char *   ProgramBuildBranch; ///< Git branch in use
extern const char *   ProgramBuildInfo;   ///< Git build info string
extern const char *   ProgramBuildDate;   ///< Date string of last git commit
extern const char *   ProgramBuildTime;   ///< Time string of last git commit

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_VERSION_H */
