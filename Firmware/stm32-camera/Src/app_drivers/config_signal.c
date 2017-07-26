/**
 * @file      config_signal.c
 *
 * @brief     Support module to handling signalling changes confir parameters.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "config_signal.h"

#include "qassert.h"
#include "app_config.h"
#include "app_events.h"
#include "app_signals.h"
#include "event_subscribe.h"

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION SIGNALLING ----------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC void
config_signal_auxiliary_set_mode( AuxiliaryPort_t port,
                                  AuxiliaryMode_t auxiliary_mode )
{
    AuxiliaryModeEvent * ame = EVENT_NEW( AuxiliaryModeEvent,
                                          AUXILIARY_MODE_SIGNAL );

    /* Send signal so that auxiliary tasks switch modes */
    if( ame )
    {
        ame->port = port;
        ame->mode = auxiliary_mode;
        eventPublish( (StateEvent*)ame );
    }
}									  

/* ----- End ---------------------------------------------------------------- */


