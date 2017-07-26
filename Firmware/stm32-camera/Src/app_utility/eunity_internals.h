/* ==========================================
    eUnity Project - A Test Framework for C
    Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef EUNITY_INTERNALS_H
#define EUNITY_INTERNALS_H

#ifdef EUNITY_INCLUDE_CONFIG_H
#include "eunity_config.h"
#endif

#include <setjmp.h>

/* eUnity Attempts to Auto-Detect Integer Types
 * Attempt 1: UINT_MAX, ULONG_MAX, etc in <stdint.h>
 * Attempt 2: UINT_MAX, ULONG_MAX, etc in <limits.h>
 * Attempt 3: Deduced from sizeof() macros */
#ifndef EUNITY_EXCLUDE_STDINT_H
#include <stdint.h>
#endif

#ifndef EUNITY_EXCLUDE_LIMITS_H
#include <limits.h>
#endif

#ifndef EUNITY_EXCLUDE_SIZEOF
#ifndef UINT_MAX
#define UINT_MAX     (sizeof(unsigned int) * 256 - 1)
#endif
#ifndef ULONG_MAX
#define ULONG_MAX    (sizeof(unsigned long) * 256 - 1)
#endif
#ifndef UINTPTR_MAX
/* apparently this is not a constant expression: (sizeof(unsigned int *) * 256 - 1) so we have to just let this fall through */
#endif
#endif

#ifndef EUNITY_EXCLUDE_MATH_H
#include <math.h>
#endif

/*-------------------------------------------------------
 * Guess Widths If Not Specified
 *-------------------------------------------------------*/

/* Determine the size of an int, if not already specificied.
 * We cannot use sizeof(int), because it is not yet defined
 * at this stage in the trnslation of the C program.
 * Therefore, infer it from UINT_MAX if possible. */
#ifndef EUNITY_INT_WIDTH
  #ifdef UINT_MAX
    #if (UINT_MAX == 0xFFFF)
      #define EUNITY_INT_WIDTH (16)
    #elif (UINT_MAX == 0xFFFFFFFF)
      #define EUNITY_INT_WIDTH (32)
    #elif (UINT_MAX == 0xFFFFFFFFFFFFFFFF)
      #define EUNITY_INT_WIDTH (64)
    #endif
  #endif
#endif
#ifndef EUNITY_INT_WIDTH
  #define EUNITY_INT_WIDTH (32)
#endif

/* Determine the size of a long, if not already specified,
 * by following the process used above to define
 * EUNITY_INT_WIDTH. */
#ifndef EUNITY_LONG_WIDTH
  #ifdef ULONG_MAX
    #if (ULONG_MAX == 0xFFFF)
      #define EUNITY_LONG_WIDTH (16)
    #elif (ULONG_MAX == 0xFFFFFFFF)
      #define EUNITY_LONG_WIDTH (32)
    #elif (ULONG_MAX == 0xFFFFFFFFFFFFFFFF)
      #define EUNITY_LONG_WIDTH (64)
    #endif
  #endif
#endif
#ifndef EUNITY_LONG_WIDTH
  #define EUNITY_LONG_WIDTH (32)
#endif

/* Determine the size of a pointer, if not already specified,
 * by following the process used above to define
 * EUNITY_INT_WIDTH. */
#ifndef EUNITY_POINTER_WIDTH
  #ifdef UINTPTR_MAX
    #if (UINTPTR_MAX+0 <= 0xFFFF)
      #define EUNITY_POINTER_WIDTH (16)
    #elif (UINTPTR_MAX+0 <= 0xFFFFFFFF)
      #define EUNITY_POINTER_WIDTH (32)
    #elif (UINTPTR_MAX+0 <= 0xFFFFFFFFFFFFFFFF)
      #define EUNITY_POINTER_WIDTH (64)
    #endif
  #endif
#endif
#ifndef EUNITY_POINTER_WIDTH
  #ifdef INTPTR_MAX
    #if (INTPTR_MAX+0 <= 0x7FFF)
      #define EUNITY_POINTER_WIDTH (16)
    #elif (INTPTR_MAX+0 <= 0x7FFFFFFF)
      #define EUNITY_POINTER_WIDTH (32)
    #elif (INTPTR_MAX+0 <= 0x7FFFFFFFFFFFFFFF)
      #define EUNITY_POINTER_WIDTH (64)
    #endif
  #endif
#endif
#ifndef EUNITY_POINTER_WIDTH
  #define EUNITY_POINTER_WIDTH EUNITY_LONG_WIDTH
#endif

