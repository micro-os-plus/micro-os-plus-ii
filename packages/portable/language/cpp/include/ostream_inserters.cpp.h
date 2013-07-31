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
/// \brief Output streams inserters function definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iterator.h"

namespace os
{
  namespace std
  {
    // ========================================================================

    /// \addtogroup ostreamInserters
    /// @{

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, TChar_T c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<TChar_T, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<TChar_T, TTraits_T> _Ip;

            const TChar_T* pBeg = &c;
            const TChar_T* pEnd = &c + 1;
            const TChar_T* pPad;
            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<TChar_T, TTraits_T>::sentry se(outs);
        if (se)
          {
            TChar_T c = outs.widen(ch);
            typedef ostreambuf_iterator<TChar_T, TTraits_T> _Ip;

            const TChar_T* pBeg = &c;
            const TChar_T* pEnd = &c + 1;
            const TChar_T* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;

            const char* pBeg = &ch;
            const char* pEnd = &ch + 1;
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, signed char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;

            const char* pBeg = (char*) &ch;
            const char* pEnd = (char*) &ch + 1;
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, unsigned char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;

            const char* pBeg = (char*) &ch;
            const char* pEnd = (char*) &ch + 1;
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TChar_T, class TTraits_T>
      basic_ostream<TChar_T, TTraits_T>&
      operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const TChar_T* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<TChar_T, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<TChar_T, TTraits_T> _Ip;
            size_t len = TTraits_T::length(str);

            const TChar_T* pBeg = str;
            const TChar_T* pEnd = str + len;
            const TChar_T* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class TChar_T, class TTraits_T>
    basic_ostream<TChar_T, TTraits_T>&
    operator<<(basic_ostream<TChar_T, TTraits_T>& os, const char* __strn)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            typename basic_ostream<TChar_T, TTraits_T>::sentry se(os);
            if (se)
              {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
                typedef ostreambuf_iterator<TChar_T, TTraits_T> _Ip;
                size_t __len = char_traits<char>::length(__strn);
                const int __bs = 100;
                TChar_T __wbb[__bs];
                TChar_T* __wb = __wbb;
                unique_ptr<TChar_T, void
                (*)(void*)> __h(0, free);
                if (__len > __bs)
                  {
                    __wb = (TChar_T*) malloc(__len * sizeof(TChar_T));
                    if (__wb == 0)
                    __throw_bad_alloc();
                    __h.reset(__wb);
                  }
                for (TChar_T* __p = __wb; *__strn != '\0'; ++__strn, ++__p)
                *__p = os.widen(*__strn);
                if (__pad_and_output(_Ip(os), __wb,
                        (os.flags() & ios_base::adjustfield) == ios_base::left ?
                        __wb + __len : __wb, __wb + __len, os, os.fill()).failed())
                  {
                    os.setstate(ios_base::badbit | ios_base::failbit);
                  }
#else
                os.setstate(ios_base::badbit | ios_base::failbit);
#endif
              }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
          }
        catch (...)
          {
            os.__set_badbit_and_consider_rethrow();
          }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return os;
      }
#endif

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, const char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;
            size_t len = TTraits_T::length(str);

            const char* pBeg = str;
            const char* pEnd = str + len;
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, const signed char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;
            size_t len = TTraits_T::length((const char*) str);

            const char* pBeg = (const char*) (str);
            const char* pEnd = (const char*) (str + len);
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

    template<class TTraits_T>
      basic_ostream<char, TTraits_T>&
      operator<<(basic_ostream<char, TTraits_T>& outs, const unsigned char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, TTraits_T>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, TTraits_T> _Ip;
            size_t len = TTraits_T::length((const char*) str);

            const char* pBeg = (const char*) (str);
            const char* pEnd = (const char*) (str + len);
            const char* pPad;

            if ((outs.flags() & ios_base::adjustfield) == ios_base::left)
              {
                pPad = pEnd;
              }
            else
              {
                pPad = pBeg;
              }

            if (__padAndOutput(_Ip(outs), pBeg, pPad, pEnd, outs, outs.fill()).failed())
              {
                outs.setstate(ios_base::badbit | ios_base::failbit);
              }
          }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      }
    catch (...)
      {
        outs.__set_badbit_and_consider_rethrow();
      }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        return outs;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template<class TChar_T, class TTraits_T, class _Allocator>
  basic_ostream<TChar_T, TTraits_T>&
  operator<<(basic_ostream<TChar_T, TTraits_T>& outs,
      const basic_string<TChar_T, TTraits_T, _Allocator>& str)
    {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      try
        {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          typename basic_ostream<TChar_T, TTraits_T>::sentry se(outs);
          if (se)
            {
              typedef ostreambuf_iterator<TChar_T, TTraits_T> _Ip;
              size_t __len = str.size();
              if (__pad_and_output(_Ip(outs), str.data(),
                      (outs.flags() & ios_base::adjustfield) == ios_base::left ?
                      str.data() + __len : str.data(), str.data() + __len,
                      outs, outs.fill()).failed())
                {
                  outs.setstate(ios_base::badbit | ios_base::failbit);
                }
            }
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        }
      catch (...)
        {
          outs.__set_badbit_and_consider_rethrow();
        }
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
      return outs;
    }
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
  template<class TChar_T, class TTraits_T, size_t _Size>
  basic_ostream<TChar_T, TTraits_T>&
  operator<<(basic_ostream<TChar_T, TTraits_T>& outs, const bitset<_Size>& __x)
    {
      return outs
      << __x.template to_string<TChar_T, TTraits_T>(
          use_facet < ctype<TChar_T> > (outs.getloc()).widen('0'),
          use_facet < ctype<TChar_T> > (outs.getloc()).widen('1'));
    }
#endif

  /// @}

}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_
