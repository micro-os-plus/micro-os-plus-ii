//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex OLIMEXINO-STM32 declarations of the board class.

#ifndef HAL_PLATFORM_OLIMEX_OLIMEXINOSTM32_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_OLIMEX_OLIMEXINOSTM32_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_OLIMEXINOSTM32) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace olimexinostm32
  {
    // ========================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/olimex/olimexinostm32/include/PlatformImplementation.h"
    /// \ingroup olimexinostm32
    /// \nosubgrouping
    ///
    /// \brief Olimex OLIMEXINO-STM32 board implementation class.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

      // TODO: add more platform members, like initialiseSystem()
    };

  // ==========================================================================

  }// namespace olimexinostm32

  namespace platform
  {
    // ------------------------------------------------------------------------

    typedef olimexinostm32::PlatformImplementation PlatformImplementation;

  // --------------------------------------------------------------------------
  }// namespace platform

} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_OLIMEXINOSTM32)
#endif // HAL_PLATFORM_OLIMEX_OLIMEXINOSTM32_PLATFORMIMPLEMENTATION_H_
