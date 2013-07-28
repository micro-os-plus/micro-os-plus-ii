//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

/// \file
/// \brief Global new/delete definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/exception.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

    class bad_alloc : public exception
    {
    public:
      bad_alloc() noexcept;

      virtual
      ~bad_alloc() noexcept;

      virtual const char*
      what() const noexcept;
    };

    class bad_array_new_length : public bad_alloc
    {
    public:
      bad_array_new_length() noexcept;

      virtual
      ~bad_array_new_length() noexcept;

      virtual const char*
      what() const noexcept;
    };

#endif

    // not in C++ spec
    void
    __throw_bad_alloc() __attribute__((noreturn));

    struct nothrow_t
    {
    };

    extern const nothrow_t nothrow;

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS)

    typedef void
    (*new_handler)();

    new_handler
    set_new_handler(new_handler) noexcept;

    new_handler
    get_new_handler() noexcept;

#endif

  }  // namespace std
} // namespace os

// skip when already included in POSIX environments
#if !defined(_NEW) || defined(__DOXYGEN__)

void*
operator new(os::std::size_t __sz)
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    throw(os::std::bad_alloc)
#endif
;//
void*
__attribute__((malloc))
operator new(os::std::size_t __sz, const os::std::nothrow_t&) noexcept;

void
operator delete(void* __p) noexcept;

void
operator delete(void* __p, const os::std::nothrow_t&) noexcept;

void*
operator new[](os::std::size_t __sz)
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    throw(os::std::bad_alloc)
#endif
;//
void*
__attribute__((malloc))
operator new[](os::std::size_t __sz, const os::std::nothrow_t&) noexcept;

void
operator delete[](void* __p) noexcept;

void
operator delete[](void* __p, const os::std::nothrow_t&) noexcept;

inline void*
__attribute__ ((__always_inline__))
operator new(os::std::size_t, void* __p) noexcept
{
  return __p;
}

inline void*
__attribute__ ((__always_inline__))
operator new[](os::std::size_t, void* __p) noexcept
{
  return __p;
}

inline void
__attribute__ ((__always_inline__))
operator delete(void*, void*) noexcept
{
}

inline void
__attribute__ ((__always_inline__))
operator delete[](void*, void*) noexcept
{
}

#endif // !defined(_NEW)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
