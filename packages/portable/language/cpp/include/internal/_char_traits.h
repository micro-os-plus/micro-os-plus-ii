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
/// \brief Character traits.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_CHAR_TRAITS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_CHAR_TRAITS_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/iosfwd.h"
#include "portable/language/cpp/include/type_traits.h"

#include <stdio.h>
#include <string.h>

#include "portable/language/cpp/include/internal/_undef_min_max.h"

#if 0
#include <stdio.h>
#include <string.h>
#include <iosfwd>
#include <cstring>
#include <cstdio>  // For EOF.
#include <cwchar>
#include <algorithm>
#include <iterator>
#include <utility>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <__functional_base>
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
#include <cstdint>
#endif
#if !defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(_LIBCPP_DEBUG)
#include <cassert>
#endif

#include <__undef_min_max>

#endif

namespace os
{
  namespace std
  {

    // char_traits

    template<class TChar_T>
      struct char_traits
      {
        typedef TChar_T char_type;
        typedef int int_type;
        typedef streamoff off_type;
        typedef streampos pos_type;
        typedef mbstate_t state_type;

        static void
        __attribute__((always_inline))
        assign(char_type& __c1, const char_type& __c2) noexcept
        {
          __c1 = __c2;
        }

        static constexpr bool
        __attribute__((always_inline))
        eq(char_type __c1, char_type __c2) noexcept
        {
          return __c1 == __c2;
        }

        static constexpr bool
        __attribute__((always_inline))
        lt(char_type __c1, char_type __c2) noexcept
        {
          return __c1 < __c2;
        }

        static int
        compare(const char_type* __s1, const char_type* __s2, size_t __n);

        static size_t
        length(const char_type* __s);

        static const char_type*
        find(const char_type* __s, size_t __n, const char_type& __a);

        static char_type*
        move(char_type* __s1, const char_type* __s2, size_t __n);

        static char_type*
        copy(char_type* __s1, const char_type* __s2, size_t __n);

        static char_type*
        assign(char_type* __s, size_t __n, char_type __a);

        static constexpr int_type
        __attribute__((always_inline))
        not_eof(int_type __c) noexcept
        {
          return eq_int_type(__c, eof()) ? ~eof() : __c;
        }

        static constexpr char_type
        __attribute__((always_inline))
        to_char_type(int_type __c) noexcept
        {
          return char_type(__c);
        }

        static constexpr int_type
        __attribute__((always_inline))
        to_int_type(char_type __c) noexcept
        {
          return int_type(__c);
        }

        static constexpr bool
        __attribute__((always_inline))
        eq_int_type(int_type __c1, int_type __c2) noexcept
        {
          return __c1 == __c2;
        }

        __attribute__((always_inline))
                        static constexpr int_type
        eof() noexcept
        {
          return int_type(EOF);
        }
      };

    template<class TChar_T>
      int
      char_traits<TChar_T>::compare(const char_type* __s1,
          const char_type* __s2, size_t __n)
      {
        for (; __n; --__n, ++__s1, ++__s2)
          {
            if (lt(*__s1, *__s2))
              return -1;
            if (lt(*__s2, *__s1))
              return 1;
          }
        return 0;
      }

    template<class TChar_T>
      inline size_t
      __attribute__((always_inline))
      char_traits<TChar_T>::length(const char_type* __s)
      {
        size_t __len = 0;
        for (; !eq(*__s, char_type(0)); ++__s)
          ++__len;
        return __len;
      }

    template<class TChar_T>
      inline const TChar_T*
      __attribute__((always_inline))
      char_traits<TChar_T>::find(const char_type* __s, size_t __n,
          const char_type& __a)
      {
        for (; __n; --__n)
          {
            if (eq(*__s, __a))
              return __s;
            ++__s;
          }
        return 0;
      }

    template<class TChar_T>
      TChar_T*
      char_traits<TChar_T>::move(char_type* __s1, const char_type* __s2,
          size_t __n)
      {
        char_type* __r = __s1;
        if (__s1 < __s2)
          {
            for (; __n; --__n, ++__s1, ++__s2)
              assign(*__s1, *__s2);
          }
        else if (__s2 < __s1)
          {
            __s1 += __n;
            __s2 += __n;
            for (; __n; --__n)
              assign(*--__s1, *--__s2);
          }
        return __r;
      }

