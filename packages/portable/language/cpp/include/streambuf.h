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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/iosfwd.h"
#include "portable/language/cpp/include/ios.h"
//#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/internal/_fpos.h"

#if 0
#include <__config>
#include <iosfwd>
#include <ios>
#endif

//_LIBCPP_BEGIN_NAMESPACE_STD
namespace os
{
  namespace std
  {

    template<class _CharT, class _Traits>
      class _LIBCPP_VISIBLE basic_streambuf
      {
      public:
        // types:
        typedef _CharT char_type;
        typedef _Traits traits_type;
        typedef typename traits_type::int_type int_type;
        typedef typename traits_type::pos_type pos_type;
        typedef typename traits_type::off_type off_type;

        virtual
        ~basic_streambuf();

        // 27.6.2.2.1 locales:
        locale
        pubimbue(const locale& __loc);
        locale
        getloc() const;

        // 27.6.2.2.2 buffer and positioning:
        basic_streambuf*
        pubsetbuf(char_type* __s, streamsize __n);
        pos_type
        pubseekoff(off_type __off, ios_base::seekdir __way,
            ios_base::openmode __which = ios_base::in | ios_base::out);
        pos_type
        pubseekpos(pos_type __sp,
            ios_base::openmode __which = ios_base::in | ios_base::out);
        int
        pubsync();

        // Get and put areas:
        // 27.6.2.2.3 Get area:
        streamsize
        in_avail();
        int_type
        snextc();
        int_type
        sbumpc();
        int_type
        sgetc();
        streamsize
        sgetn(char_type* __s, streamsize __n);

        // 27.6.2.2.4 Putback:
        int_type
        sputbackc(char_type __c);
        int_type
        sungetc();

        // 27.6.2.2.5 Put area:
        int_type
        sputc(char_type __c);
        streamsize
        sputn(const char_type* __s, streamsize __n);

      protected:
        basic_streambuf();
        basic_streambuf(const basic_streambuf& __rhs);
        basic_streambuf&
        operator=(const basic_streambuf& __rhs);
        void
        swap(basic_streambuf& __rhs);

        // 27.6.2.3.2 Get area:
        _LIBCPP_ALWAYS_INLINE
        char_type*
        eback() const;

        _LIBCPP_ALWAYS_INLINE
        char_type*
        gptr() const;

        _LIBCPP_ALWAYS_INLINE
        char_type*
        egptr() const;

        void
        gbump(int __n);

        void
        setg(char_type* __gbeg, char_type* __gnext, char_type* __gend);

        // 27.6.2.3.3 Put area:
        _LIBCPP_ALWAYS_INLINE
        char_type*
        pbase() const;

        _LIBCPP_ALWAYS_INLINE
        char_type*
        pptr() const;

        _LIBCPP_ALWAYS_INLINE
        char_type*
        epptr() const;

        void
        pbump(int __n);

        void
        setp(char_type* __pbeg, char_type* __pend);

        // 27.6.2.4 virtual functions:
        // 27.6.2.4.1 Locales:
        virtual void
        imbue(const locale& __loc);

        // 27.6.2.4.2 Buffer management and positioning:
        virtual basic_streambuf*
        setbuf(char_type* __s, streamsize __n);
        virtual pos_type
        seekoff(off_type __off, ios_base::seekdir __way,
            ios_base::openmode __which = ios_base::in | ios_base::out);
        virtual pos_type
        seekpos(pos_type __sp,
            ios_base::openmode __which = ios_base::in | ios_base::out);
        virtual int
        sync();

        // 27.6.2.4.3 Get area:
        virtual streamsize
        showmanyc();
        virtual streamsize
        xsgetn(char_type* __s, streamsize __n);
        virtual int_type
        underflow();
        virtual int_type
        uflow();

        // 27.6.2.4.4 Putback:
        virtual int_type
        pbackfail(int_type __c = traits_type::eof());

        // 27.6.2.4.5 Put area:
        virtual streamsize
        xsputn(const char_type* __s, streamsize __n);
        virtual int_type
        overflow(int_type __c = traits_type::eof());

      private:

