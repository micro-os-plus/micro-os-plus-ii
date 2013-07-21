//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_LD_VL sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSLDVL_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSLDVL_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_LDVL) || defined(__DOXYGEN__)

#include "InterruptNumbersBase.h"


namespace hal
{
  namespace stm32f10xldvl
  {
    // ========================================================================

    /// \ingroup stm32f1ldvl_irq
    /// \headerfile InterruptNumbersLDVL.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersLDVL.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_LD_VL devices interrupt numbers.
    class InterruptNumber : public hal::stm32f1::InterruptNumberBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumber(void) = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      static constexpr interruptNumber_t ADC1 = 18; ///< ADC1 global Interrupt
      static constexpr interruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static constexpr interruptNumber_t Timer1Break_TIM15 = 24; ///< TIM1 Break and TIM15 Interrupts
      static constexpr interruptNumber_t Timer1Update_TIM16 = 25; ///< TIM1 Update and TIM16 Interrupts
      static constexpr interruptNumber_t Timer1TriggerCommutation_TIM17 = 26; ///< TIM1 Trigger and Commutation and TIM17 Interrupt
      static constexpr interruptNumber_t Timer1CaptureCompare = 27; ///< TIM1 Capture Compare Interrupt
      static constexpr interruptNumber_t Timer2Global = 28; ///< Timer2 global Interrupt
      static constexpr interruptNumber_t Timer3Global = 29; ///< Timer3 global Interrupt
      static constexpr interruptNumber_t I2C1Event = 31; ///< I2C1 Event Interrupt
      static constexpr interruptNumber_t I2C1Error = 32; ///< I2C1 Error Interrupt
      static constexpr interruptNumber_t SPI1Global = 35; ///< SPI1 global Interrupt
      static constexpr interruptNumber_t USART1Global = 37; ///< USART1 global Interrupt
      static constexpr interruptNumber_t USART2Global = 38; ///< USART2 global Interrupt
      static constexpr interruptNumber_t ExternalLines15_10 = 40; ///< External Line[15:10] Interrupts
      static constexpr interruptNumber_t RealTimeClockAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static constexpr interruptNumber_t CEC = 42; ///< HDMI-CEC Interrupt
      static constexpr interruptNumber_t TIM6_DAC = 54; ///< TIM6 and DAC underrun Interrupt
      static constexpr interruptNumber_t TIM7 = 55; ///< TIM7 Interrupt

      /// @} end of name Interrupt numbers

    };

    // ========================================================================

  } // namespace stm32f10xldvl

  namespace cortexm
  {
    typedef  hal::stm32f10xldvl::InterruptNumber InterruptNumber;
  }
} // namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_LDVL
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSLDVL_H_
