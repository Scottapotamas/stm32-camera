/**
 * @file      app_task_supervisor_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Supervisor
*
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_SUPERVISOR_PRIVATE_H
#define APP_TASK_SUPERVISOR_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void AppTaskSupervisorConstructor( AppTaskSupervisor *me );
PRIVATE void AppTaskSupervisor_initial( AppTaskSupervisor *me,
                                        const StateEvent *e );

PRIVATE STATE AppTaskSupervisor_main( AppTaskSupervisor *me,
                                      const StateEvent *e );

PRIVATE STATE AppTaskSupervisor_placeholder( AppTaskSupervisor *me,
                                      const StateEvent *e );


PRIVATE void AppTaskSupervisorButtonEvent( ButtonId_t button,
                                          ButtonPressType_t press_type );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_SUPERVISOR_PRIVATE_H */
