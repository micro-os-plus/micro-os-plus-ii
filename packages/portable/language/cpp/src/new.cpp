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
/// \brief Global new/delete definitions.

#include "portable/core/include/ConfigDefines.h"


#include "portable/language/cpp/include/new.h"
#include "portable/language/cpp/include/malloc.h"

#include "portable/language/cpp/include/abort.h"

#include "portable/diagnostics/include/Trace.h"

void *
operator new(os::std::size_t size)
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    throw(os::std::bad_alloc)
#endif
{    //
    if (size == 0)
      {
        size = 1;
      }

    void* p;
    while ((p = os::std::malloc(size)) == 0)
      {
#if 0
// If malloc fails and there is a new_handler,
// call it to try free up memory.
//    std::new_handler nh = std::get_new_handler();
//    if (nh)
//    nh();
//    else
#endif
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    throw os::std::bad_alloc();
#else
    break;
#endif
  }
return p;
}

void*
operator new(os::std::size_t size, const os::std::nothrow_t&) noexcept
{
  void* p = 0;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
  try
    {
      p = ::operator new(size);
    }
  catch (...)
    {
    }
#else
  p = ::operator new(size);

#endif  // _LIBCPP_NO_EXCEPTIONS
  return p;
}

//__attribute__((__weak__, __visibility__("default")))
void*
operator new[](os::std::size_t size)
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
    throw(os::std::bad_alloc)
#endif
{    return ::operator new(size);
  }

//__attribute__((__weak__, __visibility__("default")))
void*
operator new[](os::std::size_t size, const os::std::nothrow_t&) noexcept
{
  void* p = 0;
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
  try
    {
      p = ::operator new[](size);
    }
  catch (...)
    {
    }
#else
  p = ::operator new[](size);
#endif  // _LIBCPP_NO_EXCEPTIONS
  return p;
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr) noexcept
{
  if (ptr)
    os::std::free(ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete(void* ptr, const os::std::nothrow_t&) noexcept
{
  ::operator delete(ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete[](void* ptr) noexcept
{
  ::operator delete(ptr);
}

//__attribute__((__weak__, __visibility__("default")))
void
operator delete[](void* ptr, const os::std::nothrow_t&) noexcept
{
  ::operator delete[](ptr);
}

namespace os
{
  namespace std
  {

    const nothrow_t nothrow =
      { };

#ifndef _LIBCPPABI_VERSION

#if 0

    new_handler
    set_new_handler(new_handler handler) noexcept
      {
        return __sync_lock_test_and_set(&__new_handler, handler);
      }

    new_handler
    get_new_handler() noexcept
      {
        return __sync_fetch_and_add(&__new_handler, (new_handler)0);
      }

#endif

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)

    bad_alloc::bad_alloc() noexcept
    {
    }

    bad_alloc::~bad_alloc() noexcept
    {
    }

    const char*
    bad_alloc::what() const noexcept
    {
      return "std::bad_alloc";
    }

    bad_array_new_length::bad_array_new_length() noexcept
    {
    }

    bad_array_new_length::~bad_array_new_length() noexcept
    {
    }

    const char*
    bad_array_new_length::what() const noexcept
    {
      return "bad_array_new_length";
    }

#endif

#if 0
    void
    __throw_bad_alloc()
    {
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS)
      throw bad_alloc();
#else

#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      os::std::abort();
#endif
    }
#endif

  }  // namespace std
} // namespace os

#endif