/*-------------------------------------------------------
 * Int Support (Define types based on detected sizes)
 *-------------------------------------------------------*/

#if (EUNITY_INT_WIDTH == 32)
    typedef unsigned char   _UU8;
    typedef unsigned short  _UU16;
    typedef unsigned int    _UU32;
    typedef signed char     _US8;
    typedef signed short    _US16;
    typedef signed int      _US32;
#elif (EUNITY_INT_WIDTH == 16)
    typedef unsigned char   _UU8;
    typedef unsigned int    _UU16;
    typedef unsigned long   _UU32;
    typedef signed char     _US8;
    typedef signed int      _US16;
    typedef signed long     _US32;
#else
    #error Invalid EUNITY_INT_WIDTH specified! (16 or 32 are supported)
#endif

/*-------------------------------------------------------
 * 64-bit Support
 *-------------------------------------------------------*/

#ifndef EUNITY_SUPPORT_64
#if EUNITY_LONG_WIDTH > 32
#define EUNITY_SUPPORT_64
#endif
#endif
#ifndef EUNITY_SUPPORT_64
#if EUNITY_POINTER_WIDTH > 32
#define EUNITY_SUPPORT_64
#endif
#endif

#ifndef EUNITY_SUPPORT_64

/* No 64-bit Support */
typedef _UU32 _U_UINT;
typedef _US32 _U_SINT;

#else

/* 64-bit Support */
#if (EUNITY_LONG_WIDTH == 32)
    typedef unsigned long long _UU64;
    typedef signed long long   _US64;
#elif (EUNITY_LONG_WIDTH == 64)
    typedef unsigned long      _UU64;
    typedef signed long        _US64;
#else
    #error Invalid EUNITY_LONG_WIDTH specified! (32 or 64 are supported)
#endif
typedef _UU64 _U_UINT;
typedef _US64 _U_SINT;

#endif

/*-------------------------------------------------------
 * Pointer Support
 *-------------------------------------------------------*/

#if (EUNITY_POINTER_WIDTH == 32)
    typedef _UU32 _UP;
#define EUNITY_DISPLAY_STYLE_POINTER EUNITY_DISPLAY_STYLE_HEX32
#elif (EUNITY_POINTER_WIDTH == 64)
    typedef _UU64 _UP;
#define EUNITY_DISPLAY_STYLE_POINTER EUNITY_DISPLAY_STYLE_HEX64
#elif (EUNITY_POINTER_WIDTH == 16)
    typedef _UU16 _UP;
#define EUNITY_DISPLAY_STYLE_POINTER EUNITY_DISPLAY_STYLE_HEX16
#else
    #error Invalid EUNITY_POINTER_WIDTH specified! (16, 32 or 64 are supported)
#endif

#ifndef EUNITY_PTR_ATTRIBUTE
#define EUNITY_PTR_ATTRIBUTE
#endif

#ifndef EUNITY_INTERNAL_PTR
#define EUNITY_INTERNAL_PTR EUNITY_PTR_ATTRIBUTE const void*
/* #define EUNITY_INTERNAL_PTR EUNITY_PTR_ATTRIBUTE const _UU8* */
#endif

/*-------------------------------------------------------
 * Float Support
 *-------------------------------------------------------*/

#ifdef EUNITY_EXCLUDE_FLOAT

/* No Floating Point Support */
#undef EUNITY_INCLUDE_FLOAT
#undef EUNITY_FLOAT_PRECISION
#undef EUNITY_FLOAT_TYPE
#undef EUNITY_FLOAT_VERBOSE

#else

#ifndef EUNITY_INCLUDE_FLOAT
#define EUNITY_INCLUDE_FLOAT
#endif

/* Floating Point Support */
#ifndef EUNITY_FLOAT_PRECISION
#define EUNITY_FLOAT_PRECISION (0.00001f)
#endif
#ifndef EUNITY_FLOAT_TYPE
#define EUNITY_FLOAT_TYPE float
#endif
typedef EUNITY_FLOAT_TYPE _UF;

#ifndef isinf
#define isinf(n) (((1.0f / f_zero) == n) ? 1 : 0) || (((-1.0f / f_zero) == n) ? 1 : 0)
#define EUNITY_FLOAT_NEEDS_ZERO
#endif

#ifndef isnan
#define isnan(n) ((n != n) ? 1 : 0)
#endif

#ifndef isneg
#define isneg(n) ((n < 0.0f) ? 1 : 0)
#endif

#ifndef ispos
#define ispos(n) ((n > 0.0f) ? 1 : 0)
#endif

#endif

