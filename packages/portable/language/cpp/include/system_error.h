//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief String declarations.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_SYSTEMERROR_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_SYSTEMERROR_H

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/cerrno"
#include "portable/language/cpp/include/type_traits.h"
#include "portable/language/cpp/include/stdexcept.h"
#include "portable/language/cpp/include/internal/_functional_base.h"

namespace os
{
  namespace std
  {

    // is_error_code_enum

    template<class _Tp>
      struct is_error_code_enum : public false_type
      {
      };

    // is_error_condition_enum

    template<class _Tp>
      struct is_error_condition_enum : public false_type
      {
      };

    // Some error codes are not present on all platforms, so we provide equivalents
    // for them:

    enum class errc
    {
    // ILG: content removed
    };

    template<>
      struct is_error_condition_enum<errc> : true_type
      {
      };

#ifdef _LIBCPP_HAS_NO_STRONG_ENUMS
    template <>
    struct is_error_condition_enum<errc::__lx>
    : true_type
      {};
#endif

    class error_condition;
    class error_code;

    // class error_category

    class __do_message;

    class error_category
    {
    public:
      virtual
      ~error_category() noexcept;

      error_category() noexcept;
    private:
      error_category(const error_category&); // = delete;
      error_category&
      operator=(const error_category&); // = delete;

    public:
      virtual const char*
      name() const noexcept = 0;
      virtual error_condition
      default_error_condition(int __ev) const noexcept;
      virtual bool
      equivalent(int __code, const error_condition& __condition) const noexcept;
      virtual bool
      equivalent(const error_code& __code, int __condition) const noexcept;
      virtual string
      message(int __ev) const = 0;

      __attribute__((always_inline))
      bool
      operator==(const error_category& __rhs) const noexcept
      {
        return this == &__rhs;
      }

      __attribute__((always_inline))
      bool
      operator!=(const error_category& __rhs) const noexcept
      {
        return !(*this == __rhs);
      }

      __attribute__((always_inline))
      bool
      operator<(const error_category& __rhs) const noexcept
      {
        return this < &__rhs;
      }

      friend class __do_message;
    };

    class __do_message : public error_category
    {
    public:
      virtual string
      message(int ev) const;
    };

    const error_category&
    generic_category() noexcept;
    const error_category&
    system_category() noexcept;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    class error_condition
    {
      int __val_;
      const error_category* __cat_;

    public:
      __attribute__((always_inline))
      error_condition()
noexcept          : //
          __val_(0),//
          __cat_(&generic_category())
            {

            }

          __attribute__((always_inline))
          error_condition(int __val, const error_category& __cat) noexcept
          : __val_(__val), __cat_(&__cat)
            {}

          template <class _Ep>
          __attribute__((always_inline))
          error_condition(_Ep __e,
              typename enable_if<is_error_condition_enum<_Ep>::value>::type* = 0
          ) noexcept
            { *this = make_error_condition(__e);}

          __attribute__((always_inline))
          void assign(int __val, const error_category& __cat) noexcept
            {
              __val_ = __val;
              __cat_ = &__cat;
            }

          template <class _Ep>
          __attribute__((always_inline))
          typename enable_if
          <
          is_error_condition_enum<_Ep>::value,
          error_condition&
          >::type
          operator=(_Ep __e) noexcept
            { *this = make_error_condition(__e); return *this;}

          __attribute__((always_inline))
          void clear() noexcept
            {
              __val_ = 0;
              __cat_ = &generic_category();
            }

          __attribute__((always_inline))
          int value() const noexcept
            { return __val_;}

          __attribute__((always_inline))
          const error_category& category() const noexcept
            { return *__cat_;}
          string message() const;

          __attribute__((always_inline))
          explicit
          operator bool() const noexcept
            { return __val_ != 0;}
        };

#pragma GCC diagnostic pop

    inline __attribute__((always_inline))
    error_condition
    make_error_condition(errc __e) noexcept
    {
      return error_condition(static_cast<int>(__e), generic_category());
    }

    inline __attribute__((always_inline))
    bool
    operator<(const error_condition& __x, const error_condition& __y) noexcept
    {
      return __x.category() < __y.category()
          || (__x.category() == __y.category() && __x.value() < __y.value());
    }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    // error_code
    class error_code
    {
      int __val_;
      const error_category* __cat_;
    public:
      __attribute__((always_inline))
      error_code()
noexcept          : __val_(0), __cat_(&system_category())
            {}

