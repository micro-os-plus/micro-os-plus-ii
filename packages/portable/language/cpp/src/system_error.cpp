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
/// \brief System errors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/system_error.h"
#include "portable/language/cpp/include/string.h"
#include "portable/language/cpp/include/cstring.h"

namespace os
{
  namespace std
  {

    // class error_category

    error_category::error_category() noexcept
    {
    }

    error_category::~error_category() noexcept
    {
    }

    error_condition
    error_category::default_error_condition(int ev) const noexcept
    {
      return error_condition(ev, *this);
    }

    bool
    error_category::equivalent(int code, const error_condition& condition) const noexcept
    {
      return default_error_condition(code) == condition;
    }

    bool
    error_category::equivalent(const error_code& code, int condition) const noexcept
    {
      return *this == code.category() && code.value() == condition;
    }

    string
    __do_message::message(int ev) const
    {
      return string(strerror(ev));
    }

    class __generic_error_category : public __do_message
    {
    public:
      virtual const char*
      name() const noexcept;
      virtual string
      message(int ev) const;
    };

    const char*
    __generic_error_category::name() const noexcept
    {
      return "generic";
    }

    string
    __generic_error_category::message(int ev) const
    {
#ifdef ELAST
      if (ev > ELAST)
      return string("unspecified generic_category error");
#endif  // ELAST
      return __do_message::message(ev);
    }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
    const error_category&
    generic_category() noexcept
    {
      static __generic_error_category s;
      return s;
    }
#pragma GCC diagnostic pop

    class __system_error_category : public __do_message
    {
    public:
      virtual const char*
      name() const noexcept;
      virtual string
      message(int ev) const;
      virtual error_condition
      default_error_condition(int ev) const noexcept;
    };

    const char*
    __system_error_category::name() const noexcept
    {
      return "system";
    }

    string
    __system_error_category::message(int ev) const
    {
#ifdef ELAST
      if (ev > ELAST)
      return string("unspecified system_category error");
#endif  // ELAST
      return __do_message::message(ev);
    }

    error_condition
    __system_error_category::default_error_condition(int ev) const noexcept
    {
#ifdef ELAST
      if (ev > ELAST)
      return error_condition(ev, system_category());
#endif  // ELAST
      return error_condition(ev, generic_category());
    }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
    const error_category&
    system_category() noexcept
    {
      static __system_error_category s;
      return s;
    }
#pragma GCC diagnostic pop

    // error_condition

    string
    error_condition::message() const
    {
      return __cat_->message(__val_);
    }

    // error_code

    string
    error_code::message() const
    {
      return __cat_->message(__val_);
    }

    // system_error

    string
    system_error::__init(const error_code& ec, string what_arg)
    {
      if (ec)
        {
          if (!what_arg.empty())
            what_arg += ": ";
          what_arg += ec.message();
        }
      return os::std::move(what_arg);
    }

    system_error::system_error(error_code ec, const string& what_arg)
        : runtime_error(__init(ec, what_arg)), __ec_(ec)
    {
    }

    system_error::system_error(error_code ec, const char* what_arg)
        : runtime_error(__init(ec, what_arg)), __ec_(ec)
    {
    }

    system_error::system_error(error_code ec)
        : runtime_error(__init(ec, "")), __ec_(ec)
    {
    }

    system_error::system_error(int ev, const error_category& ecat,
        const string& what_arg)
        : runtime_error(__init(error_code(ev, ecat), what_arg)), __ec_(
            error_code(ev, ecat))
    {
    }

    system_error::system_error(int ev, const error_category& ecat,
        const char* what_arg)
        : runtime_error(__init(error_code(ev, ecat), what_arg)), __ec_(
            error_code(ev, ecat))
    {
    }

    system_error::system_error(int ev, const error_category& ecat)
        : runtime_error(__init(error_code(ev, ecat), "")), __ec_(
            error_code(ev, ecat))
    {
    }

    system_error::~system_error() noexcept
    {
    }

    void
    __attribute__((noreturn))
    __throw_system_error(int ev, const char* what_arg)
    {
      throw system_error(error_code(ev, system_category()), what_arg);
    }

  } // namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
