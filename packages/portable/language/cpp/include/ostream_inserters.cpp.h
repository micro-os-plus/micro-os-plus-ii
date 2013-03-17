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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/iterator.h"

namespace os
{
  namespace std
  {
    // ========================================================================

    /// \addtogroup ostreamInserters
    /// @{

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& outs, _CharT c)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;

            const _CharT* pBeg = &c;
            const _CharT* pEnd = &c + 1;
            const _CharT* pPad;
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

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& outs, char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry se(outs);
        if (se)
          {
            _CharT c = outs.widen(ch);
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;

            const _CharT* pBeg = &c;
            const _CharT* pEnd = &c + 1;
            const _CharT* pPad;

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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, signed char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, unsigned char ch)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;

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

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& outs, const _CharT* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<_CharT, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
            size_t __len = _Traits::length(str);

            const _CharT* pBeg = str;
            const _CharT* pEnd = str + __len;
            const _CharT* pPad;

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
    template<class _CharT, class _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& os, const char* __strn)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
            typename basic_ostream<_CharT, _Traits>::sentry se(os);
            if (se)
              {
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
                typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
                size_t __len = char_traits<char>::length(__strn);
                const int __bs = 100;
                _CharT __wbb[__bs];
                _CharT* __wb = __wbb;
                unique_ptr<_CharT, void
                (*)(void*)> __h(0, free);
                if (__len > __bs)
                  {
                    __wb = (_CharT*) malloc(__len * sizeof(_CharT));
                    if (__wb == 0)
                    __throw_bad_alloc();
                    __h.reset(__wb);
                  }
                for (_CharT* __p = __wb; *__strn != '\0'; ++__strn, ++__p)
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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, const char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length(str);

            const char* pBeg = str;
            const char* pEnd = str + __len;
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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, const signed char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length((const char*) str);

            const char* pBeg = (const char*) (str);
            const char* pEnd = (const char*) (str + __len);
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

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& outs, const unsigned char* str)
      {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
        try
          {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
        typename basic_ostream<char, _Traits>::sentry se(outs);
        if (se)
          {
            typedef ostreambuf_iterator<char, _Traits> _Ip;
            size_t __len = _Traits::length((const char*) str);

            const char* pBeg = (const char*) (str);
            const char* pEnd = (const char*) (str + __len);
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
  template<class _CharT, class _Traits, class _Allocator>
  basic_ostream<_CharT, _Traits>&
  operator<<(basic_ostream<_CharT, _Traits>& outs,
      const basic_string<_CharT, _Traits, _Allocator>& str)
    {
#if defined(OS_INCLUDE_LIBCPP_EXCEPTIONS)
      try
        {
#endif  // OS_INCLUDE_LIBCPP_EXCEPTIONS
          typename basic_ostream<_CharT, _Traits>::sentry se(outs);
          if (se)
            {
              typedef ostreambuf_iterator<_CharT, _Traits> _Ip;
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
  template<class _CharT, class _Traits, size_t _Size>
  basic_ostream<_CharT, _Traits>&
  operator<<(basic_ostream<_CharT, _Traits>& outs, const bitset<_Size>& __x)
    {
      return outs
      << __x.template to_string<_CharT, _Traits>(
          use_facet < ctype<_CharT> > (outs.getloc()).widen('0'),
          use_facet < ctype<_CharT> > (outs.getloc()).widen('1'));
    }
#endif

  /// @}

}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_INSERTERS_CPP_H_