/*-------------------------------------------------------
 * Double Float Support
 *-------------------------------------------------------*/

/* unlike FLOAT, we DON'T include by default */
#ifndef EUNITY_EXCLUDE_DOUBLE
#ifndef EUNITY_INCLUDE_DOUBLE
#define EUNITY_EXCLUDE_DOUBLE
#endif
#endif

#ifdef EUNITY_EXCLUDE_DOUBLE

/* No Floating Point Support */
#undef EUNITY_DOUBLE_PRECISION
#undef EUNITY_DOUBLE_TYPE
#undef EUNITY_DOUBLE_VERBOSE

#ifdef EUNITY_INCLUDE_DOUBLE
#undef EUNITY_INCLUDE_DOUBLE
#endif

#else

/* Double Floating Point Support */
#ifndef EUNITY_DOUBLE_PRECISION
#define EUNITY_DOUBLE_PRECISION (1e-12f)
#endif
#ifndef EUNITY_DOUBLE_TYPE
#define EUNITY_DOUBLE_TYPE double
#endif
typedef EUNITY_DOUBLE_TYPE _UD;

#endif

#ifdef EUNITY_DOUBLE_VERBOSE
#ifndef EUNITY_FLOAT_VERBOSE
#define EUNITY_FLOAT_VERBOSE
#endif
#endif

/*-------------------------------------------------------
 * Output Method: stdout (DEFAULT)
 *-------------------------------------------------------*/
#ifndef EUNITY_OUTPUT_CHAR
/* Default to using putchar, which is defined in stdio.h */
#include <stdio.h>
#define EUNITY_OUTPUT_CHAR(a) (void)putchar(a)
#else
  /* If defined as something else, make sure we declare it here so it's ready for use */
  #ifndef EUNITY_OMIT_OUTPUT_CHAR_HEADER_DECLARATION
extern void EUNITY_OUTPUT_CHAR(int);
  #endif
#endif

#ifndef EUNITY_OUTPUT_FLUSH
/* Default to using fflush, which is defined in stdio.h */
#include <stdio.h>
#define EUNITY_OUTPUT_FLUSH (void)fflush(stdout)
#else
  /* If defined as something else, make sure we declare it here so it's ready for use */
  #ifndef EUNITY_OMIT_OUTPUT_FLUSH_HEADER_DECLARATION
extern void EUNITY_OUTPUT_FLUSH(void);
  #endif
#endif

#ifndef EUNITY_OUTPUT_FLUSH
#define EUNITY_FLUSH_CALL()
#else
#define EUNITY_FLUSH_CALL() EUNITY_OUTPUT_FLUSH
#endif

#ifndef EUNITY_PRINT_EOL
#define EUNITY_PRINT_EOL()    EUNITY_OUTPUT_CHAR('\n')
#endif

#ifndef EUNITY_OUTPUT_START
#define EUNITY_OUTPUT_START()
#endif

#ifndef EUNITY_OUTPUT_COMPLETE
#define EUNITY_OUTPUT_COMPLETE()
#endif

/*-------------------------------------------------------
 * Footprint
 *-------------------------------------------------------*/

#ifndef EUNITY_LINE_TYPE
#define EUNITY_LINE_TYPE _U_UINT
#endif

#ifndef EUNITY_COUNTER_TYPE
#define EUNITY_COUNTER_TYPE _U_UINT
#endif

/*-------------------------------------------------------
 * Language Features Available
 *-------------------------------------------------------*/
#if !defined(EUNITY_WEAK_ATTRIBUTE) && !defined(EUNITY_WEAK_PRAGMA)
#   ifdef __GNUC__ /* includes clang */
#       if !(defined(__WIN32__) && defined(__clang__)) && !defined(__TMS470__)
#           define EUNITY_WEAK_ATTRIBUTE __attribute__((weak))
#       endif
#   endif
#endif

#ifdef EUNITY_NO_WEAK
#   undef EUNITY_WEAK_ATTRIBUTE
#   undef EUNITY_WEAK_PRAGMA
#endif


/*-------------------------------------------------------
 * Internal Structs Needed
 *-------------------------------------------------------*/

typedef void (*eUnityTestFunction)(void);

#define EUNITY_DISPLAY_RANGE_INT  (0x10)
#define EUNITY_DISPLAY_RANGE_UINT (0x20)
#define EUNITY_DISPLAY_RANGE_HEX  (0x40)
#define EUNITY_DISPLAY_RANGE_AUTO (0x80)

