//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X array of interrupt vectors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace stm32f10x
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10x_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief WindowWatchdog Handler.
      extern void
      WindowWatchdog(void);

      /// \brief ProgramableVoltageDetector Handler.
      extern void
      ProgramableVoltageDetector(void);

      /// \brief TamperDetection Handler.
      extern void
      TamperDetection(void);

      /// \brief RealTimeClock Handler.
      extern void
      RealTimeClock(void);

      /// \brief Flash Handler.
      extern void
      Flash(void);

      /// \brief ResetClockControl (RCC) Handler.
      extern void
      ResetClockControl(void);

      /// \brief External Line0 (EXTI0) Handler.
      extern void
      ExternalLine0(void);

      /// \brief External Line1 (EXTI1) Handler.
      extern void
      ExternalLine1(void);

      /// \brief External Line2 (EXTI2) Handler.
      extern void
      ExternalLine2(void);

      /// \brief External Line3 (EXTI3) Handler.
      extern void
      ExternalLine3(void);

      /// \brief External Line4 (EXTI4) Handler.
      extern void
      ExternalLine4(void);

      /// \brief DMA1 Channel1 Handler.
      extern void
      DMA1Channel1(void);

      /// \brief DMA1 Channel2 Handler.
      extern void
      DMA1Channel2(void);

      /// \brief DMA1 Channel3 Handler.
      extern void
      DMA1Channel3(void);

      /// \brief DMA1 Channel4 Handler.
      extern void
      DMA1Channel4(void);

      /// \brief DMA1 Channel5 Handler.
      extern void
      DMA1Channel5(void);

      /// \brief DMA1 Channel6 Handler.
      extern void
      DMA1Channel6(void);

      /// \brief DMA1 Channel7 Handler.
      extern void
      DMA1Channel7(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10x_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f10x_irq
    /// \brief STM32F10x specific interrupt vectors.
    __attribute__ ((section(".family_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // 0: Watchdog Timer
        reinterpret_cast<interruptVector_t>(InterruptHandler::WindowWatchdog),

        // 1: Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::ProgramableVoltageDetector),

            // 2: Tamper
            reinterpret_cast<interruptVector_t>(InterruptHandler::TamperDetection),

            // 3: Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClock),

            // 4: Flash
            reinterpret_cast<interruptVector_t>(InterruptHandler::Flash),

            // 5: Reset and clock control
            reinterpret_cast<interruptVector_t>(InterruptHandler::ResetClockControl),

            // 6: ExternalLine Line0
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine0),

            // 7: ExternalLine Line1
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine1),

            // 8: ExternalLine Line2
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine2),

            // 9: ExternalLine Line3
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine3),

            // 10: ExternalLine Line4
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine4),

            // 11: DMA1 Channel1
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel1),

            // 12: DMA1 Channel2
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel2),

            // 13: DMA1 Channel3
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel3),

            // 14: DMA1 Channel4
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel4),

            // 15: DMA1 Channel5
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel5),

            // 16: DMA1 Channel6
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel6),

            // 17: DMA1 Channel7
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel7)

        //
        };

    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10x_irq
      /// \name Interrupt handlers
      /// \brief Default interrupt handler.
      ///
      /// \details
      /// All undefined interrupt handlers are routed to this function,
      /// via weak references, and from here to the architecture Default.
      __attribute__ ((naked))
      void
      Default(void)
      {
        // jump to the os::cortexm::defaultInterruptHandler()
        asm volatile (
            " b _ZN3hal7cortexm16InterruptHandler7DefaultEv \n"
            ::
        );
      }
    } // namespace InterruptHandler

  // --------------------------------------------------------------------------

  }// namespace stm32f10x
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::WindowWatchdog = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler14WindowWatchdogEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PDV = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler26ProgramableVoltageDetectorEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TamperDetection = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler15TamperDetectionEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClock = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13RealTimeClockEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Flash = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5FlashEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ResetClockControl = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler17ResetClockControlEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine0 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine0Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel5 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel5Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel6 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel6Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel7 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel7Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X)
