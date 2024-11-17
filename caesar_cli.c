/*
 * FILE          caesar_cli.c
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include <caesar.h>

#define PROG_NAME "caesar"
#define COMMAND_ENCRYPT_NAME "encrypt"
#define COMMAND_DECRYPT_NAME "decrypt"
#define COMMAND_BRUTFORCE_NAME "bruteforce"

typedef int bool32_t;

static void
PrintHelp(void)
{
    fprintf(stdout, "%s [command] [arguments...]\n", PROG_NAME);
    fprintf(stdout, "    This program shifts ASCII alphabet. All other characters ignored\n");
    fprintf(stdout, "    encrypt    [message] [key]\n");
    fprintf(stdout, "    decrypt    [message] [key]\n");
    fprintf(stdout, "    bruteforce [message]\n");
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

    bool32_t isEncrypt = strcmp(command, COMMAND_ENCRYPT_NAME) == 0;
    bool32_t isDecrypt = strcmp(command, COMMAND_DECRYPT_NAME) == 0;

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

        Caesar_ShiftMessage(resultBuffer, resultBufferSize, message, shift);
        resultBuffer[messageLength] = 0;
        printf("%s\n", resultBuffer);

        free(resultBuffer);

    } else if (strcmp(command, COMMAND_BRUTFORCE_NAME) == 0) {
        size_t resultBufferSize = messageLength + 1;
        char *resultBuffer = malloc(resultBufferSize);
        memset(resultBuffer, 0, resultBufferSize);

        for (int shift = 0; shift < ('z' - 'a'); ++shift) {
            Caesar_ShiftMessage(resultBuffer, resultBufferSize, message, shift);
            printf("%s (key = %2d)\n", resultBuffer, shift);
        }

        free(resultBuffer);
    } else {
        PrintHelp();
        fprintf(stderr, "Unknown command: %s\n", command);
    }

    return 0;
}
