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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/internal/_fpos.h"

#if 0
#include <__config>
#include <iosfwd>
#include <ios>
#endif

namespace os
{
  namespace std
  {

    template<class _CharT, class _Traits>
      basic_streambuf<_CharT, _Traits>::~basic_streambuf()
      {
      }

    template<class _CharT, class _Traits>
      basic_streambuf<_CharT, _Traits>::basic_streambuf()
          : //
          m_binp(nullptr), //
          m_ninp(nullptr), //
          m_einp(nullptr), //
          m_bout(nullptr), //
          m_nout(nullptr), //
          m_eout(nullptr)
      {
      }

    template<class _CharT, class _Traits>
      basic_streambuf<_CharT, _Traits>::basic_streambuf(
          const basic_streambuf& __sb)
          : //
          m_binp(__sb.m_binp), //
          m_ninp(__sb.m_ninp), //
          m_einp(__sb.m_einp), //
          m_bout(__sb.m_bout), //
          m_nout(__sb.m_nout), //
          m_eout(__sb.m_eout), //
          m_locale(__sb.m_locale)
      {
      }

    template<class _CharT, class _Traits>
      basic_streambuf<_CharT, _Traits>&
      basic_streambuf<_CharT, _Traits>::operator=(const basic_streambuf& __sb)
      {
        m_locale = __sb.m_locale;
        m_binp = __sb.m_binp;
        m_ninp = __sb.m_ninp;
        m_einp = __sb.m_einp;
        m_bout = __sb.m_bout;
        m_nout = __sb.m_nout;
        m_eout = __sb.m_eout;

        return *this;
      }

    template<class _CharT, class _Traits>
      void
      basic_streambuf<_CharT, _Traits>::swap(basic_streambuf& __sb)
      {
        _VSTD::swap(m_locale, __sb.m_locale);

        _VSTD::swap(m_binp, __sb.m_binp);
        _VSTD::swap(m_ninp, __sb.m_ninp);
        _VSTD::swap(m_einp, __sb.m_einp);
        _VSTD::swap(m_bout, __sb.m_bout);
        _VSTD::swap(m_nout, __sb.m_nout);
        _VSTD::swap(m_eout, __sb.m_eout);
      }

//#endif

    template<class _CharT, class _Traits>
      void
      basic_streambuf<_CharT, _Traits>::imbue(const locale&)
      {
      }

    template<class _CharT, class _Traits>
      basic_streambuf<_CharT, _Traits>*
      basic_streambuf<_CharT, _Traits>::setbuf(char_type*, streamsize)
      {
        return this;
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::seekoff(off_type, ios_base::seekdir,
          ios_base::openmode)
      {
        return pos_type(off_type(-1));
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::seekpos(pos_type, ios_base::openmode)
      {
        return pos_type(off_type(-1));
      }

    template<class _CharT, class _Traits>
      int
      basic_streambuf<_CharT, _Traits>::sync()
      {
        return 0;
      }

    template<class _CharT, class _Traits>
      streamsize
      basic_streambuf<_CharT, _Traits>::showmanyc()
      {
        return 0;
      }

    template<class _CharT, class _Traits>
      streamsize
      basic_streambuf<_CharT, _Traits>::xsgetn(char_type* __s, streamsize __n)
      {
        const int_type __eof = traits_type::eof();
        int_type __c;
        streamsize __i = 0;
        for (; __i < __n; ++__i, ++__s)
          {
            if (m_ninp < m_einp)
              {
                *__s = *m_ninp++;
              }
            else if ((__c = uflow()) != __eof)
              {
                *__s = traits_type::to_char_type(__c);
              }
            else
              break;
          }
        return __i;
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::underflow()
      {
        return traits_type::eof();
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::uflow()
      {
        if (underflow() == traits_type::eof())
          {
            return traits_type::eof();
          }
        return traits_type::to_int_type(*m_ninp++);
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::pbackfail(int_type)
      {
        return traits_type::eof();
      }

    template<class _CharT, class _Traits>
      streamsize
      basic_streambuf<_CharT, _Traits>::xsputn(const char_type* __s,
          streamsize __n)
      {
        streamsize __i = 0;
        int_type __eof = traits_type::eof();
        for (; __i < __n; ++__s, ++__i)
          {
            if (m_nout < m_eout)
              {
                *m_nout++ = *__s;
              }
            else if (overflow(traits_type::to_int_type(*__s)) == __eof)
              {
                break;
              }
          }
        return __i;
      }

    template<class _CharT, class _Traits>
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::overflow(int_type)
      {
        return traits_type::eof();
      }

  }
}

#endif /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_CPP_H_ */
