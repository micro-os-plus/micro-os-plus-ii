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

/// \file
/// \brief C standard library functions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include <stdlib.h>

#include "portable/language/cpp/include/abort.h"

namespace os
{
  namespace std
  {

    using ::size_t;
    using ::div_t;
    using ::ldiv_t;
    using ::lldiv_t;

//  using ::abort; //  removed, since it is defined now in abort.h

#if 0
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
  using ::atexit;
  using ::exit;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  using ::_Exit;
#endif
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

#endif

#if 0
  // TODO: define labs(), llabs(), ldiv(), lldiv()
  inline long
  __attribute__((always_inline))
  abs(long __x) noexcept
    {
      return labs(__x);
    }

  inline long long
  __attribute__((always_inline))
  abs(long long __x) noexcept
    {
      return llabs(__x);
    }

  inline ldiv_t
  __attribute__((always_inline))
  div(long __x, long __y) noexcept
    {
      return ldiv(__x, __y);
    }

  inline lldiv_t
  __attribute__((always_inline))
  div(long long __x, long long __y) noexcept
    {
      return lldiv(__x, __y);
    }
#endif

}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTLIB_H_
