/**
 * @file    eunity_config.h
 *
 * @brief   Additional configuration for Unity.
 *          Particularly a method to override UNITY_PUTCHAR.
 *
 * @author  Marco Hess <marcoh@applidyne.com.au>
 *
 * @copyright (c) 2017 Applidyne Pty. Ltd. - All rights reserved.
 */

#ifndef EUNITY_CONFIG_H
#define EUNITY_CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif

/* ----- Local Includes ----------------------------------------------------- */

#include "hal_stdio.h"

/* ----- Defines ------------------------------------------------------------ */

#define EUNITY_OUTPUT_CHAR      hal_stdio_put

#define EUNITY_OMIT_OUTPUT_FLUSH_HEADER_DECLARATION
#define EUNITY_OUTPUT_FLUSH     hal_stdio_flush()

#define EUNITY_PRINT_EOL()      EUNITY_OUTPUT_CHAR('\r'); \
                                EUNITY_OUTPUT_CHAR('\n')

#define EUNITY_FLOAT_VERBOSE

#define TEST_ASSERT_HIGH(condition)                     EUNITY_TEST_ASSERT(  (condition), __LINE__, " Expected HIGH Was LOW")
#define TEST_ASSERT_LOW(condition)                      EUNITY_TEST_ASSERT( !(condition), __LINE__, " Expected LOW Was HIGH")

#define TEST_ASSERT_HIGH_MESSAGE(condition,message)     EUNITY_TEST_ASSERT(  (condition), __LINE__, (message) )
#define TEST_ASSERT_LOW_MESSAGE(condition,message)      EUNITY_TEST_ASSERT( !(condition), __LINE__, (message) )

/* ----- End ---------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* EUNITY_CONFIG_H */

