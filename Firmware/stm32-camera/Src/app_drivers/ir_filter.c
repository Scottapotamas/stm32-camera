/**
 * @file      ir_filter.h
 *

 */


#include <string.h>

/* ----- Local Includes ----------------------------------------------------- */

#include "ir_filter.h"
#include "simple_state_machine.h"
#include "hal_solenoid.h"

/* ----- Private Types ------------------------------------------------------ */

typedef enum
{
    FILTER_STATE_CLEAR = 0,
    FILTER_STATE_IR
} FilterPositionState_t;

typedef struct
{
    FilterPositionState_t previousState;
    FilterPositionState_t currentState;
    FilterPositionState_t nextState;
    uint32_t              filter_map;
} FilterPositionStateVars_t;

/* ----- Private Data ------------------------------------------------------- */

PRIVATE FilterPositionStateVars_t ir_filter_state_machine;
PRIVATE FilterPositionStateVars_t *me = &ir_filter_state_machine;

/* ----- Public Functions --------------------------------------------------- */

/** Init the filter default level */

PUBLIC void
ir_filter_init( void )
{
    memset( &ir_filter_state_machine, 0, sizeof(ir_filter_state_machine) );

    hal_solenoid_init();

    STATE_INIT_INITIAL( FILTER_STATE_CLEAR );
    ir_filter_process();
}

/* -------------------------------------------------------------------------- */

/** Set the filter to a different setting */

PUBLIC void
ir_filter_set( uint8_t id, FilterPosition_t mode )
{
    switch( mode )
    {
        case FILTER_STATE_IR:
            me->filter_map = _BV(id);
            break;

        case FILTER_STATE_CLEAR:
            me->filter_map &= ~_BV(id);
            break;
    }
    ir_filter_process();
}

/* -------------------------------------------------------------------------- */

PUBLIC FilterPosition_t
ir_filter_get( void )
{
    return me->filter_map ? FILTER_STATE_IR : FILTER_STATE_CLEAR;
}

/* -------------------------------------------------------------------------- */

/** Process the ir filter setting */

PUBLIC void
ir_filter_process( void )
{
    do
    {
        switch( me->currentState )
        {
           case FILTER_STATE_CLEAR:
               STATE_ENTRY_ACTION
                   me->filter_map = 0;
                   hal_solenoid_activate( false ); //drive the IR filter
                   hal_delay_ms(50);
                   hal_solenoid_off();  //disable output to save power

               STATE_TRANSITION_TEST
                    if( me->filter_map != 0 )
                    {
                        STATE_NEXT( FILTER_STATE_IR );
                    }
                STATE_EXIT_ACTION
                STATE_END
                break;

           case FILTER_STATE_IR:
               STATE_ENTRY_ACTION
                   hal_solenoid_activate( true );   //drive the IR filter
               	   hal_delay_ms(50);
                   hal_solenoid_off();  //disable output to save power
                STATE_TRANSITION_TEST
                    if( me->filter_map == 0 )
                    {
                        STATE_NEXT( FILTER_STATE_CLEAR );
                    }
                STATE_EXIT_ACTION
                STATE_END
                break;
        }
    } while( STATE_IS_TRANSITIONING );
}

/* ----- End ---------------------------------------------------------------- */
