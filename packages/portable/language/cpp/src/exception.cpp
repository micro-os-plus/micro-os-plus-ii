//===------------------------ exception.cpp -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/exception.h"

//#include <stdlib.h>


#ifndef __has_include
#define __has_include(inc) 0
#endif

#if 0 //__APPLE__
  #include <cxxabi.h>

  using namespace __cxxabiv1;
  #define HAVE_DEPENDENT_EH_ABI 1
  #ifndef _LIBCPPABI_VERSION
    using namespace __cxxabiapple;
    // On Darwin, there are two STL shared libraries and a lower level ABI
    // shared libray.  The globals holding the current terminate handler and
    // current unexpected handler are in the ABI library.
#if 0
    #define __terminate_handler  __cxxabiapple::__cxa_terminate_handler
    #define __unexpected_handler __cxxabiapple::__cxa_unexpected_handler
#endif

  #endif  // _LIBCPPABI_VERSION
#elif defined(LIBCXXRT) || __has_include(<cxxabi.h>)
  #include <cxxabi.h>
  using namespace __cxxabiv1;
  #if defined(LIBCXXRT) || defined(_LIBCPPABI_VERSION)
    #define HAVE_DEPENDENT_EH_ABI 1
  #endif
#elif 0 //!defined(__GLIBCXX__) // __has_include(<cxxabi.h>)
  static std::terminate_handler  __terminate_handler;
  static std::unexpected_handler __unexpected_handler;
#else

#define HAVE_DEPENDENT_EH_ABI 0

#endif // __has_include(<cxxabi.h>)

  namespace os
  {
namespace std
{

#if !defined(LIBCXXRT) && !defined(_LIBCPPABI_VERSION) && !defined(__GLIBCXX__)

#if 0
// libcxxrt provides implementations of these functions itself.
unexpected_handler
set_unexpected(unexpected_handler func) _NOEXCEPT
{
    return __sync_lock_test_and_set(&__unexpected_handler, func);
}

unexpected_handler
get_unexpected() _NOEXCEPT
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
set_terminate(terminate_handler func) _NOEXCEPT
{
    return __sync_lock_test_and_set(&__terminate_handler, func);
}

terminate_handler
get_terminate() _NOEXCEPT
{
    return __sync_fetch_and_add(&__terminate_handler, (terminate_handler)0);
}
#endif

_LIBCPP_NORETURN
void
terminate() _NOEXCEPT
{
#if 0
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        (*get_terminate())();
        // handler should not return
        ::abort ();
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
        // handler should not throw exception
        ::abort ();
    }
#endif  // _LIBCPP_NO_EXCEPTIONS

#else

    // TODO: reset
    for(;;)
      ;

#endif
}

#endif // !defined(LIBCXXRT) && !defined(_LIBCPPABI_VERSION)

//#if !defined(LIBCXXRT) && !defined(__GLIBCXX__)

#if 0


bool uncaught_exception() _NOEXCEPT
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


exception::~exception() _NOEXCEPT
{
}

const char* exception::what() const _NOEXCEPT
{
  return "os::std::exception";
}

// --------

//#endif //LIBCXXRT
#if !defined(_LIBCPPABI_VERSION) && !defined(__GLIBCXX__)

bad_exception::~bad_exception() _NOEXCEPT
{
}

const char* bad_exception::what() const _NOEXCEPT
{
  return "os::std::bad_exception";
}

#endif

#if 0
exception_ptr::~exception_ptr() _NOEXCEPT
{
#if 0 //HAVE_DEPENDENT_EH_ABI
    __cxa_decrement_exception_refcount(__ptr_);
#else
//    #warning exception_ptr not yet implemented
    ::abort();
#endif  // __APPLE__
}

exception_ptr::exception_ptr(const exception_ptr& other) _NOEXCEPT
    : __ptr_(other.__ptr_)
{
#if 0 //HAVE_DEPENDENT_EH_ABI
    __cxa_increment_exception_refcount(__ptr_);
#else
//    #warning exception_ptr not yet implemented
    ::abort();
#endif  // __APPLE__
}

exception_ptr& exception_ptr::operator=(const exception_ptr& other) _NOEXCEPT
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
nested_exception::nested_exception() _NOEXCEPT
    : __ptr_(current_exception())
{
}

nested_exception::~nested_exception() _NOEXCEPT
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
exception_ptr current_exception() _NOEXCEPT
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

} // std
}
