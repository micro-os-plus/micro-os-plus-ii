//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F CMSIS simple led definitions.

#include "portable/core/include/OS.h"

#include "../include/simpleLed.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)

#define LED_PORT_ADDRESS        (GPIOA_BASE + 0x0400*OS_INTEGER_ACTIVELED_PORT)
#define LED_PORT_POINTER        ((GPIO_TypeDef *) LED_PORT_ADDRESS)
#define LED_GPIO_PIN            ((uint16_t)(1 << OS_INTEGER_ACTIVELED_BIT))

void
Led::powerUp(void)
{
  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA << OS_INTEGER_ACTIVELED_PORT,
      ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in output push/pull mode */
  GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LED_PORT_POINTER, &GPIO_InitStructure);
}

void
Led::powerDown(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in input mode */
  GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LED_PORT_POINTER, &GPIO_InitStructure);

  // DO NOT disable clock, other devices may still need it
}

void
Led::turnOn(void)
{
#if OS_BOOL_ACTIVELED_ISACTIVELOW
    // Reset pin low
    LED_PORT_POINTER ->BRR = LED_GPIO_PIN;
#else
    // Set pin high
    LED_PORT_POINTER ->BSRR = LED_GPIO_PIN;
#endif

}

void
Led::turnOff(void)
{
#if OS_BOOL_ACTIVELED_ISACTIVELOW
    // Set pin high
    LED_PORT_POINTER ->BSRR = LED_GPIO_PIN;
#else
    // Reset pin low
    LED_PORT_POINTER ->BRR = LED_GPIO_PIN;
#endif
}

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)

#define LED_PORT_ADDRESS        (GPIOA_BASE + 0x0400*OS_INTEGER_ACTIVELED_PORT)
#define LED_PORT_POINTER        ((GPIO_TypeDef *) LED_PORT_ADDRESS)
#define LED_GPIO_PIN            ((uint16_t)(1 << OS_INTEGER_ACTIVELED_BIT))

void
Led::powerUp(void)
  {
    /* GPIO bus clock enable */
    RCC_AHB1PeriphClockCmd(
        (RCC_AHB1Periph_GPIOA << OS_INTEGER_ACTIVELED_PORT), ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC13 in output push/pull mode */
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(LED_PORT_POINTER, &GPIO_InitStructure);
  }

void
Led::turnOn(void)
  {
#if OS_BOOL_ACTIVELED_ISACTIVELOW
    // Reset pin low
    LED_PORT_POINTER ->BSRRH = LED_GPIO_PIN;
#else
    // Set pin high
    LED_PORT_POINTER ->BSRRL = LED_GPIO_PIN;
#endif
  }

void
Led::turnOff(void)
  {
#if OS_BOOL_ACTIVELED_ISACTIVELOW
    // Set pin high
    LED_PORT_POINTER ->BSRRL = LED_GPIO_PIN;
#else
    // Reset pin low
    LED_PORT_POINTER ->BSRRH = LED_GPIO_PIN;
#endif
  }

void
Led::powerDown(void)
  {
    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure pin in input mode
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(LED_PORT_POINTER, &GPIO_InitStructure);
  }

#endif

void
Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--)
    ;
}