typedef enum
{
#if (EUNITY_INT_WIDTH == 16)
    EUNITY_DISPLAY_STYLE_INT      = 2 + EUNITY_DISPLAY_RANGE_INT + EUNITY_DISPLAY_RANGE_AUTO,
#elif (EUNITY_INT_WIDTH  == 32)
    EUNITY_DISPLAY_STYLE_INT      = 4 + EUNITY_DISPLAY_RANGE_INT + EUNITY_DISPLAY_RANGE_AUTO,
#elif (EUNITY_INT_WIDTH  == 64)
    EUNITY_DISPLAY_STYLE_INT      = 8 + EUNITY_DISPLAY_RANGE_INT + EUNITY_DISPLAY_RANGE_AUTO,
#endif
    EUNITY_DISPLAY_STYLE_INT8     = 1 + EUNITY_DISPLAY_RANGE_INT,
    EUNITY_DISPLAY_STYLE_INT16    = 2 + EUNITY_DISPLAY_RANGE_INT,
    EUNITY_DISPLAY_STYLE_INT32    = 4 + EUNITY_DISPLAY_RANGE_INT,
#ifdef EUNITY_SUPPORT_64
    EUNITY_DISPLAY_STYLE_INT64    = 8 + EUNITY_DISPLAY_RANGE_INT,
#endif

#if (EUNITY_INT_WIDTH == 16)
    EUNITY_DISPLAY_STYLE_UINT     = 2 + EUNITY_DISPLAY_RANGE_UINT + EUNITY_DISPLAY_RANGE_AUTO,
#elif (EUNITY_INT_WIDTH  == 32)
    EUNITY_DISPLAY_STYLE_UINT     = 4 + EUNITY_DISPLAY_RANGE_UINT + EUNITY_DISPLAY_RANGE_AUTO,
#elif (EUNITY_INT_WIDTH  == 64)
    EUNITY_DISPLAY_STYLE_UINT     = 8 + EUNITY_DISPLAY_RANGE_UINT + EUNITY_DISPLAY_RANGE_AUTO,
#endif
    EUNITY_DISPLAY_STYLE_UINT8    = 1 + EUNITY_DISPLAY_RANGE_UINT,
    EUNITY_DISPLAY_STYLE_UINT16   = 2 + EUNITY_DISPLAY_RANGE_UINT,
    EUNITY_DISPLAY_STYLE_UINT32   = 4 + EUNITY_DISPLAY_RANGE_UINT,
#ifdef EUNITY_SUPPORT_64
    EUNITY_DISPLAY_STYLE_UINT64   = 8 + EUNITY_DISPLAY_RANGE_UINT,
#endif
    EUNITY_DISPLAY_STYLE_HEX8     = 1 + EUNITY_DISPLAY_RANGE_HEX,
    EUNITY_DISPLAY_STYLE_HEX16    = 2 + EUNITY_DISPLAY_RANGE_HEX,
    EUNITY_DISPLAY_STYLE_HEX32    = 4 + EUNITY_DISPLAY_RANGE_HEX,
#ifdef EUNITY_SUPPORT_64
    EUNITY_DISPLAY_STYLE_HEX64    = 8 + EUNITY_DISPLAY_RANGE_HEX,
#endif
    EUNITY_DISPLAY_STYLE_UNKNOWN
} EUNITY_DISPLAY_STYLE_T;

#ifndef EUNITY_EXCLUDE_FLOAT
typedef enum _UNITY_FLOAT_TRAIT_T
{
    EUNITY_FLOAT_IS_NOT_INF       = 0,
    EUNITY_FLOAT_IS_INF,
    EUNITY_FLOAT_IS_NOT_NEG_INF,
    EUNITY_FLOAT_IS_NEG_INF,
    EUNITY_FLOAT_IS_NOT_NAN,
    EUNITY_FLOAT_IS_NAN,
    EUNITY_FLOAT_IS_NOT_DET,
    EUNITY_FLOAT_IS_DET,
    EUNITY_FLOAT_INVALID_TRAIT
} EUNITY_FLOAT_TRAIT_T;
#endif

struct _eUnity
{
    const char* TestFile;
    const char* CurrentTestName;
#ifndef EUNITY_EXCLUDE_DETAILS
    const char* CurrentDetail1;
    const char* CurrentDetail2;
#endif
    EUNITY_LINE_TYPE CurrentTestLineNumber;
    EUNITY_COUNTER_TYPE NumberOfTests;
    EUNITY_COUNTER_TYPE TestFailures;
    EUNITY_COUNTER_TYPE TestIgnores;
    EUNITY_COUNTER_TYPE CurrentTestFailed;
    EUNITY_COUNTER_TYPE CurrentTestIgnored;
    jmp_buf AbortFrame;
    eUnityTestFunction  setUp;
    eUnityTestFunction  tearDown;
};

