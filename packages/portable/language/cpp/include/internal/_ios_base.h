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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

    // 27.5.2 Types
    typedef ptrdiff_t streamsize;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // 27.5.3 Class ios_base
    class _LIBCPP_VISIBLE ios_base
    {
    public:
      // actual definitions in _ios_base_failure.h
      class _LIBCPP_VISIBLE failure;

      // 27.5.3.1.2 fmtflags
      typedef unsigned int fmtflags;
      static const fmtflags boolalpha = 0x0001;
      static const fmtflags dec = 0x0002;
      static const fmtflags fixed = 0x0004;
      static const fmtflags hex = 0x0008;
      static const fmtflags internal = 0x0010;
      static const fmtflags left = 0x0020;
      static const fmtflags oct = 0x0040;
      static const fmtflags right = 0x0080;
      static const fmtflags scientific = 0x0100;
      static const fmtflags showbase = 0x0200;
      static const fmtflags showpoint = 0x0400;
      static const fmtflags showpos = 0x0800;
      static const fmtflags skipws = 0x1000;
      static const fmtflags unitbuf = 0x2000;
      static const fmtflags uppercase = 0x4000;
      // As per Table 123 — fmtflags constants
      static const fmtflags adjustfield = left | right | internal;
      static const fmtflags basefield = dec | oct | hex;
      static const fmtflags floatfield = scientific | fixed;

      // 27.5.3.1.3 iostate
      typedef unsigned int iostate;
      static const iostate badbit = 0x1;
      static const iostate eofbit = 0x2;
      static const iostate failbit = 0x4;
      static const iostate goodbit = 0x0;

      // 27.5.3.1.4 openmode
      typedef unsigned int openmode;
      static const openmode app = 0x01;
      static const openmode ate = 0x02;
      static const openmode binary = 0x04;
      static const openmode in = 0x08;
      static const openmode out = 0x10;
      static const openmode trunc = 0x20;

      // 27.5.3.1.5 seekdir
      enum seekdir
      {
        beg, cur, end
      };

      class _LIBCPP_VISIBLE Init;

      // 27.5.3.2 fmtflags state:
      _LIBCPP_INLINE_VISIBILITY
      fmtflags
      flags() const;

      _LIBCPP_INLINE_VISIBILITY
      fmtflags
      flags(fmtflags fmtfl);

      _LIBCPP_INLINE_VISIBILITY
      fmtflags
      setf(fmtflags fmtfl);

      _LIBCPP_INLINE_VISIBILITY
      fmtflags
      setf(fmtflags fmtfl, fmtflags mask);

      _LIBCPP_INLINE_VISIBILITY void
      unsetf(fmtflags mask);

      _LIBCPP_INLINE_VISIBILITY
      streamsize
      precision() const;

      _LIBCPP_INLINE_VISIBILITY
      streamsize
      precision(streamsize prec);

      _LIBCPP_INLINE_VISIBILITY
      streamsize
      width() const;

      _LIBCPP_INLINE_VISIBILITY
      streamsize
      width(streamsize wide);

      // 27.5.3.3 locales:
      locale
      imbue(const locale& loc);
      locale
      getloc() const;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      // 27.5.3.5 storage:
      static int xalloc();
      long& iword(int idx);
      void*& pword(int idx);
#endif

      // destructor
      virtual
      ~ios_base();

      // 27.5.3.6 callbacks;
      enum event
      {
        erase_event, imbue_event, copyfmt_event
      };

      typedef void
      (*event_callback)(event, ios_base&, int index);
      void
      register_callback(event_callback fn, int index);

    private:
      ios_base(const ios_base&) = delete;
      ios_base&
      operator=(const ios_base&) = delete;

    public:
      static bool
      sync_with_stdio(bool sync = true);

    protected:

      _LIBCPP_INLINE_VISIBILITY
      ios_base();

      void
      __call_callbacks(event);

      void
      copyfmt(const ios_base&);
      void
      move(ios_base&);
      void
      swap(ios_base&) _NOEXCEPT;

      // implementation specifics

      // required, in order to keep members private
      _LIBCPP_INLINE_VISIBILITY
      void
      __init();

      // end of implementation specifics

    private:

      // All data members must be scalars

      fmtflags m_fmtflags;
      streamsize m_precision;
      streamsize m_width;
      void* m_locale;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      event_callback* __fn_;
      int* __index_;
      size_t __event_size_;
      size_t __event_cap_;
      long* __iarray_;
      size_t __iarray_size_;
      size_t __iarray_cap_;
      void** __parray_;
      size_t __parray_size_;
      size_t __parray_cap_;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      static int ms_xindex;
#endif

    };

