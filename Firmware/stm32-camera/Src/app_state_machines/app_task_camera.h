/**
 * @file      app_task_camera.h
 *
 * @ingroup   tasks
 *
 * @brief     Application Task Camera

 */

#ifndef APP_TASK_CAMERA_H
#define APP_TASK_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* ----- Local Includes ----------------------------------------------------- */
#include "global.h"
#include "state_task.h"
#include "event_timer.h"
#include "ff.h"

/* ----- State Task Control Block ------------------------------------------- */

/** Application Task Control Block Camera */
typedef struct AppTaskCamera AppTaskCamera;
struct AppTaskCamera
{
    // ~~~ Core task structure ~~~
    StateTask      super;                 ///< Core task structure

    // ~~~ Task Timers ~~~
    EventTimer     timer;                 ///< Task State timer
    EventTimer     shutterTimer;          ///< Task State timer
    EventTimer     flashTimer;            ///< Task State timer

    // ~~~ Task Variables ~~~
    bool              camera_was_init;
    bool              ready;
    bool              capturing;

    //SensorTarget_t target_type;
    uint16_t         flash_duration_time_ms;
    uint16_t         shutter_time_ms;         //*< Calculated shutter trigger time based on time of flight of gel.
    int16_t          trigger_delay_ms;        //*< Time to add or subtract from shutter_time_ms
    uint16_t         flash_level;             //*< Flash intensity for distance
    char             capture_path_name[MAX_FILE_NAME_LEN];
    char             capture_file_name[MAX_FILE_NAME_LEN];
    FIL              capture_file;
    FRESULT          f_result;
    uint32_t         image_size;
    uint32_t         image_offset;
    uint32_t         image_block;
    uint8_t          retry;
};

/* ----- Public Functions --------------------------------------------------- */

/**
 * @brief  Create the Camera task
 * @param  me             Reference to own task structure
 * @param  priority       Task priority level (fixed at compile time).
 * @param  eventQueueData event queue for this task
 * @param  eventQueueSize size of queue
 * @return StateTask *
 */
PUBLIC StateTask *
appTaskCameraCreate( AppTaskCamera *me,
                     StateEvent    *eventQueueData[ ],
                     const uint8_t eventQueueSize );

/* -------------------------------------------------------------------------- */

/** Helper function for tasks to easily take a picture in normal mode
 *  with a the shutter triggered immediately. Uses the info from the
 *  readings information to set capture file name.
 */

PUBLIC bool
appTaskCameraTakePictureNormal();

/* -------------------------------------------------------------------------- */

PUBLIC bool
appTaskCameraIsReady( void );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_CAMERA_H */
