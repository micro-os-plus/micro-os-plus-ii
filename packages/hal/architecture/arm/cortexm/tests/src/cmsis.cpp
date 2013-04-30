//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F CMSIS simple test.

#include "portable/core/include/OS.h"

#include "../include/simpleLed.h"

#include "hal/architecture/include/InterruptNumbers.h"

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

