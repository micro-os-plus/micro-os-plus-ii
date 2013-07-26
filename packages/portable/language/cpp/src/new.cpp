//===--------------------------- new.cpp ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <stdlib.h>

#include "portable/language/cpp/include/new.h"
#include "portable/language/cpp/include/malloc.h"

#ifndef __has_include
#define __has_include(inc) 0
#endif

#if 0
#if __APPLE__
    #include <cxxabi.h>

    #ifndef _LIBCPPABI_VERSION
        // On Darwin, there are two STL shared libraries and a lower level ABI
        // shared libray.  The global holding the current new handler is
        // in the ABI library and named __cxa_new_handler.
        #define __new_handler __cxxabiapple::__cxa_new_handler
    #endif
#else  // __APPLE__
    #if defined(LIBCXXRT) || __has_include(<cxxabi.h>)
        #include <cxxabi.h>
    #endif  // __has_include(<cxxabi.h>)
    #ifndef _LIBCPPABI_VERSION
        static std::new_handler __new_handler;
    #endif  // _LIBCPPABI_VERSION
#endif
#endif

// Implement all new and delete operators as weak definitions
// in this shared library, so that they can be overriden by programs
// that define non-weak copies of the functions.

//__attribute__((__weak__, __visibility__("default")))
void *
operator new(os::std::size_t size)
#if 0 //!__has_feature(cxx_noexcept)
    throw(os::std::bad_alloc)
#endif
{
    if (size == 0)
        size = 1;
    void* p;
    while ((p = os::malloc(size)) == 0)
    {
#if 0
        // If malloc fails and there is a new_handler,
        // call it to try free up memory.
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else
#endif
#if 0 // ndef _LIBCPP_NO_EXCEPTIONS
            throw os::std::bad_alloc();
#else
            break;
#endif
    }
    return p;
}

//__attribute__((__weak__, __visibility__("default")))
void*
operator new(size_t size, const os::std::nothrow_t&) _NOEXCEPT
{
    void* p = 0;
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new(size);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}

//__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size)
#if !__has_feature(cxx_noexcept)
    throw(os::std::bad_alloc)
#endif
{
    return ::operator new(size);
}

//__attribute__((__weak__, __visibility__("default")))
void*
operator new[](size_t size, const os::std::nothrow_t&) _NOEXCEPT
{
    void* p = 0;
#ifndef _LIBCPP_NO_EXCEPTIONS
    try
    {
#endif  // _LIBCPP_NO_EXCEPTIONS
        p = ::operator new[](size);
#ifndef _LIBCPP_NO_EXCEPTIONS
    }
    catch (...)
    {
    }
#endif  // _LIBCPP_NO_EXCEPTIONS
    return p;
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr) _NOEXCEPT
{
    if (ptr)
        os::free(ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr, const os::std::nothrow_t&) _NOEXCEPT
{
    ::operator delete(ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr) _NOEXCEPT
{
    ::operator delete (ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete[] (void* ptr, const os::std::nothrow_t&) _NOEXCEPT
{
    ::operator delete[](ptr);
}

namespace os
{
namespace std
{

const nothrow_t nothrow = {};

#ifndef _LIBCPPABI_VERSION

#if 0

new_handler
set_new_handler(new_handler handler) _NOEXCEPT
{
    return __sync_lock_test_and_set(&__new_handler, handler);
}

new_handler
get_new_handler() _NOEXCEPT
{
    return __sync_fetch_and_add(&__new_handler, (new_handler)0);
}

#endif

#ifndef LIBCXXRT

bad_alloc::bad_alloc() _NOEXCEPT
{
}

bad_alloc::~bad_alloc() _NOEXCEPT
{
}

const char*
bad_alloc::what() const _NOEXCEPT
{
    return "std::bad_alloc";
}

#endif //LIBCXXRT

bad_array_new_length::bad_array_new_length() _NOEXCEPT
{
}

bad_array_new_length::~bad_array_new_length() _NOEXCEPT
{
}

const char*
bad_array_new_length::what() const _NOEXCEPT
{
    return "bad_array_new_length";
}


void
__throw_bad_alloc()
{
#if 0
#ifndef _LIBCPP_NO_EXCEPTIONS
    throw bad_alloc();
#endif
#else
    for (;;)
      ;
#endif
}

}  // std
}

#endif
