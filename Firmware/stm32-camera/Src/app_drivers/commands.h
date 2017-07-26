/**
 * @file    commands.h
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

#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "cmd.h"

/* ----- Public Command Table Reference ------------------------------------- */

extern const CmdEntry *commands;

/* -------------------------------------------------------------------------- */

PUBLIC uint16_t
command_log_set_mask( CmdHandler *me, uint16_t log_mask );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_H */
