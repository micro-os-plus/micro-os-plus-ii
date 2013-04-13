//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_INTERRUPTNUMBERSBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_INTERRUPTNUMBERSBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/cortexm3/include/InterruptNumbers.h"

namespace hal
{
  namespace stm32f10x
  {
    // ========================================================================

    /// \ingroup stm32f1x_irq
    /// \headerfile InterruptNumbersBase.h "hal/architecture/arm/cortexm/stm32f/stm32f10x/include/InterruptNumbersBase.h"
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
      /// ProgramableVoltageDetector through EXTI Line detection Interrupt
      static const interruptNumber_t ProgramableVoltageDetector = 1;
      /// Tamper Interrupt
      static const interruptNumber_t TamperDetection = 2;
      /// RealTimeClock global Interrupt
      static const interruptNumber_t RealTimeClock = 3;
      /// Flash global Interrupt
      static const interruptNumber_t Flash = 4;
      /// ResetClockControl global Interrupt
      static const interruptNumber_t ResetClockControl = 5;
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
      static const interruptNumber_t DMA1Channel1 = 11;
      /// DMA1 Channel 2 global Interrupt
      static const interruptNumber_t DMA1Channel2 = 12;
      /// DMA1 Channel 3 global Interrupt
      static const interruptNumber_t DMA1Channel3 = 13;
      /// DMA1 Channel 4 global Interrupt
      static const interruptNumber_t DMA1Channel4 = 14;
      /// DMA1 Channel 5 global Interrupt
      static const interruptNumber_t DMA1Channel5 = 15;
      /// DMA1 Channel 6 global Interrupt
      static const interruptNumber_t DMA1Channel6 = 16;
      /// DMA1 Channel 7 global Interrupt
      static const interruptNumber_t DMA1Channel7 = 17;

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f10x
} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_INTERRUPTNUMBERSBASE_H_
