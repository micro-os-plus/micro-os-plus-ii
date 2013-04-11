//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/lib/cmsis/stm32f10x/include/stm32f10x.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    void
    FamilyImplementation::initialiseSystem(void)
    {
      // Currently calls the ST library function,
      // later on will use our own code
      SystemInit();
    }

    void
    FamilyImplementation::resetSystem(void)
    {
      // Currently calls the ST library function,
      // later on will use our own code
      NVIC_SystemReset();
    }

  // --------------------------------------------------------------------------

  }
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
