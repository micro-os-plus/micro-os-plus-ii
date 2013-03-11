//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//
// References are to ISO/IEC 14882:2011(E) Third edition (2011-09-01).
//

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include <stdlib.h>

namespace os
{
  namespace std
  {

    using ::size_t;
    using ::div_t;
    using ::ldiv_t;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::lldiv_t;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::atof;
    using ::atoi;
    using ::atol;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::atoll;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::strtod;
    using ::strtof;
    using ::strtold;
    using ::strtol;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::strtoll;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::strtoul;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::strtoull;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::rand;
    using ::srand;
    using ::calloc;
    using ::free;
    using ::malloc;
    using ::realloc;
    using ::abort;
    using ::atexit;
    using ::exit;
    using ::_Exit;
    using ::getenv;
    using ::system;
    using ::bsearch;
    using ::qsort;
    using ::abs;
    using ::labs;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::llabs;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::div;
    using ::ldiv;
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    using ::lldiv;
#endif // _LIBCPP_HAS_NO_LONG_LONG
    using ::mblen;
    using ::mbtowc;
    using ::wctomb;
    using ::mbstowcs;
    using ::wcstombs;
#ifdef _LIBCPP_HAS_QUICK_EXIT
    using ::at_quick_exit;
    using ::quick_exit;
#endif
#ifdef _LIBCPP_HAS_C11_FEATURES
    using ::aligned_alloc;
#endif

// MSVC already has the correct prototype in <stdlib.h.h> #ifdef __cplusplus
#if !defined(_MSC_VER) && !defined(__sun__)
    inline _LIBCPP_INLINE_VISIBILITY long
    abs(long __x) _NOEXCEPT
    {
      return labs(__x);
    }
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    inline _LIBCPP_INLINE_VISIBILITY long long
    abs(long long __x) _NOEXCEPT
    {
      return llabs(__x);
    }
#endif // _LIBCPP_HAS_NO_LONG_LONG
    inline _LIBCPP_INLINE_VISIBILITY ldiv_t
    div(long __x, long __y) _NOEXCEPT
    {
      return ldiv(__x, __y);
    }
#ifndef _LIBCPP_HAS_NO_LONG_LONG
    inline _LIBCPP_INLINE_VISIBILITY lldiv_t
    div(long long __x, long long __y) _NOEXCEPT
    {
      return lldiv(__x, __y);
    }
#endif // _LIBCPP_HAS_NO_LONG_LONG
#endif // _MSC_VER

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_
