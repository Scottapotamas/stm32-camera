/* =========================================================================
    eUnity Project - A Test Framework for C
    Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
============================================================================ */

#include "eunity.h"
#include <stddef.h>

/* If omitted from header, declare overrideable prototypes here so they're ready for use */
#ifdef EUNITY_OMIT_OUTPUT_CHAR_HEADER_DECLARATION
void EUNITY_OUTPUT_CHAR(int);
#endif

/* Helpful macros for us to use here */
#define EUNITY_FAIL_AND_BAIL   { eUnity.CurrentTestFailed  = 1; longjmp(eUnity.AbortFrame, 1); }
#define EUNITY_IGNORE_AND_BAIL { eUnity.CurrentTestIgnored = 1; longjmp(eUnity.AbortFrame, 1); }

/* return prematurely if we are already in failure or ignore state */
#define EUNITY_SKIP_EXECUTION  { if ((eUnity.CurrentTestFailed != 0) || (eUnity.CurrentTestIgnored != 0)) {return;} }

struct _eUnity eUnity;

static const char eUnityStrOk[]                     = "OK";
static const char eUnityStrPass[]                   = "PASS";
static const char eUnityStrFail[]                   = "FAIL";
static const char eUnityStrIgnore[]                 = "IGNORE";
static const char eUnityStrNull[]                   = "NULL";
static const char eUnityStrSpacer[]                 = ". ";
static const char eUnityStrExpected[]               = " Expected ";
static const char eUnityStrWas[]                    = " Was ";
static const char eUnityStrElement[]                = " Element ";
static const char eUnityStrByte[]                   = " Byte ";
static const char eUnityStrMemory[]                 = " Memory Mismatch.";
static const char eUnityStrDelta[]                  = " Values Not Within Delta ";
static const char eUnityStrPointless[]              = " You Asked Me To Compare Nothing, Which Was Pointless.";
static const char eUnityStrNullPointerForExpected[] = " Expected pointer to be NULL";
static const char eUnityStrNullPointerForActual[]   = " Actual pointer was NULL";
static const char eUnityStrNot[]                    = "Not ";
static const char eUnityStrInf[]                    = "Infinity";
static const char eUnityStrNegInf[]                 = "Negative Infinity";
static const char eUnityStrNaN[]                    = "NaN";
static const char eUnityStrDet[]                    = "Determinate";
static const char eUnityStrInvalidFloatTrait[]      = "Invalid Float Trait";
const char eUnityStrErrFloat[]                      = "Unity Floating Point Disabled";
const char eUnityStrErrDouble[]                     = "Unity Double Precision Disabled";
const char eUnityStrErr64[]                         = "Unity 64-bit Support Disabled";
static const char eUnityStrBreaker[]                = "-----------------------";
static const char eUnityStrResultsTests[]           = " Tests ";
static const char eUnityStrResultsFailures[]        = " Failures ";
static const char eUnityStrResultsIgnored[]         = " Ignored ";
static const char eUnityStrDetail1Name[]            = EUNITY_DETAIL1_NAME " ";
static const char eUnityStrDetail2Name[]            = " " EUNITY_DETAIL2_NAME " ";

#ifdef EUNITY_FLOAT_NEEDS_ZERO
/* Dividing by these constants produces +/- infinity.
 * The rationale is given in eUnityAssertFloatIsInf's body. */
static const _UF f_zero = 0.0f;
#endif

/* compiler-generic print formatting masks */
static const _U_UINT eUnitySizeMask[] =
{
    255u,         /* 0xFF */
    65535u,       /* 0xFFFF */
    65535u,
    4294967295u,  /* 0xFFFFFFFF */
    4294967295u,
    4294967295u,
    4294967295u
#ifdef EUNITY_SUPPORT_64
    ,0xFFFFFFFFFFFFFFFF
#endif
};

/*-----------------------------------------------
 * Pretty Printers & Test Result Output Handlers
 *-----------------------------------------------*/

void eUnityPrint(const char* string)
{
    const char* pch = string;

    if (pch != NULL)
    {
        while (*pch)
        {
            /* printable characters plus CR & LF are printed */
            if ((*pch <= 126) && (*pch >= 32))
            {
                EUNITY_OUTPUT_CHAR(*pch);
            }
            /* write escaped carriage returns */
            else if (*pch == 13)
            {
                EUNITY_OUTPUT_CHAR('\\');
                EUNITY_OUTPUT_CHAR('r');
            }
            /* write escaped line feeds */
            else if (*pch == 10)
            {
                EUNITY_OUTPUT_CHAR('\\');
                EUNITY_OUTPUT_CHAR('n');
            }
            /* unprintable characters are shown as codes */
            else
            {
                EUNITY_OUTPUT_CHAR('\\');
                eUnityPrintNumberHex((_U_UINT)*pch, 2);
            }
            pch++;
        }
    }
}

void eUnityPrintLen(const char* string, const _UU32 length);
void eUnityPrintLen(const char* string, const _UU32 length)
{
    const char* pch = string;

    if (pch != NULL)
    {
        while (*pch && (_UU32)(pch - string) < length)
        {
            /* printable characters plus CR & LF are printed */
            if ((*pch <= 126) && (*pch >= 32))
            {
                EUNITY_OUTPUT_CHAR(*pch);
            }
            /* write escaped carriage returns */
            else if (*pch == 13)
            {
                EUNITY_OUTPUT_CHAR('\\');
                EUNITY_OUTPUT_CHAR('r');
            }
            /* write escaped line feeds */
            else if (*pch == 10)
            {
                EUNITY_OUTPUT_CHAR('\\');
                EUNITY_OUTPUT_CHAR('n');
            }
            /* unprintable characters are shown as codes */
            else
            {
                EUNITY_OUTPUT_CHAR('\\');
                eUnityPrintNumberHex((_U_UINT)*pch, 2);
            }
            pch++;
        }
    }
}

