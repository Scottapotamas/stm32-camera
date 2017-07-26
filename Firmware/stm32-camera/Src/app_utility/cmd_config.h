/**
 * @file      cmd_config.h
 *
 * @brief     Command Line Processing Configuration Data
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef CMD_CONFIG_H
#define CMD_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- Defines ------------------------------------------------------------ */

// allotted buffer size for command entry
// (must be enough chars for typed commands and the arguments that follow)
#define CMD_BUFFERSIZE         128

// Maximum number of arguments that the cmd handler has space for to handle
// This includes any subcommands.
#define CMD_MAX_NUM_ARGUMENTS  8

// number of lines of command history to keep
// (each history buffer is CMDLINE_BUFFERSIZE in size)
// ***** ONLY ONE LINE OF COMMAND HISTORY IS CURRENTLY SUPPORTED
#define CMD_HISTORYSIZE        1

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CMD_CONFIG_H */
