/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_KERNEL_OS_DEFINES_H_
#define OS_PORTABLE_KERNEL_OS_DEFINES_H_

// ----------------------------------------------------------------------------
//
// This file should be included right at the bottom of all source files,
// to give access to definitions needed to decide if the file is compiled
// or not.
//
// IMPORTANT: since this is also included in assembly source files,
// it should not include anything else than preprocessor defines.

// mainly use the dynamically generated definitions

#include "xcdl/OS_Defines.h"

// ----------------------------------------------------------------------------
// Operating System versions and greeting definitions

// Notice: do not use parenthesis! (the values will be stringified)
#define OS_CFGINT_VERSION_MAJOR         4
#define OS_CFGINT_VERSION_MINOR         3
#define OS_CFGINT_VERSION_REVISION      7628

#define OS_CFGSTR_STRINGIFY(x)          OS_CFGSTR_SHARP(x)
#define OS_CFGSTR_SHARP(x)              #x

// stringify above integers
#define OS_CFGSTR_VERSION_MAJOR         OS_CFGSTR_STRINGIFY(OS_CFGINT_VERSION_MAJOR)
#define OS_CFGSTR_VERSION_MINOR         OS_CFGSTR_STRINGIFY(OS_CFGINT_VERSION_MINOR)
#define OS_CFGSTR_VERSION_REVISION      OS_CFGSTR_STRINGIFY(OS_CFGINT_VERSION_REVISION)

#define OS_CFGSTR_VERSION               OS_CFGSTR_VERSION_MAJOR "." OS_CFGSTR_VERSION_MINOR "." OS_CFGSTR_VERSION_REVISION

#define OS_CFGSTR_GREETING              "uOS++ v" OS_CFGSTR_VERSION ", GCC " __VERSION__

// ----------------------------------------------------------------------------

#endif /* OS_PORTABLE_KERNEL_OS_DEFINES_H_ */