/*-----------------------------------------------*/
void eUnityPrintNumberByStyle(const _U_SINT number, const EUNITY_DISPLAY_STYLE_T style)
{
    if ((style & EUNITY_DISPLAY_RANGE_INT) == EUNITY_DISPLAY_RANGE_INT)
    {
        eUnityPrintNumber(number);
    }
    else if ((style & EUNITY_DISPLAY_RANGE_UINT) == EUNITY_DISPLAY_RANGE_UINT)
    {
        eUnityPrintNumberUnsigned(  (_U_UINT)number  &  eUnitySizeMask[((_U_UINT)style & (_U_UINT)0x0F) - 1]  );
    }
    else
    {
        eUnityPrintNumberHex((_U_UINT)number, (char)((style & 0x000F) << 1));
    }
}

/*-----------------------------------------------*/
void eUnityPrintNumber(const _U_SINT number_to_print)
{
    _U_UINT number = (_U_UINT)number_to_print;

    if (number_to_print < 0)
    {
        /* A negative number, including MIN negative */
        EUNITY_OUTPUT_CHAR('-');
        number = (_U_UINT)(-number_to_print);
    }
    eUnityPrintNumberUnsigned(number);
}

/*-----------------------------------------------
 * basically do an itoa using as little ram as possible */
void eUnityPrintNumberUnsigned(const _U_UINT number)
{
    _U_UINT divisor = 1;

    /* figure out initial divisor */
    while (number / divisor > 9)
    {
        divisor *= 10;
    }

    /* now mod and print, then divide divisor */
    do
    {
        EUNITY_OUTPUT_CHAR((char)('0' + (number / divisor % 10)));
        divisor /= 10;
    }
    while (divisor > 0);
}

/*-----------------------------------------------*/
void eUnityPrintNumberHex(const _U_UINT number, const char nibbles_to_print)
{
    _U_UINT nibble;
    char nibbles = nibbles_to_print;
    EUNITY_OUTPUT_CHAR('0');
    EUNITY_OUTPUT_CHAR('x');

    while (nibbles > 0)
    {
        nibble = (number >> (--nibbles << 2)) & 0x0000000F;
        if (nibble <= 9)
        {
            EUNITY_OUTPUT_CHAR((char)('0' + nibble));
        }
        else
        {
            EUNITY_OUTPUT_CHAR((char)('A' - 10 + nibble));
        }
    }
}

/*-----------------------------------------------*/
void eUnityPrintMask(const _U_UINT mask, const _U_UINT number)
{
    _U_UINT current_bit = (_U_UINT)1 << (EUNITY_INT_WIDTH - 1);
    _US32 i;

    for (i = 0; i < EUNITY_INT_WIDTH; i++)
    {
        if (current_bit & mask)
        {
            if (current_bit & number)
            {
                EUNITY_OUTPUT_CHAR('1');
            }
            else
            {
                EUNITY_OUTPUT_CHAR('0');
            }
        }
        else
        {
            EUNITY_OUTPUT_CHAR('X');
        }
        current_bit = current_bit >> 1;
    }
}

/*-----------------------------------------------*/
#ifdef EUNITY_FLOAT_VERBOSE
#include <stdio.h>

#ifndef EUNITY_VERBOSE_NUMBER_MAX_LENGTH
# ifdef EUNITY_DOUBLE_VERBOSE
#  define EUNITY_VERBOSE_NUMBER_MAX_LENGTH 317
# else
#  define EUNITY_VERBOSE_NUMBER_MAX_LENGTH 47
# endif
#endif

void eUnityPrintFloat(_UF number)
{
    char TempBuffer[EUNITY_VERBOSE_NUMBER_MAX_LENGTH + 1];
    snprintf(TempBuffer, sizeof(TempBuffer), "%.6f", number);
    eUnityPrint(TempBuffer);
}
#endif

/*-----------------------------------------------*/

void eUnityPrintFail(void);
void eUnityPrintFail(void)
{
    eUnityPrint(eUnityStrFail);
}

void eUnityPrintOk(void);
void eUnityPrintOk(void)
{
    eUnityPrint(eUnityStrOk);
}

/*-----------------------------------------------*/
static void eUnityTestResultsBegin(const char* file, const EUNITY_LINE_TYPE line);
static void eUnityTestResultsBegin(const char* file, const EUNITY_LINE_TYPE line)
{
#ifndef EUNITY_FIXTURES
    eUnityPrint(file);
    EUNITY_OUTPUT_CHAR(':');
    eUnityPrintNumber((_U_SINT)line);
    EUNITY_OUTPUT_CHAR(':');
    eUnityPrint(eUnity.CurrentTestName);
    EUNITY_OUTPUT_CHAR(':');
#else
    EUNITY_UNUSED(file);
    EUNITY_UNUSED(line);
#endif
}

/*-----------------------------------------------*/
static void eUnityTestResultsFailBegin(const EUNITY_LINE_TYPE line);
static void eUnityTestResultsFailBegin(const EUNITY_LINE_TYPE line)
{
#ifndef EUNITY_FIXTURES
    eUnityTestResultsBegin(eUnity.TestFile, line);
#else
    EUNITY_UNUSED(line);
#endif
    eUnityPrint(eUnityStrFail);
    EUNITY_OUTPUT_CHAR(':');
}

/*-----------------------------------------------*/
void eUnityConcludeTest(void)
{
    if (eUnity.CurrentTestIgnored)
    {
        eUnity.TestIgnores++;
    }
    else if (!eUnity.CurrentTestFailed)
    {
        eUnityTestResultsBegin(eUnity.TestFile, eUnity.CurrentTestLineNumber);
        eUnityPrint(eUnityStrPass);
    }
    else
    {
        eUnity.TestFailures++;
    }

    eUnity.CurrentTestFailed = 0;
    eUnity.CurrentTestIgnored = 0;
    EUNITY_PRINT_EOL();
    EUNITY_FLUSH_CALL();
}

/*-----------------------------------------------*/
static void eUnityAddMsgIfSpecified(const char* msg);
static void eUnityAddMsgIfSpecified(const char* msg)
{
    if (msg)
    {
        eUnityPrint(eUnityStrSpacer);
#ifndef EUNITY_EXCLUDE_DETAILS
        if (eUnity.CurrentDetail1)
        {
            eUnityPrint(eUnityStrDetail1Name);
            eUnityPrint(eUnity.CurrentDetail1);
            if (eUnity.CurrentDetail2)
            {
                eUnityPrint(eUnityStrDetail2Name);
                eUnityPrint(eUnity.CurrentDetail2);
            }
            eUnityPrint(eUnityStrSpacer);
        }
#endif
        eUnityPrint(msg);
    }
}