extern struct _eUnity eUnity;

/*-------------------------------------------------------
 * Test Suite Management
 *-------------------------------------------------------*/

void eUnityBegin(const char*       filename,
                 eUnityTestFunction setUp,
                 eUnityTestFunction tearDown );
int  eUnityEnd(void);
void eUnityConcludeTest(void);
void eUnityDefaultTestRun(eUnityTestFunction Func, const char* FuncName, const int FuncLineNum);

/*-------------------------------------------------------
 * Details Support
 *-------------------------------------------------------*/

#ifdef EUNITY_EXCLUDE_DETAILS
#define EUNITY_CLR_DETAILS()
#define EUNITY_SET_DETAIL(d1)
#define EUNITY_SET_DETAILS(d1,d2)
#else
#define EUNITY_CLR_DETAILS()      { eUnity.CurrentDetail1 = 0;   eUnity.CurrentDetail2 = 0;  }
#define EUNITY_SET_DETAIL(d1)     { eUnity.CurrentDetail1 = d1;  eUnity.CurrentDetail2 = 0;  }
#define EUNITY_SET_DETAILS(d1,d2) { eUnity.CurrentDetail1 = d1;  eUnity.CurrentDetail2 = d2; }

#ifndef EUNITY_DETAIL1_NAME
#define EUNITY_DETAIL1_NAME "Function"
#endif

#ifndef EUNITY_DETAIL2_NAME
#define EUNITY_DETAIL2_NAME "Argument"
#endif
#endif

/*-------------------------------------------------------
 * Test Output
 *-------------------------------------------------------*/

void eUnityPrint(const char* string);
void eUnityPrintMask(const _U_UINT mask, const _U_UINT number);
void eUnityPrintNumberByStyle(const _U_SINT number, const EUNITY_DISPLAY_STYLE_T style);
void eUnityPrintNumber(const _U_SINT number);
void eUnityPrintNumberUnsigned(const _U_UINT number);
void eUnityPrintNumberHex(const _U_UINT number, const char nibbles);

#ifdef EUNITY_FLOAT_VERBOSE
void eUnityPrintFloat(const _UF number);
#endif

/*-------------------------------------------------------
 * Test Assertion Fuctions
 *-------------------------------------------------------
 *  Use the macros below this section instead of calling
 *  these directly. The macros have a consistent naming
 *  convention and will pull in file and line information
 *  for you. */

void eUnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber,
                            const EUNITY_DISPLAY_STYLE_T style);

void eUnityAssertEqualIntArray(EUNITY_INTERNAL_PTR expected,
                              EUNITY_INTERNAL_PTR actual,
                              const _UU32 num_elements,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber,
                              const EUNITY_DISPLAY_STYLE_T style);

