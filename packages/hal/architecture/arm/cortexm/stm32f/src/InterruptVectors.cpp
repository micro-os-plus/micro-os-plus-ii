//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "../../ldscripts/LinkerScript.h"

namespace hal
{
  namespace arch
  {
    namespace stm32f
    {
      // ----------------------------------------------------------------------

      extern void
      WWDG_IRQHandler(void);
      extern void
      PVD_IRQHandler(void);

      typedef hal::arch::cortexm::InterruptVector_t InterruptVector_t;

      /// \brief STM32Fx specific interrupt vectors
      __attribute__ ((section(".isr_vector")))
      InterruptVector_t interruptVectors[] =
        { //
          reinterpret_cast<InterruptVector_t>(WWDG_IRQHandler), // 0:  Watchdog Timer
              reinterpret_cast<InterruptVector_t>(PVD_IRQHandler) // 1:  Real Time Clock

          };
      // ----------------------------------------------------------------------

      void
      WWDG_IRQHandler(void)
      {
      }
      void
      PVD_IRQHandler(void)
      {
      }

    // ------------------------------------------------------------------------

    }
  }
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
