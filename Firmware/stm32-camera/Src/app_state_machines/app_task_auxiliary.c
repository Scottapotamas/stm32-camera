/**
 * @file    app_task_auxiliary.c
 *
 * @ingroup tasks
 *
 * @brief   Application Task Auxiliary I/O
 *
 *          Processing of auxiliary I/O serial data and I/O events. Expected to
 *          some protocol handling for detecting RF id tags detection that is
 *          to prevent firing on 'tagged' animals.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */

#include <ctype.h>
#include <string.h>
#include <event_subscribe.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "qassert.h"
#include "app_config.h"
#include "app_tasks.h"
#include "app_task_ids.h"
#include "app_times.h"
#include "app_signals.h"
#include "app_events.h"
#include "app_version.h"

#include "log.h"
#include "auxiliary.h"
#include "debounce.h"
#include "hal_uart.h"
#include "hal_systick.h"
#include "config.h"
#include "app_task_auxiliary.h"
#include "app_task_auxiliary_private.h"

/* -------------------------------------------------------------------------- */

//DEFINE_THIS_FILE; /* Used for ASSERT checks to define __FILE__ only once */

/* ----------------------- Public Functions --------------------------------- */

PUBLIC StateTask *
appTaskAuxiliaryCreate( AppTaskAuxiliary   *me,
                        StateEvent         *eventQueueData[ ],
                        const uint8_t      eventQueueSize,
                        AuxiliaryPort_t    instance )
{
    /* Clear all task data */
    memset( me, 0, sizeof(AppTaskAuxiliary) );

    /* Initialise State Machine structures */
    AppTaskAuxiliaryConstructor( me );

    /* Aux A or Aux B or Aux C */
    me->instance = instance;

    /* Initialise State Machine Task */
    return stateTaskCreate( (StateTask*)me,
                            eventQueueData,
                            eventQueueSize,
                            0,
                            0 );
}

/* ----- Private Functions -------------------------------------------------- */

/* State Machine Construction */
PRIVATE void AppTaskAuxiliaryConstructor( AppTaskAuxiliary *me )
{
    stateTaskCtor( &me->super, (State)&AppTaskAuxiliary_initial );
}

/* -------------------------------------------------------------------------- */

/*  State Machine Initial State */
PRIVATE void AppTaskAuxiliary_initial( AppTaskAuxiliary *me,
                                       const StateEvent *e __attribute__((__unused__)) )
{
    eventSubscribe( (StateTask*)me, AUXILIARY_MODE_SIGNAL );
    STATE_INIT( &AppTaskAuxiliary_main );
}

/* -------------------------------------------------------------------------- */

/* State Machine Initial State */
PRIVATE STATE
AppTaskAuxiliary_main( AppTaskAuxiliary *me,
                       const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            LOG( AUXILIARY,
                 LOG_INFO,
                 "Auxiliary port %c mode %s",
                 me->instance + 'A',
                 auxiliary_mode_name( config_auxiliary_mode( me->instance ) ) );
            return 0;

        case STATE_INIT_SIGNAL:
            switch( config_auxiliary_mode( me->instance ) )
            {
                case AUX_MODE_NONE:
                    STATE_INIT( AppTaskAuxiliary_mode_none );
                    break;

                case AUX_MODE_IO:
                    STATE_INIT( AppTaskAuxiliary_mode_gpio );
                    break;

                case AUX_MODE_DAC:
                    STATE_INIT( AppTaskAuxiliary_mode_dac );
                    break;

                case AUX_MODE_PWM:
                    STATE_INIT( AppTaskAuxiliary_mode_pwm );
                    break;
            }
            return 0;

        case AUXILIARY_MODE_SIGNAL:
            {
                AuxiliaryModeEvent *ame = (AuxiliaryModeEvent*)e;
                if( ame->port == me->instance )
                {
                    switch( ame->mode )
                    {
                        case AUX_MODE_NONE:
                            STATE_TRAN_DYN( AppTaskAuxiliary_mode_none );
                            break;
                        case AUX_MODE_IO:
                            STATE_TRAN_DYN( AppTaskAuxiliary_mode_gpio );
                            break;
                        case AUX_MODE_DAC:
                            STATE_TRAN_DYN( AppTaskAuxiliary_mode_dac );
                            break;
                        case AUX_MODE_PWM:
                            STATE_TRAN_DYN( AppTaskAuxiliary_mode_pwm );
                            break;
                    }
                }
            }
            return 0;

    }
    return (STATE)hsmTop;
}

/* -------------------------------------------------------------------------- */

/* State Machine Mode None */
PRIVATE STATE
AppTaskAuxiliary_mode_none( AppTaskAuxiliary *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:
            auxiliary_gpio_mode( AUX_GPIO_0, AUX_GPIO_MODE_INPUT );
            auxiliary_gpio_mode( AUX_GPIO_1, AUX_GPIO_MODE_INPUT );
            auxiliary_gpio_mode( AUX_GPIO_2, AUX_GPIO_MODE_INPUT );
            return 0;
    }
    return (STATE)AppTaskAuxiliary_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE
AppTaskAuxiliary_mode_gpio( AppTaskAuxiliary *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

        case STATE_STEP1_SIGNAL:

            return 0;
    }
    return (STATE)AppTaskAuxiliary_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE
AppTaskAuxiliary_mode_dac( AppTaskAuxiliary *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

        case STATE_STEP1_SIGNAL:

            return 0;
    }
    return (STATE)AppTaskAuxiliary_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE STATE
AppTaskAuxiliary_mode_pwm( AppTaskAuxiliary *me, const StateEvent *e )
{
    switch( e->signal )
    {
        case STATE_ENTRY_SIGNAL:

        case STATE_STEP1_SIGNAL:

            return 0;
    }
    return (STATE)AppTaskAuxiliary_main;
}

/* -------------------------------------------------------------------------- */

PRIVATE void
AppTaskAuxiliary_monitor_inputs( void  )
{
    static  DebounceStatus_t debounced;
    static  uint8_t          previous;
    uint8_t input   = 0;
    uint8_t status  = 0;

    if( auxiliary_gpio_in( AUX_GPIO_0 ) ) input |= _BV(0);
    if( auxiliary_gpio_in( AUX_GPIO_1 ) ) input |= _BV(1);

    status = debounce( &debounced, input );

    if( ( status ^ previous ) & _BV(0) )
    {

    }
    if( ( status ^ previous ) & _BV(1) )
    {

    }

    previous = status;
}

/* ----- End ---------------------------------------------------------------- */

