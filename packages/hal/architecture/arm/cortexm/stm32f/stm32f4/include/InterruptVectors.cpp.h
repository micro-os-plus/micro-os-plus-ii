//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 interrupt vectors.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTVECTORS_CPP_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTVECTORS_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

#include "hal/architecture/arm/cortexm/cortexm4/include/InterruptVectors.cpp.h"

namespace hal
{
  namespace stm32f4
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f4_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief Window Watchdog handler.
      extern void
      WindowWatchdog(void);

      /// \brief Programable Voltage Detector  through EXTI Line detection handler.
      extern void
      ProgramableVoltageDetector(void);

      /// \brief Tamper and TimeStamp interrupts through the EXTI line handler.
      extern void
      TamperAndTimeStamp(void);

      /// \brief RTC Wakeup interrupt through the EXTI line handler.
      extern void
      RealTimeClockWakeup(void);

      /// \brief Flash Global handler.
      extern void
      FlashGlobal(void);

      /// \brief Reset Clock Control Global (RCC) handler.
      extern void
      ResetClockControlGlobal(void);

      /// \brief External Line0 (EXTI0) handler.
      extern void
      ExternalLine0(void);

      /// \brief External Line1 (EXTI1) handler.
      extern void
      ExternalLine1(void);

      /// \brief External Line2 (EXTI2) handler.
      extern void
      ExternalLine2(void);

      /// \brief External Line3 (EXTI3) handler.
      extern void
      ExternalLine3(void);

      /// \brief External Line4 (EXTI4) handler.
      extern void
      ExternalLine4(void);

      /// \brief DMA1 Stream 0 Global handler.
      extern void
      DMA1Stream0Global(void);

      /// \brief DMA1 Stream 1 Global handler.
      extern void
      DMA1Stream1Global(void);

      /// \brief DMA1 Stream 2 Global handler.
      extern void
      DMA1Stream2Global(void);

      /// \brief DMA1 Stream 3 Global handler.
      extern void
      DMA1Stream3Global(void);

      /// \brief DMA1 Stream 4 Global handler.
      extern void
      DMA1Stream4Global(void);

      /// \brief DMA1 Stream 5 Global handler.
      extern void
      DMA1Stream5Global(void);

      /// \brief DMA1 Stream 6 Global handler.
      extern void
      DMA1Stream6Global(void);

      /// \brief ADC1, ADC2 and ADC3 Global handler.
      extern void
      ADCGlobal(void);

      /// \brief CAN1 TX handler.
      extern void
      CAN1TX(void);

      /// \brief CAN1 RX0 handler.
      extern void
      CAN1RX0(void);

      /// \brief CAN1 RX1 handler.
      extern void
      CAN1RX1(void);

      /// \brief CAN1 SCE handler.
      extern void
      CAN1SCE(void);

      /// \brief External Line[9:5] handler.
      extern void
      ExternalLines9_5(void);

      /// \brief TIM1 Break interrupt and TIM9 Global handler.
      extern void
      TIM1BreakAndTIM9Global(void);

      /// \brief TIM1 Update Interrupt and TIM10 Global handler.
      extern void
      TIM1UpdateAndTIM10Global(void);

      /// \brief TIM1 Trigger and Commutation Interrupt and TIM11 Global handler.
      extern void
      TIM1TriggerAndCommutationAndTIM11Global(void);

      /// \brief TIM1 Capture Compare handler.
      extern void
      TIM1CaptureCompare(void);

      /// \brief TIM2 Global handler.
      extern void
      TIM2Global(void);

      /// \brief TIM3 Global handler.
      extern void
      TIM3Global(void);

      /// \brief TIM4 Global handler.
      extern void
      TIM4Global(void);

      /// \brief I2C1 Event handler.
      extern void
      I2C1Event(void);

      /// \brief I2C1 Error handler.
      extern void
      I2C1Error(void);

      /// \brief I2C2 Event handler.
      extern void
      I2C2Event(void);

      /// \brief I2C2 Error handler.
      extern void
      I2C2Error(void);

      /// \brief SPI1 Global handler.
      extern void
      SPI1Global(void);

      /// \brief SPI2 Global handler.
      extern void
      SPI2Global(void);

      /// \brief USART1 Global handler.
      extern void
      USART1Global(void);

      /// \brief USART2 Global handler.
      extern void
      USART2Global(void);

      /// \brief USART3 Global handler.
      extern void
      USART3Global(void);

