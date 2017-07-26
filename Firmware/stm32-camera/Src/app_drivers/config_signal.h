/**
 * @file      config_signal.h
 *
 * @brief     Configuration data change signalling.
 *
 * @author    Marco Hess <marco.hess@through-ip.com>
 *
 * @copyright (c) 2015 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef CONFIG_SIGNAL_H
#define CONFIG_SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ----- System Includes ---------------------------------------------------- */


/* ----- Local Includes ----------------------------------------------------- */

#include "global.h"
#include "auxiliary.h"

/* -------------------------------------------------------------------------- */
/* --- AUXILIARY CONFIGURATION SIGNALLING ----------------------------------- */
/* -------------------------------------------------------------------------- */

PUBLIC void
config_signal_auxiliary_set_mode( AuxiliaryPort_t port,
                                  AuxiliaryMode_t auxiliary_mode );

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_SIGNAL_H */

