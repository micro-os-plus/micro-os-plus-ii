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

template class hal::stm32f4::TGpio<1, 2>;
typedef class hal::stm32f4::TGpio<1, 2> GPIOBp2;

#endif

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

  // Template implementation
  GPIOBp2 pin1;
  pin1.setPinHigh();
  pin1.setPinLow();

  Led::turnOn(); // separator

  // Dynamic object with constant port and bit definitions
  hal::stm32f4::Gpio pin2(1, 2);

  pin2.configureMode(hal::stm32f4::gpio::Mode::GeneralPurposeOutput);

  __NOP();
  pin2.configureOutputType(hal::stm32f4::gpio::OutputType::OpenDrain);

  __NOP();
  pin2.configureOutputSpeed(hal::stm32f4::gpio::OutputSpeed::HighSpeed_100MHz);

  __NOP();
  pin2.configureOutputSpeed(hal::stm32f4::gpio::OutputSpeed::HighSpeed_100MHz);

  __NOP();
  pin2.setPinHigh();
  __NOP();
  pin2.setPinLow();

  __NOP();
  pin2.togglePin();

  __NOP();
  if (pin2.isPinHigh())
    {
      __NOP(); // separator
    }
  Led::turnOn(); // separator

  // Dynamic object with variable input
  volatile int xp = 1;
  volatile int xb = 2;
  hal::stm32f4::Gpio pin3(xp, xb);

  pin3.setPinHigh();
  pin3.setPinLow();

  Led::turnOn(); // separator


#endif

  for (int i = CYCLES; --i;)
    {

      Led::turnOn();

      Delay(DELAY_DURATION);

      Led::turnOff();

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

