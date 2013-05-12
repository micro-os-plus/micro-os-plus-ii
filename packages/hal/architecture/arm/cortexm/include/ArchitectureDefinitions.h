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

#include <stdint.h>

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

    typedef uint32_t bitNumber_t; // 0-31
    typedef uint32_t portNumber_t; // 0 = port 'A'
    typedef uint32_t index_t; // index in an array of registers

  // --------------------------------------------------------------------------

  }// namespace cortexm
} // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREDEFINITIONS_H_
