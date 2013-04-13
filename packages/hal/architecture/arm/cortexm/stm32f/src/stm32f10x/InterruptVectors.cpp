//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace stm32f10x
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10x_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief WWDC Handler
      extern void
      WindowWatchdog(void);

      extern void
      ProgramableVoltageDetector(void);

      extern void
      TamperDetection(void);

      extern void
      RealTimeClock(void);

      extern void
      Flash(void);

      extern void
      ResetClockControl(void);

      extern void
      ExternalLine0(void);

      extern void
      ExternalLine1(void);

      extern void
      ExternalLine2(void);

      extern void
      ExternalLine3(void);

      extern void
      ExternalLine4(void);

      extern void
      DMA1Channel1(void);

      extern void
      DMA1Channel2(void);

      extern void
      DMA1Channel3(void);

      extern void
      DMA1Channel4(void);

      extern void
      DMA1Channel5(void);

      extern void
      DMA1Channel6(void);

      extern void
      DMA1Channel7(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10x_irq

    }

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f10x_irq
    /// \brief STM32F10x specific interrupt vectors
    __attribute__ ((section(".family_isr_vectors")))
    interruptVector_t stm32f1xInterruptVectors[] =
      { //
        // 0: Watchdog Timer
        reinterpret_cast<interruptVector_t>(InterruptHandler::WindowWatchdog),

        // 1: Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::ProgramableVoltageDetector),

            // 2: Tamper
            reinterpret_cast<interruptVector_t>(InterruptHandler::TamperDetection),

            // 3: Real Time Clock
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClock),

            // 4: Flash
            reinterpret_cast<interruptVector_t>(InterruptHandler::Flash),

            // 5: Reset and clock control
            reinterpret_cast<interruptVector_t>(InterruptHandler::ResetClockControl),

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
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel1),

            // 12: DMA1 Channel2
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel2),

            // 13: DMA1 Channel3
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel3),

            // 14: DMA1 Channel4
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel4),

            // 15: DMA1 Channel5
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel5),

            // 16: DMA1 Channel6
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel6),

            // 17: DMA1 Channel7
            reinterpret_cast<interruptVector_t>(InterruptHandler::DMA1Channel7)

        //
        };

    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10x_irq
      /// \name Interrupt handlers
      /// \brief Default interrupt handler
      ///
      /// \details
      /// All undefined interrupt handlers are routed to this function,
      /// via weak references, and from here to the architecture Default.
      __attribute__ ((naked))
      void
      Default(void)
      {
        // jump to the os::cortexm::defaultInterruptHandler()
        asm volatile (
            " b _ZN3hal7cortexm16InterruptHandler7DefaultEv \n"
            ::
        );
      }
    } // namespace InterruptHandler
  } // namespace stm32f10x
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::WindowWatchdog = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler14WindowWatchdogEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PDV = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler26ProgramableVoltageDetectorEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TamperDetection = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler15TamperDetectionEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClock = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13RealTimeClockEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Flash = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler5FlashEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ResetClockControl = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler17ResetClockControlEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine0 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine0Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLine4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler13ExternalLine4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel1 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel2 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel3 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel4 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel5 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel5Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel6 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel6Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DMA1Channel7 = InterruptHandler::Default
#pragma weak _ZN3hal9stm32f10x16InterruptHandler12DMA1Channel7Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)

namespace hal
{
  namespace stm32f10xmd
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10xmd_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief ADC1_2 Handler
      extern void
      ADC1_2(void);

      extern void
      USB_HP_CAN1_TX(void);

      extern void
      USB_LP_CAN1_RX0(void);

      extern void
      CAN1_RX1(void);

      extern void
      CAN1_SCE(void);

      extern void
      EXTI9_5(void);

      extern void
      TIM1_BRK(void);

      extern void
      TIM1_UP(void);

      extern void
      TIM1_TRG_COM(void);

      extern void
      TIM1_CC(void);

      extern void
      TIM2(void);

      extern void
      TIM3(void);

      extern void
      TIM4(void);

      extern void
      I2C1_EV(void);

      extern void
      I2C1_ER(void);

      extern void
      I2C2_EV(void);

      extern void
      I2C2_ER(void);

      extern void
      SPI1(void);

      extern void
      SPI2(void);

      extern void
      USART1(void);

      extern void
      USART2(void);

      extern void
      USART3(void);

      extern void
      EXTI15_10(void);

      extern void
      RTCAlarm(void);

      extern void
      USBWakeUp(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10xmd_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f10xmd_irq
    /// \brief STM32F10X_MD specific interrupt vectors
    __attribute__ ((section(".device_isr_vectors")))
    interruptVector_t stm32f10xmdInterruptVectors[] =
      { //
        // 18: ADC1 and ADC2
        reinterpret_cast<interruptVector_t>(InterruptHandler::ADC1_2),

        // 19: USB Device High Priority or CAN1 TX Interrupts
            reinterpret_cast<interruptVector_t>(InterruptHandler::USB_HP_CAN1_TX),

            // 20: USB Device Low Priority or CAN1 RX0 Interrupts
            reinterpret_cast<interruptVector_t>(InterruptHandler::USB_LP_CAN1_RX0),

            // 21: CAN1 RX1
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1_RX1),

            // 22: CAN1 SCE
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1_SCE),

            // 23: External Line[9:5]
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI9_5),

            // 24: TIM1 Break Line0
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1_BRK),

            // 25: TIM1 Update
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1_UP),

            // 26: TIM1 Trigger and Commutation Interrupt
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1_TRG_COM),

            // 27: TIM1 Capture Compare
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM1_CC),

            // 28: TIM2
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM2),

            // 29: TIM3
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM3),

            // 30: TIM4
            reinterpret_cast<interruptVector_t>(InterruptHandler::TIM4),

            // 31: I2C1 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1_EV),

            // 32: I2C1 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1_ER),

            // 33: I2C2 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2_EV),

            // 34: I2C2 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2_ER),

            // 35: SPI1
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI1),

            // 36: SPI2
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI2),

            // 37: USART1
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART1),

            // 38: USART2
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART2),

            // 39: USART3
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART3),

            // 40: External Line[15:10]
            reinterpret_cast<interruptVector_t>(InterruptHandler::EXTI15_10),

            // 41: RTC Alarm through ExternalLine Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::RTCAlarm),

            // 42: USB Device WakeUp from suspend through ExternalLine Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::USBWakeUp),

            // 43-49: reserved
            0, 0, 0, 0, 0, 0, 0,

            // 50: (@0x108) This is for boot in RAM mode
            0xF108F85F
        //
        };
  } // namespace stm32f10xmd
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::ADC1_2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6ADC1_2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_HP_CAN1_TX = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler14USB_HP_CAN1_TXEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_LP_CAN1_RX0 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler15USB_LP_CAN1_RX0Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_RX1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_RX1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_SCE = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_SCEEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI9_5 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7EXTI9_5Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_BRK = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8TIM1_BRKEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_UP = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7TIM1_UPEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_TRG_COM = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12TIM1_TRG_COMEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_CC = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7TIM1_CCEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM3 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM4 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM4Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1_EV = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C1_EVEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1_ER = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C1_EREv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2_EV = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C2_EVEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2_ER = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C2_EREv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4SPI1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4SPI2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART1Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART2Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART3 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART3Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI15_10 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9EXTI15_10Ev = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RTCAlarm = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8RTCAlarmEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USBWakeUp = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9USBWakeUpEv = _ZN3hal9stm32f10x16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

// TODO: add more specific sub-families
#else

#error "No specific STM32F10X sub-family"

#endif

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
