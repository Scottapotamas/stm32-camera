/**
 * @file      app_task_file_system_private.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task File System
 *
 * @author    Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef APP_TASK_FILE_SYSTEM_PRIVATE_H
#define APP_TASK_FILE_SYSTEM_PRIVATE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ----- Private State Functions Declarations ------------------------------- */

PRIVATE void AppTaskFileSystemConstructor( AppTaskFileSystem *me );

PRIVATE void AppTaskFileSystem_initial( AppTaskFileSystem *me,
                                        const StateEvent *e );

PRIVATE STATE AppTaskFileSystem_main( AppTaskFileSystem *me,
                                      const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_unmounted( AppTaskFileSystem *me,
                                           const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mount( AppTaskFileSystem *me,
                                       const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mounting_power_on( AppTaskFileSystem *me,
                                                   const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mounting( AppTaskFileSystem *me,
                                          const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mounting_retry( AppTaskFileSystem *me,
                                                const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mounted( AppTaskFileSystem *me,
                                         const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_mounted_standby( AppTaskFileSystem *me,
                                                const StateEvent *e );
PRIVATE STATE AppTaskFileSystem_unmounting( AppTaskFileSystem *me,
                                            const StateEvent *e );

/* ----- Helper Function Declaration ---------------------------------------- */

PRIVATE void AppTaskFileSystemHelper_send_mounted_status( AppTaskFileSystem *me,
                                                          StateTask * requesting_task );
PRIVATE void AppTaskFileSystemHelper_send_unmounted_status( AppTaskFileSystem *me,
                                                            StateTask * requesting_task );
PRIVATE uint8_t AppTaskFileSystemHelper_num_mounted( AppTaskFileSystem *me );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_FILE_SYSTEM_PRIVATE_H */
