//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_CL sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSCL_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSCL_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_CL) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersBase.h"


namespace hal
{
  namespace stm32f10xcl
  {
    // ========================================================================

    /// \ingroup stm32f1cl_irq
    /// \headerfile InterruptNumbersCL.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersCL.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_CL devices interrupt numbers.
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

      static const interruptNumber_t ADC1_2Global = 18; ///< ADC1 and ADC2 Global Interrupt
      static const interruptNumber_t CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const interruptNumber_t CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const interruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const interruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const interruptNumber_t ExternalLines9_5 = 23; ///< External Line[9:5] Interrupts
      static const interruptNumber_t Timer1Break = 24; ///< TIM1 Break Interrupt
      static const interruptNumber_t Timer1Update = 25; ///< TIM1 Update Interrupt
      static const interruptNumber_t Timer1TriggerCommutation = 26; ///< TIM1 Trigger and Commutation Interrupt
      static const interruptNumber_t Timer1CaptureCompare = 27; ///< TIM1 Capture Compare Interrupt
      static const interruptNumber_t Timer2Global = 28; ///< Timer2 Global Interrupt
      static const interruptNumber_t Timer3Global = 29; ///< Timer3 Global Interrupt
      static const interruptNumber_t Timer4Global = 30; ///< Timer4 Global Interrupt
      static const interruptNumber_t I2C1Event = 31; ///< I2C1 Event Interrupt
      static const interruptNumber_t I2C1Error = 32; ///< I2C1 Error Interrupt
      static const interruptNumber_t I2C2Event = 33; ///< I2C2 Event Interrupt
      static const interruptNumber_t I2C2Error = 34; ///< I2C2 Error Interrupt
      static const interruptNumber_t SPI1Global = 35; ///< SPI1 Global Interrupt
      static const interruptNumber_t SPI2Global = 36; ///< SPI2 Global Interrupt
      static const interruptNumber_t USART1Global = 37; ///< USART1 Global Interrupt
      static const interruptNumber_t USART2Global = 38; ///< USART2 Global Interrupt
      static const interruptNumber_t USART3Global = 39; ///< USART3 Global Interrupt
      static const interruptNumber_t ExternalLine15_10 = 40; ///< External Line[15:10] Interrupts
      static const interruptNumber_t RealTimeClockAlarm = 41; ///< RTC Alarm through ExternalLine Line Interrupt
      static const interruptNumber_t OTG_FS_Wakeup = 42; ///< USB OTG FS WakeUp from suspend through ExternalLine Line Interrupt
      static const interruptNumber_t TIM5Global = 50; ///< TIM5 Global Interrupt
      static const interruptNumber_t SPI3Global = 51; ///< SPI3 Global Interrupt
      static const interruptNumber_t UART4Global = 52; ///< UART4 Global Interrupt
      static const interruptNumber_t UART5Global = 53; ///< UART5 Global Interrupt
      static const interruptNumber_t TIM6Global = 54; ///< TIM6 Global Interrupt
      static const interruptNumber_t TIM7Global = 55; ///< TIM7 Global Interrupt
      static const interruptNumber_t DMA2Channel1 = 56; ///< DMA2 Channel 1 Global Interrupt
      static const interruptNumber_t DMA2Channel2 = 57; ///< DMA2 Channel 2 Global Interrupt
      static const interruptNumber_t DMA2Channel3 = 58; ///< DMA2 Channel 3 Global Interrupt
      static const interruptNumber_t DMA2Channel4 = 59; ///< DMA2 Channel 4 Global Interrupt
      static const interruptNumber_t DMA2Channel5 = 60; ///< DMA2 Channel 5 Global Interrupt
      static const interruptNumber_t ETHGlobal = 61; ///< Ethernet Global Interrupt
      static const interruptNumber_t ETHWakeup = 62; ///< Ethernet Wakeup through ExternalLine line Interrupt
      static const interruptNumber_t CAN2_TX = 63; ///< CAN2 TX Interrupt
      static const interruptNumber_t CAN2_RX0 = 64; ///< CAN2 RX0 Interrupt
      static const interruptNumber_t CAN2_RX1 = 65; ///< CAN2 RX1 Interrupt
      static const interruptNumber_t CAN2_SCE = 66; ///< CAN2 SCE Interrupt
      static const interruptNumber_t OTG_FS = 67; ///< USB OTG FS Global Interrupt

      /// @} end of name Interrupt numbers

    };

    // ========================================================================

  } // namespace stm32f10xcl

  namespace cortexm
  {
    typedef  hal::stm32f10xcl::InterruptNumber InterruptNumber;
  }
} // namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_CL
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_INTERRUPTNUMBERSCL_H_