    template<class TChar_T>
      inline TChar_T*
      __attribute__((always_inline))
      char_traits<TChar_T>::copy(char_type* __s1, const char_type* __s2,
          size_t __n)
      {
        char_type* __r = __s1;
        for (; __n; --__n, ++__s1, ++__s2)
          assign(*__s1, *__s2);
        return __r;
      }

    template<class TChar_T>
      inline TChar_T*
      __attribute__((always_inline))
      char_traits<TChar_T>::assign(char_type* __s, size_t __n, char_type __a)
      {
        char_type* __r = __s;
        for (; __n; --__n, ++__s)
          assign(*__s, __a);
        return __r;
      }

    // char_traits<char>

    template<>
      struct char_traits<char>
      {
        typedef char char_type;
        typedef int int_type;
        typedef streamoff off_type;
        typedef streampos pos_type;
        typedef mbstate_t state_type;

        static void
        __attribute__((always_inline))
        assign(char_type& __c1, const char_type& __c2) noexcept
        {
          __c1 = __c2;
        }

        static constexpr bool
        __attribute__((always_inline))
        eq(char_type __c1, char_type __c2) noexcept
        {
          return __c1 == __c2;
        }

        static constexpr bool
        __attribute__((always_inline))
        lt(char_type __c1, char_type __c2) noexcept
        {
          return (unsigned char) __c1 < (unsigned char) __c2;
        }

        static int
        __attribute__((always_inline))
        compare(const char_type* __s1, const char_type* __s2, size_t __n)
        {
          return memcmp(__s1, __s2, __n);
        }

        static size_t
        __attribute__((always_inline))
        length(const char_type* __s)
        {
          return strlen(__s);
        }

        static const char_type*
        __attribute__((always_inline))
        find(const char_type* __s, size_t __n, const char_type& __a)
        {
          return (const char_type*) memchr(__s, to_int_type(__a), __n);
        }

        static char_type*
        __attribute__((always_inline))
        move(char_type* __s1, const char_type* __s2, size_t __n)
        {
          return (char_type*) memmove(__s1, __s2, __n);
        }

        static char_type*
        __attribute__((always_inline))
        copy(char_type* __s1, const char_type* __s2, size_t __n)
        {
          return (char_type*) memcpy(__s1, __s2, __n);
        }

        static char_type*
        __attribute__((always_inline))
        assign(char_type* __s, size_t __n, char_type __a)
        {
          return (char_type*) memset(__s, to_int_type(__a), __n);
        }

        static constexpr int_type
        __attribute__((always_inline))
        not_eof(int_type __c) noexcept
        {
          return eq_int_type(__c, eof()) ? ~eof() : __c;
        }

        static constexpr char_type
        __attribute__((always_inline))
        to_char_type(int_type __c) noexcept
        {
          return char_type(__c);
        }

        static constexpr int_type
        __attribute__((always_inline))
        to_int_type(char_type __c) noexcept
        {
          return int_type((unsigned char) __c);
        }

        static constexpr bool
        __attribute__((always_inline))
        eq_int_type(int_type __c1, int_type __c2) noexcept
        {
          return __c1 == __c2;
        }

        static constexpr int_type
        __attribute__((always_inline))
        eof() noexcept
        {
          return int_type(EOF);
        }
      };

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

// char_traits<wchar_t>

  template <>
  struct char_traits<wchar_t>
    {
      typedef wchar_t char_type;
      typedef wint_t int_type;
      typedef streamoff off_type;
      typedef streampos pos_type;
      typedef mbstate_t state_type;

      __attribute__((always_inline))
      static void assign(char_type& __c1, const char_type& __c2) noexcept
        { __c1 = __c2;}
      __attribute__((always_inline))
      static constexpr bool eq(char_type __c1, char_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr bool lt(char_type __c1, char_type __c2) noexcept
        { return __c1 < __c2;}

      __attribute__((always_inline))
      static int compare(const char_type* __s1, const char_type* __s2, size_t __n)
        { return wmemcmp(__s1, __s2, __n);}
      __attribute__((always_inline))
      static size_t length(const char_type* __s)
        { return wcslen(__s);}
      __attribute__((always_inline))
      static const char_type* find(const char_type* __s, size_t __n, const char_type& __a)
        { return (const char_type*)wmemchr(__s, __a, __n);}
      __attribute__((always_inline))
      static char_type* move(char_type* __s1, const char_type* __s2, size_t __n)
        { return (char_type*)wmemmove(__s1, __s2, __n);}
      __attribute__((always_inline))
      static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n)
        { return (char_type*)wmemcpy(__s1, __s2, __n);}
      __attribute__((always_inline))
      static char_type* assign(char_type* __s, size_t __n, char_type __a)
        { return (char_type*)wmemset(__s, __a, __n);}

