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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/iosfwd.h"
#include "portable/language/cpp/include/internal/_char_traits.h"
#include "portable/language/cpp/include/internal/_ios_base.h"

#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

    // 27.5.5 Class template basic_ios
    // default for _Traits is defined in iosfwd.h
    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE basic_ios : public ios_base
      {
      public:
        // types:
        typedef _CharT char_type;
        typedef _Traits traits_type;

        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::pos_type pos_type;
        typedef typename traits_type::off_type off_type;

        _LIBCPP_ALWAYS_INLINE
        _LIBCPP_EXPLICIT
        operator bool() const;

        _LIBCPP_ALWAYS_INLINE
        bool
        operator!() const;

        _LIBCPP_ALWAYS_INLINE
        iostate
        rdstate() const;

        void
        clear(iostate __state = goodbit);

        _LIBCPP_ALWAYS_INLINE
        void
        setstate(iostate __state);

        _LIBCPP_ALWAYS_INLINE
        bool
        good() const;

        _LIBCPP_ALWAYS_INLINE
        bool
        eof() const;

        _LIBCPP_ALWAYS_INLINE
        bool
        fail() const;

        _LIBCPP_ALWAYS_INLINE
        bool
        bad() const;

        _LIBCPP_ALWAYS_INLINE
        iostate
        exceptions() const;

        _LIBCPP_ALWAYS_INLINE
        void
        exceptions(iostate __except);

        // 27.5.5.2 Constructor/destructor:
        _LIBCPP_INLINE_VISIBILITY
        explicit
        basic_ios(basic_streambuf<char_type, traits_type>* __sb);

        virtual
        ~basic_ios();

        // 27.5.5.3 Members:
        _LIBCPP_INLINE_VISIBILITY
        basic_ostream<char_type, traits_type>*
        tie() const;

        _LIBCPP_INLINE_VISIBILITY
        basic_ostream<char_type, traits_type>*
        tie(basic_ostream<char_type, traits_type>* __tiestr);

        _LIBCPP_INLINE_VISIBILITY
        basic_streambuf<char_type, traits_type>*
        rdbuf() const;

        _LIBCPP_INLINE_VISIBILITY
        basic_streambuf<char_type, traits_type>*
        rdbuf(basic_streambuf<char_type, traits_type>* __sb);

        basic_ios&
        copyfmt(const basic_ios& __rhs);

        _LIBCPP_INLINE_VISIBILITY
        char_type
        fill() const;

        _LIBCPP_INLINE_VISIBILITY
        char_type
        fill(char_type __ch);

        _LIBCPP_INLINE_VISIBILITY
        locale
        imbue(const locale& __loc);

        _LIBCPP_INLINE_VISIBILITY
        char
        narrow(char_type __c, char __dfault) const;

#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wattributes"
        _LIBCPP_INLINE_VISIBILITY
        char_type
        widen(char __c) const;
#pragma GCC diagnostic pop

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
        void
        __set_badbit_and_consider_rethrow();

        void
        __set_failbit_and_consider_rethrow();
#endif

      protected:
        _LIBCPP_ALWAYS_INLINE
        basic_ios();

        void
        init(basic_streambuf<char_type, traits_type>* __sb);

        _LIBCPP_INLINE_VISIBILITY
        void
        move(basic_ios& __rhs);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_ALWAYS_INLINE
        void
        move(basic_ios&& __rhs);
#endif

        _LIBCPP_INLINE_VISIBILITY
        void
        swap(basic_ios& __rhs) _NOEXCEPT;

        _LIBCPP_INLINE_VISIBILITY
        void
        set_rdbuf(basic_streambuf<char_type, traits_type>* __sb);

      private:
        basic_ostream<char_type, traits_type>* m_tie;
        basic_streambuf<char_type, traits_type>* m_rdbuf;
        iostate m_rdstate;
        iostate m_exceptions;
        mutable int_type m_fill;

      };

    // 27.5.5.2 basic_ios constructors

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ios<_CharT, _Traits>::basic_ios(
          basic_streambuf<char_type, traits_type>* __sb)
      {
        init(__sb);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ios<_CharT, _Traits>::basic_ios()
      {
        // purposefully does no initialisation ("...leaving its member objects
        // uninitialized")
      }

#if defined(SHOULD_BE_DELETED)
    template<class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    void
    basic_ios<_CharT, _Traits>::init(
        basic_streambuf<char_type, traits_type>* __sb)
      {
#if SHOULD_BE_DELETED
        ios_base::init(__sb);
#endif
        m_rdbuf = __sb;

        m_rdstate = m_rdbuf ? goodbit : badbit;
        m_exceptions = goodbit;

        m_tie = 0;
        m_fill = traits_type::eof();
      }
#endif

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      basic_ios<_CharT, _Traits>::operator bool() const
      {
        return !fail();
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      bool
      basic_ios<_CharT, _Traits>::operator!() const
      {
        return fail();
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      ios_base::iostate
      basic_ios<_CharT, _Traits>::rdstate() const
      {
        return m_rdstate;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<_CharT, _Traits>::setstate(iostate __state)
      {
        clear(m_rdstate | __state);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<_CharT, _Traits>::good() const
      {
        return m_rdstate == 0;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<_CharT, _Traits>::eof() const
      {
        return m_rdstate & eofbit;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<_CharT, _Traits>::fail() const
      {
        return m_rdstate & (failbit | badbit);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      bool
      basic_ios<_CharT, _Traits>::bad() const
      {
        return m_rdstate & badbit;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      ios_base::iostate
      basic_ios<_CharT, _Traits>::exceptions() const
      {
        return m_exceptions;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<_CharT, _Traits>::exceptions(iostate __except)
      {
        m_exceptions = __except;
        clear(m_rdstate);
      }

    // 27.5.5.3 Member functions
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>*
      basic_ios<_CharT, _Traits>::tie() const
      {
        return m_tie;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>*
      basic_ios<_CharT, _Traits>::tie(
          basic_ostream<char_type, traits_type>* __tiestr)
      {
        basic_ostream<char_type, traits_type>* __r = m_tie;
        m_tie = __tiestr;
        return __r;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<_CharT, _Traits>*
      basic_ios<_CharT, _Traits>::rdbuf() const
      {
        return m_rdbuf;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<_CharT, _Traits>*
      basic_ios<_CharT, _Traits>::rdbuf(
          basic_streambuf<char_type, traits_type>* __sb)
      {
        basic_streambuf<char_type, traits_type>* __r = rdbuf();
        m_rdbuf = __sb;
        clear();
        return __r;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_ios<_CharT, _Traits>::imbue(const locale& __loc)
      {
        locale __r = getloc();
        ios_base::imbue(__loc);
        if (rdbuf())
          {
            rdbuf()->pubimbue(__loc);
          }
        return __r;
      }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template <class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    char
    basic_ios<_CharT, _Traits>::narrow(char_type __c, char __dfault) const
      {
        return use_facet<ctype<char_type> >(getloc()).narrow(__c, __dfault);
      }

    template <class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    _CharT
    basic_ios<_CharT, _Traits>::widen(char __c) const
      {
        return use_facet<ctype<char_type> >(getloc()).widen(__c);
      }

#else

    // Tiny version, without locales

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      char
      basic_ios<_CharT, _Traits>::narrow(char_type __c, char __dfault) const
      {
        // TODO: extend this test according to locale
        if (__c == '\xFE')
          {
            return __dfault;
          }
        else
          {
            return static_cast<char>(__c);
          }
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      _CharT
      basic_ios<_CharT, _Traits>::widen(char __c) const
      {
        return static_cast<_CharT>(__c);
      }

#endif

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      _CharT
      basic_ios<_CharT, _Traits>::fill() const
      {
        if (traits_type::eq_int_type(traits_type::eof(), m_fill))
          {
            m_fill = widen(' ');
          }
        return (_CharT) m_fill;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      _CharT
      basic_ios<_CharT, _Traits>::fill(char_type __ch)
      {
        char_type __r = (char_type) m_fill;
        m_fill = __ch;
        return __r;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<_CharT, _Traits>::move(basic_ios& __rhs)
      {
        ios_base::move(__rhs);

        m_rdstate = __rhs.m_rdstate;
        m_exceptions = __rhs.m_exceptions;
        m_rdbuf = 0;

        m_tie = __rhs.m_tie;
        __rhs.m_tie = 0;
        m_fill = __rhs.m_fill;
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    void
    basic_ios<_CharT, _Traits>::move(basic_ios&& __rhs)
      {
        move(__rhs);
      }
#endif

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ios<_CharT, _Traits>::swap(basic_ios& __rhs)
      _NOEXCEPT
      {
        ios_base::swap(__rhs);

        _VSTD::swap(m_rdstate, __rhs.m_rdstate);
        _VSTD::swap(m_exceptions, __rhs.m_exceptions);

        _VSTD::swap(m_tie, __rhs.m_tie);
        _VSTD::swap(m_fill, __rhs.m_fill);
      }

  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_BASIC_IOS_H_
