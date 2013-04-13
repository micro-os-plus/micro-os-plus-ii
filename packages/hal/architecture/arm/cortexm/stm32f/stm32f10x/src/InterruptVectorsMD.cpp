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

      /// \brief ADC1_2 Handler.
      extern void
      ADC1_2(void);

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
      EXTI9_5(void);

      /// \brief TIM1_BRK Handler
      extern void
      TIM1_BRK(void);

      /// \brief TIM1_TRG_COM Handler
      extern void
      TIM1_UP(void);

      /// \brief  Handler
      extern void
      TIM1_TRG_COM(void);

      /// \brief TIM1_CC Handler
      extern void
      TIM1_CC(void);

      /// \brief TIM2 Handler
      extern void
      TIM2(void);

      /// \brief TIM3 Handler
      extern void
      TIM3(void);

      /// \brief TIM4 Handler
      extern void
      TIM4(void);

      /// \brief I2C1_EV Handler
      extern void
      I2C1_EV(void);

      /// \brief I2C1_ER Handler
      extern void
      I2C1_ER(void);

      /// \brief I2C2_EV Handler
      extern void
      I2C2_EV(void);

      /// \brief I2C2_ER Handler
      extern void
      I2C2_ER(void);

      /// \brief SPI1 Handler
      extern void
      SPI1(void);

      /// \brief SPI2 Handler
      extern void
      SPI2(void);

      /// \brief USART1 Handler
      extern void
      USART1(void);

      /// \brief USART2 Handler
      extern void
      USART2(void);

      /// \brief USART3 Handler
      extern void
      USART3(void);

      /// \brief EXTI15_10 Handler
      extern void
      EXTI15_10(void);

      /// \brief RTCAlarm Handler
      extern void
      RTCAlarm(void);

      /// \brief USBWakeUp Handler
      extern void
      USBWakeUp(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f10xmd_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f10xmd_irq
    /// \brief STM32F10X_MD specific interrupt vectors.
    __attribute__ ((section(".device_isr_vectors")))
    interruptVector_t interruptVectors[] =
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

    // ------------------------------------------------------------------------

  } // namespace stm32f10xmd
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::ADC1_2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6ADC1_2Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_HP_CAN1_TX = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler14USB_HP_CAN1_TXEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USB_LP_CAN1_RX0 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler15USB_LP_CAN1_RX0Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_RX1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_RX1Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::CAN1_SCE = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8CAN1_SCEEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI9_5 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7EXTI9_5Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_BRK = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8TIM1_BRKEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_UP = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7TIM1_UPEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_TRG_COM = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler12TIM1_TRG_COMEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM1_CC = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7TIM1_CCEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM2Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM3 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM3Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::TIM4 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4TIM4Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1_EV = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C1_EVEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C1_ER = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C1_EREv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2_EV = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C2_EVEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::I2C2_ER = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler7I2C2_EREv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4SPI1Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SPI2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler4SPI2Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART1 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART1Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART2 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART2Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USART3 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler6USART3Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::EXTI15_10 = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9EXTI15_10Ev = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::RTCAlarm = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler8RTCAlarmEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::USBWakeUp = InterruptHandler::Default
#pragma weak _ZN3hal11stm32f10xmd16InterruptHandler9USBWakeUpEv = _ZN3hal11stm32f10xmd16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)
