/**
 * @file      app_task_log_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Log
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_LOG_PRIVATE_H
#define APP_TASK_LOG_PRIVATE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void AppTaskLogConstructor( AppTaskLog *me );

PRIVATE void AppTaskLog_initial( AppTaskLog *me,
                                 const StateEvent *e );

PRIVATE STATE AppTaskLog_main( AppTaskLog *me,
                               const StateEvent *e );

PRIVATE STATE AppTaskLog_idle( AppTaskLog *me,
                               const StateEvent *e );

PRIVATE STATE AppTaskLog_flushing( AppTaskLog *me,
                                   const StateEvent *e );
PRIVATE STATE AppTaskLog_flush_open( AppTaskLog *me,
                                     const StateEvent *e );
PRIVATE STATE AppTaskLog_flush_seek( AppTaskLog *me,
                                     const StateEvent *e );
PRIVATE STATE AppTaskLog_flush_write( AppTaskLog *me,
                                      const StateEvent *e );
PRIVATE STATE AppTaskLog_flush_write_finish( AppTaskLog *me,
                                             const StateEvent *e );

/* ----- Helpers ------------------------------------------------------------ */

PRIVATE void
AppTaskLog_log_event_handler( LOG_LEVEL level,
                              uint32_t used,
                              uint32_t percent_full );

PRIVATE void
AppTaskLog_set_log_path_and_filename( AppTaskLog *me );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_LOG_PRIVATE_H */
