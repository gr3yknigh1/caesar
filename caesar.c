/*
 * FILE          caesar.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "caesar.h"

#define ASCII_UPPER_FIRST 'A'
#define ASCII_UPPER_LAST 'Z'
#define ASCII_LOWER_FIRST 'a'
#define ASCII_LOWER_LAST 'z'

char
Caesar_ShiftChar(int c, int shift)
{
    if (!isalpha(c)) {
        return c;
    }

    int first = isupper(c) ? ASCII_UPPER_FIRST : ASCII_LOWER_FIRST;
    int last = isupper(c) ? ASCII_UPPER_LAST : ASCII_LOWER_LAST;

    if (c + shift > last) {
        shift = shift - last;
    }

    if (c + shift < first) {
        shift = last + shift;
    }

    char result = c + shift;

    return result;
}

void
Caesar_ShiftMessage(char *outBuffer, size_t outBufferSize, const char *message, int shift)
{
    for (size_t messageIndex = 0; messageIndex < outBufferSize; ++messageIndex) {
        char shiftedChar = Caesar_ShiftChar(message[messageIndex], shift);
        outBuffer[messageIndex] = shiftedChar;
    }
}
