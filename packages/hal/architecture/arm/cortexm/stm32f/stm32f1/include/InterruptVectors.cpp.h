//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F1 interrupt vectors.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F1_INTERRUPTVECTORS_CPP_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F1_INTERRUPTVECTORS_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

#include "hal/architecture/arm/cortexm/cortexm3/include/InterruptVectors.cpp.h"

namespace hal
{
  namespace stm32f1
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f1_irq
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
      RealTimeClockGlobal(void);

      /// \brief Flash Handler.
      extern void
      FlashGlobal(void);

      /// \brief ResetClockControl (RCC) Handler.
      extern void
      ResetClockControlGlobal(void);

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
      DMA1Channel1Global(void);

      /// \brief DMA1 Channel2 Handler.
      extern void
      DMA1Channel2Global(void);

      /// \brief DMA1 Channel3 Handler.
      extern void
      DMA1Channel3Global(void);

      /// \brief DMA1 Channel4 Handler.
      extern void
      DMA1Channel4Global(void);

      /// \brief DMA1 Channel5 Handler.
      extern void
      DMA1Channel5Global(void);

      /// \brief DMA1 Channel6 Handler.
      extern void
      DMA1Channel6Global(void);

      /// \brief DMA1 Channel7 Handler.
      extern void
      DMA1Channel7Global(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10x_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f1_irq
    /// \showinitializer
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
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClockGlobal),

            // 4: Flash
            reinterpret_cast<interruptVector_t>(InterruptHandler::FlashGlobal),

            // 5: Reset and clock control
            reinterpret_cast<interruptVector_t>(InterruptHandler::ResetClockControlGlobal),

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
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel1Global),

            // 12: DMA1 Channel2
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel2Global),

            // 13: DMA1 Channel3
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel3Global),

            // 14: DMA1 Channel4
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel4Global),

            // 15: DMA1 Channel5
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel5Global),

            // 16: DMA1 Channel6
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel6Global),

            // 17: DMA1 Channel7
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel7Global)

        //
        };

  // --------------------------------------------------------------------------

  }// namespace stm32f1
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::WindowWatchdog = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler14WindowWatchdogEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PDV = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler26ProgramableVoltageDetectorEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TamperDetection = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler15TamperDetectionEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClockGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler19RealTimeClockGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::FlashGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler11FlashGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ResetClockControlGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler23ResetClockControlGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine0 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler13ExternalLine0Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine1 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler13ExternalLine1Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine2 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler13ExternalLine2Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine3 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler13ExternalLine3Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine4 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler13ExternalLine4Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel1Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel1GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel4Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel4GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel5Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel5GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel6Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel6GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel7Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f116InterruptHandler18DMA1Channel7GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F1_INTERRUPTVECTORS_CPP_H_
