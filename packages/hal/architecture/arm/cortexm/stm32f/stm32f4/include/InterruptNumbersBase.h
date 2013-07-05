//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Common interrupt numbers for the entire STM32F4 family.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERSBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERSBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/cortexm4/include/InterruptNumbers.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================

    /// \ingroup stm32f4_irq
    /// \headerfile interruptNumbersBase.h "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptNumbersBase.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F4 family interrupt numbers.
    ///
    /// \details
    /// The STM32F4 family is based on Cortex-M4; so it inherits
    /// all Cortex-M4 interrupt numbers and adds more specific ones.
    class InterruptNumberBase : public hal::cortexm4::InterruptNumber
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumberBase(void) = delete;

      /// @} end of name Constructors/destructor

      /// \name interrupt numbers
      /// @{

      /// Window WatchDog interrupt
      static const interruptNumber_t WindowWatchdog = 0;

      /// Programable Voltage Detector through EXTI Line detection interrupt
      static const interruptNumber_t ProgramableVoltageDetector = 1;

      /// Tamper and TimeStamp interrupts through the EXTI line
      static const interruptNumber_t TamperAndTimeStamp = 2;

      /// RTC Wakeup interrupt through the EXTI line
      static const interruptNumber_t RealTimeClockWakeup = 3;

      /// Flash global interrupt
      static const interruptNumber_t FlashGlobal = 4;

      /// Reset Clock Control global interrupt
      static const interruptNumber_t ResetClockControlGlobal = 5;

      /// EXTI Line0 interrupt
      static const interruptNumber_t ExternalLine0 = 6;

      /// EXTI Line1 interrupt
      static const interruptNumber_t ExternalLine1 = 7;

      /// EXTI Line2 interrupt
      static const interruptNumber_t ExternalLine2 = 8;

      /// EXTI Line3 interrupt
      static const interruptNumber_t ExternalLine3 = 9;

      /// EXTI Line4 interrupt
      static const interruptNumber_t ExternalLine4 = 10;

      /// DMA1 Stream 0 global interrupt
      static const interruptNumber_t DMA1Stream0Global = 11;

      /// DMA1 Stream 1 global interrupt
      static const interruptNumber_t DMA1Stream1Global = 12;

      /// DMA1 Stream 2 global interrupt
      static const interruptNumber_t DMA1Stream2Global = 13;

      /// DMA1 Stream 3 global interrupt
      static const interruptNumber_t DMA1Stream3Global = 14;

      /// DMA1 Stream 4 global interrupt
      static const interruptNumber_t DMA1Stream4Global = 15;

      /// DMA1 Stream 5 global interrupt
      static const interruptNumber_t DMA1Stream5Global = 16;

      /// DMA1 Stream 6 global interrupt
      static const interruptNumber_t DMA1Stream6Global = 17;

      static const interruptNumber_t ADCGlobal = 18; ///< ADC1, ADC2 and ADC3 global interrupts
      static const interruptNumber_t CAN1TX = 19; ///< CAN1 TX interrupt
      static const interruptNumber_t CAN1RX0 = 20; ///< CAN1 RX0 interrupt
      static const interruptNumber_t CAN1RX1 = 21; ///< CAN1 RX1 interrupt
      static const interruptNumber_t CAN1SCE = 22; ///< CAN1 SCE interrupt
      static const interruptNumber_t ExternalLines9_5 = 23; ///< External Line[9:5] interrupts
      static const interruptNumber_t TIM1BreakAndTIM9Global = 24; ///< TIM1 Break interrupt and TIM9 global interrupt
      static const interruptNumber_t TIM1UpdateAndTIM10Global = 25; ///< TIM1 Update interrupt and TIM10 global interrupt
      static const interruptNumber_t TIM1TriggerAndCommutationAndTIM11Global = 26; ///< TIM1 Trigger and Commutation interrupt and TIM11 global interrupt
      static const interruptNumber_t TIM1CaptureCompare = 27; ///< TIM1 Capture Compare interrupt
      static const interruptNumber_t TIM2Global = 28; ///< TIM2 global interrupt
      static const interruptNumber_t TIM3Global = 29; ///< TIM3 global interrupt
      static const interruptNumber_t TIM4Global = 30; ///< TIM4 global interrupt
      static const interruptNumber_t I2C1Event = 31; ///< I2C1 Event interrupt
      static const interruptNumber_t I2C1Error = 32; ///< I2C1 Error interrupt
      static const interruptNumber_t I2C2Event = 33; ///< I2C2 Event interrupt
      static const interruptNumber_t I2C2Error = 34; ///< I2C2 Error interrupt
      static const interruptNumber_t SPI1Global = 35; ///< SPI1 global interrupt
      static const interruptNumber_t SPI2Global = 36; ///< SPI2 global interrupt
      static const interruptNumber_t USART1Global = 37; ///< USART1 global interrupt
      static const interruptNumber_t USART2Global = 38; ///< USART2 global interrupt
      static const interruptNumber_t USART3Global = 39; ///< USART3 global interrupt
      static const interruptNumber_t ExternalLines15_10 = 40; ///< External Line[15:10] interrupts
      static const interruptNumber_t RealTimeClockAlarm = 41; ///< RTC Alarm (A and B) through EXTI Line interrupt
      static const interruptNumber_t OTG_FS_Wakeup = 42; ///< USB OTG FS Wakeup through EXTI line interrupt
      static const interruptNumber_t TIM8BreakAndTIM12Global = 43; ///< TIM8 Break interrupt and TIM12 global interrupt
      static const interruptNumber_t TIM8UpdateAndTIM13Global = 44; ///< TIM8 Update interrupt and TIM13 global interrupt
      static const interruptNumber_t TIM8TriggerAndCommutationAndTIM14Global = 45; ///< TIM8 Trigger and Commutation interrupt and TIM14 global interrupt
      static const interruptNumber_t TIM8CaptureCompare = 46; ///< TIM8 Capture Compare interrupt
      static const interruptNumber_t DMA1Stream7Global = 47; ///< DMA1 Stream7 interrupt
      static const interruptNumber_t FSMCGlobal = 48; ///< FSMC global interrupt
      static const interruptNumber_t SDIOGlobal = 49; ///< SDIO global interrupt
      static const interruptNumber_t TIM5Global = 50; ///< TIM5 global interrupt
      static const interruptNumber_t SPI3Global = 51; ///< SPI3 global interrupt
      static const interruptNumber_t UART4Global = 52; ///< UART4 global interrupt
      static const interruptNumber_t UART5Global = 53; ///< UART5 global interrupt
      static const interruptNumber_t TIM6GlobalAndDACUnderrun = 54; ///< TIM6 global and DAC1&2 underrun error interrupts
      static const interruptNumber_t TIM7Global = 55; ///< TIM7 global interrupt
      static const interruptNumber_t DMA2Stream0Global = 56; ///< DMA2 Stream 0 global interrupt
      static const interruptNumber_t DMA2Stream1Global = 57; ///< DMA2 Stream 1 global interrupt
      static const interruptNumber_t DMA2Stream2Global = 58; ///< DMA2 Stream 2 global interrupt
      static const interruptNumber_t DMA2Stream3Global = 59; ///< DMA2 Stream 3 global interrupt
      static const interruptNumber_t DMA2Stream4Global = 60; ///< DMA2 Stream 4 global interrupt
      static const interruptNumber_t ETHGlobal = 61; ///< Ethernet global interrupt
      static const interruptNumber_t ETHWakeup = 62; ///< Ethernet Wakeup through EXTI line interrupt
      static const interruptNumber_t CAN2TX = 63; ///< CAN2 TX interrupt
      static const interruptNumber_t CAN2RX0 = 64; ///< CAN2 RX0 interrupt
      static const interruptNumber_t CAN2RX1 = 65; ///< CAN2 RX1 interrupt
      static const interruptNumber_t CAN2SCE = 66; ///< CAN2 SCE interrupt
      static const interruptNumber_t OTG_FS_Global = 67; ///< USB OTG FS global interrupt
      static const interruptNumber_t DMA2Stream5Global = 68; ///< DMA2 Stream 5 global interrupt
      static const interruptNumber_t DMA2Stream6Global = 69; ///< DMA2 Stream 6 global interrupt
      static const interruptNumber_t DMA2Stream7Global = 70; ///< DMA2 Stream 7 global interrupt
      static const interruptNumber_t USART6Global = 71; ///< USART6 global interrupt
      static const interruptNumber_t I2C3Event = 72; ///< I2C3 event interrupt
      static const interruptNumber_t I2C3Error = 73; ///< I2C3 error interrupt
      static const interruptNumber_t OTG_HS_EP1_OUT_Global = 74; ///< USB OTG HS End Point 1 Out global interrupt
      static const interruptNumber_t OTG_HS_EP1_IN_Global = 75; ///< USB OTG HS End Point 1 In global interrupt
      static const interruptNumber_t OTG_HS_Wakeup = 76; ///< USB OTG HS Wakeup through EXTI interrupt
      static const interruptNumber_t OTG_HS_Global = 77; ///< USB OTG HS global interrupt
      static const interruptNumber_t DCMIGlobal = 78; ///< DCMI global interrupt
      static const interruptNumber_t CRYPGlobal = 79; ///< CRYP crypto global interrupt
      static const interruptNumber_t HashAndRngGlobal = 80; ///< Hash and Rng global interrupt

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f4
} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F4
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERSBASE_H_
