/*
 * InfSec. Assignment 3.
 *
 * FILE          caesar.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PROG_NAME "caesar"
#define COMMAND_ENCRYPT_NAME "encrypt"
#define COMMAND_DECRYPT_NAME "decrypt"
#define COMMAND_BRUTFORCE_NAME "bruteforce"

#define ASCII_UPPER_FIRST 'A'
#define ASCII_UPPER_LAST 'Z'
#define ASCII_LOWER_FIRST 'a'
#define ASCII_LOWER_LAST 'z'

typedef int bool32;

static void
PrintHelp(void)
{
    fprintf(stdout, "%s [command] [arguments...]\n", PROG_NAME);
    fprintf(stdout, "    This program shifts ASCII alphabet. All other characters ignored\n");
    fprintf(stdout, "    encrypt    [message] [key]\n");
    fprintf(stdout, "    decrypt    [message] [key]\n");
    fprintf(stdout, "    bruteforce [message]\n");
}

static char
ShiftChar(int c, int shift)
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

static void
ShiftMessage(char *outBuffer, size_t outBufferSize, const char *message, int shift)
{
    for (size_t messageIndex = 0; messageIndex < outBufferSize; ++messageIndex) {
        char shiftedChar = ShiftChar(message[messageIndex], shift);
        outBuffer[messageIndex] = shiftedChar;
    }
}

int
main(int argc, char *argv[])
{
    const static int minimumCountOfArgs = 3;

    enum {
        ARG_EXEC,
        ARG_COMMAND,
        ARG_MESSAGE,
        ARG_KEY,
        ARG_COUNT_,
    };

    if (argc < minimumCountOfArgs) {
        PrintHelp();
        return 1;
    }

    const char *command = argv[ARG_COMMAND];
    const char *message = argv[ARG_MESSAGE];
    size_t messageLength = strlen(message);

    bool32 isEncrypt = strcmp(command, COMMAND_ENCRYPT_NAME) == 0;
    bool32 isDecrypt = strcmp(command, COMMAND_DECRYPT_NAME) == 0;

    if (isEncrypt || isDecrypt) {
        if (argc < ARG_COUNT_) {
            PrintHelp();
            fprintf(stderr, "Need more arguments for command '%s'\n", command);
            return 1;
        }

        const char *key = argv[ARG_KEY];
        int shift = 0;

        if (sscanf(key, "%i", &shift) != 1) {
            fprintf(stderr, "Invalid key: %s\n", key);
            return 1;
        }

        size_t resultBufferSize = messageLength + 1;
        char *resultBuffer = malloc(resultBufferSize);
        memset(resultBuffer, 0, resultBufferSize);

        if (isDecrypt) {
            shift = shift * (-1);
        }

        ShiftMessage(resultBuffer, resultBufferSize, message, shift);
        resultBuffer[messageLength] = 0;
        printf("%s\n", resultBuffer);

    } else if (strcmp(command, COMMAND_BRUTFORCE_NAME) == 0) {
    } else {
        PrintHelp();
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }
}