/*-----------------------------------------------*/
static void eUnityPrintExpectedAndActualStrings(const char* expected, const char* actual);
static void eUnityPrintExpectedAndActualStrings(const char* expected, const char* actual)
{
    eUnityPrint(eUnityStrExpected);
    if (expected != NULL)
    {
        EUNITY_OUTPUT_CHAR('\'');
        eUnityPrint(expected);
        EUNITY_OUTPUT_CHAR('\'');
    }
    else
    {
      eUnityPrint(eUnityStrNull);
    }
    eUnityPrint(eUnityStrWas);
    if (actual != NULL)
    {
        EUNITY_OUTPUT_CHAR('\'');
        eUnityPrint(actual);
        EUNITY_OUTPUT_CHAR('\'');
    }
    else
    {
      eUnityPrint(eUnityStrNull);
    }
}

/*-----------------------------------------------*/
static void eUnityPrintExpectedAndActualStringsLen(const char* expected, const char* actual, const _UU32 length)
{
    eUnityPrint(eUnityStrExpected);
    if (expected != NULL)
    {
        EUNITY_OUTPUT_CHAR('\'');
        eUnityPrintLen(expected, length);
        EUNITY_OUTPUT_CHAR('\'');
    }
    else
    {
      eUnityPrint(eUnityStrNull);
    }
    eUnityPrint(eUnityStrWas);
    if (actual != NULL)
    {
        EUNITY_OUTPUT_CHAR('\'');
        eUnityPrintLen(actual, length);
        EUNITY_OUTPUT_CHAR('\'');
    }
    else
    {
      eUnityPrint(eUnityStrNull);
    }
}



/*-----------------------------------------------
 * Assertion & Control Helpers
 *-----------------------------------------------*/

static int eUnityCheckArraysForNull(EUNITY_INTERNAL_PTR expected, EUNITY_INTERNAL_PTR actual, const EUNITY_LINE_TYPE lineNumber, const char* msg)
{
    /* return true if they are both NULL */
    if ((expected == NULL) && (actual == NULL))
        return 1;

    /* throw error if just expected is NULL */
    if (expected == NULL)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrNullPointerForExpected);
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }

    /* throw error if just actual is NULL */
    if (actual == NULL)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrNullPointerForActual);
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }

    /* return false if neither is NULL */
    return 0;
}

/*-----------------------------------------------
 * Assertion Functions
 *-----------------------------------------------*/

void eUnityAssertBits(const _U_SINT mask,
                     const _U_SINT expected,
                     const _U_SINT actual,
                     const char* msg,
                     const EUNITY_LINE_TYPE lineNumber)
{
    EUNITY_SKIP_EXECUTION;

    if ((mask & expected) != (mask & actual))
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrExpected);
        eUnityPrintMask((_U_UINT)mask, (_U_UINT)expected);
        eUnityPrint(eUnityStrWas);
        eUnityPrintMask((_U_UINT)mask, (_U_UINT)actual);
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

/*-----------------------------------------------*/
void eUnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber,
                            const EUNITY_DISPLAY_STYLE_T style)
{
    EUNITY_SKIP_EXECUTION;

    if (expected != actual)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrExpected);
        eUnityPrintNumberByStyle(expected, style);
        eUnityPrint(eUnityStrWas);
        eUnityPrintNumberByStyle(actual, style);
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

#define eUnityPrintPointlessAndBail()       \
{                                          \
    eUnityTestResultsFailBegin(lineNumber); \
    eUnityPrint(eUnityStrPointless);         \
    eUnityAddMsgIfSpecified(msg);           \
    EUNITY_FAIL_AND_BAIL; }

/*-----------------------------------------------*/
void eUnityAssertEqualIntArray(EUNITY_INTERNAL_PTR expected,
                               EUNITY_INTERNAL_PTR actual,
                               const _UU32 num_elements,
                               const char* msg,
                               const EUNITY_LINE_TYPE lineNumber,
                               const EUNITY_DISPLAY_STYLE_T style)
{
    _UU32 elements = num_elements;
    EUNITY_INTERNAL_PTR ptr_exp = (EUNITY_INTERNAL_PTR)expected;
    EUNITY_INTERNAL_PTR ptr_act = (EUNITY_INTERNAL_PTR)actual;

    EUNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        eUnityPrintPointlessAndBail();
    }

    if (eUnityCheckArraysForNull((EUNITY_INTERNAL_PTR)expected, (EUNITY_INTERNAL_PTR)actual, lineNumber, msg) == 1)
        return;

    /* If style is EUNITY_DISPLAY_STYLE_INT, we'll fall into the default case rather than the INT16 or INT32 (etc) case
     * as EUNITY_DISPLAY_STYLE_INT includes a flag for EUNITY_DISPLAY_RANGE_AUTO, which the width-specific
     * variants do not. Therefore remove this flag. */
    switch(style & (EUNITY_DISPLAY_STYLE_T)(~EUNITY_DISPLAY_RANGE_AUTO))
    {
        case EUNITY_DISPLAY_STYLE_HEX8:
        case EUNITY_DISPLAY_STYLE_INT8:
        case EUNITY_DISPLAY_STYLE_UINT8:
            while (elements--)
            {
                if (*(EUNITY_PTR_ATTRIBUTE const _US8*)ptr_exp != *(EUNITY_PTR_ATTRIBUTE const _US8*)ptr_act)
                {
                    eUnityTestResultsFailBegin(lineNumber);
                    eUnityPrint(eUnityStrElement);
                    eUnityPrintNumberUnsigned(num_elements - elements - 1);
                    eUnityPrint(eUnityStrExpected);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US8*)ptr_exp, style);
                    eUnityPrint(eUnityStrWas);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US8*)ptr_act, style);
                    eUnityAddMsgIfSpecified(msg);
                    EUNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (EUNITY_INTERNAL_PTR)((_UP)ptr_exp + 1);
                ptr_act = (EUNITY_INTERNAL_PTR)((_UP)ptr_act + 1);
            }
            break;
        case EUNITY_DISPLAY_STYLE_HEX16:
        case EUNITY_DISPLAY_STYLE_INT16:
        case EUNITY_DISPLAY_STYLE_UINT16:
            while (elements--)
            {
                if (*(EUNITY_PTR_ATTRIBUTE const _US16*)ptr_exp != *(EUNITY_PTR_ATTRIBUTE const _US16*)ptr_act)
                {
                    eUnityTestResultsFailBegin(lineNumber);
                    eUnityPrint(eUnityStrElement);
                    eUnityPrintNumberUnsigned(num_elements - elements - 1);
                    eUnityPrint(eUnityStrExpected);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US16*)ptr_exp, style);
                    eUnityPrint(eUnityStrWas);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US16*)ptr_act, style);
                    eUnityAddMsgIfSpecified(msg);
                    EUNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (EUNITY_INTERNAL_PTR)((_UP)ptr_exp + 2);
                ptr_act = (EUNITY_INTERNAL_PTR)((_UP)ptr_act + 2);
            }
            break;