      /// \brief External Line[15:10] handler.
      extern void
      ExternalLines15_10(void);

      /// \brief RTC Alarm (A and B) through EXTI Line handler.
      extern void
      RealTimeClockAlarm(void);

      /// \brief USB OTG FS Wakeup through EXTI line handler.
      extern void
      OTG_FS_Wakeup(void);

      /// \brief TIM8 Break Interrupt and TIM12 Global handler.
      extern void
      TIM8BreakAndTIM12Global(void);

      /// \brief TIM8 Update Interrupt and TIM13 Global handler.
      extern void
      TIM8UpdateAndTIM13Global(void);

      /// \brief TIM8 Trigger and Commutation Interrupt and TIM14 Global handler.
      extern void
      TIM8TriggerAndCommutationAndTIM14Global(void);

      /// \brief TIM8 Capture Compare handler.
      extern void
      TIM8CaptureCompare(void);

      /// \brief DMA1 Stream7 handler.
      extern void
      DMA1Stream7Global(void);

      /// \brief FSMC Global handler.
      extern void
      FSMCGlobal(void);

      /// \brief SDIO Global handler.
      extern void
      SDIOGlobal(void);

      /// \brief TIM5 Global handler.
      extern void
      TIM5Global(void);

      /// \brief SPI3 Global handler.
      extern void
      SPI3Global(void);

      /// \brief UART4 Global handler.
      extern void
      UART4Global(void);

      /// \brief UART5 Global handler.
      extern void
      UART5Global(void);

      /// \brief TIM6 Global and DAC1&2 underrun error handler.
      extern void
      TIM6GlobalAndDACUnderrun(void);

      /// \brief TIM7 Global handler.
      extern void
      TIM7Global(void);

      /// \brief DMA2 Stream 0 Global handler.
      extern void
      DMA2Stream0Global(void);

      /// \brief DMA2 Stream 1 Global handler.
      extern void
      DMA2Stream1Global(void);

      /// \brief DMA2 Stream 2 Global handler.
      extern void
      DMA2Stream2Global(void);

      /// \brief DMA2 Stream 3 Global handler.
      extern void
      DMA2Stream3Global(void);

      /// \brief DMA2 Stream 4 Global handler.
      extern void
      DMA2Stream4Global(void);

      /// \brief Ethernet Global handler.
      extern void
      ETHGlobal(void);

      /// \brief Ethernet Wakeup through EXTI line handler.
      extern void
      ETHWakeup(void);

      /// \brief CAN2 TX handler.
      extern void
      CAN2TX(void);

      /// \brief CAN2 RX0 handler.
      extern void
      CAN2RX0(void);

      /// \brief CAN2 RX1 handler.
      extern void
      CAN2RX1(void);

      /// \brief CAN2 SCE handler.
      extern void
      CAN2SCE(void);

      /// \brief USB OTG FS Global handler.
      extern void
      OTG_FS_Global(void);

      /// \brief DMA2 Stream 5 Global handler.
      extern void
      DMA2Stream5Global(void);

      /// \brief DMA2 Stream 6 Global handler.
      extern void
      DMA2Stream6Global(void);

      /// \brief DMA2 Stream 7 Global handler.
      extern void
      DMA2Stream7Global(void);

      /// \brief USART6 Global handler.
      extern void
      USART6Global(void);

      /// \brief I2C3 event handler.
      extern void
      I2C3Event(void);

      /// \brief I2C3 error handler.
      extern void
      I2C3Error(void);

      /// \brief USB OTG HS End Point 1 Out Global handler.
      extern void
      OTG_HS_EP1_OUT_Global(void);

      /// \brief USB OTG HS End Point 1 In Global handler.
      extern void
      OTG_HS_EP1_IN_Global(void);

      /// \brief USB OTG HS Wakeup through EXTI handler.
      extern void
      OTG_HS_Wakeup(void);

      /// \brief USB OTG HS Global handler.
      extern void
      OTG_HS_Global(void);

      /// \brief DCMI Global handler.
      extern void
      DCMIGlobal(void);

      /// \brief CRYP crypto Global handler.
      extern void
      CRYPGlobal(void);

