/**
 * @file     cmd.c
 *
 * @brief    Command Line Processing
 *
 * @author   Marco Hess <marcoh@applidyne.com.au>
 *
* @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
  */

/* ----- System Includes ---------------------------------------------------- */

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"         // include our global settings from the project
#include "qassert.h"
#include "cmd.h"            // additional configuration parameters

/* ----- Defines ------------------------------------------------------------ */

#define ASCII_BEL             0x07
#define ASCII_BS              0x08
#define ASCII_CR              0x0D
#define ASCII_LF              0x0A
#define ASCII_ESC             0x1B
#define ASCII_DEL             0x7F

#define VT100_ARROWUP         'A'
#define VT100_ARROWDOWN       'B'
#define VT100_ARROWRIGHT      'C'
#define VT100_ARROWLEFT       'D'

/* ------------------------Typedefs ---------------------------------------- */

typedef enum
{
    CMD_HISTORY_SAVE = 0,
    CMD_HISTORY_PREV,
    CMD_HISTORY_NEXT,
} CmdHistCmd;

/* ----------------------- Private Functions ------------------------------- */

PRIVATE void cmd_repaint( CmdHandler *me );

PRIVATE void cmd_do_history( CmdHandler *me, CmdHistCmd action );

PRIVATE void cmd_process_input_string( CmdHandler *me );

PRIVATE bool cmd_get_sub_command( const CmdEntry *entry,
                                  const CmdEntry **subCommand );

PRIVATE const CmdEntry* cmd_command_lookup( CmdHandler     *me,
                                            const CmdEntry *commandFinger,
                                            uint8_t        level );

PRIVATE void cmd_print_prompt( CmdHandler *me );

PRIVATE void cmd_error_handler( CmdHandler *me,
                                CmdStatus  status);

PRIVATE void cmd_print_command_table( CmdHandler *me,
                                      const CmdEntry *pCurrentCommandTable );

PRIVATE void cmd_print_command_usage( CmdHandler     *me,
                                      const CmdEntry *pEntry );

#ifdef NO_LONGER_USED_AND_TO_BE_REMOVED
PRIVATE int  cmd_strnicmp(const char *s1, const char *s2, size_t n);
#endif

/* ----------------------- Variables ----------------------------------------*/

// None. Everything is handled with the application
// declaring a CmdHandler struct and passing this on to the command handler
// functions.

/* ----------------------- Start implementation ----------------------------- */

// Status descriptions. Must match CmdStatus entries.
PRIVATE const char * CmdErrorDescriptions[] =
{
    "",
    "Serial port error",
    "No such command",
    "Ambiguous command",
    "Wrong number of args for command",
    "Arg out of range",
    "Arg syntax error",
    "Too long",
    "Bad arg type"
};

/* ----------------------- Start implementation ----------------------------- */

