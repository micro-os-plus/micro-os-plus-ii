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

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)

    /// \class bad_alloc malloc.h "portable/language/cpp/include/new.h"
    /// \ingroup std_dynmem
    /// \nosubgrouping
    ///
    /// \brief bad_alloc exception
    ///
    /// \details
    /// The class bad_alloc defines the type of objects thrown as
    /// exceptions by the implementation to report a failure to
    /// allocate storage.
    class bad_alloc : public exception
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        bad_alloc(void) noexcept;

        /// \brief Destructor.
        virtual
        ~bad_alloc() noexcept;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        virtual const char*
        what(void) const noexcept;

        /// @} end of Public member functions

      };

    /// \class bad_array_new_length malloc.h "portable/language/cpp/include/new.h"
    /// \ingroup std_dynmem
    /// \nosubgrouping
    ///
    /// \brief bad_array_new_length exception
    ///
    /// \details
    /// The class bad_array_new_length defines the type of objects
    /// thrown as exceptions by the implementation to report an
    /// attempt to allocate an array of size less than zero or greater
    /// than an implementation-defined limit (5.3.4).
    class bad_array_new_length : public bad_alloc
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        bad_array_new_length(void) noexcept;

        /// \brief Destructor.
        virtual
        ~bad_array_new_length() noexcept;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        virtual const char*
        what(void) const noexcept;

        /// @} end of Public member functions

      };

#endif

#if 0
    // not in C++ spec
    void
    __throw_bad_alloc() __attribute__((noreturn));
#endif

    /// \addtogroup std_dynmem
    /// @{

    struct nothrow_t
    {
    };

    extern const nothrow_t nothrow;

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS) || defined(__DOXYGEN__)

  /// \brief Pointer to new handler function.
  ///
  /// \details
  /// The type of a handler function to be called by operator new()
  /// or operator new[]() (18.6.1) when they cannot satisfy a request
  /// for additional storage.
  ///
  /// The new_handler shall perform one of the following:
  /// - make more storage available for allocation and then return;
  /// - throw an exception of type bad_alloc or a class derived from bad_alloc;
  /// - terminate execution of the program without returning to the caller;
  typedef void
  (*new_handler)(void);

  /// \brief Set handler for new allocations.
  ///
  /// \param [in] new_p         The new handler.
  /// \return                   The previous handler.
  ///
  /// \details
  /// Establishes the function designated by new_p as the current new_handler.
  /// The initial handler is a null pointer.
  new_handler
  set_new_handler(new_handler new_p) noexcept;

  /// \brief Get handler for new allocations.
  /// \par Parameters
  ///    None.
  /// \return The current pointer to the handler.
  new_handler
  get_new_handler(void) noexcept;

#endif

  /// @} end of addtogroup std_dynmem

}
  // namespace std
} // namespace os

// skip when already included in POSIX environments
#if !defined(_NEW) || defined(__DOXYGEN__)

/// \addtogroup std_dynmem
/// @{

/// \brief Single object allocation.
#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS) || defined(__DOXYGEN__)
void*
operator new(os::std::size_t size); //throw(os::std::bad_alloc);
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
operator new[](os::std::size_t size); //throw(os::std::bad_alloc);
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
__attribute__((always_inline))
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
__attribute__((always_inline))
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
__attribute__((always_inline))
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
__attribute__((always_inline))
operator delete[](void*, void*) noexcept
{
}

/// @} end of addtogroup std_dynmem

#endif // !defined(_NEW)
#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_NEW_H