      /// \brief Hash and Rng Global handler.
      extern void
      HashAndRngGlobal(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f40xx_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f4_irq
    /// \showinitializer
    /// \brief STM32F4 specific interrupt vectors.
    __attribute__ ((section(".family_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // 0: Window WatchDog Timer
        reinterpret_cast<interruptVector_t>(InterruptHandler::WindowWatchdog),

        // 1: Programable Voltage Detector through EXTI Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::ProgramableVoltageDetector),

            // 2: Tamper and TimeStamp interrupts through the EXTI line
            reinterpret_cast<interruptVector_t>(InterruptHandler::TamperAndTimeStamp),

            // 3: RTC Wakeup interrupt through the EXTI line
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClockWakeup),

            // 4: Flash Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::FlashGlobal),

            // 5: Reset Clock Control Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::ResetClockControlGlobal),

            // 6: External Line Line0
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine0),

            // 7: External Line Line1
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine1),

            // 8: External Line Line2
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine2),

            // 9: External Line Line3
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine3),

            // 10: External Line Line4
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLine4),

            // 11: DMA1 Stream 0 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream0Global),

            // 12: DMA1 Stream 1 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream1Global),

            // 13: DMA1 Stream 2 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream2Global),

            // 14: DMA1 Stream 3 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream3Global),

            // 15: DMA1 Stream 4 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream4Global),

            // 16: DMA1 Stream 5 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream5Global),

            // 17: DMA1 Stream 6 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream6Global),

            // 18: ADCGlobal
            reinterpret_cast<interruptVector_t>(InterruptHandler::ADCGlobal),

            // 19: CAN1 TX
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1TX),

            // 20: CAN1 RX0
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1RX0),

            // 21: CAN1 RX1
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1RX1),

            // 22: CAN1 SCE
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1SCE),

            // 23: External Line[9:5]
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLines9_5),

            // 24: TIM1 Break interrupt and TIM9 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1BreakAndTIM9Global),

            // 25: TIM1 Update Interrupt and TIM10 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1UpdateAndTIM10Global),

            // 26: TIM1 Trigger and Commutation Interrupt and TIM11 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1TriggerAndCommutationAndTIM11Global),

            // 27: TIM1 Capture Compare
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1CaptureCompare),

            // 28: TIM2 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM2Global),

            // 29: TIM3 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM3Global),

            // 30: TIM4 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM4Global),

            // 31: I2C1 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1Event),

            // 32: I2C1 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1Error),

            // 33: I2C2 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2Event),

            // 34: I2C2 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2Error),

            // 35: SPI1 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI1Global),

            // 36: SPI2 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI2Global),

            // 37: USART1 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART1Global),

            // 38: USART2 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART2Global),

            // 39: USART3 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART3Global),

            // 40: External Line[15:10]
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLines15_10),

            // 41: RTC Alarm (A and B) through EXTI Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClockAlarm),

            // 42: USB OTG FS Wakeup through EXTI line
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_FS_Wakeup),

            // 43: TIM8 Break Interrupt and TIM12 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM8BreakAndTIM12Global),

            // 44: TIM8 Update Interrupt and TIM13 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM8UpdateAndTIM13Global),

            // 45: TIM8 Trigger and Commutation and TIM14 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM8TriggerAndCommutationAndTIM14Global),

            // 46: TIM8 Capture Compare
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM8CaptureCompare),

            // 47: DMA1 Stream7
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Stream7Global),

            // 48: FSMC Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::FSMCGlobal),

            // 49: SDIO Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SDIOGlobal),

            // 50: TIM5 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM5Global),

            // 51: SPI3 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI3Global),

            // 52: UART4 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::UART4Global),

            // 53: UART5 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::UART5Global),

            // 54: TIM6 Global and DAC1&2 underrun error
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM6GlobalAndDACUnderrun),

            // 55: TIM7 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM7Global),

            // 56: DMA2 Stream 0 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream0Global),

            // 57: DMA2 Stream 1 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream1Global),

            // 58: DMA2 Stream 2 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream2Global),

            // 59: DMA2 Stream 3 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream3Global),

            // 60: DMA2 Stream 4 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream4Global),

            // 61: Ethernet Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::ETHGlobal),

            // 62: Ethernet Wakeup through EXTI line
            reinterpret_cast<interruptVector_t>(InterruptHandler::ETHWakeup),

            // 63: CAN2 TX
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN2TX),

            // 64: CAN2 RX0
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN2RX0),

            // 65: CAN2 RX1
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN2RX1),

            // 66: CAN2 SCE
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN2SCE),

            // 67: USB OTG FS Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_FS_Global),

            // 68: DMA2 Stream 5 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream5Global),

            // 69: DMA2 Stream 6 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream6Global),

            // 70: DMA2 Stream 7 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA2Stream7Global),

            // 71: USART6 Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART6Global),

            // 72: I2C3 event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C3Event),

            // 73: I2C3 error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C3Error),

            // 74: USB OTG HS End Point 1 Out Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_HS_EP1_OUT_Global),

            // 75: USB OTG HS End Point 1 In Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_HS_EP1_IN_Global),

            // 76: USB OTG HS Wakeup through EXTI
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_HS_Wakeup),

            // 77: USB OTG HS Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::OTG_HS_Global),

            // 78: DCMI Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::DCMIGlobal),

            // 79: CRYP crypto Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::CRYPGlobal),

            // 80: Hash and Rng Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::HashAndRngGlobal)

        //
        };

  // --------------------------------------------------------------------------

  }// namespace stm32f4
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::WindowWatchdog = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler14WindowWatchdogEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PDV = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler26ProgramableVoltageDetectorEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TamperDetection = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler18TamperAndTimeStampEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClock = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler19RealTimeClockWakeupEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Flash = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler11FlashGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ResetClockControl = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler23ResetClockControlGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine0 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13ExternalLine0Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine1 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13ExternalLine1Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine2 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13ExternalLine2Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine3 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13ExternalLine3Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine4 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13ExternalLine4Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream0Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream0GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream1Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream1GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream4Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream4GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream5Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream5GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream6Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream6GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ADCGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9ADCGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1TX = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler6CAN1TXEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1RX0 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN1RX0Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1RX1 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN1RX1Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1SCE = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN1SCEEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLines9_5 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler16ExternalLines9_5Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1BreakAndTIM9Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler22TIM1BreakAndTIM9GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1UpdateAndTIM10Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler24TIM1UpdateAndTIM10GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1TriggerAndCommutationAndTIM11Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler39TIM1TriggerAndCommutationAndTIM11GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1CaptureCompare = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler18TIM1CaptureCompareEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10TIM2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10TIM3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM4Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10TIM4GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1Event = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C1EventEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1Error = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C1ErrorEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2Event = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C2EventEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2Error = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C2ErrorEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI1Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10SPI1GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10SPI2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART1Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler12USART1GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler12USART2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler12USART3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLines15_10 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler18ExternalLines15_10Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClockAlarm = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler18RealTimeClockAlarmEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_FS_Wakeup = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13OTG_FS_WakeupEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM8BreakAndTIM12Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler23TIM8BreakAndTIM12GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM8UpdateAndTIM13Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler24TIM8UpdateAndTIM13GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM8TriggerAndCommutationAndTIM14Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler39TIM8TriggerAndCommutationAndTIM14GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM8CaptureCompare = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler18TIM8CaptureCompareEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Stream7Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA1Stream7GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::FSMCGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10FSMCGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SDIOGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10SDIOGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM5Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10TIM5GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10SPI3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::UART4Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler11UART4GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::UART5Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler11UART5GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM6GlobalAndDACUnderrun = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler24TIM6GlobalAndDACUnderrunEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM7Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10TIM7GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream0Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream0GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream1Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream1GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream2Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream2GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream3Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream3GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream4Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream4GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ETHGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9ETHGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ETHWakeup = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9ETHWakeupEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN2TX = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler6CAN2TXEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN2RX0 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN2RX0Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN2RX1 = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN2RX1Ev = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN2SCE = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler7CAN2SCEEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_FS_Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13OTG_FS_GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream5Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream5GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream6Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream6GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA2Stream7Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler17DMA2Stream7GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART6Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler12USART6GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C3Event = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C3EventEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C3Error = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler9I2C3ErrorEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_HS_EP1_OUT_Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler21OTG_HS_EP1_OUT_GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_HS_EP1_IN_Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler20OTG_HS_EP1_IN_GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_HS_Wakeup = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13OTG_HS_WakeupEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::OTG_HS_Global = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler13OTG_HS_GlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DCMIGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10DCMIGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CRYPGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler10CRYPGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::HashAndRngGlobal = InterruptHandler::Default
#pragma weak _ZN3hal7stm32f416InterruptHandler16HashAndRngGlobalEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTVECTORS_CPP_H_
