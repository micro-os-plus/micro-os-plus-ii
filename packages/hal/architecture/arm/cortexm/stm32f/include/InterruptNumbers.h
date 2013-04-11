//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_INTERRUPTNUMBERS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_INTERRUPTNUMBERS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"

namespace hal
{
  namespace stm32f10x
  {
    /// \ingroup stm32f1x
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X family interrupt numbers
    class InterruptNumberBase : public hal::cortexm::CortexM3InterruptNumber
    {
    public:
      //InterruptNumberBase() = delete;

      /// \name Interrupt numbers
      /// @{

      /// Window WatchDog Interrupt
      static const InterruptNumber_t WWDG = 0;
      /// PVD through EXTI Line detection Interrupt
      static const InterruptNumber_t PVD = 1;
      /// Tamper Interrupt
      static const InterruptNumber_t TAMPER = 2;
      /// RTC global Interrupt
      static const InterruptNumber_t RTC = 3;
      /// FLASH global Interrupt
      static const InterruptNumber_t FLASH = 4;
      /// RCC global Interrupt
      static const InterruptNumber_t RCC = 5;
      /// EXTI Line0 Interrupt
      static const InterruptNumber_t EXTI0 = 6;
      /// EXTI Line1 Interrupt
      static const InterruptNumber_t EXTI1 = 7;
      /// EXTI Line2 Interrupt
      static const InterruptNumber_t EXTI2 = 8;
      /// EXTI Line3 Interrupt
      static const InterruptNumber_t EXTI3 = 9;
      /// EXTI Line4 Interrupt
      static const InterruptNumber_t EXTI4 = 10;
      /// DMA1 Channel 1 global Interrupt
      static const InterruptNumber_t DMA1_Channel1 = 11;
      /// DMA1 Channel 2 global Interrupt
      static const InterruptNumber_t DMA1_Channel2 = 12;
      /// DMA1 Channel 3 global Interrupt
      static const InterruptNumber_t DMA1_Channel3 = 13;
      /// DMA1 Channel 4 global Interrupt
      static const InterruptNumber_t DMA1_Channel4 = 14;
      /// DMA1 Channel 5 global Interrupt
      static const InterruptNumber_t DMA1_Channel5 = 15;
      /// DMA1 Channel 6 global Interrupt
      static const InterruptNumber_t DMA1_Channel6 = 16;
      /// DMA1 Channel 7 global Interrupt
      static const InterruptNumber_t DMA1_Channel7 = 17;

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xld
  {
    /// \ingroup stm32f10xld
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_LD family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1_2 = 18; ///< ADC1 and ADC2 global Interrupt
      static const InterruptNumber_t USB_HP_CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const InterruptNumber_t USB_LP_CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const InterruptNumber_t CAN1_RX1 = 21;      ///< CAN1 RX1 Interrupt
      static const InterruptNumber_t CAN1_SCE = 22;      ///< CAN1 SCE Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK = 24;    ///< TIM1 Break Interrupt
      static const InterruptNumber_t TIM1_UP = 25;    ///< TIM1 Update Interrupt
      static const InterruptNumber_t TIM1_TRG_COM = 26; ///< TIM1 Trigger and Commutation Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28;      ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29;      ///< TIM3 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31;     ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32;     ///< I2C1 Error Interrupt
      static const InterruptNumber_t SPI1 = 35;      ///< SPI1 global Interrupt
      static const InterruptNumber_t USART1 = 37;   ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38;   ///< USART2 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t USBWakeUp = 42; ///< USB Device WakeUp from suspend through EXTI Line Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xldvl
  {
    /// \ingroup stm32f10xldvl
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_LD_VL family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      static const InterruptNumber_t ADC1 = 18; ///< ADC1 global Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK_TIM15 = 24; ///< TIM1 Break and TIM15 Interrupts
      static const InterruptNumber_t TIM1_UP_TIM16 = 25; ///< TIM1 Update and TIM16 Interrupts
      static const InterruptNumber_t TIM1_TRG_COM_TIM17 = 26; ///< TIM1 Trigger and Commutation and TIM17 Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t CEC = 42; ///< HDMI-CEC Interrupt
      static const InterruptNumber_t TIM6_DAC = 54; ///< TIM6 and DAC underrun Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 Interrupt
    };
  }
}

namespace hal
{
  namespace stm32f10xmd
  {
    /// \ingroup stm32f10xmd
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_MD devices interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1_2 = 18; ///< ADC1 and ADC2 global Interrupt
      static const InterruptNumber_t USB_HP_CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const InterruptNumber_t USB_LP_CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const InterruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const InterruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK = 24; ///< TIM1 Break Interrupt
      static const InterruptNumber_t TIM1_UP = 25; ///< TIM1 Update Interrupt
      static const InterruptNumber_t TIM1_TRG_COM = 26; ///< TIM1 Trigger and Commutation Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t USBWakeUp = 42; ///< USB Device WakeUp from suspend through EXTI Line Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xmdvl
  {
    /// \ingroup stm32f10xmdvl
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_MD_VL family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1 = 18; ///< ADC1 global Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK_TIM15 = 24; ///< TIM1 Break and TIM15 Interrupts
      static const InterruptNumber_t TIM1_UP_TIM16 = 25; ///< TIM1 Update and TIM16 Interrupts
      static const InterruptNumber_t TIM1_TRG_COM_TIM17 = 26; ///< TIM1 Trigger and Commutation and TIM17 Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t CEC = 42; ///< HDMI-CEC Interrupt
      static const InterruptNumber_t TIM6_DAC = 54; ///< TIM6 and DAC underrun Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xhd
  {
    /// \ingroup stm32f10xhd
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_HD family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1_2 = 18; ///< ADC1 and ADC2 global Interrupt
      static const InterruptNumber_t USB_HP_CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const InterruptNumber_t USB_LP_CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const InterruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const InterruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK = 24; ///< TIM1 Break Interrupt
      static const InterruptNumber_t TIM1_UP = 25; ///< TIM1 Update Interrupt
      static const InterruptNumber_t TIM1_TRG_COM = 26; ///< TIM1 Trigger and Commutation Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t USBWakeUp = 42; ///< USB Device WakeUp from suspend through EXTI Line Interrupt
      static const InterruptNumber_t TIM8_BRK = 43; ///< TIM8 Break Interrupt
      static const InterruptNumber_t TIM8_UP = 44; ///< TIM8 Update Interrupt
      static const InterruptNumber_t TIM8_TRG_COM = 45; ///< TIM8 Trigger and Commutation Interrupt
      static const InterruptNumber_t TIM8_CC = 46; ///< TIM8 Capture Compare Interrupt
      static const InterruptNumber_t ADC3 = 47; ///< ADC3 global Interrupt
      static const InterruptNumber_t FSMC = 48; ///< FSMC global Interrupt
      static const InterruptNumber_t SDIO = 49; ///< SDIO global Interrupt
      static const InterruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const InterruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const InterruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const InterruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const InterruptNumber_t TIM6 = 54; ///< TIM6 global Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 global Interrupt
      static const InterruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const InterruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const InterruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const InterruptNumber_t DMA2_Channel4_5 = 59; ///< DMA2 Channel 4 and Channel 5 global Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xhdvl
  {
    /// \ingroup stm32f10xhdvl
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_HD_VL family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1 = 18; ///< ADC1 global Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK_TIM15 = 24; ///< TIM1 Break and TIM15 Interrupts
      static const InterruptNumber_t TIM1_UP_TIM16 = 25; ///< TIM1 Update and TIM16 Interrupts
      static const InterruptNumber_t TIM1_TRG_COM_TIM17 = 26; ///< TIM1 Trigger and Commutation and TIM17 Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t CEC = 42; ///< HDMI-CEC Interrupt
      static const InterruptNumber_t TIM12 = 43; ///< TIM12 global Interrupt
      static const InterruptNumber_t TIM13 = 44; ///< TIM13 global Interrupt
      static const InterruptNumber_t TIM14 = 45; ///< TIM14 global Interrupt
      static const InterruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const InterruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const InterruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const InterruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const InterruptNumber_t TIM6_DAC = 54; ///< TIM6 and DAC underrun Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 Interrupt
      static const InterruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const InterruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const InterruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const InterruptNumber_t DMA2_Channel4_5 = 59; ///< DMA2 Channel 4 and Channel 5 global Interrupt
      static const InterruptNumber_t DMA2_Channel5 = 60; ///< DMA2 Channel 5 global Interrupt (DMA2 Channel 5 is mapped at position 60 only if the MISC_REMAP bit in the AFIO_MAPR2 register is set)

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xxl
  {
    /// \ingroup stm32f10xxl
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_XL family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1_2 = 18; ///< ADC1 and ADC2 global Interrupt
      static const InterruptNumber_t USB_HP_CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const InterruptNumber_t USB_LP_CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const InterruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const InterruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK_TIM9 = 24; ///< TIM1 Break Interrupt and TIM9 global Interrupt
      static const InterruptNumber_t TIM1_UP_TIM10 = 25; ///< TIM1 Update Interrupt and TIM10 global Interrupt
      static const InterruptNumber_t TIM1_TRG_COM_TIM11 = 26; ///< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t USBWakeUp = 42; ///< USB Device WakeUp from suspend through EXTI Line Interrupt
      static const InterruptNumber_t TIM8_BRK_TIM12 = 43; ///< TIM8 Break Interrupt and TIM12 global Interrupt
      static const InterruptNumber_t TIM8_UP_TIM13 = 44; ///< TIM8 Update Interrupt and TIM13 global Interrupt
      static const InterruptNumber_t TIM8_TRG_COM_TIM14 = 45; ///< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt
      static const InterruptNumber_t TIM8_CC = 46; ///< TIM8 Capture Compare Interrupt
      static const InterruptNumber_t ADC3 = 47; ///< ADC3 global Interrupt
      static const InterruptNumber_t FSMC = 48; ///< FSMC global Interrupt
      static const InterruptNumber_t SDIO = 49; ///< SDIO global Interrupt
      static const InterruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const InterruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const InterruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const InterruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const InterruptNumber_t TIM6 = 54; ///< TIM6 global Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 global Interrupt
      static const InterruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const InterruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const InterruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const InterruptNumber_t DMA2_Channel4_5 = 59; ///< DMA2 Channel 4 and Channel 5 global Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f10xcl
  {
    /// \ingroup stm32f10xcl
    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/include/InterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F10X_CL family interrupt numbers
    class InterruptNumber : public hal::stm32f10x::InterruptNumberBase
    {
    public:
      //InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      static const InterruptNumber_t ADC1_2 = 18; ///< ADC1 and ADC2 global Interrupt
      static const InterruptNumber_t CAN1_TX = 19; ///< USB Device High Priority or CAN1 TX Interrupts
      static const InterruptNumber_t CAN1_RX0 = 20; ///< USB Device Low Priority or CAN1 RX0 Interrupts
      static const InterruptNumber_t CAN1_RX1 = 21; ///< CAN1 RX1 Interrupt
      static const InterruptNumber_t CAN1_SCE = 22; ///< CAN1 SCE Interrupt
      static const InterruptNumber_t EXTI9_5 = 23; ///< External Line[9:5] Interrupts
      static const InterruptNumber_t TIM1_BRK = 24; ///< TIM1 Break Interrupt
      static const InterruptNumber_t TIM1_UP = 25; ///< TIM1 Update Interrupt
      static const InterruptNumber_t TIM1_TRG_COM = 26; ///< TIM1 Trigger and Commutation Interrupt
      static const InterruptNumber_t TIM1_CC = 27; ///< TIM1 Capture Compare Interrupt
      static const InterruptNumber_t TIM2 = 28; ///< TIM2 global Interrupt
      static const InterruptNumber_t TIM3 = 29; ///< TIM3 global Interrupt
      static const InterruptNumber_t TIM4 = 30; ///< TIM4 global Interrupt
      static const InterruptNumber_t I2C1_EV = 31; ///< I2C1 Event Interrupt
      static const InterruptNumber_t I2C1_ER = 32; ///< I2C1 Error Interrupt
      static const InterruptNumber_t I2C2_EV = 33; ///< I2C2 Event Interrupt
      static const InterruptNumber_t I2C2_ER = 34; ///< I2C2 Error Interrupt
      static const InterruptNumber_t SPI1 = 35; ///< SPI1 global Interrupt
      static const InterruptNumber_t SPI2 = 36; ///< SPI2 global Interrupt
      static const InterruptNumber_t USART1 = 37; ///< USART1 global Interrupt
      static const InterruptNumber_t USART2 = 38; ///< USART2 global Interrupt
      static const InterruptNumber_t USART3 = 39; ///< USART3 global Interrupt
      static const InterruptNumber_t EXTI15_10 = 40; ///< External Line[15:10] Interrupts
      static const InterruptNumber_t RTCAlarm = 41; ///< RTC Alarm through EXTI Line Interrupt
      static const InterruptNumber_t OTG_FS_WKUP = 42; ///< USB OTG FS WakeUp from suspend through EXTI Line Interrupt
      static const InterruptNumber_t TIM5 = 50; ///< TIM5 global Interrupt
      static const InterruptNumber_t SPI3 = 51; ///< SPI3 global Interrupt
      static const InterruptNumber_t UART4 = 52; ///< UART4 global Interrupt
      static const InterruptNumber_t UART5 = 53; ///< UART5 global Interrupt
      static const InterruptNumber_t TIM6 = 54; ///< TIM6 global Interrupt
      static const InterruptNumber_t TIM7 = 55; ///< TIM7 global Interrupt
      static const InterruptNumber_t DMA2_Channel1 = 56; ///< DMA2 Channel 1 global Interrupt
      static const InterruptNumber_t DMA2_Channel2 = 57; ///< DMA2 Channel 2 global Interrupt
      static const InterruptNumber_t DMA2_Channel3 = 58; ///< DMA2 Channel 3 global Interrupt
      static const InterruptNumber_t DMA2_Channel4 = 59; ///< DMA2 Channel 4 global Interrupt
      static const InterruptNumber_t DMA2_Channel5 = 60; ///< DMA2 Channel 5 global Interrupt
      static const InterruptNumber_t ETH = 61; ///< Ethernet global Interrupt
      static const InterruptNumber_t ETH_WKUP = 62; ///< Ethernet Wakeup through EXTI line Interrupt
      static const InterruptNumber_t CAN2_TX = 63; ///< CAN2 TX Interrupt
      static const InterruptNumber_t CAN2_RX0 = 64; ///< CAN2 RX0 Interrupt
      static const InterruptNumber_t CAN2_RX1 = 65; ///< CAN2 RX1 Interrupt
      static const InterruptNumber_t CAN2_SCE = 66; ///< CAN2 SCE Interrupt
      static const InterruptNumber_t OTG_FS = 67; ///< USB OTG FS global Interrupt

      /// @}

    };
  }
}

namespace hal
{
  namespace stm32f
  {

#if defined(STM32F10X_LD)

    /// \ingroup stm32f
    ///
    /// \brief Current family interrupt numbers
    typedef hal::stm32f10xld::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_LD_VL)

    /// \ingroup stm32f
    ///
    /// \brief Current family interrupt numbers
    typedef hal::stm32f10xldvl::InterruptNumber InterruptNumber;

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)

    /// \ingroup stm32f
    ///
    /// \brief Current family interrupt numbers
    typedef hal::stm32f10xmd::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_MD_VL)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f10xmdvl::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_HD)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f10xhd::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_HD_VL)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f10xhdvl::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_XL)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f10xxl::InterruptNumber InterruptNumber;

#elif defined(STM32F10X_CL)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f10xcl::InterruptNumber InterruptNumber;

#elif defined(__DOXYGEN__)

  /// \ingroup stm32f
  ///
  /// \brief Current family interrupt numbers
  typedef hal::stm32f1::InterruptNumber InterruptNumber;

#else

#error "No specific STM32F device"

#endif

}
}

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_INTERRUPTNUMBERS_H_