// -*- C++ -*-
//===--------------------------- climits ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_CLIMITS
#define _LIBCPP_CLIMITS

/*
    climits synopsis

Macros:

    CHAR_BIT
    SCHAR_MIN
    SCHAR_MAX
    UCHAR_MAX
    CHAR_MIN
    CHAR_MAX
    MB_LEN_MAX
    SHRT_MIN
    SHRT_MAX
    USHRT_MAX
    INT_MIN
    INT_MAX
    UINT_MAX
    LONG_MIN
    LONG_MAX
    ULONG_MAX
    LLONG_MIN   // C99
    LLONG_MAX   // C99
    ULLONG_MAX  // C99

*/

#if defined(__MICRO_OS_PLUS_PLUS__)
#include "portable/language/cpp/include/__config.h"
#include <limits.h>

#else
#include <__config>
#include <limits.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif
#endif

#endif  // _LIBCPP_CLIMITS
