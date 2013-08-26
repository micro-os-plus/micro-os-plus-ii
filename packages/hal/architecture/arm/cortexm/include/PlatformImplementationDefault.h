//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Default declarations for the Cortex-M platform implementation.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

// As default, the base definitions are enough, if you need more
// just derive your own class from PlatformBase and add the
// specifics (see PlatformImplementationSample.h).
#if !defined(__DOXYGEN__)
namespace hal
{
  namespace platform
  {
     using PlatformImplementation = hal::cortexm::PlatformBase;
  }// namespace platform
} // namespace hal
#endif // !defined(__DOXYGEN__)

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
