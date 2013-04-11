//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace stm32f10x
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      extern void
      WWDG(void);

      extern void
      PVD(void);

      extern void
      TAMPER(void);

      extern void
      RTC(void);

      extern void
      FLASH(void);

      extern void
      RCC(void);

      extern void
      EXTI0(void);

      extern void
      EXTI1(void);

      extern void
      EXTI2(void);

      extern void
      EXTI3(void);

      extern void
      EXTI4(void);

      extern void
      DMA1_Channel1(void);

      extern void
      DMA1_Channel2(void);

      extern void
      DMA1_Channel3(void);

      extern void
      DMA1_Channel4(void);

      extern void
      DMA1_Channel5(void);

      extern void
      DMA1_Channel6(void);

      extern void
      DMA1_Channel7(void);
    }

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    /// \brief STM32F10x specific interrupt vectors
    __attribute__ ((section(".family_isr_vectors")))
    interruptVector_t familyInterruptVectors[] =
      { //
            reinterpret_cast<interruptVector_t>(InterruptHandler::WWDG), // 0:  Watchdog Timer
            reinterpret_cast<interruptVector_t>(InterruptHandler::PVD), // 1:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::TAMPER), // 2:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::RTC), // 3:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::FLASH), // 4:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::RCC), // 5:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI0), // 6:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI1), // 7:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI2), // 8:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI3), // 9:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI4), // 10:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel1), // 11:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel2), // 12:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel3), // 13:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel4), // 14:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel5), // 15:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel6), // 16:  Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1_Channel7) // 17:  Real Time Clock

        };

    namespace InterruptHandler
    {
      void
      Default(void)
      {
        // Another idea would be to jump to the
        // os::cortexm::defaultInterruptHandler()

#if defined(DEBUG)

        os::diag::trace.putNewLine();
        os::diag::trace.putString(__PRETTY_FUNCTION__);
        os::diag::trace.putNewLine();

        for (;;)
          ;
#else
        // soft reset
        os::platform.resetSystem();
#endif
      }
    }

// TODO: don't forget about the BootRAM definition,
// see startup_stm32f10x_md.s

  }
}

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::WWDG = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler4WWDGEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PDV = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler3PVDEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TAMPER = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler6TAMPEREv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RTC = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler3RTCEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::FLASH = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5FLASHEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RCC = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler3RCCEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI0 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5EXTI0Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5EXTI1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5EXTI2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5EXTI3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5EXTI4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel5 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel5Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel6 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel6Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1_Channel7 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13DMA1_Channel7Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