#pragma GCC diagnostic pop

  // ------------------------------------------------------------------------
  // 27.5.3.1.6 Class ios_base::Init
    class _LIBCPP_VISIBLE ios_base::Init
    {
    public:
      Init();
      ~Init();

    private:
      static int init_cnt; // exposition only
    };

    // ------------------------------------------------------------------------
    // fmtflags

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base::fmtflags
    ios_base::flags() const
    {
      return m_fmtflags;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base::fmtflags
    ios_base::flags(fmtflags fmtfl)
    {
      fmtflags __r = m_fmtflags;
      m_fmtflags = fmtfl;
      return __r;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base::fmtflags
    ios_base::setf(fmtflags fmtfl)
    {
      fmtflags __r = m_fmtflags;
      m_fmtflags |= fmtfl;
      return __r;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    void
    ios_base::unsetf(fmtflags mask)
    {
      m_fmtflags &= ~mask;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base::fmtflags
    ios_base::setf(fmtflags fmtfl, fmtflags mask)
    {
      fmtflags __r = m_fmtflags;
      unsetf(mask);
      m_fmtflags |= fmtfl & mask;
      return __r;
    }

    // precision

    inline _LIBCPP_INLINE_VISIBILITY
    streamsize
    ios_base::precision() const
    {
      return m_precision;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    streamsize
    ios_base::precision(streamsize prec)
    {
      streamsize __r = m_precision;
      m_precision = prec;
      return __r;
    }

    // width

    inline _LIBCPP_INLINE_VISIBILITY
    streamsize
    ios_base::width() const
    {
      return m_width;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    streamsize
    ios_base::width(streamsize wide)
    {
      streamsize __r = m_width;
      m_width = wide;
      return __r;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base::ios_base()
    {
      // purposefully does no initialisation ("Each ios_base member has an
      // indeterminate value after construction").
    }

    // ------------------------------------------------------------------------

    // ------------------------------------------------------------------------
    // 27.5.6 ios_base manipulators

    // 27.5.6.1 fmtflags manipulators
    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    boolalpha(ios_base& str)
    {
      str.setf(ios_base::boolalpha);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    noboolalpha(ios_base& str)
    {
      str.unsetf(ios_base::boolalpha);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    showbase(ios_base& str)
    {
      str.setf(ios_base::showbase);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    noshowbase(ios_base& str)
    {
      str.unsetf(ios_base::showbase);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    showpoint(ios_base& str)
    {
      str.setf(ios_base::showpoint);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    noshowpoint(ios_base& str)
    {
      str.unsetf(ios_base::showpoint);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    showpos(ios_base& str)
    {
      str.setf(ios_base::showpos);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    noshowpos(ios_base& str)
    {
      str.unsetf(ios_base::showpos);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    skipws(ios_base& str)
    {
      str.setf(ios_base::skipws);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    noskipws(ios_base& str)
    {
      str.unsetf(ios_base::skipws);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    uppercase(ios_base& str)
    {
      str.setf(ios_base::uppercase);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    nouppercase(ios_base& str)
    {
      str.unsetf(ios_base::uppercase);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    unitbuf(ios_base& str)
    {
      str.setf(ios_base::unitbuf);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    nounitbuf(ios_base& str)
    {
      str.unsetf(ios_base::unitbuf);
      return str;
    }

    // 27.5.6.2 adjustfield manipulators
    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    internal(ios_base& str)
    {
      str.setf(ios_base::internal, ios_base::adjustfield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    left(ios_base& str)
    {
      str.setf(ios_base::left, ios_base::adjustfield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    right(ios_base& str)
    {
      str.setf(ios_base::right, ios_base::adjustfield);
      return str;
    }

    // 27.5.6.3 basefield manipulators
    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    dec(ios_base& str)
    {
      str.setf(ios_base::dec, ios_base::basefield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    hex(ios_base& str)
    {
      str.setf(ios_base::hex, ios_base::basefield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    oct(ios_base& str)
    {
      str.setf(ios_base::oct, ios_base::basefield);
      return str;
    }

    // 27.5.6.4 floatfield manipulators
    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    fixed(ios_base& str)
    {
      str.setf(ios_base::fixed, ios_base::floatfield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    scientific(ios_base& str)
    {
      str.setf(ios_base::scientific, ios_base::floatfield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    hexfloat(ios_base& str)
    {
      str.setf(ios_base::fixed | ios_base::scientific, ios_base::floatfield);
      return str;
    }

    inline _LIBCPP_INLINE_VISIBILITY
    ios_base&
    defaultfloat(ios_base& str)
    {
      str.unsetf(ios_base::floatfield);
      return str;
    }

  // ------------------------------------------------------------------------

    inline _LIBCPP_INLINE_VISIBILITY
    void
    ios_base::__init()
    {
      m_fmtflags = skipws | dec;
      m_width = 0;
      m_precision = 6;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      __fn_ = 0;
      __index_ = 0;
      __event_size_ = 0;
      __event_cap_ = 0;
      __iarray_ = 0;
      __iarray_size_ = 0;
      __iarray_cap_ = 0;
      __parray_ = 0;
      __parray_size_ = 0;
      __parray_cap_ = 0;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
      ::new (&m_locale) locale;
#endif
    }

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  // 27.5.6.5 Error reporting
  inline _LIBCPP_INLINE_VISIBILITY
  error_code
  make_error_code(io_errc e)
    {
      return error_code(static_cast<int>(e), iostream_category());
    }

  inline _LIBCPP_INLINE_VISIBILITY
  error_condition
  make_error_condition(io_errc e)
    {
      return error_condition(static_cast<int>(e), iostream_category());
    }

#endif

}
}

#endif // defined( INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_INTERNAL_IOS_BASE_H_ */
