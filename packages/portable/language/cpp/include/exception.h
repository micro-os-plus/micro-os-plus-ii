//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief exception definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
//#include "portable/language/cpp/include/cstddef.h"
//#include "portable/language/cpp/include/type_traits.h"

namespace os
{
  namespace std
  {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

    class exception
    {
    public:
      __attribute__((always_inline))
      exception() noexcept
      {
      }

      virtual
      ~exception() noexcept;

      virtual const char*
      what() const noexcept;
    };

    class bad_exception : public exception
    {
    public:
      __attribute__((always_inline))
      bad_exception() noexcept
      {
      }

      virtual
      ~bad_exception() noexcept;

      virtual const char*
      what() const noexcept;
    };

#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS)
    typedef void
    (*unexpected_handler)();

    unexpected_handler
    set_unexpected(unexpected_handler) noexcept;

    unexpected_handler
    get_unexpected() noexcept;

    void __attribute__((noreturn))
    unexpected();

    typedef void
    (*terminate_handler)();

    terminate_handler
    set_terminate(terminate_handler) noexcept;

    terminate_handler
    get_terminate() noexcept;
#endif
    void
    __attribute__((noreturn))
    terminate() noexcept;

#if 0

  bool uncaught_exception() noexcept;

  class exception_ptr;

  exception_ptr current_exception() noexcept;
  _LIBCPP_NORETURN void rethrow_exception(exception_ptr);

  class exception_ptr
    {
      void* __ptr_;
    public:
      __attribute__((always_inline)) exception_ptr() noexcept : __ptr_()
        {}
      __attribute__((always_inline)) exception_ptr(nullptr_t) noexcept : __ptr_()
        {}
      exception_ptr(const exception_ptr&) noexcept;
      exception_ptr& operator=(const exception_ptr&) noexcept;
      ~exception_ptr() noexcept;

      __attribute__((always_inline))
      _LIBCPP_EXPLICIT
      operator bool() const noexcept
        { return __ptr_ != nullptr;}

      friend __attribute__((always_inline))
      bool operator==(const exception_ptr& __x, const exception_ptr& __y) noexcept
        { return __x.__ptr_ == __y.__ptr_;}
      friend __attribute__((always_inline))
      bool operator!=(const exception_ptr& __x, const exception_ptr& __y) noexcept
        { return !(__x == __y);}

      friend exception_ptr current_exception() noexcept;
      friend void rethrow_exception(exception_ptr);
    };

  template<class _Ep>
  exception_ptr
  make_exception_ptr(_Ep __e) noexcept
    {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      try
        {
          throw __e;
        }
      catch (...)
        {
          return current_exception();
        }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
    }


// nested_exception

  class nested_exception
    {
      exception_ptr __ptr_;
    public:
      nested_exception() noexcept;
//     nested_exception(const nested_exception&) noexcept = default;
//     nested_exception& operator=(const nested_exception&) noexcept = default;
      virtual ~nested_exception() noexcept;

// access functions
      _LIBCPP_NORETURN void rethrow_nested() const;
      __attribute__((always_inline)) exception_ptr nested_ptr() const noexcept
        { return __ptr_;}
    };

  template <class _Tp>
  struct __nested
  : public _Tp,
public nested_exception
    {
      __attribute__((always_inline)) explicit __nested(const _Tp& __t) : _Tp(__t)
        {}
    };

  template <class _Tp>
  _LIBCPP_NORETURN
  void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
  throw_with_nested(_Tp&& __t, typename enable_if<
      is_class<typename remove_reference<_Tp>::type>::value &&
      !is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
      >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
  throw_with_nested (_Tp& __t, typename enable_if<
      is_class<_Tp>::value && !is_base_of<nested_exception, _Tp>::value
      >::type* = 0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      throw __nested<typename remove_reference<_Tp>::type>(_VSTD::forward<_Tp>(__t));
#endif
    }

  template <class _Tp>
  _LIBCPP_NORETURN
  void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
  throw_with_nested(_Tp&& __t, typename enable_if<
      !is_class<typename remove_reference<_Tp>::type>::value ||
      is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
      >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
  throw_with_nested (_Tp& __t, typename enable_if<
      !is_class<_Tp>::value || is_base_of<nested_exception, _Tp>::value
      >::type* = 0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
    {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      throw os::std::forward<_Tp>(__t);
#endif
    }

  template <class _Ep>
  inline __attribute__((always_inline))
  void
  rethrow_if_nested(const _Ep& __e, typename enable_if<
      is_polymorphic<_Ep>::value
      >::type* = 0)
    {
      const nested_exception* __nep = dynamic_cast<const nested_exception*>(&__e);
      if (__nep)
      __nep->rethrow_nested();
    }

  template <class _Ep>
  inline __attribute__((always_inline))
  void
  rethrow_if_nested(const _Ep&, typename enable_if<
      !is_polymorphic<_Ep>::value
      >::type* = 0)
    {
    }
#endif

}
 // namespace std
}// namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H
