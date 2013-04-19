//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_MD sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSMD_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSMD_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD) || defined(__DOXYGEN__)

#include "InterruptNumbersBase.h"

namespace hal
{
  namespace stm32f10xmd
  {
    // ========================================================================

    /// \ingroup stm32f10xmd_irq
    /// \headerfile InterruptNumbersMD.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersMD.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_MD devices interrupt numbers.
    class InterruptNumber : public hal::stm32f1::InterruptNumberBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumber() = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      /// ADC1 and ADC2 global Interrupt
      static const interruptNumber_t ADC1_2Global = 18;
      /// USB Device High Priority or CAN1 TX Interrupts
      static const interruptNumber_t USB_HP_CAN1_TX = 19;
      /// USB Device Low Priority or CAN1 RX0 Interrupts
      static const interruptNumber_t USB_LP_CAN1_RX0 = 20;
      /// CAN1 RX1 Interrupt
      static const interruptNumber_t CAN1_RX1 = 21;
      /// CAN1 SCE Interrupt
      static const interruptNumber_t CAN1_SCE = 22;
      /// External Line[9:5] Interrupts
      static const interruptNumber_t ExternalLines9_5 = 23;
      /// TIM1 Break Interrupt
      static const interruptNumber_t Timer1Break = 24;
      /// TIM1 Update Interrupt
      static const interruptNumber_t Timer1Update = 25;
      /// TIM1 Trigger and Commutation Interrupt
      static const interruptNumber_t Timer1TriggerCommutation = 26;
      /// TIM1 Capture Compare Interrupt
      static const interruptNumber_t Timer1CaptureCompare = 27;
      /// Timer2 global Interrupt
      static const interruptNumber_t Timer2Global = 28;
      /// Timer3 global Interrupt
      static const interruptNumber_t Timer3Global = 29;
      /// Timer4 global Interrupt
      static const interruptNumber_t Timer4Global = 30;
      /// I2C1 Event Interrupt
      static const interruptNumber_t I2C1Event = 31;
      /// I2C1 Error Interrupt
      static const interruptNumber_t I2C1Error = 32;
      /// I2C2 Event Interrupt
      static const interruptNumber_t I2C2Event = 33;
      /// I2C2 Error Interrupt
      static const interruptNumber_t I2C2Error = 34;
      /// SPI1 global Interrupt
      static const interruptNumber_t SPI1Global = 35;
      /// SPI2 global Interrupt
      static const interruptNumber_t SPI2Global = 36;
      /// USART1 global Interrupt
      static const interruptNumber_t USART1Global = 37;
      /// USART2 global Interrupt
      static const interruptNumber_t USART2Global = 38;
      /// USART3 global Interrupt
      static const interruptNumber_t USART3Global = 39;
      /// External Line[15:10] Interrupts
      static const interruptNumber_t ExternalLines15_10 = 40;
      /// RTC Alarm through ExternalLine Line Interrupt
      static const interruptNumber_t RealTimeClockAlarm = 41;
      /// USB Device WakeUp from suspend through ExternalLine Line Interrupt
      static const interruptNumber_t USBDeviceWakeUp = 42;

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f10xmd

  namespace stm32f10x
  {
    typedef hal::stm32f10xmd::InterruptNumber InterruptNumber;
  }
} // namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSMD_H_
