//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F CMSIS simple test.

#include "portable/core/include/OS.h"

#if defined(OS_INCLUDE_HAL_MCU_DEVICE_STM32F103RB)
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_rcc.h"
#endif
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/include/InterruptNumbersSelector.h"

void
Delay(__IO uint32_t nCount);


int
main()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif


  /* At this stage the microcontroller clock setting is already configured,
   this is done through SystemInit() function which is called from startup
   file (startup_stm32f10x_xx.s) before to branch to application main.
   To reconfigure the default setting of SystemInit() function, refer to
   system_stm32f10x.c file
   */

  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

#define DELAY_DURATION  5000000
#define CYCLES  60

  for (int i=CYCLES; --i; )
    {
      // Set PC12 high (turn of led)
      GPIOC ->BSRR = GPIO_Pin_12;

      Delay(DELAY_DURATION);
      // Reset PC12 low (turn on led)
      GPIOC ->BRR = GPIO_Pin_12;

      Delay(DELAY_DURATION);

#if defined(DEBUG)
  os::diag::trace.putChar('*');
#endif

    }

#if defined(DEBUG)
  os::diag::trace.putString(" done");
  os::diag::trace.putNewLine();
#endif

  return 0;
}

/**
 * @brief  Inserts a delay time.
 * @param  nCount: specifies the delay time length.
 * @retval None
 */
void
Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--)
    ;
}

