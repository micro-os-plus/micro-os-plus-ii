//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(__APPLE__)
// mainly for ucontext.h, but seems it is needed in other system
// headers, since without it the sleep test crashes
#define _XOPEN_SOURCE 600L
#endif

// Platform headers
#include <stdint.h>
#include <signal.h>

namespace hal
{
  namespace posix
  {
  // TBD
  }// namespace posix
} // namespace hal

// Portable definitions.
namespace hal
{
  namespace arch
  {
    /// \addtogroup posix
    /// @{

    /// \name Types and constants
    /// @{

#if defined(__x86_64__) || defined(__DOXYGEN__)
    /// \brief Type definition of a stack word unit.
    typedef uint64_t stackElement_t;

    /// \brief A magic value used to fill the stack.
    constexpr stackElement_t STACK_FILL = 0x55AA5A5AA5A5AA55;
#else
    /// \brief Type definition of a stack word unit.
    typedef uint32_t stackElement_t;

    constexpr stackElement_t STACK_FILL = 0x55AAAA55;
#endif

    /// \brief Type definition to represent a stack size.
    typedef uint32_t stackSize_t;

    /// \brief The minimum stack size, as defined in the POSIX headers.
    constexpr stackSize_t MIN_STACK_SIZE = SIGSTKSZ;

  /// @} end of name Types and constants

  /// @} end of addtogroup posix

  }// namespace arch
} // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_
