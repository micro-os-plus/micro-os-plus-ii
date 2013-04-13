//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/include/InterruptNumbersSelector.h"

#if defined(OS_INCLUDE_HAL_MCU_DEVICE_STM32F103RB)
#include "hal/architecture/arm/cortexm/stm32f/lib/cmsis/stm32f10x/include/stm32f10x.h"
#endif


int
main()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  return 0;
}

