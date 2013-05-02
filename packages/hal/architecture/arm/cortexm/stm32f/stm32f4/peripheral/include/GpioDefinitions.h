//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 GPIO memory mapped registers & definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIODEFINITIONS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIODEFINITIONS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/FamilyDefinitions.h"

namespace hal
{
  namespace stm32f4
  {
    namespace gpio
    {
      typedef unsigned int portNumber_t;
      typedef unsigned int bitNumber_t;
      typedef unsigned int index_t;

      // ======================================================================

      // ----- Port memory mapped registers -----------------------------------

      class PortRegisters
      {
      public:
        // --------------------------------------------------------------------

        //const static address_t MEMORY_BASE = hal::stm32f4::PeripheralAddressMap::GPIO;
        static const address_t MEMORY_BASE = 0x40020000UL;
        static const address_t MEMORY_OFFSET = 0x0400;

        PortRegisters() = delete;

        // ----- Memory map ---------------------------------------------------

        regReadWrite_t moder; // 0x0000
        regReadWrite_t otyper; // 0x0004
        regReadWrite_t ospeedr; // 0x0008
        regReadWrite_t pupdr; // 0x000C
        regReadOnly_t idr; // 0x0010
        regReadWrite_t odr; // 0x0014
        regWriteOnly_t bssr; // 0x0018
        regReadWrite_t lckr; // 0x001C
        regReadWrite_t afr[2]; // 0x0020-24

        // ----- Member functions ---------------------------------------------

        // 2 bits / pin
        reg32_t
        readMode(void);

        void
        writeMode(const reg32_t value);

        // 1 bit / pin
        reg16_t
        readOutputType(void);

        void
        writeOutputType(const reg16_t value);

        // 2 bits / pin
        reg32_t
        readOutputSpeed(void);

        void
        writeOutputSpeed(const reg32_t value);

        // 2 bits / pin
        reg32_t
        readPullUpPullDown(void);

        void
        writePullUpPullDown(const reg32_t value);

        // 1 bit / pin
        reg16_t
        readInputData(void);

        // 1 bit / pin
        reg16_t
        readOutputData(void);

        void
        writeOutputData(const reg16_t value);

        void
        writeSetReset(const reg32_t value);

        reg32_t
        readConfigurationLock(void);

        void
        writeConfigurationLock(reg32_t value);

        reg32_t
        readAlternateFunction(index_t index);

        void
        writeAlternateFunction(index_t index, reg32_t value);
      };

      // ----- Inline member function definitions -----------------------------

      reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readMode(void)
      {
        return this->moder;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeMode(const reg32_t value)
      {
        this->moder = value;
      }

      // 1 bit / pin
      reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputType(void)
      {
        return this->odr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputType(const reg16_t value)
      {
        this->odr = value;
      }

      // 2 bits / pin
      reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputSpeed(void)
      {
        return this->ospeedr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputSpeed(const reg32_t value)
      {
        this->ospeedr = value;
      }

      // 2 bits / pin
      reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readPullUpPullDown(void)
      {
        return this->pupdr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writePullUpPullDown(const reg32_t value)
      {
        this->pupdr = value;
      }

      // 1 bit / pin
      reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readInputData(void)
      {
        return this->idr;
      }

      // 1 bit / pin
      reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputData(void)
      {
        return this->odr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputData(const reg16_t value)
      {
        this->odr = value;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeSetReset(const reg32_t value)
      {
        this->bssr = value;
      }

      reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readConfigurationLock(void)
      {
        return this->lckr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeConfigurationLock(reg32_t value)
      {
        this->lckr = value;
      }

      reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readAlternateFunction(index_t index)
      {
        return this->afr[index];
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeAlternateFunction(index_t index, reg32_t value)
      {
        this->afr[index] = value;
      }

    // ========================================================================
    }// namespace gpio
  } // namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIODEFINITIONS_H_
