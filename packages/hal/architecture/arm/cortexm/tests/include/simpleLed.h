//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F simple led declarations.

#include "portable/core/include/OS.h"

#include <stdint.h>

class Led
{
public:
  Led() = delete;

  static void
  powerUp(void);

  static void
  powerDown(void);

  static void
  turnOn(void);

  static void
  turnOff(void);
};

#if defined(OS_HAS_ACTIVELED)
#include "hal/platform/include/XCDL_LedsDefines.h"
#endif

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x_rcc.h"

#define DELAY_DURATION  2500000

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_rcc.h"

#define DELAY_DURATION  5000000

#endif

void
Delay(__IO uint32_t nCount);

