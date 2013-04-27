//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-P107 declarations of the board class.

#ifndef HAL_PLATFORM_OLIMEX_STM32P107_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_OLIMEX_STM32P107_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32P107) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace stm32p107
  {
    // ========================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/olimex/stm32p107/include/PlatformImplementation.h"
    /// \ingroup stm32fp107
    /// \nosubgrouping
    ///
    /// \brief Olimex STM32F-P107 board implementation class.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

      // TODO: add more platform members, like initialiseSystem()
    };

  // ==========================================================================

  }// namespace stm32p107

  namespace platform
  {
    // ------------------------------------------------------------------------

    typedef stm32p107::PlatformImplementation PlatformImplementation;

  // --------------------------------------------------------------------------
  }// namespace platform

} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32P107)
#endif // HAL_PLATFORM_OLIMEX_STM32P107_PLATFORMIMPLEMENTATION_H_
