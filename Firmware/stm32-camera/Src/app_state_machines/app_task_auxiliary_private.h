/**
 * @file      app_task_auxiliary_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Auxiliary Private Prototypes
 *            in a separate header file to enable unit testing.
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2016 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_AUXILIARY_PRIVATE_H
#define APP_TASK_AUXILIARY_PRIVATE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void
AppTaskAuxiliaryConstructor( AppTaskAuxiliary *me );

PRIVATE void
AppTaskAuxiliary_initial( AppTaskAuxiliary *me, const StateEvent *e );

PRIVATE STATE
AppTaskAuxiliary_main( AppTaskAuxiliary *me, const StateEvent *e );

    PRIVATE STATE
    AppTaskAuxiliary_mode_none( AppTaskAuxiliary *me, const StateEvent *e );

    PRIVATE STATE
    AppTaskAuxiliary_mode_gpio( AppTaskAuxiliary *me, const StateEvent *e );

    PRIVATE STATE
    AppTaskAuxiliary_mode_dac( AppTaskAuxiliary *me, const StateEvent *e );

    PRIVATE STATE
    AppTaskAuxiliary_mode_pwm( AppTaskAuxiliary *me, const StateEvent *e );

/* ----- Private Helper Function Declarations ------------------------------- */

PRIVATE void
AppTaskAuxiliary_monitor_inputs( void  );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_AUXILIARY_PRIVATE_H */
