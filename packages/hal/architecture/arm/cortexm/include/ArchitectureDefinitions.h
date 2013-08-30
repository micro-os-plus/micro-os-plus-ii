//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREDEFINITIONS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREDEFINITIONS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/cstdint.h"

// ----------------------------------------------------------------------------

// The highest interrupt priority from which µOS++ API functions can be called.
// Interrupts from 0x7F to 0x00 cannot call system functions.
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (0x80)

// The lowest possible priority, used for the PendSV and SysTick
#define configKERNEL_INTERRUPT_PRIORITY (0xFF)

// ----------------------------------------------------------------------------

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    // Register types
    typedef uint32_t volatile regReadWrite_t;
    typedef uint32_t const volatile regReadOnly_t;
    typedef uint32_t volatile regWriteOnly_t;
    typedef uint32_t const volatile regNotAllocated_t;

    typedef uint32_t address_t;
    typedef uint32_t reg32_t;
    typedef uint16_t reg16_t;
    typedef uint8_t reg8_t;

    typedef uint32_t bitNumber_t; // 0-31
    typedef uint32_t portNumber_t; // 0 = port 'A'
    typedef uint32_t index_t; // index in an array of registers

    /// \brief Type definition of an interrupt number
    /// (a signed integer, from -16 to +495).
    typedef int16_t interruptNumber_t;

    typedef uint8_t interruptPriority_t;

    typedef uint32_t basepri_t;

  // --------------------------------------------------------------------------

  }// namespace cortexm
} // namespace hal

// Portable definitions.
namespace hal
{
  namespace arch
  {
    /// \addtogroup arm_cm
    /// @{

    /// \name Types and constants
    /// @{

    /// \brief Type definition of a stack word unit.
    typedef uint32_t stackElement_t;

    /// \brief Type definition to represent a stack size.
    typedef uint32_t stackSize_t;

    /// \brief A magic value used to fill the stack.
    static constexpr stackElement_t STACK_FILL = 0x55AAAA55;

    /// \brief The minimum stack size.
    constexpr stackSize_t MIN_STACK_SIZE = 1024;

  /// @} end of name Types and constants

  /// @} end of addtogroup posix

  }// namespace arch
}    // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREDEFINITIONS_H_
