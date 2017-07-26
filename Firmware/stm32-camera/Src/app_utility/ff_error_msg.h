/**
 * @file       ff_error_msg.h
 *
 * @brief      Print FatFs error codes as text.
 *
 * @author     Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2013-2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef FF_ERROR_MSG_H
#define	FF_ERROR_MSG_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "ff.h"

/* -------------------------------------------------------------------------- */

/* Returns a pointer to a text message representing the FRESULT err code. */
PUBLIC const char *
f_error_msg( FRESULT err );

/* -------------------------------------------------------------------------- */

#ifdef	__cplusplus
}
#endif

#endif	/* FF_ERROR_MSG_H */

