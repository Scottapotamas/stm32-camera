/**
 * @file      hal_button.c
 *
 * @brief     Low level GPIO interface to the buttons.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
*/

#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdbool.h>

/* ----- Local includes ----------------------------------------------------- */

#include "global.h"

/* ----- Types -------------------------------------------------------------- */

typedef enum
{
	BUTTON_0,
	BUTTON_1,
	BUTTON_MAX
} ButtonId_t;

/* ----- Public Prototypes -------------------------------------------------- */

PUBLIC bool
hal_button_is_pressed( ButtonId_t id );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* HAL_BUTTON_H */
