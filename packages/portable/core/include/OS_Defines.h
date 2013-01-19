/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_CORE_OS_DEFINES_H_
#define OS_PORTABLE_CORE_OS_DEFINES_H_

// ----------------------------------------------------------------------------
//
// This file should be included right at the top of all source files,
// to give access to definitions needed to decide if the file is compiled
// or not.
//
// IMPORTANT: since this is also included in assembly source files,
// it should not include anything else than preprocessor defines.

// mainly use the dynamically generated definitions

#include "portable/core/include/XCDL_Build_Defines.h"

// ----------------------------------------------------------------------------
// Operating System versions and greeting definitions

// Notice: do not use parenthesis! (the values will be stringified)
#define OS_INTEGER_VERSION_MAJOR        5
#define OS_INTEGER_VERSION_MINOR        1
#define OS_INTEGER_VERSION_REVISION     7630

#define OS_MACRO_SHARP(x)               #x
#define OS_MACRO_STRINGIFY(x)           OS_MACRO_SHARP(x)

// stringify above integers
#define OS_STRING_VERSION_MAJOR         OS_MACRO_STRINGIFY(OS_INTEGER_VERSION_MAJOR)
#define OS_STRING_VERSION_MINOR         OS_MACRO_STRINGIFY(OS_INTEGER_VERSION_MINOR)
#define OS_STRING_VERSION_REVISION      OS_MACRO_STRINGIFY(OS_INTEGER_VERSION_REVISION)

#define OS_STRING_VERSION               OS_STRING_VERSION_MAJOR "." OS_STRING_VERSION_MINOR "." OS_STRING_VERSION_REVISION

#if defined(__clang__)
#define OS_STRING_GREETING              "uOS++ v" OS_STRING_VERSION ", clang " __clang_version__
#elif defined(__GNUC__)
#define OS_STRING_GREETING              "uOS++ v" OS_STRING_VERSION ", GCC " __VERSION__
#endif

// ----------------------------------------------------------------------------

#endif /* OS_PORTABLE_CORE_OS_DEFINES_H_ */
