/**
 * @file      app_task_camera_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Camera
 *
 */

#ifndef APP_TASK_CAMERA_PRIVATE_H
#define APP_TASK_CAMERA_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void AppTaskCameraConstructor( AppTaskCamera *me );

PRIVATE void AppTaskCamera_initial( AppTaskCamera *me,
                                    const StateEvent *e );

/* State Functions */

PRIVATE STATE AppTaskCamera_off( AppTaskCamera *me,
                                 const StateEvent *e );

PRIVATE STATE AppTaskCamera_on( AppTaskCamera *me,
                                const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_init( AppTaskCamera *me,
                                         const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_init_reset( AppTaskCamera *me,
                                               const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_ready( AppTaskCamera *me,
                                          const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_capture_normal( AppTaskCamera *me,
                                                  const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_capture( AppTaskCamera *me,
                                            const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_save( AppTaskCamera *me,
                                         const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_save_open_file( AppTaskCamera *me,
                                                   const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_save_get_size( AppTaskCamera *me,
                                                  const StateEvent *e );

    PRIVATE STATE AppTaskCamera_on_save_open_file( AppTaskCamera *me,
                                                   const StateEvent *e );

PRIVATE STATE AppTaskCamera_error( AppTaskCamera *me,
                                   const StateEvent *e );

/* Helpers */

PRIVATE void
set_capture_path_and_file_name( AppTaskCamera *me );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_CAMERA_PRIVATE_H */
