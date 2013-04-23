//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-E407 board definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407) || defined(__DOXYGEN__)

#include "hal/platform/olimex/stm32e407/include/PlatformImplementation.h"

namespace hal
{
  namespace platform
  {
    namespace stm32e407
    {

      // ------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)
      void
      PlatformImplementation::putGreeting(void)
      {
        os::diag::trace.putString("Olimex SMT32-E407 development board");
        os::diag::trace.putNewLine();
        os::diag::trace.putString("STM32F407ZG Cortex-M4");
        os::diag::trace.putNewLine();

        hal::cortexm::FamilyImplementation::putGreeting();
      }
#endif

      // ------------------------------------------------------------------------

    } // namespace stm32h407
  }// namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407)
