// -*- C++ -*-
//===----------------------------- new ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H

#include "portable/language/cpp/include/internal/__config.h"
#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os {
namespace std  // purposefully not using versioning namespace
{

  class _LIBCPP_EXCEPTION_ABI exceptionnn
  {
  public:
      _LIBCPP_INLINE_VISIBILITY exceptionnn() _NOEXCEPT {}
      virtual ~exceptionnn() _NOEXCEPT;
      virtual const char* what() const _NOEXCEPT;
  };

class _LIBCPP_EXCEPTION_ABI bad_alloc
    : public exception
{
public:
    bad_alloc() _NOEXCEPT;
    virtual ~bad_alloc() _NOEXCEPT;
    virtual const char* what() const _NOEXCEPT;
};

class _LIBCPP_EXCEPTION_ABI bad_array_new_length
    : public bad_alloc
{
public:
    bad_array_new_length() _NOEXCEPT;
    virtual ~bad_array_new_length() _NOEXCEPT;
    virtual const char* what() const _NOEXCEPT;
};

void __throw_bad_alloc() __attribute__((noreturn));  // not in C++ spec

struct _LIBCPP_VISIBLE nothrow_t {};
extern _LIBCPP_VISIBLE const nothrow_t nothrow;
typedef void (*new_handler)();
_LIBCPP_VISIBLE new_handler set_new_handler(new_handler) _NOEXCEPT;
_LIBCPP_VISIBLE new_handler get_new_handler() _NOEXCEPT;

}  // std
#if defined(__MICRO_OS_PLUS_PLUS__)
}
#endif

#if !defined(_NEW)
_LIBCPP_VISIBLE void* operator new(os::std::size_t __sz)
#if !__has_feature(cxx_noexcept)
    throw(os::std::bad_alloc)
#endif
;
_LIBCPP_VISIBLE void* operator new(os::std::size_t __sz, const os::std::nothrow_t&) _NOEXCEPT _NOALIAS;
_LIBCPP_VISIBLE void  operator delete(void* __p) _NOEXCEPT;
_LIBCPP_VISIBLE void  operator delete(void* __p, const os::std::nothrow_t&) _NOEXCEPT;

_LIBCPP_VISIBLE void* operator new[](os::std::size_t __sz)
#if !__has_feature(cxx_noexcept)
    throw(os::std::bad_alloc)
#endif
;
_LIBCPP_VISIBLE void* operator new[](os::std::size_t __sz, const os::std::nothrow_t&) _NOEXCEPT _NOALIAS;
_LIBCPP_VISIBLE void  operator delete[](void* __p) _NOEXCEPT;
_LIBCPP_VISIBLE void  operator delete[](void* __p, const os::std::nothrow_t&) _NOEXCEPT;

_LIBCPP_INLINE_VISIBILITY inline void* operator new  (os::std::size_t, void* __p) _NOEXCEPT {return __p;}
_LIBCPP_INLINE_VISIBILITY inline void* operator new[](os::std::size_t, void* __p) _NOEXCEPT {return __p;}
_LIBCPP_INLINE_VISIBILITY inline void  operator delete  (void*, void*) _NOEXCEPT {}
_LIBCPP_INLINE_VISIBILITY inline void  operator delete[](void*, void*) _NOEXCEPT {}

#endif

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
