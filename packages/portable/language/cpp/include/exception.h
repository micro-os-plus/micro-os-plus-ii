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
#include "portable/language/cpp/include/cstddef.h"
#include "portable/language/cpp/include/type_traits.h"

namespace os
{
  namespace std
  {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

    // 18.8.1 Class exception

    /// \headerfile exception.h "portable/language/cpp/include/exception.h"
    /// \ingroup std_exception
    /// \nosubgrouping
    ///
    /// \brief Exception base class.
    ///
    /// \details
    /// The class exception defines the base class for the types of
    /// objects thrown as exceptions by C++ standard library components,
    /// and certain expressions, to report errors detected during program
    /// execution.
    ///
    /// Each standard library class T that derives from class exception
    /// shall have a publicly accessible copy constructor and a publicly
    /// accessible copy assignment operator that do not exit with an
    /// exception. These member functions shall meet the following
    /// postcondition: If two objects lhs and rhs both have dynamic
    /// type T and lhs is a copy of rhs, then strcmp(lhs.what(), rhs.what())
    /// shall equal 0.
    class exception
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor
      exception(void) noexcept;

      /// \brief Copy constructor
      ///
      /// \details
      /// If *this and rhs both have dynamic type exception then
      /// strcmp(what(), rhs.what()) shall equal 0.
      exception(const exception&) noexcept = default;

      /// \brief Copy assignment
      ///
      /// \details
      /// If *this and rhs both have dynamic type exception then
      /// strcmp(what(), rhs.what()) shall equal 0.
      exception&
      operator=(const exception&) noexcept = default;

      /// \brief Destructor
      virtual
      ~exception() noexcept;

      /// @} end of name Constructors/destructor

      /// \name Public method functions
      /// @{

      /// \brief Identify exception
      ///
      /// \par Parameters
      ///     None.
      /// \return  An implementation-defined null-terminated byte string.
      virtual const char*
      what(void) const noexcept;

      /// @} end of name Public method functions
    };

    // ------------------------------------------------------------------------

    /// \details
    /// Construct an object of class exception.
    inline
    __attribute__((always_inline))
    exception::exception(void) noexcept
    {
    }

    // ========================================================================

    // 18.8.2 Class bad_exception

    /// \headerfile exception.h "portable/language/cpp/include/exception.h"
    /// \ingroup std_exception
    /// \nosubgrouping
    ///
    /// \brief Bad exception class.
    ///
    /// \details
    /// The class bad_exception defines the type of objects thrown by
    /// std::unexpected() as
    /// described in (15.5.2).
    class bad_exception : public exception
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor
      bad_exception() noexcept;

      /// \brief Copy constructor
      ///
      /// \details
      /// Copy an object of class bad_exception.
      bad_exception(const bad_exception&) noexcept = default;

      /// \brief Copy constructor
      ///
      /// \details
      /// Copy an object of class bad_exception.
      bad_exception&
      operator=(const bad_exception&) noexcept = default;

      /// \brief Destructor
      virtual
      ~bad_exception() noexcept;

      /// @} end of name Constructors/destructor

      /// \name Public method functions
      /// @{

      /// \brief Identify exception
      ///
      /// \par Parameters
      ///     None.
      /// \return  An implementation-defined null-terminated byte string.
      virtual const char*
      what() const noexcept;

