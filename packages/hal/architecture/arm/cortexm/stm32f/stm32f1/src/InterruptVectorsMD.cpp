//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10X_MD array of interrupt vectors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

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

      /// \brief ADC1_2 Global Handler.
      extern void
      ADC1_2Global(void);

      /// \brief USB_HP_CAN1_TX Handler
      extern void
      USB_HP_CAN1_TX(void);

      /// \brief USB_LP_CAN1_RX0 Handler
      extern void
      USB_LP_CAN1_RX0(void);

      /// \brief CAN1_RX1 Handler
      extern void
      CAN1_RX1(void);

      /// \brief CAN1_SCE Handler
      extern void
      CAN1_SCE(void);

      /// \brief EXTI9_5 Handler
      extern void
      ExternalLines9_5(void);

      /// \brief Timer1 Break Handler
      extern void
      Timer1Break(void);

      /// \brief Timer1 Trigger and Commutation Handler
      extern void
      Timer1Update(void);

      /// \brief  Handler
      extern void
      Timer1TriggerCommutation(void);

      /// \brief Timer1 Capture and Compare Handler
      extern void
      Timer1CaptureCompare(void);

      /// \brief Timer2 Global Handler
      extern void
      Timer2Global(void);

      /// \brief Timer3 Global Handler
      extern void
      Timer3Global(void);

      /// \brief Timer4 Global Handler
      extern void
      Timer4Global(void);

      /// \brief I2C1Event Handler
      extern void
      I2C1Event(void);

      /// \brief I2C1 Error Handler
      extern void
      I2C1Error(void);

      /// \brief I2C2 Event Handler
      extern void
      I2C2Event(void);

      /// \brief I2C2 Error Handler
      extern void
      I2C2Error(void);

      /// \brief SPI1 Global Handler
      extern void
      SPI1Global(void);

      /// \brief SPI2 Global Handler
      extern void
      SPI2Global(void);

      /// \brief USART1 Global Handler
      extern void
      USART1Global(void);

      /// \brief USART2 Global Handler
      extern void
      USART2Global(void);

      /// \brief USART3 Global Handler
      extern void
      USART3Global(void);

      /// \brief ExternalLines 15_10 Handler
      extern void
      ExternalLines15_10(void);

      /// \brief RTC Alarm Handler
      extern void
      RealTimeClockAlarm(void);

      /// \brief USB Device WakeUp Handler
      extern void
      USBDeviceWakeUp(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10xmd_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f10xmd_irq
    /// \showinitializer
    /// \brief STM32F10X_MD specific interrupt vectors.
    __attribute__ ((section(".device_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // 18: ADC1 and ADC2
        reinterpret_cast<interruptVector_t>(InterruptHandler::ADC1_2Global),

        // 19: USB Device High Priority or CAN1 TX Interrupts
            reinterpret_cast<interruptVector_t>(InterruptHandler::USB_HP_CAN1_TX),

            // 20: USB Device Low Priority or CAN1 RX0 Interrupts
            reinterpret_cast<interruptVector_t>(InterruptHandler::USB_LP_CAN1_RX0),

            // 21: CAN1 RX1
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1_RX1),

            // 22: CAN1 SCE
            reinterpret_cast<interruptVector_t>(InterruptHandler::CAN1_SCE),

            // 23: External Line[9:5]
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLines9_5),

            // 24: TIM1 Break Line0
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer1Break),

            // 25: TIM1 Update
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer1Update),

            // 26: TIM1 Trigger and Commutation Interrupt
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer1TriggerCommutation),

            // 27: TIM1 Capture Compare
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer1CaptureCompare),

            // 28: Timer2Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer2Global),

            // 29: Timer3Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer3Global),

            // 30: Timer4Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::Timer4Global),

            // 31: I2C1 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1Event),

            // 32: I2C1 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C1Error),

            // 33: I2C2 Event
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2Event),

            // 34: I2C2 Error
            reinterpret_cast<interruptVector_t>(InterruptHandler::I2C2Error),

            // 35: SPI1Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI1Global),

            // 36: SPI2Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::SPI2Global),

            // 37: USART1Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART1Global),

            // 38: USART2Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART2Global),

            // 39: USART3Global
            reinterpret_cast<interruptVector_t>(InterruptHandler::USART3Global),

            // 40: External Line[15:10]
            reinterpret_cast<interruptVector_t>(InterruptHandler::ExternalLines15_10),

            // 41: RTC Alarm through ExternalLine Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::RealTimeClockAlarm),

            // 42: USB Device WakeUp from suspend through ExternalLine Line
            reinterpret_cast<interruptVector_t>(InterruptHandler::USBDeviceWakeUp),

            // 43-49: reserved
            0, 0, 0, 0, 0, 0, 0,

            // 50: (@0x108) This is for boot in RAM mode
            // TODO: document why
            0xF108F85F
        //
        };

    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f10xmd_irq
      /// \name Interrupt handlers
      /// \brief Default interrupt handler.
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

  // --------------------------------------------------------------------------

  }// namespace stm32f10xmd
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::ADC1_2Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12ADC1_2GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_HP_CAN1_TX = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler14USB_HP_CAN1_TXEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_LP_CAN1_RX0 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler15USB_LP_CAN1_RX0Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_RX1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_RX1Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_SCE = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_SCEEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI9_5 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler16ExternalLines9_5Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer1Break = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler11Timer1BreakEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer1Update = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12Timer1UpdateEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer1TriggerCommutation = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler24Timer1TriggerCommutationEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer1CaptureCompare = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler20Timer1CaptureCompareEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer2Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12Timer2GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer3Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12Timer3GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::Timer4Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12Timer4GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1Event = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9I2C1EventEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1Error = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9I2C1ErrorEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2Event = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9I2C2EventEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2Error = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9I2C2ErrorEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI1Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler10SPI1GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI2Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler10SPI2GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART1Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12USART1GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART2Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12USART2GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART3Global = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12USART3GlobalEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ExternalLines15_10 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler18ExternalLines15_10Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RealTimeClockAlarm = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler18RealTimeClockAlarmEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USBDeviceWakeUp = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler15USBDeviceWakeUpEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)
