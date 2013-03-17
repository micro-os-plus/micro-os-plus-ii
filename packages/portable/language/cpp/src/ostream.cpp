//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/ostream.h"
#include "portable/language/cpp/include/ostream.cpp.h"
#include "portable/language/cpp/include/ostream_inserters.cpp.h"

namespace os
{
  namespace std
  {

    // Explicit instantiation of the template.
    template class basic_ostream<char> ;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
    template class basic_ostream<wchar_t>;
#endif

    // Explicit instantiation of the inserters templates.
    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os, char __c);

    // signed and unsigned
    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os, signed char __c);

    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os, unsigned char __c);

    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os, const char* __str);

    // signed and unsigned
    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os,
        const signed char* __str);

    template basic_ostream<char, char_traits<char>>&
    operator<<(basic_ostream<char, char_traits<char>>& __os,
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

}
}

#endif  // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
