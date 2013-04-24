//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-E407 declarations of the board class.

#ifndef HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace stm32e407
  {
    // ======================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/olimex/stm32fe407/include/PlatformImplementation.h"
    /// \ingroup stm32fe407
    /// \nosubgrouping
    ///
    /// \brief Olimex STM32F-E407 board implementation class.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

      // TODO: add more platform members, like initialiseSystem()
    };

  // ========================================================================

  }// namespace stm32e407

  namespace platform
  {

    // ------------------------------------------------------------------------

    typedef stm32e407::PlatformImplementation PlatformImplementation;

  // ------------------------------------------------------------------------

  }
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407)
#endif // HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_