      __attribute__((always_inline))
      static constexpr int_type not_eof(int_type __c) noexcept
        { return eq_int_type(__c, eof()) ? ~eof() : __c;}
      __attribute__((always_inline))
      static constexpr char_type to_char_type(int_type __c) noexcept
        { return char_type(__c);}
      __attribute__((always_inline))
      static constexpr int_type to_int_type(char_type __c) noexcept
        { return int_type(__c);}
      __attribute__((always_inline))
      static constexpr bool eq_int_type(int_type __c1, int_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr int_type eof() noexcept
        { return int_type(WEOF);}
    };

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS

  template <>
  struct char_traits<char16_t>
    {
      typedef char16_t char_type;
      typedef uint_least16_t int_type;
      typedef streamoff off_type;
      typedef u16streampos pos_type;
      typedef mbstate_t state_type;

      __attribute__((always_inline))
      static void assign(char_type& __c1, const char_type& __c2) noexcept
        { __c1 = __c2;}
      __attribute__((always_inline))
      static constexpr bool eq(char_type __c1, char_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr bool lt(char_type __c1, char_type __c2) noexcept
        { return __c1 < __c2;}

      static int compare(const char_type* __s1, const char_type* __s2, size_t __n);
      static size_t length(const char_type* __s);
      static const char_type* find(const char_type* __s, size_t __n, const char_type& __a);
      static char_type* move(char_type* __s1, const char_type* __s2, size_t __n);
      static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n);
      static char_type* assign(char_type* __s, size_t __n, char_type __a);

      __attribute__((always_inline))
      static constexpr int_type not_eof(int_type __c) noexcept
        { return eq_int_type(__c, eof()) ? ~eof() : __c;}
      __attribute__((always_inline))
      static constexpr char_type to_char_type(int_type __c) noexcept
        { return char_type(__c);}
      __attribute__((always_inline))
      static constexpr int_type to_int_type(char_type __c) noexcept
        { return int_type(__c);}
      __attribute__((always_inline))
      static constexpr bool eq_int_type(int_type __c1, int_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr int_type eof() noexcept
        { return int_type(0xDFFF);}
    };

  inline __attribute__((always_inline))
  int
  char_traits<char16_t>::compare(const char_type* __s1, const char_type* __s2, size_t __n)
    {
      for (; __n; --__n, ++__s1, ++__s2)
        {
          if (lt(*__s1, *__s2))
          return -1;
          if (lt(*__s2, *__s1))
          return 1;
        }
      return 0;
    }

  inline __attribute__((always_inline))
  size_t
  char_traits<char16_t>::length(const char_type* __s)
    {
      size_t __len = 0;
      for (; !eq(*__s, char_type(0)); ++__s)
      ++__len;
      return __len;
    }

  inline __attribute__((always_inline))
  const char16_t*
  char_traits<char16_t>::find(const char_type* __s, size_t __n, const char_type& __a)
    {
      for (; __n; --__n)
        {
          if (eq(*__s, __a))
          return __s;
          ++__s;
        }
      return 0;
    }

  inline __attribute__((always_inline))
  char16_t*
  char_traits<char16_t>::move(char_type* __s1, const char_type* __s2, size_t __n)
    {
      char_type* __r = __s1;
      if (__s1 < __s2)
        {
          for (; __n; --__n, ++__s1, ++__s2)
          assign(*__s1, *__s2);
        }
      else if (__s2 < __s1)
        {
          __s1 += __n;
          __s2 += __n;
          for (; __n; --__n)
          assign(*--__s1, *--__s2);
        }
      return __r;
    }

  inline __attribute__((always_inline))
  char16_t*
  char_traits<char16_t>::copy(char_type* __s1, const char_type* __s2, size_t __n)
    {
      char_type* __r = __s1;
      for (; __n; --__n, ++__s1, ++__s2)
      assign(*__s1, *__s2);
      return __r;
    }