#ifdef EUNITY_SUPPORT_64
        case EUNITY_DISPLAY_STYLE_HEX64:
        case EUNITY_DISPLAY_STYLE_INT64:
        case EUNITY_DISPLAY_STYLE_UINT64:
            while (elements--)
            {
                if (*(EUNITY_PTR_ATTRIBUTE const _US64*)ptr_exp != *(EUNITY_PTR_ATTRIBUTE const _US64*)ptr_act)
                {
                    eUnityTestResultsFailBegin(lineNumber);
                    eUnityPrint(eUnityStrElement);
                    eUnityPrintNumberUnsigned(num_elements - elements - 1);
                    eUnityPrint(eUnityStrExpected);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US64*)ptr_exp, style);
                    eUnityPrint(eUnityStrWas);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US64*)ptr_act, style);
                    eUnityAddMsgIfSpecified(msg);
                    EUNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (EUNITY_INTERNAL_PTR)((_UP)ptr_exp + 8);
                ptr_act = (EUNITY_INTERNAL_PTR)((_UP)ptr_act + 8);
            }
            break;
#endif
        default:
            while (elements--)
            {
                if (*(EUNITY_PTR_ATTRIBUTE const _US32*)ptr_exp != *(EUNITY_PTR_ATTRIBUTE const _US32*)ptr_act)
                {
                    eUnityTestResultsFailBegin(lineNumber);
                    eUnityPrint(eUnityStrElement);
                    eUnityPrintNumberUnsigned(num_elements - elements - 1);
                    eUnityPrint(eUnityStrExpected);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US32*)ptr_exp, style);
                    eUnityPrint(eUnityStrWas);
                    eUnityPrintNumberByStyle(*(EUNITY_PTR_ATTRIBUTE const _US32*)ptr_act, style);
                    eUnityAddMsgIfSpecified(msg);
                    EUNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (EUNITY_INTERNAL_PTR)((_UP)ptr_exp + 4);
                ptr_act = (EUNITY_INTERNAL_PTR)((_UP)ptr_act + 4);
            }
            break;
    }
}

/*-----------------------------------------------*/
#ifndef EUNITY_EXCLUDE_FLOAT
void eUnityAssertEqualFloatArray(EUNITY_PTR_ATTRIBUTE const _UF* expected,
                                 EUNITY_PTR_ATTRIBUTE const _UF* actual,
                                 const _UU32 num_elements,
                                 const char* msg,
                                 const EUNITY_LINE_TYPE lineNumber)
{
    _UU32 elements = num_elements;
    EUNITY_PTR_ATTRIBUTE const _UF* ptr_expected = expected;
    EUNITY_PTR_ATTRIBUTE const _UF* ptr_actual = actual;
    _UF diff, tol;

    EUNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        eUnityPrintPointlessAndBail();
    }

    if (eUnityCheckArraysForNull((EUNITY_INTERNAL_PTR)expected, (EUNITY_INTERNAL_PTR)actual, lineNumber, msg) == 1)
        return;

    while (elements--)
    {
        diff = *ptr_expected - *ptr_actual;
        if (diff < 0.0f)
            diff = 0.0f - diff;
        tol = EUNITY_FLOAT_PRECISION * *ptr_expected;
        if (tol < 0.0f)
            tol = 0.0f - tol;

        /* This first part of this condition will catch any NaN or Infinite values */
        if (isnan(diff) || isinf(diff) || (diff > tol))
        {
            eUnityTestResultsFailBegin(lineNumber);
            eUnityPrint(eUnityStrElement);
            eUnityPrintNumberUnsigned(num_elements - elements - 1);
#ifdef EUNITY_FLOAT_VERBOSE
            eUnityPrint(eUnityStrExpected);
            eUnityPrintFloat(*ptr_expected);
            eUnityPrint(eUnityStrWas);
            eUnityPrintFloat(*ptr_actual);
#else
            eUnityPrint(eUnityStrDelta);
#endif
            eUnityAddMsgIfSpecified(msg);
            EUNITY_FAIL_AND_BAIL;
        }
        ptr_expected++;
        ptr_actual++;
    }
}