        // input buffer pointers
        char_type* m_binp;
        char_type* m_ninp;
        char_type* m_einp;

        // output buffer pointers
        char_type* m_bout;
        char_type* m_nout;
        char_type* m_eout;

        locale m_locale;

      };

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_streambuf<_CharT, _Traits>::pubimbue(const locale& __loc)
      {
        imbue(__loc);
        locale __r = m_locale;
        m_locale = __loc;

        return __r;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      locale
      basic_streambuf<_CharT, _Traits>::getloc() const
      {
        return m_locale;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      basic_streambuf<_CharT, _Traits>*
      basic_streambuf<_CharT, _Traits>::pubsetbuf(char_type* __s,
          streamsize __n)
      {
        return setbuf(__s, __n);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::pubseekoff(off_type __off,
          ios_base::seekdir __way,
          ios_base::openmode __which)
        {
          return seekoff(__off, __way, __which);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::pos_type
      basic_streambuf<_CharT, _Traits>::pubseekpos(pos_type __sp,
          ios_base::openmode __which)
        {
          return seekpos(__sp, __which);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      int
      basic_streambuf<_CharT, _Traits>::pubsync()
      {
        return sync();
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::in_avail()
      {
        if (m_ninp < m_einp)
          {
            return static_cast<streamsize>(m_einp - m_ninp);
          }
        return showmanyc();
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::snextc()
        {
          if (sbumpc() == traits_type::eof())
            {
              return traits_type::eof();
            }
          return sgetc();
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sbumpc()
        {
          if (m_ninp == m_einp)
            {
              return uflow();
            }
          return traits_type::to_int_type(*m_ninp++);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sgetc()
        {
          if (m_ninp == m_einp)
            {
              return underflow();
            }
          return traits_type::to_int_type(*m_ninp);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::sgetn(char_type* __s, streamsize __n)
      {
        return xsgetn(__s, __n);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sputbackc(char_type __c)
        {
          if (m_binp == m_ninp || !traits_type::eq(__c, m_ninp[-1]))
            {
              return pbackfail(traits_type::to_int_type(__c));
            }
          return traits_type::to_int_type(*--m_ninp);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sungetc()
        {
          if (m_binp == m_ninp)
            {
              return pbackfail();
            }
          return traits_type::to_int_type(*--m_ninp);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      typename basic_streambuf<_CharT, _Traits>::int_type
      basic_streambuf<_CharT, _Traits>::sputc(char_type __c)
        {
          if (m_nout == m_eout)
            {
              return overflow(traits_type::to_int_type(__c));
            }
          *m_nout++ = __c;
          return traits_type::to_int_type(__c);
        }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      streamsize
      basic_streambuf<_CharT, _Traits>::sputn(const char_type* __s,
          streamsize __n)
      {
        return xsputn(__s, __n);
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::eback() const
      {
        return m_binp;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::gptr() const
      {
        return m_ninp;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::egptr() const
      {
        return m_einp;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::gbump(int __n)
      {
        m_ninp += __n;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::setg(char_type* __gbeg,
          char_type* __gnext, char_type* __gend)
      {
        m_binp = __gbeg;
        m_ninp = __gnext;
        m_einp = __gend;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::pbase() const
      {
        return m_bout;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::pptr() const
      {
        return m_nout;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_ALWAYS_INLINE
      _CharT*
      basic_streambuf<_CharT, _Traits>::epptr() const
      {
        return m_eout;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::pbump(int __n)
      {
        m_nout += __n;
      }

    template<class _CharT, class _Traits>
      inline _LIBCPP_INLINE_VISIBILITY
      void
      basic_streambuf<_CharT, _Traits>::setp(char_type* __pbeg,
          char_type* __pend)
      {
        m_bout = m_nout = __pbeg;
        m_eout = __pend;
      }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#pragma clang diagnostic ignored "-Wpadded"
#endif

    extern template class basic_streambuf<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  extern template class basic_streambuf<wchar_t>;

#endif

#pragma GCC diagnostic pop

//_LIBCPP_END_NAMESPACE_STD
}
}

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STEAMBUF_H_ */
