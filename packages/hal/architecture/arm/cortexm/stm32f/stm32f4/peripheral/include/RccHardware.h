//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 Reset and Clock Control memory mapped registers & definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCCHARDWARE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCCHARDWARE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/peripheral/include/BitBanding.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/PeripheralMemoryMap.h"

namespace hal
{
  namespace stm32f4
  {
    namespace rcc
    {

      typedef hal::cortexm::portNumber_t portNumber_t;
      typedef hal::cortexm::bitNumber_t bitNumber_t;
      typedef hal::cortexm::index_t index_t;

      typedef hal::cortexm::bitband::bitValue_t bitValue_t;
      typedef hal::cortexm::reg16_t reg16_t;
      typedef hal::cortexm::reg32_t reg32_t;
    }

    // Forward declaration, to help find friends.
    template<hal::cortexm::address_t A_T>
      class TRcc;

    namespace rcc
    {
      /// \addtogroup stm32f4_rcc
      /// @{

      // ----------------------------------------------------------------------

      /// \brief AHB1 peripheral number type definition.
      typedef uint32_t Ahb1Peripheral_t;

      /// \brief AHB1 peripheral numbers.
      ///
      /// \details
      /// Use this when calling AHB1 related calls.
      /// \par Example
      /// \code{.cpp}
      /// Rcc::enableAhb1PeripheralClock(rcc::Ahb1Peripheral::GpioA);
      /// \endcode
      enum class Ahb1Peripheral
        : Ahb1Peripheral_t
          {
            GpioA = 0,
        GpioB = 1,
        GpioC = 2,
        GpioD = 3,
        GpioE = 4,
        GpioF = 5,
        GpioH = 6,
        GpioI = 7,
        Crc = 12,
        BkpSram = 18,
        CcmDataRam = 20,
        Dma1 = 21,
        Dma2 = 22,
        EthMac = 25,
        EthMacTx = 26,
        EthMacRx = 27,
        EthMacPtp,
        OtgHs = 29,
        OtgHsUlpi = 30
      };

      // ----------------------------------------------------------------------

      /// \brief Reload register type.
      //typedef uint16_t reloadValue_t;

      // ----------------------------------------------------------------------

      /// @} end of addtogroup stm32f4_rcc

      // ======================================================================

      /// \headerfile RccHardware.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/RccHardware.h"
      /// \ingroup stm32f4_rcc
      /// \nosubgrouping
      ///
      /// \brief RCC memory mapped registers.
      ///
      /// \warning This class is packed and mapped over a specific memory
      ///       area. DO NOT change the members order or add new data members.
      class __attribute__((packed)) Registers
      {
      public:
        // --------------------------------------------------------------------

        /// \name Constructors/destructor
        /// @{

        /// \brief Deleted constructor
        Registers() = delete;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Write the AHB1 peripheral clock register.
        ///
        /// \param [in] value A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeAhb1PeripheralClockEnable(const reg32_t value);

        /// \brief Read the AHB1 peripheral clock register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 32-bit mask.
        reg32_t
        readAhb1PeripheralClockEnable(void);

        /// @} end of Public member functions

        /// \name Memory definitions
        /// @{

        /// \brief Base address of the device.
        static const hal::cortexm::address_t MEMORY_BASE_ADDRESS =
            PeripheralMemoryMap::RCC_BASE_ADDRESS;

        /// @} end of name Memory definitions

      private:
        // The TRcc class template needs to take the addresses of some registers
        // for bit-band operations.
        template<hal::cortexm::address_t A_T>
          friend class hal::stm32f4::TRcc;

        /// \name Private memory mapped registers
        /// @{

