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
/// \brief Exceptions definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/abort.h"


namespace os
{
  namespace std
  {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS)

// libcxxrt provides implementations of these functions itself.
    unexpected_handler
    set_unexpected(unexpected_handler func) noexcept
      {
        return __sync_lock_test_and_set(&__unexpected_handler, func);
      }

    unexpected_handler
    get_unexpected() noexcept
      {
        return __sync_fetch_and_add(&__unexpected_handler, (unexpected_handler)0);
      }

    _LIBCPP_NORETURN
    void
    unexpected()
      {
        (*get_unexpected())();
        // unexpected handler should not return
        terminate();
      }

    terminate_handler
    set_terminate(terminate_handler func) noexcept
      {
        return __sync_lock_test_and_set(&__terminate_handler, func);
      }

    terminate_handler
    get_terminate() noexcept
      {
        return __sync_fetch_and_add(&__terminate_handler, (terminate_handler)0);
      }
#endif

    void
    __attribute__((noreturn))
    terminate() noexcept
    {
#if 0
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      try
        {
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
          (*get_terminate())();
          // handler should not return
          ::abort ();
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
        }
      catch (...)
        {
          // handler should not throw exception
          ::abort ();
        }
#endif  // OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS
#else

      abort();

#endif
    }


#if 0

  bool uncaught_exception() noexcept
    {
#if __APPLE__ || defined(_LIBCPPABI_VERSION)
      // on Darwin, there is a helper function so __cxa_get_globals is private
      return __cxa_uncaught_exception();
#else  // __APPLE__
#warning uncaught_exception not yet implemented
      ::abort();
#endif  // __APPLE__
    }

#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

  exception::~exception() noexcept
    {
    }

  const char* exception::what() const noexcept
    {
      return "os::std::exception";
    }

#endif

// --------

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

  bad_exception::~bad_exception() noexcept
    {
    }

  const char* bad_exception::what() const noexcept
    {
      return "os::std::bad_exception";
    }

#endif

#if 0
  exception_ptr::~exception_ptr() noexcept
    {
#if 0 //HAVE_DEPENDENT_EH_ABI
      __cxa_decrement_exception_refcount(__ptr_);
#else
//    #warning exception_ptr not yet implemented
      ::abort();
#endif  // __APPLE__
    }

  exception_ptr::exception_ptr(const exception_ptr& other) noexcept
  : __ptr_(other.__ptr_)
    {
#if 0 //HAVE_DEPENDENT_EH_ABI
      __cxa_increment_exception_refcount(__ptr_);
#else
//    #warning exception_ptr not yet implemented
      ::abort();
#endif  // __APPLE__
    }

  exception_ptr& exception_ptr::operator=(const exception_ptr& other) noexcept
    {
#if 0 //HAVE_DEPENDENT_EH_ABI
      if (__ptr_ != other.__ptr_)
        {
          __cxa_increment_exception_refcount(other.__ptr_);
          __cxa_decrement_exception_refcount(__ptr_);
          __ptr_ = other.__ptr_;
        }
      return *this;
#else  // __APPLE__
//    #warning exception_ptr not yet implemented
      ::abort();
#endif  // __APPLE__
    }

#endif

#if 0
  nested_exception::nested_exception() noexcept
  : __ptr_(current_exception())
    {
    }

  nested_exception::~nested_exception() noexcept
    {
    }

  _LIBCPP_NORETURN
  void
  nested_exception::rethrow_nested() const
    {
      if (__ptr_ == nullptr)
      terminate();
      rethrow_exception(__ptr_);
    }

#endif

#if 0
  exception_ptr current_exception() noexcept
    {
#if HAVE_DEPENDENT_EH_ABI
      // be nicer if there was a constructor that took a ptr, then
      // this whole function would be just:
      //    return exception_ptr(__cxa_current_primary_exception());
      exception_ptr ptr;
      ptr.__ptr_ = __cxa_current_primary_exception();
      return ptr;
#else  // __APPLE__
#warning exception_ptr not yet implemented
      ::abort();
#endif  // __APPLE__
    }

  _LIBCPP_NORETURN
  void rethrow_exception(exception_ptr p)
    {
#if HAVE_DEPENDENT_EH_ABI
      __cxa_rethrow_primary_exception(p.__ptr_);
      // if p.__ptr_ is NULL, above returns so we terminate
      terminate();
#else  // __APPLE__
#warning exception_ptr not yet implemented
      ::abort();
#endif  // __APPLE__
    }

#endif

}
 // namespace std
}// namespace os
