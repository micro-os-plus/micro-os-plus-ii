//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief ST STM32F4DISCOVERY declarations of the board class.

#ifndef HAL_PLATFORM_ST_STM32F4DISCOVERY_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_ST_STM32F4DISCOVERY_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_STM_STM32F4DISCOVERY) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace stm32f4discovery
  {
    // ======================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/stm/stm32f4discovery/include/PlatformImplementation.h"
    /// \ingroup stm32f4discovery
    /// \nosubgrouping
    ///
    /// \brief Olimex STM32F-E407 board implementation class.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

      // TODO: add more platform members, like initialiseSystem()
    };

  // ========================================================================

  }// namespace stm32f4discovery

  namespace platform
  {

    // ------------------------------------------------------------------------

    typedef stm32f4discovery::PlatformImplementation PlatformImplementation;

  // ------------------------------------------------------------------------

  }
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_STM_STM32F4DISCOVERY)
#endif // HAL_PLATFORM_ST_STM32F4DISCOVERY_PLATFORMIMPLEMENTATION_H_
