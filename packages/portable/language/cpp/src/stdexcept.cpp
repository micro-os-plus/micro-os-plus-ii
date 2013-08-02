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
/// \brief Standard exceptions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/stdexcept.h"
#include "portable/language/cpp/include/new.h"
#include "portable/language/cpp/include/string.h"
#include "portable/language/cpp/include/cstdlib.h"
#include "portable/language/cpp/include/cstring.h"
#include "portable/language/cpp/include/cstdint.h"
#include "portable/language/cpp/include/cstddef.h"
//#include "system_error"

namespace
{

  class __libcpp_nmstr
  {
  private:
    const char* str_;

    typedef os::std::size_t unused_t;
    typedef os::std::ptrdiff_t count_t;

    static const os::std::ptrdiff_t offset = static_cast<os::std::ptrdiff_t>(2
        * sizeof(unused_t) + sizeof(count_t));

    count_t&
    count() const noexcept
    {
      return (count_t&) (*(str_ - sizeof(count_t)));
    }
  public:
    explicit
    __libcpp_nmstr(const char* msg);
    __libcpp_nmstr(const __libcpp_nmstr& s) _LIBCPP_CANTTHROW;
    __libcpp_nmstr& operator=(const __libcpp_nmstr& s) _LIBCPP_CANTTHROW;
    ~__libcpp_nmstr() _LIBCPP_CANTTHROW;
    const char* c_str() const noexcept
      { return str_;}
  };

  __libcpp_nmstr::__libcpp_nmstr(const char* msg)
  {
    os::std::size_t len = strlen(msg);
    str_ = new char[len + 1 + offset];

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wcast-align"
#endif
    unused_t* c = (unused_t*) str_;
#pragma GCC diagnostic pop

    c[0] = c[1] = len;
    str_ += offset;
    count() = 0;
    os::std::strcpy(const_cast<char*>(c_str()), msg);
  }

  inline
  __libcpp_nmstr::__libcpp_nmstr(const __libcpp_nmstr& s)
  : str_(s.str_)
    {
      __sync_add_and_fetch(&count(), 1);
    }

  __libcpp_nmstr& __libcpp_nmstr ::operator=(const __libcpp_nmstr& s)
    {
      const char* p = str_;
      str_ = s.str_;
      __sync_add_and_fetch(&count(), 1);

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wcast-align"
#endif
      if (__sync_add_and_fetch((count_t*)(p-sizeof(count_t)), count_t(-1)) < 0)
      delete [] (p-offset);
#pragma GCC diagnostic pop

      return *this;
    }

  inline
  __libcpp_nmstr::~__libcpp_nmstr()
  {
    if (__sync_add_and_fetch(&count(), count_t(-1)) < 0)
      delete[] (str_ - offset);
  }

}

namespace os
{
  namespace std  // purposefully not using versioning namespace
  {

    logic_error::logic_error(const string& msg)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr(msg.c_str());
    }

    logic_error::logic_error(const char* msg)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr(msg);
    }

    logic_error::logic_error(const logic_error& le) noexcept : exception(le)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr((const __libcpp_nmstr&)le.__imp_);
    }

    logic_error&
    logic_error::operator=(const logic_error& le) noexcept
    {
      __libcpp_nmstr& s1 = (__libcpp_nmstr&)__imp_;
      const __libcpp_nmstr& s2 = (const __libcpp_nmstr&)le.__imp_;
      s1 = s2;
      return *this;
    }

#ifndef _LIBCPPABI_VERSION

    logic_error::~logic_error() noexcept
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      s.~__libcpp_nmstr();
    }

    const char*
    logic_error::what() const noexcept
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      return s.c_str();
    }

#endif

    runtime_error::runtime_error(const string& msg)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr(msg.c_str());
    }

    runtime_error::runtime_error(const char* msg)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr(msg);
    }

    runtime_error::runtime_error(const runtime_error& le) noexcept : exception(le)
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      ::new(&s) __libcpp_nmstr((const __libcpp_nmstr&)le.__imp_);
    }

    runtime_error&
    runtime_error::operator=(const runtime_error& le) noexcept
    {
      __libcpp_nmstr& s1 = (__libcpp_nmstr&)__imp_;
      const __libcpp_nmstr& s2 = (const __libcpp_nmstr&)le.__imp_;
      s1 = s2;
      return *this;
    }

#ifndef _LIBCPPABI_VERSION

    runtime_error::~runtime_error() noexcept
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      s.~__libcpp_nmstr();
    }

    const char*
    runtime_error::what() const noexcept
    {
      __libcpp_nmstr& s = (__libcpp_nmstr&)__imp_;
      return s.c_str();
    }

    domain_error::~domain_error() noexcept
    {
    }
    invalid_argument::~invalid_argument() noexcept
    {
    }
    length_error::~length_error() noexcept
    {
    }
    out_of_range::~out_of_range() noexcept
    {
    }

    range_error::~range_error() noexcept
    {
    }
    overflow_error::~overflow_error() noexcept
    {
    }
    underflow_error::~underflow_error() noexcept
    {
    }

#endif

  }  // namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
