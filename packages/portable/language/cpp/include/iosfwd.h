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
/// \brief I/O streams forward definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"

// include next for mbstate_t
#include <wchar.h>

namespace os
{
  namespace std
  {
#if !defined(__DOXYGEN__)
    class _LIBCPP_VISIBLE ios_base;

    /// struct char_traits.
    template<class TChar_T>
      struct _LIBCPP_VISIBLE char_traits;

    /// class allocator.
    template<class _Tp>
      class _LIBCPP_VISIBLE allocator;

    /// class basic_ios.
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
      class _LIBCPP_VISIBLE basic_ios;

    /// class basic_streambuf.
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
      class _LIBCPP_VISIBLE basic_streambuf;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_istream;
#endif

    /// class basic_ostream.
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
      class _LIBCPP_VISIBLE basic_ostream;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_iostream;

    template<class TChar_T, class TTraits_T = char_traits<TChar_T>,
    class _Allocator = allocator<TChar_T> >
    class _LIBCPP_VISIBLE basic_stringbuf;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T>,
    class _Allocator = allocator<TChar_T> >
    class _LIBCPP_VISIBLE basic_istringstream;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T>,
    class _Allocator = allocator<TChar_T> >
    class _LIBCPP_VISIBLE basic_ostringstream;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T>,
    class _Allocator = allocator<TChar_T> >
    class _LIBCPP_VISIBLE basic_stringstream;

    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_filebuf;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_ifstream;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_ofstream;
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE basic_fstream;

    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
    class _LIBCPP_VISIBLE istreambuf_iterator;
#endif

    /// class ostreambuf_iterator.
    template<class TChar_T, class TTraits_T = char_traits<TChar_T> >
      class _LIBCPP_VISIBLE ostreambuf_iterator;

    /// Base class for @c char streams.
    typedef basic_ios<char> ios;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    /// Base class for @c wchar_t streams.
    typedef basic_ios<wchar_t> wios;

#endif

    /// Base class for @c char buffers.
    typedef basic_streambuf<char> streambuf;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    /// Base class for @c char input streams.
    typedef basic_istream<char> istream;
#endif
    /// Base class for @c char output streams.
    typedef basic_ostream<char> ostream;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    /// Base class for @c char mixed input and output streams.
    typedef basic_iostream<char> iostream;

    /// Class for @c char memory buffers.
    typedef basic_stringbuf<char> stringbuf;
    /// Class for @c char input memory streams.
    typedef basic_istringstream<char> istringstream;
    /// Class for @c char output memory streams.
    typedef basic_ostringstream<char> ostringstream;
    /// Class for @c char mixed input and output memory streams.
    typedef basic_stringstream<char> stringstream;

    /// Class for @c char file buffers.
    typedef basic_filebuf<char> filebuf;
    /// Class for @c char input file streams.
    typedef basic_ifstream<char> ifstream;
    /// Class for @c char output file streams.
    typedef basic_ofstream<char> ofstream;
    /// Class for @c char mixed input and output file streams.
    typedef basic_fstream<char> fstream;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    /// Base class for @c wchar_t buffers.
    typedef basic_streambuf<wchar_t> wstreambuf;
    /// Base class for @c wchar_t input streams.
    typedef basic_istream<wchar_t> wistream;
    /// Base class for @c wchar_t output streams.
    typedef basic_ostream<wchar_t> wostream;
    /// Base class for @c wchar_t mixed input and output streams.
    typedef basic_iostream<wchar_t> wiostream;

    /// Class for @c wchar_t memory buffers.
    typedef basic_stringbuf<wchar_t> wstringbuf;
    /// Class for @c wchar_t input memory streams.
    typedef basic_istringstream<wchar_t> wistringstream;
    /// Class for @c wchar_t output memory streams.
    typedef basic_ostringstream<wchar_t> wostringstream;
    /// Class for @c wchar_t mixed input and output memory streams.
    typedef basic_stringstream<wchar_t> wstringstream;

    /// Class for @c wchar_t file buffers.
    typedef basic_filebuf<wchar_t> wfilebuf;
    /// Class for @c wchar_t input file streams.
    typedef basic_ifstream<wchar_t> wifstream;
    /// Class for @c wchar_t output file streams.
    typedef basic_ofstream<wchar_t> wofstream;
    /// Class for @c wchar_t mixed input and output file streams.
    typedef basic_fstream<wchar_t> wfstream;

#endif

    template<class _State>
      class _LIBCPP_VISIBLE fpos;

    /// \brief File position for char streams.
    ///
    /// \details
    /// The type streampos shall be an implementation-defined
    /// type that satisfies the requirements for pos_type in
    /// 27.2.2 and 27.3.
    /// The type streampos is used for
    /// positioning streams specialized on char.

    typedef fpos<mbstate_t> streampos;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    /// \brief File position for wchar_t streams.
    ///
    /// \details
    /// The type wstreampos is used for
    /// positioning streams specialized on wchar_t.
    typedef fpos<mbstate_t> wstreampos;
#endif

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    /// File position for char16_t streams.
    typedef fpos<mbstate_t> u16streampos;
    /// File position for char32_t streams.
    typedef fpos<mbstate_t> u32streampos;
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
    /// \brief Stream offset.
    ///
    /// \details
    /// The type streamoff shall be an implementation-defined
    /// type that satisfies the requirements for off_type in
    /// 27.2.2 and 27.3.
    typedef long long streamoff;        // for char_traits in <string>

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template<class TChar_T, class TTraits_T = char_traits<TChar_T>,
  class _Allocator = allocator<TChar_T> >
  class _LIBCPP_VISIBLE basic_string;

  typedef basic_string<char, char_traits<char>, allocator<char> > string;

  typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

#endif

#endif

}
}

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_ */
