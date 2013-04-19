//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_HD_VL sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSHDVL_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSHDVL_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_HDVL) || defined(__DOXYGEN__)

#include "InterruptNumbersBase.h"


namespace hal
{
  namespace stm32f10xhdvl
  {
    // ========================================================================

    /// \ingroup stm32f10xhdvl_irq
    /// \headerfile InterruptNumbersHDVL.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersHDVL.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_HD_VL devices interrupt numbers.
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

      static const interruptNumber_t ADC1 = 18; ///< ADC1 global Interrupt
      static const interruptNumber_t ExternalLines9_5 = 23; ///< External Line[9:5] Interrupts
      static const interruptNumber_t Timer1Break_TIM15 = 24; ///< TIM1 Break and TIM15 Interrupts
      static const interruptNumber_t Timer1Update_TIM16 = 25; ///< TIM1 Update and TIM16 Interrupts
      static const interruptNumber_t Timer1TriggerCommutation_TIM17 = 26; ///< TIM1 Trigger and Commutation and TIM17 Interrupt
      static const interruptNumber_t Timer1CaptureCompare = 27; ///< TIM1 Capture Compare Interrupt
      static const interruptNumber_t Timer2Global = 28; ///< Timer2 global Interrupt
      static const interruptNumber_t Timer3Global = 29; ///< Timer3 global Interrupt
      static const interruptNumber_t Timer4Global = 30; ///< Timer4 global Interrupt
      static const interruptNumber_t I2C1Event = 31; ///< I2C1 Event Interrupt
      static const interruptNumber_t I2C1Error = 32; ///< I2C1 Error Interrupt
      static const interruptNumber_t I2C2Event = 33; ///< I2C2 Event Interrupt
      static const interruptNumber_t I2C2Error = 34; ///< I2C2 Error Interrupt
      static const interruptNumber_t SPI1Global = 35; ///< SPI1 global Interrupt
      static const interruptNumber_t SPI2Global = 36; ///< SPI2 global Interrupt
      static const interruptNumber_t USART1Global = 37; ///< USART1 global Interrupt
      static const interruptNumber_t USART2Global = 38; ///< USART2 global Interrupt
      static const interruptNumber_t USART3Global = 39; ///< USART3 global Interrupt
      static const interruptNumber_t ExternalLine15_10 = 40; ///< External Line[15:10] Interrupts
      static const interruptNumber_t RealTimeClockAlarm = 41; ///< RTC Alarm through ExternalLine Line Interrupt
      static const interruptNumber_t CEC = 42; ///< HDMI-CEC Interrupt
      static const interruptNumber_t TIM12 = 43; ///< TIM12 global Interrupt
      static const interruptNumber_t TIM13 = 44; ///< TIM13 global Interrupt
      static const interruptNumber_t TIM14 = 45; ///< TIM14 global Interrupt
      static const interruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const interruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const interruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const interruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const interruptNumber_t TIM6_DAC = 54; ///< TIM6 and DAC underrun Interrupt
      static const interruptNumber_t TIM7 = 55; ///< TIM7 Interrupt
      static const interruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const interruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const interruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const interruptNumber_t DMA2_Channel4_5 = 59; ///< DMA2 Channel 4 and Channel 5 global Interrupt
      static const interruptNumber_t DMA2_Channel5 = 60; ///< DMA2 Channel 5 global Interrupt (DMA2 Channel 5 is mapped at position 60 only if the MISC_REMAP bit in the AFIO_MAPR2 register is set)

      /// @} end of name Interrupt numbers

    };

    // ========================================================================

  } // namespace stm32f10xhdvl

  namespace stm32f10x
  {
    typedef  hal::stm32f10xhdvl::InterruptNumber InterruptNumber;
  }
} // namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_HDVL
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSHDVL_H_