  inline __attribute__((always_inline))
  char16_t*
  char_traits<char16_t>::assign(char_type* __s, size_t __n, char_type __a)
    {
      char_type* __r = __s;
      for (; __n; --__n, ++__s)
      assign(*__s, __a);
      return __r;
    }

  template <>
  struct char_traits<char32_t>
    {
      typedef char32_t char_type;
      typedef uint_least32_t int_type;
      typedef streamoff off_type;
      typedef u32streampos pos_type;
      typedef mbstate_t state_type;

      __attribute__((always_inline))
      static void assign(char_type& __c1, const char_type& __c2) noexcept
        { __c1 = __c2;}
      __attribute__((always_inline))
      static constexpr bool eq(char_type __c1, char_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr bool lt(char_type __c1, char_type __c2) noexcept
        { return __c1 < __c2;}

      static int compare(const char_type* __s1, const char_type* __s2, size_t __n);
      static size_t length(const char_type* __s);
      static const char_type* find(const char_type* __s, size_t __n, const char_type& __a);
      static char_type* move(char_type* __s1, const char_type* __s2, size_t __n);
      static char_type* copy(char_type* __s1, const char_type* __s2, size_t __n);
      static char_type* assign(char_type* __s, size_t __n, char_type __a);

      __attribute__((always_inline))
      static constexpr int_type not_eof(int_type __c) noexcept
        { return eq_int_type(__c, eof()) ? ~eof() : __c;}
      __attribute__((always_inline))
      static constexpr char_type to_char_type(int_type __c) noexcept
        { return char_type(__c);}
      __attribute__((always_inline))
      static constexpr int_type to_int_type(char_type __c) noexcept
        { return int_type(__c);}
      __attribute__((always_inline))
      static constexpr bool eq_int_type(int_type __c1, int_type __c2) noexcept
        { return __c1 == __c2;}
      __attribute__((always_inline))
      static constexpr int_type eof() noexcept
        { return int_type(0xFFFFFFFF);}
    };

  inline __attribute__((always_inline))
  int
  char_traits<char32_t>::compare(const char_type* __s1, const char_type* __s2, size_t __n)
    {
      for (; __n; --__n, ++__s1, ++__s2)
        {
          if (lt(*__s1, *__s2))
          return -1;
          if (lt(*__s2, *__s1))
          return 1;
        }
      return 0;
    }

  inline __attribute__((always_inline))
  size_t
  char_traits<char32_t>::length(const char_type* __s)
    {
      size_t __len = 0;
      for (; !eq(*__s, char_type(0)); ++__s)
      ++__len;
      return __len;
    }

  inline __attribute__((always_inline))
  const char32_t*
  char_traits<char32_t>::find(const char_type* __s, size_t __n, const char_type& __a)
    {
      for (; __n; --__n)
        {
          if (eq(*__s, __a))
          return __s;
          ++__s;
        }
      return 0;
    }

  inline __attribute__((always_inline))
  char32_t*
  char_traits<char32_t>::move(char_type* __s1, const char_type* __s2, size_t __n)
    {
      char_type* __r = __s1;
      if (__s1 < __s2)
        {
          for (; __n; --__n, ++__s1, ++__s2)
          assign(*__s1, *__s2);
        }
      else if (__s2 < __s1)
        {
          __s1 += __n;
          __s2 += __n;
          for (; __n; --__n)
          assign(*--__s1, *--__s2);
        }
      return __r;
    }

  inline __attribute__((always_inline))
  char32_t*
  char_traits<char32_t>::copy(char_type* __s1, const char_type* __s2, size_t __n)
    {
      char_type* __r = __s1;
      for (; __n; --__n, ++__s1, ++__s2)
      assign(*__s1, *__s2);
      return __r;
    }

  inline __attribute__((always_inline))
  char32_t*
  char_traits<char32_t>::assign(char_type* __s, size_t __n, char_type __a)
    {
      char_type* __r = __s;
      for (; __n; --__n, ++__s)
      assign(*__s, __a);
      return __r;
    }

#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
#endif

//_LIBCPP_END_NAMESPACE_STD
} //namespace std
} // namespace os

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_CHAR_TRAITS_H_ */