        /// \brief 0x0000 - Clock control register.
        hal::cortexm::regReadWrite_t cr;
        /// \brief 0x0004 - PLL configuration register.
        hal::cortexm::regReadWrite_t pllcfgr;
        /// \brief 0x0008 - clock configuration register.
        hal::cortexm::regReadWrite_t cfgr;
        /// \brief 0x000C - clock interrupt register.
        hal::cortexm::regReadWrite_t cir;
        /// \brief 0x0010 - AHB1 peripheral reset register.
        hal::cortexm::regReadWrite_t ahb1rstr;
        /// \brief 0x0014 - AHB2 peripheral reset register.
        hal::cortexm::regReadWrite_t ahb2rstr;
        /// \brief 0x0018 - AHB3 peripheral reset register.
        hal::cortexm::regReadWrite_t ahb3rstr;
        /// \brief 0x001C - reserved.
        hal::cortexm::regReadWrite_t reserved0;
        /// \brief 0x0020 - APB1 peripheral reset register.
        hal::cortexm::regReadWrite_t apb1rstr;
        /// \brief 0x0024 - APB2 peripheral reset register.
        hal::cortexm::regReadWrite_t apb2rstr;
        /// \brief 0x0028-0x002C - reserved.
        hal::cortexm::regReadWrite_t reserved1[2];
        /// \brief 0x0030 - AHB1 peripheral clock register.
        hal::cortexm::regReadWrite_t ahb1enr;
        /// \brief 0x0034 - AHB1 peripheral clock register.
        hal::cortexm::regReadWrite_t ahb2enr;
        /// \brief 0x0038 - AHB2 peripheral clock register.
        hal::cortexm::regReadWrite_t ahb3enr;
        /// \brief 0x003C - AHB3 peripheral clock reserved.
        hal::cortexm::regReadWrite_t reserved2;
        /// \brief 0x0040 - APB1 peripheral clock enable register.
        hal::cortexm::regReadWrite_t apb1enr;
        /// \brief 0x0044 - APB2 peripheral clock enable register.
        hal::cortexm::regReadWrite_t apb2enr;
        /// \brief 0x0048-0x004C - reserved.
        hal::cortexm::regReadWrite_t reserved3[2];
        /// \brief 0x0050 - AHB1 peripheral clock enable in low power mode register.
        hal::cortexm::regReadWrite_t ahb1lpenr;
        /// \brief 0x0054 - AHB2 peripheral clock enable in low power mode register.
        hal::cortexm::regReadWrite_t ahb2lpenr;
        /// \brief 0x0058 - AHB3 peripheral clock enable in low power mode register.
        hal::cortexm::regReadWrite_t ahb3lpenr;
        /// \brief 0x005C - reserved.
        hal::cortexm::regReadWrite_t reserved4;
        /// \brief 0x0060 - APB1 peripheral clock enable in low power mode register.
        hal::cortexm::regReadWrite_t apb1lpenr;
        /// \brief 0x0064 - APB2 peripheral clock enable in low power mode register.
        hal::cortexm::regReadWrite_t apb2lpenr;
        /// \brief 0x0068-0x006C - reserved.
        hal::cortexm::regReadWrite_t reserved5[2];
        /// \brief 0x0070 - Backup domain control register.
        hal::cortexm::regReadWrite_t bdcr;
        /// \brief 0x0074 - clock control & status register.
        hal::cortexm::regReadWrite_t csr;
        /// \brief 0x0078-0x007C - reserved.
        hal::cortexm::regReadWrite_t reserved6[2];
        /// \brief 0x0080 - spread spectrum clock generation register.
        hal::cortexm::regReadWrite_t sscgr;
        /// \brief 0x0084 - PLLI2S configuration register.
        hal::cortexm::regReadWrite_t plli2scfgr;
#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F427X) || defined(__DOXYGEN__)
        /// \brief 0x0088 - reserved.
        hal::cortexm::regReadWrite_t reserved7;
        /// \brief 0x008C - Dedicated Clocks configuration register.
        hal::cortexm::regReadWrite_t dckcfgr;
#endif

        /// @} end of name Memory mapped registers

      };

      // ----- Inline member function definitions -----------------------------

      inline void
      __attribute__((always_inline))
      Registers::writeAhb1PeripheralClockEnable(const reg32_t value)
      {
        this->ahb1enr = value;
      }

      inline reg32_t
      __attribute__((always_inline))
      Registers::readAhb1PeripheralClockEnable(void)
      {
        return this->ahb1enr;
      }

    // ========================================================================
    }// namespace rcc
  } // namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCCHARDWARE_H_
