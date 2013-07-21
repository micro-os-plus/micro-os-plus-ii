//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M definitions.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

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
#if defined(__x86_64__)
    /// \brief Type definition of a stack word unit.
    typedef uint64_t stackElement_t;

    constexpr stackElement_t STACK_FILL = 0x55AA5A5AA5A5AA55;
#else
    /// \brief Type definition of a stack word unit.
    typedef uint32_t stackElement_t;

    constexpr stackElement_t STACK_FILL = 0x55AAAA55;
#endif

    typedef uint32_t stackSize_t;

    constexpr stackSize_t MIN_STACK_SIZE = SIGSTKSZ;

  //typedef sigset_t interruptStatus_t;

  }// namespace arch
} // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREDEFINITIONS_H_
