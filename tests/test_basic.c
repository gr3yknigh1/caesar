/*
 * FILE          tests/test_basic.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */

#include <nocheck/nocheck.h>

#include <string.h>

#include <caesar.h>

#define NOC_TASSERT_STRISEQ(CASEPTR, STR0, STR1) NOC_TASSERT((CASEPTR), strcmp((STR0), (STR1)) == 0)

#define _TEST_CASE(CASEPTR, IN_STR, EXP_STR, KEY) \
    do { \
        size_t resultBufferSize = strlen((IN_STR)) + 1; \
        char *resultBuffer = (char *)calloc(1, resultBufferSize); \
        Caesar_ShiftMessage(resultBuffer, resultBufferSize, (IN_STR), (KEY)); \
        NOC_TASSERT_STRISEQ((CASEPTR), resultBuffer, (EXP_STR)); \
        free(resultBuffer); \
    } while (0)

void
TC_Basic0(NOC_TestCase *c)
{
    _TEST_CASE(c, "Hello world!", "Ifmmp Xpsme!", 1);
}

void
TC_Basic1(NOC_TestCase *c)
{
}

int
main(void)
{
    NOC_TestSuite *suite = NOC_TestSuiteMake("basic");
    NOC_TestSuiteAddCase(suite, "Basic0", TC_Basic0);
    NOC_TestSuiteAddCase(suite, "Basic1", TC_Basic1);

    int exitCode = NOC_TestSuiteExecute(suite);
    NOC_TestSuiteDestroy(suite);
    return exitCode;
}