/*-----------------------------------------------*/
void eUnityAssertFloatsWithin(const _UF delta,
                             const _UF expected,
                             const _UF actual,
                             const char* msg,
                             const EUNITY_LINE_TYPE lineNumber)
{
    _UF diff = actual - expected;
    _UF pos_delta = delta;

    EUNITY_SKIP_EXECUTION;

    if (diff < 0.0f)
    {
        diff = 0.0f - diff;
    }
    if (pos_delta < 0.0f)
    {
        pos_delta = 0.0f - pos_delta;
    }

    /* This first part of this condition will catch any NaN or Infinite values */
    if (isnan(diff) || isinf(diff) || (pos_delta < diff))
    {
        eUnityTestResultsFailBegin(lineNumber);
#ifdef EUNITY_FLOAT_VERBOSE
        eUnityPrint(eUnityStrExpected);
        eUnityPrintFloat(expected);
        eUnityPrint(eUnityStrWas);
        eUnityPrintFloat(actual);
#else
        eUnityPrint(eUnityStrDelta);
#endif
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

/*-----------------------------------------------*/
void eUnityAssertFloatSpecial(const _UF actual,
                             const char* msg,
                             const EUNITY_LINE_TYPE lineNumber,
                             const EUNITY_FLOAT_TRAIT_T style)
{
    const char* trait_names[] = { eUnityStrInf, eUnityStrNegInf, eUnityStrNaN, eUnityStrDet };
    _U_SINT should_be_trait   = ((_U_SINT)style & 1);
    _U_SINT is_trait          = !should_be_trait;
    _U_SINT trait_index       = (_U_SINT)(style >> 1);

    EUNITY_SKIP_EXECUTION;

    switch(style)
    {
        /* To determine Inf / Neg Inf, we compare to an Inf / Neg Inf value we create on the fly
         * We are using a variable to hold the zero value because some compilers complain about dividing by zero otherwise */
        case EUNITY_FLOAT_IS_INF:
        case EUNITY_FLOAT_IS_NOT_INF:
            is_trait = isinf(actual) & ispos(actual);
            break;
        case EUNITY_FLOAT_IS_NEG_INF:
        case EUNITY_FLOAT_IS_NOT_NEG_INF:
            is_trait = isinf(actual) & isneg(actual);
            break;

        /* NaN is the only floating point value that does NOT equal itself. Therefore if Actual == Actual, then it is NOT NaN. */
        case EUNITY_FLOAT_IS_NAN:
        case EUNITY_FLOAT_IS_NOT_NAN:
            is_trait = isnan(actual);
            break;

        /* A determinate number is non infinite and not NaN. (therefore the opposite of the two above) */
        case EUNITY_FLOAT_IS_DET:
        case EUNITY_FLOAT_IS_NOT_DET:
            if (isinf(actual) | isnan(actual))
                is_trait = 0;
            else
                is_trait = 1;
            break;

        default:
            trait_index = 0;
            trait_names[0] = eUnityStrInvalidFloatTrait;
            break;
    }

    if (is_trait != should_be_trait)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrExpected);
        if (!should_be_trait)
            eUnityPrint(eUnityStrNot);
        eUnityPrint(trait_names[trait_index]);
        eUnityPrint(eUnityStrWas);
#ifdef EUNITY_FLOAT_VERBOSE
        eUnityPrintFloat(actual);
#else
        if (should_be_trait)
            eUnityPrint(eUnityStrNot);
        eUnityPrint(trait_names[trait_index]);
#endif
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

#endif /* not EUNITY_EXCLUDE_FLOAT */

/*-----------------------------------------------*/
#ifndef EUNITY_EXCLUDE_DOUBLE
void eUnityAssertEqualDoubleArray(EUNITY_PTR_ATTRIBUTE const _UD* expected,
                                 EUNITY_PTR_ATTRIBUTE const _UD* actual,
                                 const _UU32 num_elements,
                                 const char* msg,
                                 const EUNITY_LINE_TYPE lineNumber)
{
    _UU32 elements = num_elements;
    EUNITY_PTR_ATTRIBUTE const _UD* ptr_expected = expected;
    EUNITY_PTR_ATTRIBUTE const _UD* ptr_actual = actual;
    _UD diff, tol;

    EUNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        eUnityPrintPointlessAndBail();
    }

    if (eUnityCheckArraysForNull((EUNITY_INTERNAL_PTR)expected, (EUNITY_INTERNAL_PTR)actual, lineNumber, msg) == 1)
        return;

    while (elements--)
    {
        diff = *ptr_expected - *ptr_actual;
        if (diff < 0.0)
          diff = 0.0 - diff;
        tol = EUNITY_DOUBLE_PRECISION * *ptr_expected;
        if (tol < 0.0)
            tol = 0.0 - tol;

        /* This first part of this condition will catch any NaN or Infinite values */
        if (isnan(diff) || isinf(diff) || (diff > tol))
        {
            eUnityTestResultsFailBegin(lineNumber);
            eUnityPrint(eUnityStrElement);
            eUnityPrintNumberUnsigned(num_elements - elements - 1);
#ifdef EUNITY_DOUBLE_VERBOSE
            eUnityPrint(eUnityStrExpected);
            eUnityPrintFloat((float)(*ptr_expected));
            eUnityPrint(eUnityStrWas);
            eUnityPrintFloat((float)(*ptr_actual));
#else
            eUnityPrint(eUnityStrDelta);
#endif
            eUnityAddMsgIfSpecified(msg);
            EUNITY_FAIL_AND_BAIL;
        }
        ptr_expected++;
        ptr_actual++;
    }
}

/*-----------------------------------------------*/
void eUnityAssertDoublesWithin(const _UD delta,
                              const _UD expected,
                              const _UD actual,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber)
{
    _UD diff = actual - expected;
    _UD pos_delta = delta;

    EUNITY_SKIP_EXECUTION;

    if (diff < 0.0)
    {
        diff = 0.0 - diff;
    }
    if (pos_delta < 0.0)
    {
        pos_delta = 0.0 - pos_delta;
    }

    /* This first part of this condition will catch any NaN or Infinite values */
    if (isnan(diff) || isinf(diff) || (pos_delta < diff))
    {
        eUnityTestResultsFailBegin(lineNumber);
#ifdef EUNITY_DOUBLE_VERBOSE
        eUnityPrint(eUnityStrExpected);
        eUnityPrintFloat((float)expected);
        eUnityPrint(eUnityStrWas);
        eUnityPrintFloat((float)actual);
#else
        eUnityPrint(eUnityStrDelta);
#endif
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

/*-----------------------------------------------*/

void eUnityAssertDoubleSpecial(const _UD actual,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber,
                              const EUNITY_FLOAT_TRAIT_T style)
{
    const char* trait_names[] = { eUnityStrInf, eUnityStrNegInf, eUnityStrNaN, eUnityStrDet };
    _U_SINT should_be_trait   = ((_U_SINT)style & 1);
    _U_SINT is_trait          = !should_be_trait;
    _U_SINT trait_index       = (_U_SINT)(style >> 1);

    EUNITY_SKIP_EXECUTION;

     switch(style)
    {
        /* To determine Inf / Neg Inf, we compare to an Inf / Neg Inf value we create on the fly
         * We are using a variable to hold the zero value because some compilers complain about dividing by zero otherwise */
        case EUNITY_FLOAT_IS_INF:
        case EUNITY_FLOAT_IS_NOT_INF:
            is_trait = isinf(actual) & ispos(actual);
            break;
        case EUNITY_FLOAT_IS_NEG_INF:
        case EUNITY_FLOAT_IS_NOT_NEG_INF:
            is_trait = isinf(actual) & isneg(actual);
            break;

        /* NaN is the only floating point value that does NOT equal itself. Therefore if Actual == Actual, then it is NOT NaN. */
        case EUNITY_FLOAT_IS_NAN:
        case EUNITY_FLOAT_IS_NOT_NAN:
            is_trait = isnan(actual);
            break;

        /* A determinate number is non infinite and not NaN. (therefore the opposite of the two above) */
        case EUNITY_FLOAT_IS_DET:
        case EUNITY_FLOAT_IS_NOT_DET:
            if (isinf(actual) | isnan(actual))
                is_trait = 0;
            else
                is_trait = 1;
            break;

        default:
            trait_index = 0;
            trait_names[0] = eUnityStrInvalidFloatTrait;
            break;
    }

    if (is_trait != should_be_trait)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrExpected);
        if (!should_be_trait)
            eUnityPrint(eUnityStrNot);
        eUnityPrint(trait_names[trait_index]);
        eUnityPrint(eUnityStrWas);
#ifdef EUNITY_DOUBLE_VERBOSE
        eUnityPrintFloat(actual);
#else
        if (should_be_trait)
            eUnityPrint(eUnityStrNot);
        eUnityPrint(trait_names[trait_index]);
#endif
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}


#endif /* not EUNITY_EXCLUDE_DOUBLE */

/*-----------------------------------------------*/
void eUnityAssertNumbersWithin( const _U_UINT delta,
                               const _U_SINT expected,
                               const _U_SINT actual,
                               const char* msg,
                               const EUNITY_LINE_TYPE lineNumber,
                               const EUNITY_DISPLAY_STYLE_T style)
{
    EUNITY_SKIP_EXECUTION;

    if ((style & EUNITY_DISPLAY_RANGE_INT) == EUNITY_DISPLAY_RANGE_INT)
    {
        if (actual > expected)
            eUnity.CurrentTestFailed = ((_U_UINT)(actual - expected) > delta);
        else
            eUnity.CurrentTestFailed = ((_U_UINT)(expected - actual) > delta);
    }
    else
    {
        if ((_U_UINT)actual > (_U_UINT)expected)
            eUnity.CurrentTestFailed = ((_U_UINT)(actual - expected) > delta);
        else
            eUnity.CurrentTestFailed = ((_U_UINT)(expected - actual) > delta);
    }

    if (eUnity.CurrentTestFailed)
    {
        eUnityTestResultsFailBegin(lineNumber);
        eUnityPrint(eUnityStrDelta);
        eUnityPrintNumberByStyle((_U_SINT)delta, style);
        eUnityPrint(eUnityStrExpected);
        eUnityPrintNumberByStyle(expected, style);
        eUnityPrint(eUnityStrWas);
        eUnityPrintNumberByStyle(actual, style);
        eUnityAddMsgIfSpecified(msg);
        EUNITY_FAIL_AND_BAIL;
    }
}

/*-----------------------------------------------*/
void eUnityAssertEqualString(const char* expected,
                            const char* actual,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber)
{
    _UU32 i;

    EUNITY_SKIP_EXECUTION;

    /* if both pointers not null compare the strings */
    if (expected && actual)
    {
        for (i = 0; expected[i] || actual[i]; i++)
        {
            if (expected[i] != actual[i])
            {
                eUnity.CurrentTestFailed = 1;
                break;
            }
        }
    }
    else
    { /* handle case of one pointers being null (if both null, test should pass) */
        if (expected != actual)
        {
            eUnity.CurrentTestFailed = 1;
        }
    }

    if (eUnity.CurrentTestFailed)
    {
      eUnityTestResultsFailBegin(lineNumber);
      eUnityPrintExpectedAndActualStrings(expected, actual);
      eUnityAddMsgIfSpecified(msg);
      EUNITY_FAIL_AND_BAIL;
    }
}

/*-----------------------------------------------*/
void eUnityAssertEqualStringLen(const char* expected,
                            const char* actual,
                            const _UU32 length,
                            const char* msg,
                            const EUNITY_LINE_TYPE lineNumber)
{
    _UU32 i;

    EUNITY_SKIP_EXECUTION;

    /* if both pointers not null compare the strings */
    if (expected && actual)
    {
        for (i = 0; (expected[i] || actual[i]) && i < length; i++)
        {
            if (expected[i] != actual[i])
            {
                eUnity.CurrentTestFailed = 1;
                break;
            }
        }
    }
    else
    { /* handle case of one pointers being null (if both null, test should pass) */
        if (expected != actual)
        {
            eUnity.CurrentTestFailed = 1;
        }
    }

    if (eUnity.CurrentTestFailed)
    {
      eUnityTestResultsFailBegin(lineNumber);
      eUnityPrintExpectedAndActualStringsLen(expected, actual, length);
      eUnityAddMsgIfSpecified(msg);
      EUNITY_FAIL_AND_BAIL;
    }
}


/*-----------------------------------------------*/
void eUnityAssertEqualStringArray( const char** expected,
                                  const char** actual,
                                  const _UU32 num_elements,
                                  const char* msg,
                                  const EUNITY_LINE_TYPE lineNumber)
{
    _UU32 i, j = 0;

    EUNITY_SKIP_EXECUTION;

    /* if no elements, it's an error */
    if (num_elements == 0)
    {
        eUnityPrintPointlessAndBail();
    }

    if (eUnityCheckArraysForNull((EUNITY_INTERNAL_PTR)expected, (EUNITY_INTERNAL_PTR)actual, lineNumber, msg) == 1)
        return;

    do
    {
        /* if both pointers not null compare the strings */
        if (expected[j] && actual[j])
        {
            for (i = 0; expected[j][i] || actual[j][i]; i++)
            {
                if (expected[j][i] != actual[j][i])
                {
                    eUnity.CurrentTestFailed = 1;
                    break;
                }
            }
        }
        else
        { /* handle case of one pointers being null (if both null, test should pass) */
            if (expected[j] != actual[j])
            {
                eUnity.CurrentTestFailed = 1;
            }
        }

        if (eUnity.CurrentTestFailed)
        {
            eUnityTestResultsFailBegin(lineNumber);
            if (num_elements > 1)
            {
                eUnityPrint(eUnityStrElement);
                eUnityPrintNumberUnsigned(j);
            }
            eUnityPrintExpectedAndActualStrings((const char*)(expected[j]), (const char*)(actual[j]));
            eUnityAddMsgIfSpecified(msg);
            EUNITY_FAIL_AND_BAIL;
        }
    } while (++j < num_elements);
}

/*-----------------------------------------------*/
void eUnityAssertEqualMemory( EUNITY_INTERNAL_PTR expected,
                              EUNITY_INTERNAL_PTR actual,
                              const _UU32 length,
                              const _UU32 num_elements,
                              const char* msg,
                              const EUNITY_LINE_TYPE lineNumber)
{
    EUNITY_PTR_ATTRIBUTE const unsigned char* ptr_exp = (EUNITY_PTR_ATTRIBUTE const unsigned char*)expected;
    EUNITY_PTR_ATTRIBUTE const unsigned char* ptr_act = (EUNITY_PTR_ATTRIBUTE const unsigned char*)actual;
    _UU32 elements = num_elements;
    _UU32 bytes;

    EUNITY_SKIP_EXECUTION;

    if ((elements == 0) || (length == 0))
    {
        eUnityPrintPointlessAndBail();
    }

    if (eUnityCheckArraysForNull((EUNITY_INTERNAL_PTR)expected, (EUNITY_INTERNAL_PTR)actual, lineNumber, msg) == 1)
        return;

    while (elements--)
    {
        /* /////////////////////////////////// */
        bytes = length;
        while (bytes--)
        {
            if (*ptr_exp != *ptr_act)
            {
                eUnityTestResultsFailBegin(lineNumber);
                eUnityPrint(eUnityStrMemory);
                if (num_elements > 1)
                {
                    eUnityPrint(eUnityStrElement);
                    eUnityPrintNumberUnsigned(num_elements - elements - 1);
                }
                eUnityPrint(eUnityStrByte);
                eUnityPrintNumberUnsigned(length - bytes - 1);
                eUnityPrint(eUnityStrExpected);
                eUnityPrintNumberByStyle(*ptr_exp, EUNITY_DISPLAY_STYLE_HEX8);
                eUnityPrint(eUnityStrWas);
                eUnityPrintNumberByStyle(*ptr_act, EUNITY_DISPLAY_STYLE_HEX8);
                eUnityAddMsgIfSpecified(msg);
                EUNITY_FAIL_AND_BAIL;
            }
            ptr_exp = (EUNITY_INTERNAL_PTR)((_UP)ptr_exp + 1);
            ptr_act = (EUNITY_INTERNAL_PTR)((_UP)ptr_act + 1);
        }
        /* /////////////////////////////////// */

    }
}

/*-----------------------------------------------
 * Control Functions
 *-----------------------------------------------*/

void eUnityFail(const char* msg, const EUNITY_LINE_TYPE line)
{
    EUNITY_SKIP_EXECUTION;

    eUnityTestResultsBegin(eUnity.TestFile, line);
    eUnityPrintFail();
    if (msg != NULL)
    {
        EUNITY_OUTPUT_CHAR(':');

#ifndef EUNITY_EXCLUDE_DETAILS
        if (eUnity.CurrentDetail1)
        {
            eUnityPrint(eUnityStrDetail1Name);
            eUnityPrint(eUnity.CurrentDetail1);
            if (eUnity.CurrentDetail2)
            {
                eUnityPrint(eUnityStrDetail2Name);
                eUnityPrint(eUnity.CurrentDetail2);
            }
            eUnityPrint(eUnityStrSpacer);
        }
#endif
        if (msg[0] != ' ')
        {
            EUNITY_OUTPUT_CHAR(' ');
        }
        eUnityPrint(msg);
    }

    EUNITY_FAIL_AND_BAIL;
}

/*-----------------------------------------------*/
void eUnityIgnore(const char* msg, const EUNITY_LINE_TYPE line)
{
    EUNITY_SKIP_EXECUTION;

    eUnityTestResultsBegin(eUnity.TestFile, line);
    eUnityPrint(eUnityStrIgnore);
    if (msg != NULL)
    {
      EUNITY_OUTPUT_CHAR(':');
      EUNITY_OUTPUT_CHAR(' ');
      eUnityPrint(msg);
    }
    EUNITY_IGNORE_AND_BAIL;
}

/*-----------------------------------------------*/
#if defined(EUNITY_WEAK_ATTRIBUTE)
//    EUNITY_WEAK_ATTRIBUTE void setUp(void) { }
//    EUNITY_WEAK_ATTRIBUTE void tearDown(void) { }
#elif defined(EUNITY_WEAK_PRAGMA)
#   pragma weak setUp
    void setUp(void) { }
#   pragma weak tearDown
    void tearDown(void) { }
#endif
/*-----------------------------------------------*/
void eUnityDefaultTestRun(eUnityTestFunction Func, const char* FuncName, const int FuncLineNum)
{
    eUnity.CurrentTestName = FuncName;
    eUnity.CurrentTestLineNumber = (EUNITY_LINE_TYPE)FuncLineNum;
    eUnity.NumberOfTests++;
    EUNITY_CLR_DETAILS();
    if (TEST_PROTECT())
    {
        eUnity.setUp();
        Func();
    }
    if (TEST_PROTECT() && !(eUnity.CurrentTestIgnored))
    {
        eUnity.tearDown();
    }
    eUnityConcludeTest();
}

/*-----------------------------------------------*/
void eUnityBegin(const char*        filename,
                 eUnityTestFunction setUp,
                 eUnityTestFunction tearDown )
{
    eUnity.TestFile = filename;
    eUnity.CurrentTestName = NULL;
    eUnity.CurrentTestLineNumber = 0;
    eUnity.NumberOfTests = 0;
    eUnity.TestFailures = 0;
    eUnity.TestIgnores = 0;
    eUnity.CurrentTestFailed = 0;
    eUnity.CurrentTestIgnored = 0;
    eUnity.setUp = setUp;
    eUnity.tearDown = tearDown;

    EUNITY_CLR_DETAILS();
    EUNITY_OUTPUT_START();
}

/*-----------------------------------------------*/
int eUnityEnd(void)
{
    EUNITY_PRINT_EOL();
    eUnityPrint(eUnityStrBreaker);
    EUNITY_PRINT_EOL();
    eUnityPrintNumber((_U_SINT)(eUnity.NumberOfTests));
    eUnityPrint(eUnityStrResultsTests);
    eUnityPrintNumber((_U_SINT)(eUnity.TestFailures));
    eUnityPrint(eUnityStrResultsFailures);
    eUnityPrintNumber((_U_SINT)(eUnity.TestIgnores));
    eUnityPrint(eUnityStrResultsIgnored);
    EUNITY_PRINT_EOL();
    if (eUnity.TestFailures == 0U)
    {
        eUnityPrintOk();
    }
    else
    {
        eUnityPrintFail();
#ifdef EUNITY_DIFFERENTIATE_FINAL_FAIL
        EUNITY_OUTPUT_CHAR('E'); EUNITY_OUTPUT_CHAR('D');
#endif
    }
    EUNITY_PRINT_EOL();
    EUNITY_FLUSH_CALL();
    EUNITY_OUTPUT_COMPLETE();
    return (int)(eUnity.TestFailures);
}

/*-----------------------------------------------
 * Command Line Argument Support
 *-----------------------------------------------*/
#ifdef EUNITY_USE_COMMAND_LINE_ARGS

char* eUnityOptionIncludeNamed = NULL;
char* eUnityOptionExcludeNamed = NULL;
int   eUnityVerbosity          = 1;

int eUnityParseOptions(int argc, char** argv)
{
    eUnityOptionIncludeNamed = NULL;
    eUnityOptionExcludeNamed = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'l': /* list tests */
                    return -1;
                case 'n': /* include tests with name including this string */
                case 'f': /* an alias for -n */
                    if (argv[i][2] == '=')
                        eUnityOptionIncludeNamed = &argv[i][3];
                    else if (++i < argc)
                        eUnityOptionIncludeNamed = argv[i];
                    else
                    {
                        eUnityPrint("ERROR: No Test String to Include Matches For");
                        EUNITY_PRINT_EOL();
                        return 1;
                    }
                    break;
                case 'q': /* quiet */
                    eUnityVerbosity = 0;
                    break;
                case 'v': /* verbose */
                    eUnityVerbosity = 2;
                    break;
                case 'x': /* exclude tests with name including this string */
                    if (argv[i][2] == '=')
                        eUnityOptionExcludeNamed = &argv[i][3];
                    else if (++i < argc)
                        eUnityOptionExcludeNamed = argv[i];
                    else
                    {
                        eUnityPrint("ERROR: No Test String to Exclude Matches For");
                        EUNITY_PRINT_EOL();
                        return 1;
                    }
                    break;
                default:
                    eUnityPrint("ERROR: Unknown Option ");
                    EUNITY_OUTPUT_CHAR(argv[i][1]);
                    EUNITY_PRINT_EOL();
                    return 1;
            }
        }
    }

    return 0;
}

