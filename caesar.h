#if !defined(CAESAR_H_INCLUDED)
/*
 * FILE          caesar.h
 *
 * AUTHORS
 *               Ilya Akkuzin <gr3yknigh1@gmail.com>
 *
 * NOTICE        (c) Copyright 2024 by Ilya Akkuzin. All rights reserved.
 */
#define CAESAR_H_INCLUDED

#include <stdlib.h> // size_t

#if defined(__cplusplus)
#define CAESAR_CXX_DETECTED
#endif

#if defined(CAESAR_CXX_DETECTED)
#define CAESAR_API extern "C"
#else
#define CAESAR_API
#endif

CAESAR_API char Caesar_ShiftChar(int c, int shift);
CAESAR_API void Caesar_ShiftMessage(char *outBuffer, size_t outBufferSize, const char *message, int shift);

#endif // CAESAR_H_INCLUDED
