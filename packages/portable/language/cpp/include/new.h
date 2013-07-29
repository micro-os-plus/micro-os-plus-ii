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

#if 0
    // not in C++ spec
    void
    __throw_bad_alloc() __attribute__((noreturn));
#endif

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

}
 // namespace std
}// namespace os

// skip when already included in POSIX environments
#if !defined(_NEW) || defined(__DOXYGEN__)

/// \addtogroup std_support
/// @{

/// \brief Single object allocation.
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)
void*
operator new(os::std::size_t size) throw(os::std::bad_alloc);
#else
void*
operator new(os::std::size_t size) noexcept;
#endif

/// \brief Single object allocation without exceptions.
///
/// \param [in] size        The size to allocate, in bytes.
void*
__attribute__((malloc))
operator new(os::std::size_t size, const os::std::nothrow_t&) noexcept;

/// \brief Single object deallocation.
void
operator delete(void* ptr) noexcept;

/// \brief Single object deallocation without exceptions.
void
operator delete(void* ptr, const os::std::nothrow_t&) noexcept;

/// \brief Array allocation.
///
/// \param [in] size        The size to allocate, in bytes.
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)
void*
operator new[](os::std::size_t size) throw(os::std::bad_alloc);
#else
void*
operator new[](os::std::size_t size) noexcept;
#endif

/// \brief Array allocation without exceptions.
///
/// \param [in] size        The size to allocate, in bytes.
void*
__attribute__((malloc))
operator new[](os::std::size_t size, const os::std::nothrow_t&) noexcept;

/// \brief Array deallocation.
void
operator delete[](void* ptr) noexcept;

/// \brief Array deallocation without exceptions.
void
operator delete[](void* ptr, const os::std::nothrow_t&) noexcept;

/// \brief Single object placement.
///
/// \param [in] size        The size to allocate, in bytes.
/// \param [in] ptr         Pointer to the placement location.
///
/// \details
/// Intentionally performs no other action.
///
/// \note A C++ program may not define functions that displace the
/// versions in the Standard C++ library (17.6.4)
inline void*
__attribute__ ((__always_inline__))
operator new(os::std::size_t size __attribute__((unused)), void* ptr) noexcept
{
return ptr;
}

/// \brief Array placement.
///
/// \param [in] size        The size to allocate, in bytes.
/// \param [in] ptr         Pointer to the placement location.
///
/// \details
/// Intentionally performs no other action.
///
/// \note A C++ program may not define functions that displace the
/// versions in the Standard C++ library (17.6.4)
inline void*
__attribute__ ((__always_inline__))
operator new[](os::std::size_t size __attribute__((unused)), void* ptr) noexcept
{
return ptr;
}

/// \brief Single object placement deallocation.
///
/// \details
/// Intentionally performs no other action.
///
/// \note A C++ program may not define functions that displace the
/// versions in the Standard C++ library (17.6.4)
inline void
__attribute__ ((__always_inline__))
operator delete(void*, void*) noexcept
{
}

/// \brief Array placement deallocation.
///
/// \details
/// Intentionally performs no other action.
///
/// \note A C++ program may not define functions that displace the
/// versions in the Standard C++ library (17.6.4)
inline void
__attribute__ ((__always_inline__))
operator delete[](void*, void*) noexcept
{
}

/// @} end of addtogroup std_support

#endif // !defined(_NEW)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
