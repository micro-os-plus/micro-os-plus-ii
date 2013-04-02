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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/iosfwd.h"
//#include "portable/language/cpp/include/internal/_locale.h"
#include "portable/language/cpp/include/internal/_char_traits.h"
#include "portable/language/cpp/include/internal/_ios_base.h"
#include "portable/language/cpp/include/internal/_basic_ios.h"
#include "portable/language/cpp/include/internal/_fpos.h"

#include "portable/language/cpp/include/cstddef.h"

namespace os
  {
    namespace std
      {

        // As per 27.5.1,
        // - streamsize is present here indirectly, from ios_base.h

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)
//enum class io_errc
        //_LIBCPP_DECLARE_STRONG_ENUM(io_errc)
        enum class io_errc
          {
            stream = 1
          };
        _LIBCPP_DECLARE_STRONG_ENUM_EPILOG(io_errc)
#endif

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

        template <>
        struct _LIBCPP_VISIBLE is_error_code_enum<io_errc> : public true_type
          {};

#ifdef _LIBCPP_HAS_NO_STRONG_ENUMS
        template <>
        struct _LIBCPP_VISIBLE is_error_code_enum<io_errc::__lx> : public true_type
          {};
#endif

        _LIBCPP_VISIBLE
        const error_category& iostream_category();

        inline _LIBCPP_INLINE_VISIBILITY
        error_code
        make_error_code(io_errc __e)
          {
            return error_code(static_cast<int>(__e), iostream_category());
          }

        inline _LIBCPP_INLINE_VISIBILITY
        error_condition
        make_error_condition(io_errc __e)
          {
            return error_condition(static_cast<int>(__e), iostream_category());
          }

        class _LIBCPP_EXCEPTION_ABI ios_base::failure
        : public system_error
          {
          public:
            explicit failure(const string& __msg, const error_code& __ec = io_errc::stream);
            explicit failure(const char* __msg, const error_code& __ec = io_errc::stream);
            virtual ~failure() throw();
          };

#endif

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wweak-template-vtables"
#pragma clang diagnostic ignored "-Wpadded"
#endif

        extern template class basic_ios<char>;

#if defined(OS_SKIP_NOT_YET_IMPLEMENTED)

        _LIBCPP_EXTERN_TEMPLATE(class basic_ios<wchar_t>)

#endif

#pragma GCC diagnostic pop

      }
  }
#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_IOS_H_
