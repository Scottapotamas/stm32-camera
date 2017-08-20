/**
 * @file      cmd.h
 *
 * @brief     Command Line Processing
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef CMD_H
#define CMD_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "cmd_config.h"

#if CMD_BUFFERSIZE > 255
    #error "CMD_BUFFERSIZE must be less than 255!"
#endif

/* ----------------------- Typedefs -----------------------------------------*/

/** Command processing status.
 *  @note that this must match the table of strings for
 *        error messages in cmdtable. */
typedef enum
{
    CMD_SUCCESS,
    CMD_ERR_PORT_PROBLEM,
    CMD_ERR_NO_SUCH_COMMAND,
    CMD_ERR_AMBIGUOUS_COMMAND,
    CMD_ERR_WRONG_NUMBER_OF_ARGUMENTS,
    CMD_ERR_ARGUMENT_OUT_OF_RANGE,
    CMD_ERR_ARGUMENT_SYNTAX_ERROR,
    CMD_ERR_STRING_TOO_LONG,
    CMD_ERR_INVALID_ARGUMENT_TYPE
} CmdStatus;

/* -------------------------------------------------------------------------- */

/** Current VT100 escape parsing mode */
typedef enum
{
    CMD_VT100_STATE_NONE = 0,       ///< Not in VT100 escape sequence
    CMD_VT100_STATE_GOT_ESC,        ///< Got the esc[ sequence
    CMD_VT100_STATE_IN_CMD          ///< Parsing the VT100 command sequence.
} CmdVt100;

/* -------------------------------------------------------------------------- */

/** Compact set of flags for Cmd operation. */
typedef struct
{
    unsigned handlerActive:1; ///< 'true' when cmd handler is initialised.
    unsigned cmdInitDone:1;   ///< 'false' at first call to action function.
    unsigned cmdDone:1;       ///< 'true' when command execution is complete.
    unsigned cmdRunning:1;    ///< command is running (e.g. long execution)
    unsigned echoOn:1;        ///< command echo is on
} CmdFlags;

/* -------------------------------------------------------------------------- */

/** Forward declration of a command or submenu item to be processed. */
typedef struct CmdEntry__ CmdEntry;

/* -------------------------------------------------------------------------- */

/** Declares all data used by the Cmd handler.*/
typedef struct
{
    CmdFlags            flags;
    CmdVt100            vt100;
    uint8_t             BufferLength;
    uint8_t             BufferEditPos;
    uint32_t            LogMask;

    /** Current edit buffer */
    char                Buffer[CMD_BUFFERSIZE];

    /** Command history buffers */
    char                history[CMD_HISTORYSIZE][CMD_BUFFERSIZE];

    /** Parsed command line arguments */
    uint8_t             argc;
    char                *argv[CMD_MAX_NUM_ARGUMENTS];

    /** Current command processing */
    CmdStatus           status;
    uint8_t             cmdLevel;
    const CmdEntry      *pActiveTable;
    const CmdEntry      *pCurrentCommandTable;
    const CmdEntry      *pCmdEntry;

    // Configuration Items To Be Initialised

    /** Top Level Command Table */
    const CmdEntry *pMainTable;

    /** Output a character */
    bool (*put)( uint8_t c );

    /** Flush the command output */
    void (*flush)( void );

} CmdHandler;

/* -------------------------------------------------------------------------- */

/** Command action function prototype
 *  @return true when command has completed.
 */
typedef bool (*CmdAction)(CmdHandler *me);

/* -------------------------------------------------------------------------- */

/** Actual declares a command or sub menu item to be processed.
 *  When action is NULL it is a sub menu item and the arguments string is then
 *  a pointer to the sub menu table. The arguments string is intended to help
 *  validate the command and its required arguments number and types but is yet
 *  to be implemented.
 */

struct CmdEntry__
{
  const char *    name;            ///< Command name
  const CmdAction action;          ///< Command action function. NULL for sub menu
  const char *    arguments;       ///< Command arguments or pointer to sub menu
  const char *    description;     ///< Extended command description.
};

/* ----------------------- Macros ------------------------------------------- */

/** Macro to define a CLI action */
#define CmdEntryAction(name, action, description) \
    { (name), (action), NULL, (description) }

/** Macro to define a CLI sub-menu (nested command) */
#define CmdEntrySubMenu(name, subMenu, description)  \
    { (name), NULL, (const char *)(subMenu), (description) }

/** Macro to define a command entry array terminator.*/
#define CmdEntryTerminator() \
    { NULL, NULL, NULL, NULL }

/* ----------------------- Data --------------------------------------------- */


/* ----------------------- Functions Specifications ------------------------- */

//! initalize the command line system.
PUBLIC void
cmd_init( CmdHandler *me, const CmdEntry *pTable );

//! sets the function used for sending characters to the user terminal
PUBLIC void
cmd_set_output_put( CmdHandler *me,
                    bool (*output_func)( uint8_t c ) );

//! sets the function used for flushing characters to the user terminal
PUBLIC void
cmd_set_output_flush( CmdHandler *me,
                      void (*output_flush)( void ));

//! sets the prompt
PUBLIC void
cmd_set_prompt( CmdHandler *me, const char * prompt );

//! sets the echo mode
PUBLIC void
cmd_set_echo( CmdHandler *me, const bool echo );

//! call this function to pass input characters from the user terminal
PUBLIC void
cmd_input_func( CmdHandler *me, unsigned char c );

//! returns true when a command is being input
PUBLIC bool
cmd_is_active( CmdHandler *me );

/* -------------------------------------------------------------------------- */

//! call this function in your program's main loop
/// returns true when the command was completed, false when the command
/// needs more time to process (e.g. waiting for external events)
PUBLIC bool
cmd_main_loop( CmdHandler *me );

/* -------------------------------------------------------------------------- */

//! formatted print output functions. Output goes via the allocated output handler
PUBLIC void
cmd_puts( CmdHandler *me,  const char * string );

//! formatted print output functions. Output goes via the allocated output handler
PUBLIC void
cmd_printf( CmdHandler *me, const char * format, ... )
                              __attribute__ ((format (printf, 2, 3)));

/* -------------------------------------------------------------------------- */

//! return number of arguments following the command
PUBLIC uint8_t
cmd_get_argc( CmdHandler *me );

//! returns a string pointer to argument number [argnum] on the command line
//  argnum 0 is always the current command with argnum==1 the first argument
//  following. Use negative numbers to find the higher level commands that
//  used to invoke this command for sub menu commands.
//  Arguments can be enclosed in "" and have embedded spaces and will be
//  returned without these "". Returns NULL if the argument is not available.
PUBLIC char *
cmd_get_argv( CmdHandler *me, int8_t argnum );

//! as per cmd_get_argv but return the argument string converted to
//  an integer number. The argument can use base overrides like 0x for
//  hexadecimal numbers.
//  Returns 0 if the argument cannot be converted or does not exist.
PUBLIC int32_t
cmd_get_argv_int( CmdHandler *me, int8_t argnum );

//! as per cmd_get_argv but return the argument string converted to
//  an floating point number. Returns 0 if the argument cannot be converted
//  or does not exist.
PUBLIC float32_t
cmd_get_argv_float( CmdHandler *me, int8_t argnum );

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CMD_H */



