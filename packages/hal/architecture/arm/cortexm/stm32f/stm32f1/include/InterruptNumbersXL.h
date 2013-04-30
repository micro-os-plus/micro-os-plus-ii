//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_XL sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSXL_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSXL_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_XL) || defined(__DOXYGEN__)

#include "InterruptNumbersBase.h"


namespace hal
{
  namespace stm32f10xxl
  {
    // ========================================================================

    /// \ingroup stm32f1xl_irq
    /// \headerfile InterruptNumbersXL.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersXL.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_XL devices interrupt numbers.
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

      static const interruptNumber_t ADC1_2Global = 18; ///< ADC1 and ADC2 global Interrupt
      static const interruptNumber_t USB_HP_CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const interruptNumber_t USB_LP_CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const interruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const interruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const interruptNumber_t ExternalLines9_5 = 23; ///< External Line[9:5] Interrupts
      static const interruptNumber_t Timer1Break_TIM9 = 24; ///< TIM1 Break Interrupt and TIM9 global Interrupt
      static const interruptNumber_t Timer1Update_TIM10 = 25; ///< TIM1 Update Interrupt and TIM10 global Interrupt
      static const interruptNumber_t Timer1TriggerCommutation_TIM11 = 26; ///< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt
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
      static const interruptNumber_t USBDeviceWakeUp = 42; ///< USB Device WakeUp from suspend through ExternalLine Line Interrupt
      static const interruptNumber_t TIM8_BRK_TIM12 = 43; ///< TIM8 Break Interrupt and TIM12 global Interrupt
      static const interruptNumber_t TIM8_UP_TIM13 = 44; ///< TIM8 Update Interrupt and TIM13 global Interrupt
      static const interruptNumber_t TIM8_TRG_COM_TIM14 = 45; ///< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt
      static const interruptNumber_t TIM8_CC = 46; ///< TIM8 Capture Compare Interrupt
      static const interruptNumber_t ADC3 = 47; ///< ADC3 global Interrupt
      static const interruptNumber_t FSMC = 48; ///< FSMC global Interrupt
      static const interruptNumber_t SDIO = 49; ///< SDIO global Interrupt
      static const interruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const interruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const interruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const interruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const interruptNumber_t TIM6 = 54; ///< TIM6 global Interrupt
      static const interruptNumber_t TIM7 = 55; ///< TIM7 global Interrupt
      static const interruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const interruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const interruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const interruptNumber_t DMA2_Channel4_5 = 59; ///< DMA2 Channel 4 and Channel 5 global Interrupt

      /// @} end of name Interrupt numbers

    };

    // ========================================================================

  } // namespace stm32f10xxl

  namespace stm32f10x
  {
    typedef  hal::stm32f10xxl::InterruptNumber InterruptNumber;
  }
} // namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_XL
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSXL_H_
