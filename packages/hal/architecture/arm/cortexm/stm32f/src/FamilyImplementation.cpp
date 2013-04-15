//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The generic STM32F initialisation code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++
    void
    FamilyImplementation::initialiseSystem(void)
    {
      SystemInit();
    }

    /// \details
    /// The generic STM32F software reset code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++
    void
    FamilyImplementation::resetSystem(void)
    {
      NVIC_SystemReset();
    }

  // --------------------------------------------------------------------------

  }
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
