//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F CMSIS simple test.

#include "portable/core/include/OS.h"

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

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x_rcc.h"

#define DELAY_DURATION  2500000

void
Led::powerUp(void)
{
  /* GPIOC Periph clock enable */
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in output push/pull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void
Led::powerDown(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in input mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // DO NOT disable clock, other devices may still need it
}

void
Led::turnOn(void)
{
  // Reset PC12 low (turn on led)
  GPIOC ->BRR = GPIO_Pin_12;
}

void
Led::turnOff(void)
{
  // Set PC12 high (turn off led)
  GPIOC ->BSRR = GPIO_Pin_12;
}

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_rcc.h"

#define DELAY_DURATION  5000000

void
Led::powerUp(void)
  {
    /* GPIOC Periph clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC13 in output push/pull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
  }

void
Led::turnOn(void)
  {
    // Reset PC13 low (turn on led)
    GPIOC ->BSRRH = GPIO_Pin_13;
  }

void
Led::turnOff(void)
  {
    // Set PC13 high (turn off led)
    GPIOC ->BSRRL = GPIO_Pin_13;
  }

void
Led::powerDown(void)
  {
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC13 in output push/pull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  }

#endif

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersSelector.h"

void
Delay(__IO uint32_t nCount);

void
Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--)
    ;
}

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

      Delay(DELAY_DURATION/2);

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


