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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STDEXCEPT_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STDEXCEPT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/iosfwd.h"

namespace os
{
  namespace std
  {

    class logic_error : public exception
    {
    private:
      void* __imp_;
    public:
      explicit
      logic_error(const string&);
      explicit
      logic_error(const char*);

      logic_error(const logic_error&) noexcept;
      logic_error&
      operator=(const logic_error&) noexcept;

      virtual
      ~logic_error() noexcept;

      virtual const char*
      what() const noexcept;
    };

    class runtime_error : public exception
    {
    private:
      void* __imp_;
    public:
      explicit
      runtime_error(const string&);
      explicit
      runtime_error(const char*);

      runtime_error(const runtime_error&) noexcept;
      runtime_error&
      operator=(const runtime_error&) noexcept;

      virtual
      ~runtime_error() noexcept;

      virtual const char*
      what() const noexcept;
    };

    class domain_error : public logic_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      domain_error(const string& __s)
          : logic_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      domain_error(const char* __s)
          : logic_error(__s)
      {
      }

      virtual
      ~domain_error() noexcept;
    };

    class invalid_argument : public logic_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      invalid_argument(const string& __s)
          : logic_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      invalid_argument(const char* __s)
          : logic_error(__s)
      {
      }

      virtual
      ~invalid_argument() noexcept;
    };

    class length_error : public logic_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      length_error(const string& __s)
          : logic_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      length_error(const char* __s)
          : logic_error(__s)
      {
      }

      virtual
      ~length_error() noexcept;
    };

    class out_of_range : public logic_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      out_of_range(const string& __s)
          : logic_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      out_of_range(const char* __s)
          : logic_error(__s)
      {
      }

      virtual
      ~out_of_range() noexcept;
    };

    class range_error : public runtime_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      range_error(const string& __s)
          : runtime_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      range_error(const char* __s)
          : runtime_error(__s)
      {
      }

      virtual
      ~range_error() noexcept;
    };

    class overflow_error : public runtime_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      overflow_error(const string& __s)
          : runtime_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      overflow_error(const char* __s)
          : runtime_error(__s)
      {
      }

      virtual
      ~overflow_error() noexcept;
    };

    class underflow_error : public runtime_error
    {
    public:
      __attribute__ ((always_inline)) explicit
      underflow_error(const string& __s)
          : runtime_error(__s)
      {
      }
      __attribute__ ((always_inline)) explicit
      underflow_error(const char* __s)
          : runtime_error(__s)
      {
      }

      virtual
      ~underflow_error() noexcept;
    };

  }  // namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_STDEXCEPT_H_