      /// @} end of name Public method functions

    };

    // ------------------------------------------------------------------------

    /// \details
    /// Construct an object of class bad_exception.
    inline
    __attribute__((always_inline))
    bad_exception::bad_exception(void) noexcept
    {
    }

    // ========================================================================

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

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

    bool
    uncaught_exception() noexcept;

    class exception_ptr;

    exception_ptr
    current_exception() noexcept;

    void
    __attribute__((noreturn))
    rethrow_exception(exception_ptr);

    // ========================================================================

    class exception_ptr
    {
      void* __ptr_;

    public:
      exception_ptr() noexcept;

      exception_ptr(nullptr_t) noexcept;

      exception_ptr(const exception_ptr&) noexcept;

      exception_ptr&
      operator=(const exception_ptr&) noexcept;

      ~exception_ptr() noexcept;

      explicit
      __attribute__((always_inline))
      operator bool() const noexcept
      {
        return __ptr_ != nullptr;
      }

      friend __attribute__((always_inline))
      bool
      operator==(const exception_ptr& __x, const exception_ptr& __y) noexcept
      {
        return __x.__ptr_ == __y.__ptr_;
      }

      friend __attribute__((always_inline))
      bool
      operator!=(const exception_ptr& __x, const exception_ptr& __y) noexcept
      {
        return !(__x == __y);
      }

      friend exception_ptr
      current_exception() noexcept;
      friend void
      rethrow_exception(exception_ptr);
    };

    inline
    __attribute__((always_inline))
    exception_ptr::exception_ptr()
noexcept        : __ptr_()
          {
          }

    inline
    __attribute__((always_inline))
    exception_ptr::exception_ptr(nullptr_t)
noexcept        : __ptr_()
          {}

        // ========================================================================

    template<class _Ep>
      exception_ptr
      make_exception_ptr(_Ep __e) noexcept
      {
        try
          {
            throw __e;
          }
        catch (...)
          {
            return current_exception();
          }
      }

    // ========================================================================

    // nested_exception
    class nested_exception
    {
      exception_ptr __ptr_;
    public:
      nested_exception() noexcept;

      nested_exception(const nested_exception&) noexcept = default;

      nested_exception&
      operator=(const nested_exception&) noexcept = default;

      virtual
      ~nested_exception() noexcept;

      // access functions
      void
      __attribute__((noreturn))
      rethrow_nested() const;

      exception_ptr
      __attribute__((always_inline))
      nested_ptr() const noexcept
      {
        return __ptr_;
      }
    };

    // ========================================================================

    template<class _Tp>
      struct __nested : public _Tp, public nested_exception
      {
        __attribute__((always_inline)) explicit
        __nested(const _Tp& __t)
            : _Tp(__t)
        {
        }
      };

    // ========================================================================

    template<class _Tp>
      __attribute__((noreturn))
      void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      throw_with_nested(_Tp&& __t, typename enable_if<
          is_class<typename remove_reference<_Tp>::type>::value &&
          !is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
          >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      throw_with_nested(_Tp& __t,
          typename enable_if<
              is_class<_Tp>::value && !is_base_of<nested_exception, _Tp>::value>::type* =
              0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      {
        throw __nested<typename remove_reference<_Tp>::type>(_VSTD::forward<_Tp>(__t));
      }

    template<class _Tp>
      __attribute__((noreturn))
      void
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
      throw_with_nested(_Tp&& __t, typename enable_if<
          !is_class<typename remove_reference<_Tp>::type>::value ||
          is_base_of<nested_exception, typename remove_reference<_Tp>::type>::value
          >::type* = 0)
#else  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      throw_with_nested(_Tp& __t,
          typename enable_if<
              !is_class<_Tp>::value || is_base_of<nested_exception, _Tp>::value>::type* =
              0)
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES
      {
        throw os::std::forward<_Tp>(__t);
      }

    // ========================================================================

    template<class _Ep>
      inline void
      __attribute__((always_inline))
      rethrow_if_nested(const _Ep& __e,
          typename enable_if<is_polymorphic<_Ep>::value>::type* = 0)
      {
        const nested_exception* __nep =
            dynamic_cast<const nested_exception*>(&__e);
        if (__nep)
          __nep->rethrow_nested();
      }

    template<class _Ep>
      inline void
      __attribute__((always_inline))
      rethrow_if_nested(const _Ep&,
          typename enable_if<!is_polymorphic<_Ep>::value>::type* = 0)
      {
      }

  // ========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
  }
// namespace std
}// namespace os

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_EXCEPTION_H