int IsStringInBiggerString(const char* longstring, const char* shortstring)
{
    char* lptr = (char*)longstring;
    char* sptr = (char*)shortstring;
    char* lnext = lptr;

    if (*sptr == '*')
        return 1;

    while (*lptr)
    {
        lnext = lptr + 1;

        /* If they current bytes match, go on to the next bytes */
        while (*lptr && *sptr && (*lptr == *sptr))
        {
            lptr++;
            sptr++;

            /* We're done if we match the entire string or up to a wildcard */
            if (*sptr == '*')
                return 1;
            if (*sptr == ',')
                return 1;
            if (*sptr == '"')
                return 1;
            if (*sptr == '\'')
                return 1;
            if (*sptr == ':')
                return 2;
            if (*sptr == 0)
                return 1;
        }

        /* Otherwise we start in the long pointer 1 character further and try again */
        lptr = lnext;
        sptr = (char*)shortstring;
    }
    return 0;
}

int eUnityStringArgumentMatches(const char* str)
{
    int retval;
    const char* ptr1;
    const char* ptr2;
    const char* ptrf;

    //Go through the options and get the substrings for matching one at a time
    ptr1 = str;
    while (ptr1[0] != 0)
    {
        if ((ptr1[0] == '"') || (ptr1[0] == '\''))
            ptr1++;

        //look for the start of the next partial
        ptr2 = ptr1;
        ptrf = 0;
        do {
            ptr2++;
            if ((ptr2[0] == ':') && (ptr2[1] != 0) && (ptr2[0] != '\'') && (ptr2[0] != '"') && (ptr2[0] != ','))
                ptrf = &ptr2[1];
        } while ((ptr2[0] != 0) && (ptr2[0] != '\'') && (ptr2[0] != '"') && (ptr2[0] != ','));
        while ((ptr2[0] != 0) && ((ptr2[0] == ':') || (ptr2[0] == '\'') || (ptr2[0] == '"') || (ptr2[0] == ',')))
            ptr2++;

        //done if complete filename match
        retval = IsStringInBiggerString(eUnityTestFile, ptr1);
        if (retval == 1)
            return retval;

        //done if testname match after filename partial match
        if ((retval == 2) && (ptrf != 0))
        {
            if (IsStringInBiggerString(eUnityCurrentTestName, ptrf))
                return 1;
        }

        //done if complete testname match
        if (IsStringInBiggerString(eUnityCurrentTestName, ptr1) == 1)
            return 1;

        ptr1 = ptr2;
    }

    //we couldn't find a match for any substrings
    return 0;
}

int eUnityTestMatches(void)
{
    /* Check if this test name matches the included test pattern */
    int retval;
    if (eUnityOptionIncludeNamed)
    {
        retval = eUnityStringArgumentMatches(eUnityOptionIncludeNamed);
    }
    else
        retval = 1;

    /* Check if this test name matches the excluded test pattern */
    if (eUnityOptionExcludeNamed)
    {
        if (eUnityStringArgumentMatches(eUnityOptionExcludeNamed))
            retval = 0;
    }
    return retval;
}

#endif /* EUNITY_USE_COMMAND_LINE_ARGS */
/*-----------------------------------------------*/
