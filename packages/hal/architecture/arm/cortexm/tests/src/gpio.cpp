//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F GPIO simple test.

#include "portable/core/include/OS.h"

#include "../include/simpleLed.h"

#include "hal/architecture/include/InterruptNumbers.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Gpio.h"

#if defined(OS_INCLUDE_HAL_BOARD_STM_STM32F4DISCOVERY)

#define XPORT 3
#define XBIT 13

#endif

template class hal::stm32f4::TGpioPin<XPORT, XBIT>;
typedef class hal::stm32f4::TGpioPin<XPORT, XBIT> XGPIO;

//typedef class hal::stm32f4::TGpioPort<XPORT> GPIOX;

#endif

hal::stm32f4::GpioPin pinS(XPORT, XBIT);

int
main()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  Led::powerUp();
  Led::turnOn();

#define CYCLES  60

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)

  // Dynamic object with constant port and bit definitions
  hal::stm32f4::GpioPin pin1(XPORT, XBIT);

#if defined(DEBUG)
  os::diag::trace << os::std::setfill('0');
  os::diag::trace << "MODER=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readMode() << os::std::endl;
#endif

  pin1.configureMode(hal::stm32f4::gpio::Mode::Output);

#if defined(DEBUG)
  os::diag::trace << "MODER=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readMode() << os::std::endl;
#endif

#if defined(DEBUG)
  os::diag::trace << "OTYPER=" << os::std::hex << os::std::setw(4)
  << pin1.getPortRegisters().readOutputType() << os::std::endl;
#endif

  __NOP();
  pin1.configureOutputType(hal::stm32f4::gpio::OutputType::OpenDrain);

#if defined(DEBUG)
  os::diag::trace << "OTYPER=" << os::std::hex << os::std::setw(4)
  << pin1.getPortRegisters().readOutputType() << os::std::endl;
#endif

#if defined(DEBUG)
  os::diag::trace << "OSPEEDER=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readOutputSpeed() << os::std::endl;
#endif

  __NOP();
  pin1.configureOutputSpeed(hal::stm32f4::gpio::OutputSpeed::High_100MHz);

#if defined(DEBUG)
  os::diag::trace << "OSPEEDER=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readOutputSpeed() << os::std::endl;
#endif

#if defined(DEBUG)
  os::diag::trace << "PUPDR=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readPullUpPullDown() << os::std::endl;
#endif

  __NOP();
  pin1.configurePullUpPullDown(hal::stm32f4::gpio::Resistors::PullUp);

#if defined(DEBUG)
  os::diag::trace << "PUPDR=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readPullUpPullDown() << os::std::endl;
#endif

#if defined(DEBUG)
  os::diag::trace << "AFR[0]=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readAlternateFunction(0) << " AFR[1]="
  << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readAlternateFunction(1) << os::std::endl;
#endif

  __NOP();
  pin1.configureAlternateFunction(hal::stm32f4::gpio::AlternateFunction::AF1);

#if defined(DEBUG)
  os::diag::trace << "AFR[0]=" << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readAlternateFunction(0) << " AFR[1]="
  << os::std::hex << os::std::setw(8)
  << pin1.getPortRegisters().readAlternateFunction(1) << os::std::endl;
#endif

#if defined(DEBUG)
  os::diag::trace << "ODR=" << os::std::hex << os::std::setw(4)
  << pin1.getPortRegisters().readOutputData() << os::std::endl;
#endif

  __NOP();
  pin1.setPinHigh();

#if defined(DEBUG)
  os::diag::trace << "ODR=" << os::std::hex << os::std::setw(4)
  << pin1.getPortRegisters().readOutputData() << os::std::endl;
#endif

  __NOP();
  pin1.setPinLow();

#if defined(DEBUG)
  os::diag::trace << "ODR=" << os::std::hex
  << pin1.getPortRegisters().readOutputData() << os::std::endl;
#endif

  __NOP();
  pin1.togglePin();

#if defined(DEBUG)
  os::diag::trace << "ODR=" << os::std::hex << os::std::setw(4)
  << pin1.getPortRegisters().readOutputData() << os::std::endl;
#endif

  __NOP();
  if (pin1.isPinHigh())
    {
      __NOP(); // separator
    }

  Led::turnOn(); // separator

  // Dynamic object with variable input
  volatile int xp = XPORT;
  volatile int xb = XBIT;
  hal::stm32f4::GpioPin pin2(xp, xb);

  pin2.setPinHigh();
  pin2.setPinLow();

  Led::turnOn(); // separator

  pinS.setPinHigh();
  pinS.setPinLow();

  Led::turnOn(); // separator

  // Template implementation
  __NOP();
  XGPIO pin3;
  __NOP();
  pin3.setPinHigh();
  __NOP();
  pin3.setPinLow();
  __NOP();

  Led::turnOn(); // separator

#endif

  for (int i = CYCLES; --i;)
    {

      Led::turnOn();
      pin1.setPinHigh();

      Delay(DELAY_DURATION);

      Led::turnOff();
      pin1.setPinLow();

      Delay(DELAY_DURATION / 2);

#if defined(DEBUG)
      os::diag::trace.putChar('*');
#endif

    }

  Led::powerDown();

#if defined(DEBUG)
  os::diag::trace.putString(" done");
  os::diag::trace.putNewLine();
#endif

  return 0;
}

