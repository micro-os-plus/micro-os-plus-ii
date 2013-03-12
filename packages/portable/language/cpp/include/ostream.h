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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/ios.h"
#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/locale.h"
//#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/internal/_fpos.h"


namespace os
{
  namespace std
  {
    // 27.7.3.1 Class template basic_ostream
    // Default for _Traits defined in iosfwd.h

    /// \example portable/language/cpp/tests/src/ostream.cpp
    /// \example portable/language/cpp/tests/src/ostreamConversions.cpp
    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE basic_ostream : virtual public basic_ios<_CharT,
          _Traits>
      {
      public:
        // types (inherited from basic_ios (27.5.5)):
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::pos_type pos_type;
        typedef typename traits_type::off_type off_type;

        // 27.7.3.2 Constructor/destructor:
        explicit
        basic_ostream(basic_streambuf<char_type, traits_type>* sb);
        virtual
        ~basic_ostream();

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif
        // 27.7.3.4 Prefix/suffix:
        class _LIBCPP_VISIBLE sentry;

#pragma GCC diagnostic pop

        // 27.7.3.6 Formatted output:
        basic_ostream&
        operator<<(basic_ostream&
        (*pf)(basic_ostream&));

        basic_ostream&
        operator<<(basic_ios<char_type, traits_type>&
        (*pf)(basic_ios<char_type, traits_type>&));

        basic_ostream&
        operator<<(ios_base&
        (*pf)(ios_base&));

        basic_ostream&
        operator<<(bool n);
        basic_ostream&
        operator<<(short n);
        basic_ostream&
        operator<<(unsigned short n);
        basic_ostream&
        operator<<(int n);
        basic_ostream&
        operator<<(unsigned int n);
        basic_ostream&
        operator<<(long n);
        basic_ostream&
        operator<<(unsigned long n);
        basic_ostream&
        operator<<(long long n);
        basic_ostream&
        operator<<(unsigned long long n);
        basic_ostream&
        operator<<(float f);
        basic_ostream&
        operator<<(double f);
        basic_ostream&
        operator<<(long double f);

        basic_ostream&
        operator<<(const void* __p);
        basic_ostream&
        operator<<(basic_streambuf<char_type, traits_type>* sb);

        // 27.7.3.7 Unformatted output:
        basic_ostream&
        put(char_type c);
        basic_ostream&
        write(const char_type* s, streamsize n);

        basic_ostream&
        flush();

        // 27.7.3.5 seeks:
        pos_type
        tellp();
        basic_ostream&
        seekp(pos_type pos);
        basic_ostream&
        seekp(off_type off, ios_base::seekdir dir);

      protected:
        _LIBCPP_ALWAYS_INLINE
        basic_ostream();

        basic_ostream(const basic_ostream& rhs) = delete;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        basic_ostream(basic_ostream&& __rhs);
#endif

        // 27.7.3.3 Assign/swap

        basic_ostream& operator=(basic_ostream& rhs) = delete;

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
        _LIBCPP_INLINE_VISIBILITY
        basic_ostream& operator=(const basic_ostream&& rhs);
#endif
        void
        swap(basic_ostream& rhs);
      };

    // ========================================================================

    // 27.7.3.6.4 character inserters
    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, _CharT __c);

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, char __cn);

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, char __c);

    // signed and unsigned
    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, signed char __c);

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, unsigned char __c);

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, const _CharT* __str);

    template<class _CharT, class _Traits>
      basic_ostream<_CharT, _Traits>&
      operator<<(basic_ostream<_CharT, _Traits>& __os, const char* __strn);

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, const char* __str);

    // signed and unsigned
    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os, const signed char* __str);

    template<class _Traits>
      basic_ostream<char, _Traits>&
      operator<<(basic_ostream<char, _Traits>& __os,
          const unsigned char* __str);

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class _Stream, class _Tp>
    typename enable_if
    <
    !is_lvalue_reference<_Stream>::value &&
    is_base_of<ios_base, _Stream>::value,
    _Stream&&
    >::type
    operator<<(_Stream&& __os, const _Tp& __x);

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template<class _CharT, class _Traits>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os, const error_code& __ec);

    template<class _CharT, class _Traits, class _Yp>
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        shared_ptr<_Yp> const& __p);

#endif

    // ========================================================================

    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE basic_ostream<_CharT, _Traits>::sentry
      {
        basic_ostream<_CharT, _Traits>& m_ostream;
        bool m_ok;

        sentry(const sentry&) = delete;

        sentry&
        operator=(const sentry&) = delete;

      public:
        explicit
        sentry(basic_ostream<_CharT, _Traits>& __os);

        ~sentry();

        _LIBCPP_ALWAYS_INLINE
        _LIBCPP_EXPLICIT
        operator bool() const
          {
            return m_ok;
          }
      };

    // ========================================================================

    template<class _CharT, class _Traits>
    inline _LIBCPP_ALWAYS_INLINE
    basic_ostream<_CharT, _Traits>::basic_ostream()
    {
      ;
    }  // extension, intentionally does not initialise

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>::basic_ostream(
          basic_streambuf<char_type, traits_type>* __sb)
      {
        this->init(__sb);
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<_CharT, _Traits>::basic_ostream(basic_ostream&& __rhs)
      {
        this->move(__rhs);
      }

    template <class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<_CharT, _Traits>&
    basic_ostream<_CharT, _Traits>::operator=(basic_ostream&& __rhs)
      {
        swap(__rhs);
        return *this;
      }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_ostream<_CharT, _Traits>::swap(basic_ostream& __rhs)
      {
        basic_ios<char_type, traits_type>::swap(__rhs);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(basic_ostream&
      (*__pf)(basic_ostream&))
      {
        return __pf(*this);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(
          basic_ios<char_type, traits_type>&
          (*__pf)(basic_ios<char_type, traits_type>&))
      {
        __pf(*this);
        return *this;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      basic_ostream<_CharT, _Traits>::operator<<(ios_base&
      (*__pf)(ios_base&))
      {
        __pf(*this);
        return *this;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      endl(basic_ostream<_CharT, _Traits>& __os)
      {
        __os.put(__os.widen('\n'));
        __os.flush();
        return __os;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      ends(basic_ostream<_CharT, _Traits>& __os)
      {
        __os.put(_CharT());
        return __os;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_ostream<_CharT, _Traits>&
      flush(basic_ostream<_CharT, _Traits>& __os)
      {
        __os.flush();
        return __os;
      }

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

    template <class _Stream, class _Tp>
    inline _LIBCPP_INLINE_VISIBILITY
    typename enable_if
    <
    !is_lvalue_reference<_Stream>::value &&
    is_base_of<ios_base, _Stream>::value,
    _Stream&&
    >::type
    operator<<(_Stream&& __os, const _Tp& __x)
      {
        __os << __x;
        return _VSTD::move(__os);
      }

#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    template<class _CharT, class _Traits>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os, const error_code& __ec)
      {
        return __os << __ec.category().name() << ':' << __ec.value();
      }

    template<class _CharT, class _Traits, class _Yp>
    inline _LIBCPP_INLINE_VISIBILITY
    basic_ostream<_CharT, _Traits>&
    operator<<(basic_ostream<_CharT, _Traits>& __os,
        shared_ptr<_Yp> const& __p)
      {
        return __os << __p.get();
      }

#endif

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#pragma clang diagnostic ignored "-Wpadded"
#endif

    extern template class basic_ostream<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  extern template class basic_ostream<wchar_t>;

#endif

#pragma GCC diagnostic pop

//_LIBCPP_END_NAMESPACE_STD
}
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_OSTREAM_H_
