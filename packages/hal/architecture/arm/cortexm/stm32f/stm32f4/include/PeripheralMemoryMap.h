//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 peripheral memory map.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERALMEMORYMAP_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERALMEMORYMAP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace stm32f4
  {
    // ------------------------------------------------------------------------

    /// \ingroup stm32f4
    /// \headerfile PeripheralMemoryMap.h "hal/architecture/arm/cortexm/stm32f4/include/PeripheralMemoryMap.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F4 family peripheral memory map.

    class PeripheralMemoryMap
    {
    public:
      /// FLASH(up to 1 MB) base address in the alias region
      static const hal::cortexm::address_t FLASH_BASE_ADDRESS =
          ((uint32_t) 0x08000000UL);

      /// CCM(core coupled memory) data RAM(64 KB) base address in the alias region
      static const hal::cortexm::address_t CCMDATARAM_BASE_ADDRESS =
          ((uint32_t) 0x10000000UL);

      /// SRAM1(112 KB) base address in the alias region
      static const hal::cortexm::address_t SRAM1_BASE_ADDRESS =
          ((uint32_t) 0x20000000UL);

      /// SRAM2(16 KB) base address in the alias region
      static const hal::cortexm::address_t SRAM2_BASE_ADDRESS =
          ((uint32_t) 0x2001C000UL);
      /// SRAM3(64 KB) base address in the alias region
      static const hal::cortexm::address_t SRAM3_BASE_ADDRESS =
          ((uint32_t) 0x20020000UL);
      /// Peripheral base address in the alias region
      static const hal::cortexm::address_t PERIPH_BASE_ADDRESS =
          ((uint32_t) 0x40000000UL);
      /// Backup SRAM(4 KB) base address in the alias region
      static const hal::cortexm::address_t BKPSRAM_BASE_ADDRESS =
          ((uint32_t) 0x40024000UL);
      /// FSMC registers base address
      static const hal::cortexm::address_t FSMC_R_BASE_ADDRESS =
          ((uint32_t) 0xA0000000UL);

      /// CCM(core coupled memory) data RAM(64 KB) base address in the bit-band region
      static const hal::cortexm::address_t CCMDATARAM_BB_BASE_ADDRESS =
          ((uint32_t) 0x12000000UL);
      /// SRAM1(112 KB) base address in the bit-band region
      static const hal::cortexm::address_t SRAM1_BB_BASE_ADDRESS =
          ((uint32_t) 0x22000000UL);
      /// SRAM2(16 KB) base address in the bit-band region
      static const hal::cortexm::address_t SRAM2_BB_BASE_ADDRESS =
          ((uint32_t) 0x2201C000UL);
      /// SRAM3(64 KB) base address in the bit-band region
      static const hal::cortexm::address_t SRAM3_BB_BASE_ADDRESS =
          ((uint32_t) 0x22020000UL);
      /// Peripheral base address in the bit-band region
      static const hal::cortexm::address_t PERIPH_BB_BASE_ADDRESS =
          ((uint32_t) 0x42000000UL);
      /// Backup SRAM(4 KB) base address in the bit-band region
      static const hal::cortexm::address_t BKPSRAM_BB_BASE_ADDRESS =
          ((uint32_t) 0x42024000UL);

      /* Legacy defines */
      static const hal::cortexm::address_t SRAM_BASE_ADDRESS = SRAM1_BASE_ADDRESS;
      static const hal::cortexm::address_t SRAM_BB_BASE_ADDRESS = SRAM1_BB_BASE_ADDRESS;

      /// Peripheral memory map */
      static const hal::cortexm::address_t APB1PERIPH_BASE_ADDRESS = PERIPH_BASE_ADDRESS;
      static const hal::cortexm::address_t APB2PERIPH_BASE_ADDRESS = (PERIPH_BASE_ADDRESS
          + 0x00010000UL);
      static const hal::cortexm::address_t AHB1PERIPH_BASE_ADDRESS = (PERIPH_BASE_ADDRESS
          + 0x00020000UL);
      static const hal::cortexm::address_t AHB2PERIPH_BASE_ADDRESS = (PERIPH_BASE_ADDRESS
          + 0x10000000UL);

      // APB1 peripherals
      static const hal::cortexm::address_t TIM2_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x0000UL);
      static const hal::cortexm::address_t TIM3_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x0400UL);
      static const hal::cortexm::address_t TIM4_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x0800UL);
      static const hal::cortexm::address_t TIM5_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x0C00UL);
      static const hal::cortexm::address_t TIM6_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x1000UL);
      static const hal::cortexm::address_t TIM7_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x1400UL);
      static const hal::cortexm::address_t TIM12_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x1800UL);
      static const hal::cortexm::address_t TIM13_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x1C00UL);
      static const hal::cortexm::address_t TIM14_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x2000UL);
      static const hal::cortexm::address_t RTC_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x2800UL);
      static const hal::cortexm::address_t WWDG_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x2C00UL);
      static const hal::cortexm::address_t IWDG_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x3000UL);
      static const hal::cortexm::address_t I2S2ext_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x3400UL);
      static const hal::cortexm::address_t SPI2_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x3800UL);
      static const hal::cortexm::address_t SPI3_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x3C00UL);
      static const hal::cortexm::address_t I2S3ext_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x4000UL);
      static const hal::cortexm::address_t USART2_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x4400UL);
      static const hal::cortexm::address_t USART3_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x4800UL);
      static const hal::cortexm::address_t UART4_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x4C00UL);
      static const hal::cortexm::address_t UART5_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x5000UL);
      static const hal::cortexm::address_t I2C1_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x5400UL);
      static const hal::cortexm::address_t I2C2_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x5800UL);
      static const hal::cortexm::address_t I2C3_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x5C00UL);
      static const hal::cortexm::address_t CAN1_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x6400UL);
      static const hal::cortexm::address_t CAN2_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x6800UL);
      static const hal::cortexm::address_t PWR_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x7000UL);
      static const hal::cortexm::address_t DAC_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x7400UL);
      static const hal::cortexm::address_t UART7_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x7800UL);
      static const hal::cortexm::address_t UART8_BASE_ADDRESS = (APB1PERIPH_BASE_ADDRESS
          + 0x7C00UL);

      // APB2 peripherals
      static const hal::cortexm::address_t TIM1_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x0000UL);
      static const hal::cortexm::address_t TIM8_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x0400UL);
      static const hal::cortexm::address_t USART1_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x1000UL);
      static const hal::cortexm::address_t USART6_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x1400UL);
      static const hal::cortexm::address_t ADC1_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x2000UL);
      static const hal::cortexm::address_t ADC2_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x2100UL);
      static const hal::cortexm::address_t ADC3_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x2200UL);
      static const hal::cortexm::address_t ADC_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x2300UL);
      static const hal::cortexm::address_t SDIO_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x2C00UL);
      static const hal::cortexm::address_t SPI1_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x3000UL);
      static const hal::cortexm::address_t SPI4_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x3400UL);
      static const hal::cortexm::address_t SYSCFG_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x3800UL);
      static const hal::cortexm::address_t EXTI_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x3C00UL);
      static const hal::cortexm::address_t TIM9_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x4000UL);
      static const hal::cortexm::address_t TIM10_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x4400UL);
      static const hal::cortexm::address_t TIM11_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x4800UL);
      static const hal::cortexm::address_t SPI5_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x5000UL);
      static const hal::cortexm::address_t SPI6_BASE_ADDRESS = (APB2PERIPH_BASE_ADDRESS
          + 0x5400UL);

      // AHB1 peripherals
      static const hal::cortexm::address_t GPIOA_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x0000UL);
      static const hal::cortexm::address_t GPIOB_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x0400UL);
      static const hal::cortexm::address_t GPIOC_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x0800UL);
      static const hal::cortexm::address_t GPIOD_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x0C00UL);
      static const hal::cortexm::address_t GPIOE_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x1000UL);
      static const hal::cortexm::address_t GPIOF_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x1400UL);
      static const hal::cortexm::address_t GPIOG_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x1800UL);
      static const hal::cortexm::address_t GPIOH_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x1C00UL);
      static const hal::cortexm::address_t GPIOI_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x2000UL);
      static const hal::cortexm::address_t GPIO_OFFSET = GPIOB_BASE_ADDRESS
          - GPIOA_BASE_ADDRESS;

      static const hal::cortexm::address_t CRC_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x3000UL);
      static const hal::cortexm::address_t RCC_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x3800UL);
      static const hal::cortexm::address_t FLASH_R_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x3C00UL);
      static const hal::cortexm::address_t DMA1_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x6000UL);
      static const hal::cortexm::address_t DMA1_Stream0_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x010UL);
      static const hal::cortexm::address_t DMA1_Stream1_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x028);
      static const hal::cortexm::address_t DMA1_Stream2_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x040UL);
      static const hal::cortexm::address_t DMA1_Stream3_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x058);
      static const hal::cortexm::address_t DMA1_Stream4_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x070UL);
      static const hal::cortexm::address_t DMA1_Stream5_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x088);
      static const hal::cortexm::address_t DMA1_Stream6_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x0A0UL);
      static const hal::cortexm::address_t DMA1_Stream7_BASE_ADDRESS = (DMA1_BASE_ADDRESS
          + 0x0B8);
      static const hal::cortexm::address_t DMA2_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x6400UL);
      static const hal::cortexm::address_t DMA2_Stream0_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x010UL);
      static const hal::cortexm::address_t DMA2_Stream1_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x028);
      static const hal::cortexm::address_t DMA2_Stream2_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x040UL);
      static const hal::cortexm::address_t DMA2_Stream3_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x058UL);
      static const hal::cortexm::address_t DMA2_Stream4_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x070UL);
      static const hal::cortexm::address_t DMA2_Stream5_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x088);
      static const hal::cortexm::address_t DMA2_Stream6_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x0A0UL);
      static const hal::cortexm::address_t DMA2_Stream7_BASE_ADDRESS = (DMA2_BASE_ADDRESS
          + 0x0B8UL);
      static const hal::cortexm::address_t ETH_BASE_ADDRESS = (AHB1PERIPH_BASE_ADDRESS
          + 0x8000UL);
      static const hal::cortexm::address_t ETH_MAC_BASE_ADDRESS = (ETH_BASE_ADDRESS);
      static const hal::cortexm::address_t ETH_MMC_BASE_ADDRESS = (ETH_BASE_ADDRESS + 0x0100UL);
      static const hal::cortexm::address_t ETH_PTP_BASE_ADDRESS = (ETH_BASE_ADDRESS + 0x0700UL);
      static const hal::cortexm::address_t ETH_DMA_BASE_ADDRESS = (ETH_BASE_ADDRESS + 0x1000UL);

      // AHB2 peripherals
      static const hal::cortexm::address_t DCMI_BASE_ADDRESS = (AHB2PERIPH_BASE_ADDRESS
          + 0x50000UL);
      static const hal::cortexm::address_t CRYP_BASE_ADDRESS = (AHB2PERIPH_BASE_ADDRESS
          + 0x60000UL);
      static const hal::cortexm::address_t HASH_BASE_ADDRESS = (AHB2PERIPH_BASE_ADDRESS
          + 0x60400UL);
      static const hal::cortexm::address_t HASH_DIGEST_BASE_ADDRESS = (AHB2PERIPH_BASE_ADDRESS
          + 0x60710UL);
      static const hal::cortexm::address_t RNG_BASE_ADDRESS = (AHB2PERIPH_BASE_ADDRESS
          + 0x60800UL);

      // FSMC Bankx registers base address
      static const hal::cortexm::address_t FSMC_Bank1_R_BASE_ADDRESS = (FSMC_R_BASE_ADDRESS
          + 0x0000UL);
      static const hal::cortexm::address_t FSMC_Bank1E_R_BASE_ADDRESS = (FSMC_R_BASE_ADDRESS
          + 0x0104UL);
      static const hal::cortexm::address_t FSMC_Bank2_R_BASE_ADDRESS = (FSMC_R_BASE_ADDRESS
          + 0x0060UL);
      static const hal::cortexm::address_t FSMC_Bank3_R_BASE_ADDRESS = (FSMC_R_BASE_ADDRESS
          + 0x0080UL);
      static const hal::cortexm::address_t FSMC_Bank4_R_BASE_ADDRESS = (FSMC_R_BASE_ADDRESS
          + 0x00A0UL);

      // Debug MCU registers base address
      static const hal::cortexm::address_t DBGMCU_BASE_ADDRESS =
          ((uint32_t) 0xE0042000UL);

    };

  } // namespace stm32f4

// --------------------------------------------------------------------------
}

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F4
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERALMEMORYMAP_H_
