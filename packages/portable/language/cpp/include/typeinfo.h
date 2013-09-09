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
/// \brief Type info.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPEINFO_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPEINFO_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std  // purposefully not using versioning namespace
  {

    class type_info
    {
      type_info&
      operator=(const type_info&);
      type_info(const type_info&);
    protected:
      const char* __type_name;

      __attribute__((always_inline))
      explicit
      type_info(const char* __n) :
          __type_name(__n)
      {
      }

    public:
      virtual
      ~type_info();

      __attribute__((always_inline))
      const char*
      name() const noexcept
      {
        return __type_name;
      }

      __attribute__((always_inline))
      bool
      before(const type_info& __arg) const noexcept
      {
        return __type_name < __arg.__type_name;
      }

      __attribute__((always_inline))
       size_t
      hash_code() const noexcept
      {
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#else
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
        return *reinterpret_cast<const size_t*>(&__type_name);
#pragma GCC diagnostic pop
      }

      __attribute__((always_inline))
      bool
      operator==(const type_info& __arg) const noexcept
      {
        return __type_name == __arg.__type_name;
      }

      __attribute__((always_inline))
      bool
      operator!=(const type_info& __arg) const noexcept
      {
        return !operator==(__arg);
      }

    };

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

  class bad_cast : public exception
    {
    public:
      bad_cast() noexcept;
      virtual
      ~bad_cast() noexcept;
      virtual const char*
      what() const noexcept;
    };

  class bad_typeid : public exception
    {
    public:
      bad_typeid() noexcept;
      virtual
      ~bad_typeid() noexcept;
      virtual const char*
      what() const noexcept;
    };

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
}
  // namespace std
} // namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_TYPEINFO_H_
