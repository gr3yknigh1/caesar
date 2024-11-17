/*
 * FILE          tests/test_basic.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 *
 * REFERENCE
 *
 *  - Source of shifted messages: <https://cryptii.com/pipes/caesar-cipher>
 */

#include <nocheck/nocheck.h>

#include <string.h>

#include <caesar.h>

#define NOC_TEXPECT_STRISEQ(CASEPTR, STR0, STR1) NOC_TEXPECT((CASEPTR), strcmp((STR0), (STR1)) == 0)

#define _TEST_CASE(CASEPTR, IN_STR, EXP_STR, KEY) \
    do { \
        size_t resultBufferSize = strlen((IN_STR)) + 1; \
        char *resultBuffer = (char *)calloc(1, resultBufferSize); \
        Caesar_ShiftMessage(resultBuffer, resultBufferSize, (IN_STR), (KEY)); \
        NOC_TEXPECT_STRISEQ((CASEPTR), resultBuffer, (EXP_STR)); \
        free(resultBuffer); \
    } while (0)

void
TC_Basic0(NOC_TestCase *c)
{
    _TEST_CASE(c, "Hello world!", "Ifmmp xpsme!", 1);
    _TEST_CASE(c, "Hello world!", "Mjqqt btwqi!", 5);
    _TEST_CASE(c, "Hello world!", "Czggj rjmgy!", 99);
    _TEST_CASE(c, "Hello world!", "Spwwz hzcwo!", 63);
}

void
TC_Basic1(NOC_TestCase *c)
{
    _TEST_CASE(c, "Hello world!", "Dahhk sknhz!", -30);
    _TEST_CASE(c, "Hello world!", "Xubbe mehbt!", -10);
    _TEST_CASE(c, "Hello world!", "Khoor zruog!", -23);
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