PUBLIC void
cmd_init( CmdHandler *me, const CmdEntry *pMainTable )
{
    me->vt100 = CMD_VT100_STATE_NONE;   //< VT100 input processing state
    me->BufferLength = 0;               //< Current input buffer length
    me->BufferEditPos = 0;              //< Current input buffer position
    me->pMainTable = pMainTable;        //< Pointer to top level command table to decode.
    me->pActiveTable = NULL;            //< Pointer to currently used command table to decode.
    me->pCmdEntry = NULL;               //< Pointer to currently command
    me->flags.echoOn = false;           //< Default no echo
    me->flags.cmdInitDone = false;      //< Default Not Done
    me->flags.cmdDone = true;           //< Default Done
    me->flags.handlerActive = true;     //< CmdHandler initialised
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_set_echo( CmdHandler *me, bool echo )
{
    me->flags.echoOn = echo;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_set_output_put( CmdHandler *me,
                    bool (*output_func)(uint8_t c))
{
    me->put = output_func;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_set_output_flush( CmdHandler *me,
                      void (*output_flush)(void))
{
    me->flush = output_flush;
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_input_func( CmdHandler *me, unsigned char c )
{
  uint16_t i;

  // process the received character

  // VT100 handling
  if( me->vt100 == CMD_VT100_STATE_IN_CMD )
  {
    // we have already received ESC and [
    // now process the vt100 code
    switch(c)
    {
    case VT100_ARROWUP:
      cmd_do_history( me, CMD_HISTORY_PREV );
      break;

    case VT100_ARROWDOWN:
      cmd_do_history(  me, CMD_HISTORY_NEXT );
      break;

    case VT100_ARROWRIGHT:
      // if the edit position less than current string length
      if( me->BufferEditPos < me->BufferLength )
      {
        // increment the edit position
        me->BufferEditPos++;
        // move cursor forward one space (no erase)
        me->put( ASCII_ESC );
        me->put( '[');
        me->put( VT100_ARROWRIGHT );
      }
      else
      {
        // else, ring the bell
        me->put( ASCII_BEL );
      }
      break;

    case VT100_ARROWLEFT:
      // if the edit position is non-zero
      if( me->BufferEditPos )
      {
        // decrement the edit position
        me->BufferEditPos--;
        // move cursor back one space (no erase)
        me->put( ASCII_BS );
      }
      else
      {
        // else, ring the bell
        me->put( ASCII_BEL );
      }
      break;

    default:
      break;
    }

    // done, reset state
    me->vt100 = CMD_VT100_STATE_NONE;
    return;
  }
  else if( me->vt100 == CMD_VT100_STATE_GOT_ESC )
  {
    // we last received [ESC]
    if( c == '[' )
    {
      me->vt100 = CMD_VT100_STATE_IN_CMD;
      return;
    }
    else
    {
      me->vt100 = CMD_VT100_STATE_NONE;
    }
  }
  else
  {
    // anything else, reset state
    me->vt100 = CMD_VT100_STATE_NONE;
  }

  // Regular handling
  if( (c >= 0x20) && (c < 0x7F) )
  {
    // character is printable and we have room
    if( me->BufferLength < CMD_BUFFERSIZE )
    {
      // is this a simple append
      if( me->BufferEditPos == me->BufferLength )
      {
        // echo character to the output
        if( me->flags.echoOn )
          me->put(c);
        // add it to the command line buffer
        me->Buffer[me->BufferEditPos++] = c;
        // update buffer length
        me->BufferLength++;
      }
      else
      {
        // edit/cursor position != end of buffer
        // we're inserting characters at a mid-line edit position
        // make room at the insert point
        me->BufferLength++;
        for( i = me->BufferLength; i > me->BufferEditPos; i-- )
        {
            me->Buffer[i] = me->Buffer[i-1];
        }

        // insert character
        me->Buffer[ me->BufferEditPos++ ] = c;

        if( me->flags.echoOn )
        {
          cmd_repaint( me );
          // reposition cursor
          for(i = me->BufferEditPos; i < me->BufferLength; i++)
          {
            me->put(ASCII_BS);
          }
        }
      }
    }
    else
    {
      // buffer full, ring the bell
      me->put( ASCII_BEL );
    }
  }
  // handle special characters
  else if(c == ASCII_CR)
  {
    // user pressed [ENTER]
    // echo CR and LF to terminal
    me->put( ASCII_CR );
    me->put( ASCII_LF );
    // add null termination to command
    me->Buffer[ me->BufferLength++ ] = 0;
    me->BufferEditPos++;
    // command is complete, process it
    cmd_process_input_string( me );
    // reset buffer
    me->BufferLength = 0;
    me->BufferEditPos = 0;
  }
  else if((c == ASCII_BS) || (c == ASCII_DEL))
  {
    if(me->BufferEditPos)
    {
      // is this a simple delete (off the end of the line)
      if(me->BufferEditPos == me->BufferLength)
      {
        // destructive backspace
        // echo backspace-space-backspace
        me->put(ASCII_BS);
        me->put(' ');
        me->put(ASCII_BS);
        // decrement our buffer length and edit position
        me->BufferLength--;
        me->BufferEditPos--;
      }
      else
      {
        // edit/cursor position != end of buffer
        // we're deleting characters at a mid-line edit position
        // shift characters down, effectively deleting
        me->BufferLength--;
        me->BufferEditPos--;
        for(i = me->BufferEditPos; i < me->BufferLength; i++)
        {
          me->Buffer[i] = me->Buffer[i+1];
        }
        // repaint
        cmd_repaint( me );
        // add space to clear leftover characters
        me->put(' ');
        // reposition cursor
        for(i = me->BufferEditPos; i < (me->BufferLength+1); i++)
        {
          me->put(ASCII_BS);
        }
      }
    }
    else
    {
      // else, ring the bell
      me->put( ASCII_BEL );
    }
  }
  else if(c == ASCII_ESC)
  {
    me->vt100 = 1;
  }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_puts( CmdHandler *me, const char * string )
{
    while( *string )
    {
        me->put( *string++ );
    }
}

/* -------------------------------------------------------------------------- */

PUBLIC void
cmd_printf( CmdHandler *me, const char * format, ... )
{
    char buffer[256];
    va_list args;

    va_start( args, format );
    vsnprintf( buffer, sizeof(buffer), format, args );
    va_end( args );

    cmd_puts( me, buffer );
}

/* -------------------------------------------------------------------------- */

//! returns true when a command is being input
PUBLIC bool
cmd_is_active( CmdHandler *me )
{
  return me->BufferEditPos > 0;
}

/* -------------------------------------------------------------------------- */
/* --- Command Arguments Access Handling ----------------------------------- */
/* -------------------------------------------------------------------------- */

// return number of arguments following the command
PUBLIC uint8_t
cmd_get_argc( CmdHandler *me )
{
    return me->argc - me->cmdLevel;
}

/* -------------------------------------------------------------------------- */

//! returns a string pointer to argument number [argnum] on the command line
//  argnum 0 is always the current command with argnum==1 the first argument
//  following. Use negative numbers to find the higher level commands that
//  used to invoke this command for sub menu commands.
//  Returns NULL if the argument is not available
PUBLIC char*
cmd_get_argv( CmdHandler *me, int8_t argnum )
{
   if( ( (me->cmdLevel + argnum) <= me->argc )
       &&
       ( (me->cmdLevel + argnum) >= 0 ) )
   {
      return me->argv[me->cmdLevel + argnum];
   }
   else
   {
      return NULL;
   }
}

/* -------------------------------------------------------------------------- */

//! as per cmd_get_argv but return the argument string converted to
//  an integer number. The argument can use base overides like 0x for
//  hexadecimal numbers.
//  Returns 0 if the argument cannot be converted or does not exist.
PUBLIC int32_t
cmd_get_argv_int( CmdHandler *me, int8_t argnum )
{
   char* endptr;
   if( ( (me->cmdLevel + argnum) <= me->argc )
       &&
       ( (me->cmdLevel + argnum) >= 0 ) )
   {
      return strtol( me->argv[me->cmdLevel + argnum], &endptr, 0 );
   }
   else
   {
      return 0;
   }
}

/* -------------------------------------------------------------------------- */

//! as per cmd_get_argv but return the argument string converted to
//  an floating point number. Returns 0 if the argument cannot be converted
//  or does not exist.
PUBLIC float32_t
cmd_get_argv_float( CmdHandler *me, int8_t argnum )
{
   if( ( (me->cmdLevel + argnum) <= me->argc )
       &&
       ( (me->cmdLevel + argnum) >= 0 ) )
   {
      return strtof( me->argv[me->cmdLevel + argnum], NULL );
   }
   else
   {
      return 0;
   }
}

/* -------------------------------------------------------------------------- */
/* --------- Private Functions ----------------------------------------------*/
/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_repaint( CmdHandler *me )
{
    char*   ptr;
    uint16_t  i;

    // carriage return
    me->put( ASCII_CR );

    // print fresh prompt
    cmd_print_prompt( me );

    // print the new command line buffer
    i = me->BufferLength;
    ptr = me->Buffer;
    while( i-- )
    {
        me->put( *ptr++ );
    }
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_do_history( CmdHandler *me, CmdHistCmd action )
{
    switch( action )
    {
        case CMD_HISTORY_SAVE:
            if( strlen( me->Buffer ) )
                strcpy( me->history[0], me->Buffer );
            break;

        case CMD_HISTORY_PREV:
            strcpy( me->Buffer, me->history[0] );
            me->BufferLength = strlen( me->Buffer );
            me->BufferEditPos = me->BufferLength;
            cmd_repaint( me );
            break;

        case CMD_HISTORY_NEXT:
            break;
    }
}

/* -------------------------------------------------------------------------- */

//Important Notes:
//
//* The input string will have null characters inserted at the end of each
//  token. Keep a copy if you need the original again!
//* Token delimiters are hard coded as whitespace (tab, space, newline)
//* Parsing multiple strings at once is not possible, as I use an internal
//  static variable. For most purposes this won't be a problem, but if you
//  really need to parse multiple strings at once, I recommend placing the
//  routine into its own class, with pNext as a non-static member variable.
//* As a bonus side effect, parsing <code>"say_team" "hello"</code> will
//  return the same tokens as <code>say_team "hello"</code> So you could
//  even have console commands containing spaces, if you're feeling
//  different! ;)

PRIVATE char *
cmd_strtok( char *strToken )
{
    // Where to start searching next
    static char *pNext;
    // Start of next token
    char *pStart;

    // If NULL is passed in, continue searching
    if ( strToken == NULL )
    {
        if ( pNext != NULL )
        {
            strToken = pNext;
        }
        else
        {
            // Reached end of original string
            return NULL;
        }
    }

    // Zero length string, so no more tokens to be found
    if ( *strToken == 0 )
    {
        pNext = NULL;
        return NULL;
    }

    // Skip leading whitespace before next token
    while ( (*strToken == ' ') || (*strToken == '\t')
            || (*strToken == '\n') ) {

        ++strToken;
    }

    // It's a quoted literal - skip the first quote char
    if ( *strToken == '\"' ) {
        ++strToken;

        pStart = strToken;

        // Find ending quote or end of string
        while ( (*strToken != '\"') && (*strToken != 0) ) {
            ++strToken;
        }

        if ( *strToken == 0 ) {
            // Reached end of original string
            pNext = NULL;
        } else {
            // More to find, note where to continue searching
            *strToken = 0;
            pNext = strToken + 1;
        }

    } else {
        // Unquoted token
        pStart = strToken;

        // Find next whitespace delimiter or end of string
        while ( (*strToken != 0) && (*strToken != ' ') &&
                (*strToken != '\t') && (*strToken != '\n' ) ) {
            ++strToken;
        }

        // Reached end of original string?
        if ( *strToken == 0 ) {
            pNext = NULL;
        } else {
            *strToken = 0;
            pNext = strToken + 1;
        }
        return pStart;
    }

    // Return ptr to start of token
    return pStart;
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_process_input_string( CmdHandler *me )
{
    // Token Parsing Vars
    char     *token;

    // save command in history
    cmd_do_history( me, CMD_HISTORY_SAVE );

    // break the command line into its token arguments
    me->argc = 0;
    memset( me->argv, 0, sizeof( me->argv ) );
    token = cmd_strtok( me->Buffer );
    while( token && (me->argc < DIM( me->argv ) ) )
    {
        me->argv[ me->argc++ ] = token;
        token = cmd_strtok( NULL );
    }

    // is there actually a command?
    if( me->argc == 0 )
    {
        // output a new prompt
        cmd_print_prompt( me );
        return;
    }

    // search command list for match with entered command
    me->cmdLevel = 0;
    me->pCurrentCommandTable = me->pMainTable;
    while( true )
    {
        me->pCmdEntry = cmd_command_lookup( me,
                me->pCurrentCommandTable,
                me->cmdLevel );
        if( me->pCmdEntry == NULL )
        {
            // No match found or ambiguous match found.
            me->status = CMD_ERR_NO_SUCH_COMMAND;
            break;
        }
        else
        {
            // Found an entry in the current table.
            me->cmdLevel += 1;

            // See if this entry is possibly a sub menu item.
            if( cmd_get_sub_command( me->pCmdEntry,
                                          &me->pCurrentCommandTable ) )
            {
                // The current entry is a sub command. Check if we
                // have enough arguments to find the required sub command.
                if( me->cmdLevel >= me->argc )
                {
                    me->status = CMD_ERR_WRONG_NUMBER_OF_ARGUMENTS;
                    break;
                }
                // The pCurrentCommandTable is now updated to point to the
                // next sub menu table so continue looking for a match
                // in the new table or we run out of arguments.
            }
            else
            {
                // Found the command and it is not a sub command.
                // Good to go.
                me->status = CMD_SUCCESS;
                me->cmdLevel--;
                break;
            }
        }
    }

    if( me->status != CMD_SUCCESS )
    {
        cmd_error_handler( me, me->status );
        cmd_print_prompt( me );
    }
}

/* -------------------------------------------------------------------------- */

// This can be repeatedly called to process a certain command action
// function. If the command action outputs a lot of data, it may be worth
// breaking the processing in a small state machine and allow the action
// to be called repeatedly. Use the pHandler.flags.cmdInitDone flag to
// keep track of a first time initialisation within the action function.

PUBLIC bool
cmd_main_loop( CmdHandler *me )
{
    // Do we have a command/function to be executed?
    if( ( me->status == CMD_SUCCESS )
        &&
        ( me->pCmdEntry ) )
    {
        // Execute it
        me->flags.cmdRunning = true;
        me->flags.cmdDone = me->pCmdEntry->action( me );

        // Flush any produced output
        if( me->flush )
        {
            me->flush();
        }

        // If the command signalled it was done (true), clear the
        // command entry to signal that we don't need to continue calling it
        if( me->flags.cmdDone )
        {
            // reset
            me->pCmdEntry         = NULL;
            me->flags.cmdRunning  = false;
            me->flags.cmdInitDone = false;    // Reset for next round

            // output new prompt
            cmd_print_prompt( me );
        }
    }

    return me->flags.cmdDone;
}

/* -------------------------------------------------------------------------- */
// Command lookup and processing

// Returs true if entry is a sub command, and in this case
// it populates the subCommand pointer.
// Otherwise it returns false, and does nothing with subCommand
//
// Nested commands are implemented by setting the action
// field to NULL, and the arguments field is a pointer
// to a sub CmdEntry array.

PRIVATE bool
cmd_get_sub_command( const CmdEntry *entry,
                     const CmdEntry **subCommand )
{
    bool foundSubCommand = false;

    if( entry->action == NULL )
    {
        *subCommand = (CmdEntry*)entry->arguments;
        foundSubCommand = true;
    }

    return foundSubCommand;
}

/* -------------------------------------------------------------------------- */

PRIVATE uint8_t
charDowncase(uint8_t c)
{
  if ('A' <= c && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

/* -------------------------------------------------------------------------- */

PRIVATE const CmdEntry*
cmd_command_lookup( CmdHandler     *me,
                    const CmdEntry *commandTable,
                    uint8_t        cmdLevel )
{
  bool  multiplePossibleMatches = false;
  const CmdEntry *possibleMatch = NULL;
  char *  inputCommand = me->argv[cmdLevel];
  uint8_t inputLength = inputCommand ? strlen(inputCommand) : 0;

  me->status = CMD_ERR_NO_SUCH_COMMAND;

  // Go through the whole table to find a match to the
  // current command.
  for( ; commandTable->name != NULL; commandTable++ )
  {
    const char *entryCmdName = commandTable->name;
          char *inputCmdName = inputCommand;

    // Check names character by character
    for( ; ; entryCmdName++, inputCmdName++ )
    {
      bool endInput = (inputCmdName - inputCommand) == inputLength;
      bool endEntry = (*entryCmdName == 0);

      // If we are at the end of both name strings we found an exact match.
      if( endInput && endEntry )
      {
          // Found an exact match. Return the pointer to the current entry.
          return commandTable;
      }
      // If we are on either name string end, we found a possible match.
      else if( endInput || endEntry )
      {
        // Did we find a possible match previously?
        if( possibleMatch != NULL )
        {
          // Multiple matches detected.
          // Exit and return NULL to indicate there is no match.
          multiplePossibleMatches = true;
          break;
        }
        else
        {
          // This is the first possible partial match.
          possibleMatch = commandTable;
          break;
        }
      }
      // Keep checking the names and comparing them in a case insentitive way.
      else if (charDowncase(*inputCmdName) != charDowncase(*entryCmdName))
      {
          break;
      }
    }
  }
  // We only want to return a match if it is non ambiguous.
  return (multiplePossibleMatches ? NULL : possibleMatch);
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_print_prompt( CmdHandler *me )
{
    // print a new command prompt
    cmd_puts( me, "> " );
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_error_handler( CmdHandler *me,
                   CmdStatus  status )
{
    cmd_printf( me, "Error: %s\r\n",
                     CmdErrorDescriptions[status] );

    if( me->pCurrentCommandTable == NULL )
    {
       cmd_print_command_table( me, me->pMainTable );
    }
    else
    {
       uint8_t tokenNum;

       // Reconstruct any parent commands from the buffer.
       for( tokenNum = 0; tokenNum < me->cmdLevel - 1; tokenNum++ )
       {
          cmd_printf( me, "%s ", me->argv[tokenNum] );
       }
       cmd_print_command_table( me, me->pCurrentCommandTable );
  }
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_print_command_table( CmdHandler     *me,
                         const CmdEntry *pCurrentCommandTable )
{
    const CmdEntry *pEntry;
    uint8_t level;

    for( level = 0; level < me->cmdLevel; level++ )
    {
        cmd_printf( me, "%s ", me->argv[level] );
    }

    cmd_printf( me, "commands are:\r\n" );

    for( pEntry = pCurrentCommandTable;
         pEntry->name != NULL;
         pEntry++ )
    {
       cmd_print_command_usage( me, pEntry );
    }

    cmd_printf( me, "\r\n" );
}

/* -------------------------------------------------------------------------- */

PRIVATE void
cmd_print_command_usage( CmdHandler     *me,
                         const CmdEntry *pEntry )
{
    uint8_t spaces = 0;

    cmd_puts( me, pEntry->name );

    if ( pEntry->action == NULL )
    {
        // Show that this command has sub commands
        cmd_puts( me, " ..." );
        spaces += 4;
    }

    for( spaces += strlen( pEntry->name );
         spaces < 15;
         spaces++ )
    {
        me->put( ' ' );
    }

    if ( pEntry->description )
    {
        cmd_printf( me, "- %s", pEntry->description );
    }

    cmd_puts( me, "\r\n" );

    // Flush any produced output
   if( me->flush )
   {
       me->flush();
   }
}

/* -------------------------------------------------------------------------- */

#ifdef NO_LONGER_USED_AND_TO_BE_REMOVED
PRIVATE int
cmd_strnicmp( const char *s1, const char *s2, size_t n )
{
  while (n-- != 0 && (*s1 || *s2))
  {
    register int c1, c2;
    c1 = *s1++;
    if ('a' <= c1 && c1 <= 'z')
      c1 += ('A' - 'a');
    c2 = *s2++;
    if ('a' <= c2 && c2 <= 'z')
      c2 += ('A' - 'a');
    if (c1 != c2)
      return c1 - c2;
  } /* while */
  return 0;
}
#endif

/* -------------------------------------------------------------------------- */