void eUnityAssertBits(const _U_SINT mask,
                     const _U_SINT expected,
                     const _U_SINT actual,
                     const char* msg,
                     const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualString(const char* expected,
                            const char* actual,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualStringLen(const char* expected,
                            const char* actual,
                            const _UU32 length,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualStringArray( const char** expected,
                                  const char** actual,
                                  const _UU32 num_elements,
                                  const char* msg,
                                  const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualMemory( EUNITY_INTERNAL_PTR expected,
                             EUNITY_INTERNAL_PTR actual,
                             const _UU32 length,
                             const _UU32 num_elements,
                             const char* msg,
                             const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertNumbersWithin(const _U_UINT delta,
                              const _U_SINT expected,
                              const _U_SINT actual,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber,
                              const EUNITY_DISPLAY_STYLE_T style);

void eUnityFail(const char* message, const EUNITY_LINE_TYPE line);

void eUnityIgnore(const char* message, const EUNITY_LINE_TYPE line);

#ifndef EUNITY_EXCLUDE_FLOAT
void eUnityAssertFloatsWithin(const _UF delta,
                             const _UF expected,
                             const _UF actual,
                             const char* msg,
                             const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualFloatArray(EUNITY_PTR_ATTRIBUTE const _UF* expected,
                                EUNITY_PTR_ATTRIBUTE const _UF* actual,
                                const _UU32 num_elements,
                                const char* msg,
                                const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertFloatSpecial(const _UF actual,
                             const char* msg,
                             const EUNITY_LINE_TYPE lineNumber,
                             const EUNITY_FLOAT_TRAIT_T style);
#endif

#ifndef EUNITY_EXCLUDE_DOUBLE
void eUnityAssertDoublesWithin(const _UD delta,
                              const _UD expected,
                              const _UD actual,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertEqualDoubleArray(EUNITY_PTR_ATTRIBUTE const _UD* expected,
                                 EUNITY_PTR_ATTRIBUTE const _UD* actual,
                                 const _UU32 num_elements,
                                 const char* msg,
                                 const EUNITY_LINE_TYPE lineNumber);

void eUnityAssertDoubleSpecial(const _UD actual,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber,
                              const EUNITY_FLOAT_TRAIT_T style);
#endif

/*-------------------------------------------------------
 * Error Strings We Might Need
 *-------------------------------------------------------*/

extern const char eUnityStrErrFloat[];
extern const char eUnityStrErrDouble[];
extern const char eUnityStrErr64[];

/*-------------------------------------------------------
 * Test Running Macros
 *-------------------------------------------------------*/

#define TEST_PROTECT() (setjmp(eUnity.AbortFrame) == 0)

#define TEST_ABORT() {longjmp(eUnity.AbortFrame, 1);}

/* This tricky series of macros gives us an optional line argument to treat it as RUN_TEST(func, num=__LINE__) */
#ifndef RUN_TEST
#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define RUN_TEST(...) eUnityDefaultTestRun(RUN_TEST_FIRST(__VA_ARGS__), RUN_TEST_SECOND(__VA_ARGS__))
#define RUN_TEST_FIRST(...) RUN_TEST_FIRST_HELPER(__VA_ARGS__, throwaway)
#define RUN_TEST_FIRST_HELPER(first, ...) (first), #first
#define RUN_TEST_SECOND(...) RUN_TEST_SECOND_HELPER(__VA_ARGS__, __LINE__, throwaway)
#define RUN_TEST_SECOND_HELPER(first, second, ...) (second)
#endif
#endif
#endif

/* If we can't do the tricky version, we'll just have to require them to always include the line number */
#ifndef RUN_TEST
#ifdef CMOCK
#define RUN_TEST(func, num) eUnityDefaultTestRun(func, #func, num)
#else
#define RUN_TEST(func) eUnityDefaultTestRun(func, #func, __LINE__)
#endif
#endif

#define TEST_LINE_NUM (eUnity.CurrentTestLineNumber)
#define TEST_IS_IGNORED (eUnity.CurrentTestIgnored)
#define EUNITY_NEW_TEST(a) \
    eUnity.CurrentTestName = (a); \
    eUnity.CurrentTestLineNumber = (EUNITY_LINE_TYPE)(__LINE__); \
    eUnity.NumberOfTests++;

#ifndef EUNITY_BEGIN
#define EUNITY_BEGIN( setup, teardown ) eUnityBegin(__FILE__, setup, teardown )
#endif

#ifndef EUNITY_END
#define EUNITY_END() eUnityEnd()
#endif

#define EUNITY_UNUSED(x) (void)(sizeof(x))

/*-----------------------------------------------
 * Command Line Argument Support
 *-----------------------------------------------*/

#ifdef EUNITY_USE_COMMAND_LINE_ARGS
int eUnityParseOptions(int argc, char** argv);
int eUnityTestMatches(void);
#endif

/*-------------------------------------------------------
 * Basic Fail and Ignore
 *-------------------------------------------------------*/

#define EUNITY_TEST_FAIL(line, message)   eUnityFail(   (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_IGNORE(line, message) eUnityIgnore( (message), (EUNITY_LINE_TYPE)(line))

/*-------------------------------------------------------
 * Test Asserts
 *-------------------------------------------------------*/

#define EUNITY_TEST_ASSERT(condition, line, message)                                              if (condition) {} else {EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), (message));}
#define EUNITY_TEST_ASSERT_NULL(pointer, line, message)                                           EUNITY_TEST_ASSERT(((pointer) == NULL),  (EUNITY_LINE_TYPE)(line), (message))
#define EUNITY_TEST_ASSERT_NOT_NULL(pointer, line, message)                                       EUNITY_TEST_ASSERT(((pointer) != NULL),  (EUNITY_LINE_TYPE)(line), (message))

#define EUNITY_TEST_ASSERT_EQUAL_INT(expected, actual, line, message)                             eUnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT)
#define EUNITY_TEST_ASSERT_EQUAL_INT8(expected, actual, line, message)                            eUnityAssertEqualNumber((_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT8)
#define EUNITY_TEST_ASSERT_EQUAL_INT16(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT16)
#define EUNITY_TEST_ASSERT_EQUAL_INT32(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT32)
#define EUNITY_TEST_ASSERT_EQUAL_UINT(expected, actual, line, message)                            eUnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT)
#define EUNITY_TEST_ASSERT_EQUAL_UINT8(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(_UU8 )(expected), (_U_SINT)(_UU8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT8)
#define EUNITY_TEST_ASSERT_EQUAL_UINT16(expected, actual, line, message)                          eUnityAssertEqualNumber((_U_SINT)(_UU16)(expected), (_U_SINT)(_UU16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT16)
#define EUNITY_TEST_ASSERT_EQUAL_UINT32(expected, actual, line, message)                          eUnityAssertEqualNumber((_U_SINT)(_UU32)(expected), (_U_SINT)(_UU32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT32)
#define EUNITY_TEST_ASSERT_EQUAL_HEX8(expected, actual, line, message)                            eUnityAssertEqualNumber((_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX8)
#define EUNITY_TEST_ASSERT_EQUAL_HEX16(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX16)
#define EUNITY_TEST_ASSERT_EQUAL_HEX32(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX32)
#define EUNITY_TEST_ASSERT_BITS(mask, expected, actual, line, message)                            eUnityAssertBits((_U_SINT)(mask), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line))

#define EUNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, line, message)                     eUnityAssertNumbersWithin((delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT)
#define EUNITY_TEST_ASSERT_INT8_WITHIN(delta, expected, actual, line, message)                    eUnityAssertNumbersWithin((_UU8 )(delta), (_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT8)
#define EUNITY_TEST_ASSERT_INT16_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((_UU16)(delta), (_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT16)
#define EUNITY_TEST_ASSERT_INT32_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((_UU32)(delta), (_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT32)
#define EUNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, line, message)                    eUnityAssertNumbersWithin((delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT)
#define EUNITY_TEST_ASSERT_UINT8_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((_UU8 )(delta), (_U_SINT)(_U_UINT)(_UU8 )(expected), (_U_SINT)(_U_UINT)(_UU8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT8)
#define EUNITY_TEST_ASSERT_UINT16_WITHIN(delta, expected, actual, line, message)                  eUnityAssertNumbersWithin((_UU16)(delta), (_U_SINT)(_U_UINT)(_UU16)(expected), (_U_SINT)(_U_UINT)(_UU16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT16)
#define EUNITY_TEST_ASSERT_UINT32_WITHIN(delta, expected, actual, line, message)                  eUnityAssertNumbersWithin((_UU32)(delta), (_U_SINT)(_U_UINT)(_UU32)(expected), (_U_SINT)(_U_UINT)(_UU32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT32)
#define EUNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, line, message)                    eUnityAssertNumbersWithin((_UU8 )(delta), (_U_SINT)(_U_UINT)(_UU8 )(expected), (_U_SINT)(_U_UINT)(_UU8 )(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX8)
#define EUNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((_UU16)(delta), (_U_SINT)(_U_UINT)(_UU16)(expected), (_U_SINT)(_U_UINT)(_UU16)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX16)
#define EUNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((_UU32)(delta), (_U_SINT)(_U_UINT)(_UU32)(expected), (_U_SINT)(_U_UINT)(_UU32)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX32)

#define EUNITY_TEST_ASSERT_EQUAL_PTR(expected, actual, line, message)                             eUnityAssertEqualNumber((_U_SINT)(_UP)(expected), (_U_SINT)(_UP)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_POINTER)
#define EUNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, line, message)                          eUnityAssertEqualString((const char*)(expected), (const char*)(actual), (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len, line, message)                 eUnityAssertEqualStringLen((const char*)(expected), (const char*)(actual), (_UU32)(len), (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, line, message)                     eUnityAssertEqualMemory((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(len), 1, (message), (EUNITY_LINE_TYPE)(line))

#define EUNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, line, message)         eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT)
#define EUNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, line, message)        eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT8)
#define EUNITY_TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT16)
#define EUNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT32)
#define EUNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, line, message)        eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT)
#define EUNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT8)
#define EUNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements, line, message)      eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT16)
#define EUNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, line, message)      eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT32)
#define EUNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, line, message)        eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX8)
#define EUNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX16)
#define EUNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX32)
#define EUNITY_TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements, line, message)         eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(_UP*)(expected), (EUNITY_INTERNAL_PTR)(_UP*)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_POINTER)
#define EUNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, line, message)      eUnityAssertEqualStringArray((const char**)(expected), (const char**)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, line, message) eUnityAssertEqualMemory((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(len), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line))

#ifdef EUNITY_SUPPORT_64
#define EUNITY_TEST_ASSERT_EQUAL_INT64(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT64)
#define EUNITY_TEST_ASSERT_EQUAL_UINT64(expected, actual, line, message)                          eUnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT64)
#define EUNITY_TEST_ASSERT_EQUAL_HEX64(expected, actual, line, message)                           eUnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX64)
#define EUNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT64)
#define EUNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, line, message)      eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT64)
#define EUNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualIntArray((EUNITY_INTERNAL_PTR)(expected), (EUNITY_INTERNAL_PTR)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX64)
#define EUNITY_TEST_ASSERT_INT64_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_INT64)
#define EUNITY_TEST_ASSERT_UINT64_WITHIN(delta, expected, actual, line, message)                  eUnityAssertNumbersWithin((delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_UINT64)
#define EUNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, line, message)                   eUnityAssertNumbersWithin((delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_DISPLAY_STYLE_HEX64)
#else
#define EUNITY_TEST_ASSERT_EQUAL_INT64(expected, actual, line, message)                           EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_EQUAL_UINT64(expected, actual, line, message)                          EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_EQUAL_HEX64(expected, actual, line, message)                           EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, line, message)       EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, line, message)      EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, line, message)       EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_INT64_WITHIN(delta, expected, actual, line, message)                   EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_UINT64_WITHIN(delta, expected, actual, line, message)                  EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#define EUNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, line, message)                   EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErr64)
#endif

#ifdef EUNITY_EXCLUDE_FLOAT
#define EUNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message)                   EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message)                           EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message)       EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message)                                    EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message)                                EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message)                                    EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_DETERMINATE(actual, line, message)                            EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_INF(actual, line, message)                                EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_NEG_INF(actual, line, message)                            EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_NAN(actual, line, message)                                EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE(actual, line, message)                        EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrFloat)
#else
#define EUNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message)                   eUnityAssertFloatsWithin((_UF)(delta), (_UF)(expected), (_UF)(actual), (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message)                           EUNITY_TEST_ASSERT_FLOAT_WITHIN((_UF)(expected) * (_UF)UNITY_FLOAT_PRECISION, (_UF)(expected), (_UF)(actual), (EUNITY_LINE_TYPE)(line), (message))
#define EUNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message)       eUnityAssertEqualFloatArray((_UF*)(expected), (_UF*)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)(line))
#define EUNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message)                                    eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_INF)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message)                                eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NEG_INF)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message)                                    eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NAN)
#define EUNITY_TEST_ASSERT_FLOAT_IS_DETERMINATE(actual, line, message)                            eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_DET)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_INF(actual, line, message)                                eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_INF)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_NEG_INF(actual, line, message)                            eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_NEG_INF)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_NAN(actual, line, message)                                eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_NAN)
#define EUNITY_TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE(actual, line, message)                        eUnityAssertFloatSpecial((_UF)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_DET)
#endif

#ifdef EUNITY_EXCLUDE_DOUBLE
#define EUNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message)                  EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message)                          EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message)      EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message)                                   EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message)                               EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message)                                   EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_DETERMINATE(actual, line, message)                           EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_INF(actual, line, message)                               EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF(actual, line, message)                           EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_NAN(actual, line, message)                               EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE(actual, line, message)                       EUNITY_TEST_FAIL((EUNITY_LINE_TYPE)(line), eUnityStrErrDouble)
#else
#define EUNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message)                  eUnityAssertDoublesWithin((_UD)(delta), (_UD)(expected), (_UD)(actual), (message), (EUNITY_LINE_TYPE)line)
#define EUNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message)                          EUNITY_TEST_ASSERT_DOUBLE_WITHIN((_UD)(expected) * (_UD)UNITY_DOUBLE_PRECISION, (_UD)expected, (_UD)actual, (EUNITY_LINE_TYPE)(line), message)
#define EUNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message)      eUnityAssertEqualDoubleArray((_UD*)(expected), (_UD*)(actual), (_UU32)(num_elements), (message), (EUNITY_LINE_TYPE)line)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message)                                   eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_INF)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message)                               eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NEG_INF)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message)                                   eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NAN)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_DETERMINATE(actual, line, message)                           eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_DET)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_INF(actual, line, message)                               eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_INF)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF(actual, line, message)                           eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_NEG_INF)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_NAN(actual, line, message)                               eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_NAN)
#define EUNITY_TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE(actual, line, message)                       eUnityAssertDoubleSpecial((_UD)(actual), (message), (EUNITY_LINE_TYPE)(line), EUNITY_FLOAT_IS_NOT_DET)
#endif

/* End of EUNITY_INTERNALS_H */
#endif
