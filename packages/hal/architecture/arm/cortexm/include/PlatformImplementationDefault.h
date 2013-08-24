//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Default declarations for the Cortex-M platform implementation.

// WARNING: This file is copied to the build folder, be sure you
// edit the original and not the copy!

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

// As default, the base definitions are enough, if you need more
// just derive your own class from PlatformBase and add the
// specifics (see PlatformImplementationSample.h).

namespace hal
{
  namespace platform
  {
    // ------------------------------------------------------------------------

#if !defined(__DOXYGEN__)

    using PlatformImplementation = hal::cortexm::PlatformBase;

#endif // !defined(__DOXYGEN__)
  // --------------------------------------------------------------------------
  }// namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
