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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"

// include next for mbstate_t
#include <wchar.h>

namespace os
{
  namespace std
  {
#if !defined(__DOXYGEN__)
    class _LIBCPP_VISIBLE ios_base;

    template<class _CharT>
      struct _LIBCPP_VISIBLE char_traits;
    template<class _Tp>
      class _LIBCPP_VISIBLE allocator;

    template<class _CharT, class _Traits = char_traits<_CharT> >
      class _LIBCPP_VISIBLE basic_ios;

    template<class _CharT, class _Traits = char_traits<_CharT> >
      class _LIBCPP_VISIBLE basic_streambuf;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_istream;
#endif
    template<class _CharT, class _Traits = char_traits<_CharT> >
      class _LIBCPP_VISIBLE basic_ostream;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_iostream;

    template<class _CharT, class _Traits = char_traits<_CharT>,
    class _Allocator = allocator<_CharT> >
    class _LIBCPP_VISIBLE basic_stringbuf;
    template<class _CharT, class _Traits = char_traits<_CharT>,
    class _Allocator = allocator<_CharT> >
    class _LIBCPP_VISIBLE basic_istringstream;
    template<class _CharT, class _Traits = char_traits<_CharT>,
    class _Allocator = allocator<_CharT> >
    class _LIBCPP_VISIBLE basic_ostringstream;
    template<class _CharT, class _Traits = char_traits<_CharT>,
    class _Allocator = allocator<_CharT> >
    class _LIBCPP_VISIBLE basic_stringstream;

    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_filebuf;
    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_ifstream;
    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_ofstream;
    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE basic_fstream;

    template<class _CharT, class _Traits = char_traits<_CharT> >
    class _LIBCPP_VISIBLE istreambuf_iterator;
#endif

    template<class _CharT, class _Traits = char_traits<_CharT> >
      class _LIBCPP_VISIBLE ostreambuf_iterator;

    typedef basic_ios<char> ios;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    typedef basic_ios<wchar_t> wios;

#endif

    typedef basic_streambuf<char> streambuf;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    typedef basic_istream<char> istream;
#endif
    typedef basic_ostream<char> ostream;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    typedef basic_iostream<char> iostream;

    typedef basic_stringbuf<char> stringbuf;
    typedef basic_istringstream<char> istringstream;
    typedef basic_ostringstream<char> ostringstream;
    typedef basic_stringstream<char> stringstream;

    typedef basic_filebuf<char> filebuf;
    typedef basic_ifstream<char> ifstream;
    typedef basic_ofstream<char> ofstream;
    typedef basic_fstream<char> fstream;
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

    typedef basic_streambuf<wchar_t> wstreambuf;
    typedef basic_istream<wchar_t> wistream;
    typedef basic_ostream<wchar_t> wostream;
    typedef basic_iostream<wchar_t> wiostream;

    typedef basic_stringbuf<wchar_t> wstringbuf;
    typedef basic_istringstream<wchar_t> wistringstream;
    typedef basic_ostringstream<wchar_t> wostringstream;
    typedef basic_stringstream<wchar_t> wstringstream;

    typedef basic_filebuf<wchar_t> wfilebuf;
    typedef basic_ifstream<wchar_t> wifstream;
    typedef basic_ofstream<wchar_t> wofstream;
    typedef basic_fstream<wchar_t> wfstream;

#endif

    template<class _State>
      class _LIBCPP_VISIBLE fpos;

    typedef fpos<mbstate_t> streampos;
#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    typedef fpos<mbstate_t> wstreampos;
#endif

#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
    typedef fpos<mbstate_t> u16streampos;
    typedef fpos<mbstate_t> u32streampos;
#endif  // _LIBCPP_HAS_NO_UNICODE_CHARS
    typedef long long streamoff;        // for char_traits in <string>

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

  template<class _CharT, class _Traits = char_traits<_CharT>,
  class _Allocator = allocator<_CharT> >
  class _LIBCPP_VISIBLE basic_string;

  typedef basic_string<char, char_traits<char>, allocator<char> > string;

  typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

#endif

#endif

}
}

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOSFWD_H_ */
