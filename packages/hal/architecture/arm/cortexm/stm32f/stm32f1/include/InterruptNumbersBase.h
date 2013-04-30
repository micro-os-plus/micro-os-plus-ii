//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X base class of sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/cortexm3/include/InterruptNumbers.h"

namespace hal
{
  namespace stm32f1
  {
    // ========================================================================

    /// \ingroup stm32f1_irq
    /// \headerfile InterruptNumbersBase.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersBase.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X family interrupt numbers.
    ///
    /// \details
    /// The STM32F10X family is based on Cortex-M3, so it inherits
    /// all Cortex-M3 interrupt numbers and adds more specific ones.
    class InterruptNumberBase : public hal::cortexm3::InterruptNumber
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumberBase() = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      /// Window WatchDog Interrupt
      static const interruptNumber_t WindowWatchdog = 0;
      /// Programable Voltage Detector through EXTI Line detection Interrupt
      static const interruptNumber_t ProgramableVoltageDetector = 1;
      /// Tamper Interrupt
      static const interruptNumber_t TamperDetection = 2;
      /// Real Time Clock global Interrupt
      static const interruptNumber_t RealTimeClockGlobal = 3;
      /// Flash global Interrupt
      static const interruptNumber_t FlashGlobal = 4;
      /// Reset Clock Control global Interrupt
      static const interruptNumber_t ResetClockControlGlobal = 5;
      /// EXTI Line0 Interrupt
      static const interruptNumber_t ExternalLine0 = 6;
      /// EXTI Line1 Interrupt
      static const interruptNumber_t ExternalLine1 = 7;
      /// EXTI Line2 Interrupt
      static const interruptNumber_t ExternalLine2 = 8;
      /// EXTI Line3 Interrupt
      static const interruptNumber_t ExternalLine3 = 9;
      /// EXTI Line4 Interrupt
      static const interruptNumber_t ExternalLine4 = 10;
      /// DMA1 Channel 1 global Interrupt
      static const interruptNumber_t DMA1Channel1Global = 11;
      /// DMA1 Channel 2 global Interrupt
      static const interruptNumber_t DMA1Channel2Global = 12;
      /// DMA1 Channel 3 global Interrupt
      static const interruptNumber_t DMA1Channel3Global = 13;
      /// DMA1 Channel 4 global Interrupt
      static const interruptNumber_t DMA1Channel4Global = 14;
      /// DMA1 Channel 5 global Interrupt
      static const interruptNumber_t DMA1Channel5Global = 15;
      /// DMA1 Channel 6 global Interrupt
      static const interruptNumber_t DMA1Channel6Global = 16;
      /// DMA1 Channel 7 global Interrupt
      static const interruptNumber_t DMA1Channel7Global = 17;

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f1
} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F1
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSBASE_H_
