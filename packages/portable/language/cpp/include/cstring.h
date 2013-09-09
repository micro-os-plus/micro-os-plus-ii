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
/// \brief C string functions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTRING_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTRING_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include <string.h>

namespace os
{
  namespace std
  {

    using ::size_t;
    using ::memcpy;

    using ::memmove;

    // TODO: disable it
    using ::strcpy;
    using ::strncpy;
//    using ::strcat;
    using ::strncat;
//    using ::memcmp;
//    using ::strcmp;
    using ::strncmp;
//    using ::strcoll;
//    using ::strxfrm;

//    using ::memchr;

//    using ::strchr;

//    using ::strcspn;

//    using ::strpbrk;

//    using ::strrchr;

//    using ::strspn;

//    using ::strstr;

// MSVC, GNU libc and its derivates already have the correct prototype in <string.h> #ifdef __cplusplus
#if 0 //!defined(__GLIBC__) && !defined(_MSC_VER) && !defined(__sun__)
    inline char*
    __attribute__((always_inline))
    strchr(char* __s, int __c)
      {
        return ::strchr(__s, __c);
      }
    inline char*
    __attribute__((always_inline))
    strpbrk(char* __s1, const char* __s2)
      {
        return ::strpbrk(__s1, __s2);
      }
    inline char*
    __attribute__((always_inline))
    strrchr(char* __s, int __c)
      {
        return ::strrchr(__s, __c);
      }
    inline void*
    __attribute__((always_inline))
    memchr(void* __s, int __c, size_t __n)
      {
        return ::memchr(__s, __c, __n);
      }
    inline char*
    __attribute__((always_inline))
    strstr(char* __s1, const char* __s2)
      {
        return ::strstr(__s1, __s2);
      }

#endif

//   using ::strtok;
    using ::memset;
//    using ::strerror;
    using ::strlen;

  } // namespace std
} // namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTRING_H_