          __attribute__((always_inline))
          error_code(int __val, const error_category& __cat) noexcept
          : __val_(__val), __cat_(&__cat)
            {}

          template <class _Ep>
          __attribute__((always_inline))
          error_code(_Ep __e,
              typename enable_if<is_error_code_enum<_Ep>::value>::type* = 0
          ) noexcept
            { *this = make_error_code(__e);}

          __attribute__((always_inline))
          void assign(int __val, const error_category& __cat) noexcept
            {
              __val_ = __val;
              __cat_ = &__cat;
            }

          template <class _Ep>
          __attribute__((always_inline))
          typename enable_if
          <
          is_error_code_enum<_Ep>::value,
          error_code&
          >::type
          operator=(_Ep __e) noexcept
            { *this = make_error_code(__e); return *this;}

          __attribute__((always_inline))
          void clear() noexcept
            {
              __val_ = 0;
              __cat_ = &system_category();
            }

          __attribute__((always_inline))
          int value() const noexcept
            { return __val_;}

          __attribute__((always_inline))
          const error_category& category() const noexcept
            { return *__cat_;}

          __attribute__((always_inline))
          error_condition default_error_condition() const noexcept
            { return __cat_->default_error_condition(__val_);}

          string message() const;

          __attribute__((always_inline))
          explicit
          operator bool() const noexcept
            { return __val_ != 0;}
        };

#pragma GCC diagnostic pop

    inline __attribute__((always_inline))
    error_code
    make_error_code(errc __e) noexcept
    {
      return error_code(static_cast<int>(__e), generic_category());
    }

    inline __attribute__((always_inline))
    bool
    operator<(const error_code& __x, const error_code& __y) noexcept
    {
      return __x.category() < __y.category()
          || (__x.category() == __y.category() && __x.value() < __y.value());
    }

    inline __attribute__((always_inline))
    bool
    operator==(const error_code& __x, const error_code& __y) noexcept
    {
      return __x.category() == __y.category() && __x.value() == __y.value();
    }

    inline __attribute__((always_inline))
    bool
    operator==(const error_code& __x, const error_condition& __y) noexcept
    {
      return __x.category().equivalent(__x.value(), __y)
          || __y.category().equivalent(__x, __y.value());
    }

    inline __attribute__((always_inline))
    bool
    operator==(const error_condition& __x, const error_code& __y) noexcept
    {
      return __y == __x;
    }

    inline __attribute__((always_inline))
    bool
    operator==(const error_condition& __x, const error_condition& __y) noexcept
    {
      return __x.category() == __y.category() && __x.value() == __y.value();
    }

    inline __attribute__((always_inline))
    bool
    operator!=(const error_code& __x, const error_code& __y) noexcept
    {
      return !(__x == __y);
    }

    inline __attribute__((always_inline))
    bool
    operator!=(const error_code& __x, const error_condition& __y) noexcept
    {
      return !(__x == __y);
    }

    inline __attribute__((always_inline))
    bool
    operator!=(const error_condition& __x, const error_code& __y) noexcept
    {
      return !(__x == __y);
    }

    inline __attribute__((always_inline))
    bool
    operator!=(const error_condition& __x, const error_condition& __y) noexcept
    {
      return !(__x == __y);
    }

    template<>
      struct hash<error_code> : public unary_function<error_code, size_t>
      {
        __attribute__((always_inline))
        size_t
        operator()(const error_code& __ec) const noexcept
        {
          return static_cast<size_t>(__ec.value());
        }
      };

    // system_error

    class system_error : public runtime_error
    {
      error_code __ec_;
    public:
      system_error(error_code __ec, const string& __what_arg);
      system_error(error_code __ec, const char* __what_arg);
      system_error(error_code __ec);
      system_error(int __ev, const error_category& __ecat,
          const string& __what_arg);
      system_error(int __ev, const error_category& __ecat,
          const char* __what_arg);
      system_error(int __ev, const error_category& __ecat);
      ~system_error() noexcept;

      __attribute__((always_inline))
      const error_code&
      code() const noexcept
      {
        return __ec_;
      }

    private:
      static string
      __init(const error_code&, string);
    };

    void
    __throw_system_error(int ev, const char* what_arg);

  } // namespace std
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_SYSTEMERROR_H
