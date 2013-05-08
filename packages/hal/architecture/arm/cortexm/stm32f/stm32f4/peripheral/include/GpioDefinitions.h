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

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace stm32f4
  {
    namespace gpio
    {
      typedef hal::cortexm::portNumber_t portNumber_t;
      typedef hal::cortexm::bitNumber_t bitNumber_t;
      typedef hal::cortexm::index_t index_t;

      typedef enum Mode
        : uint32_t
          {
            Input = 0, GeneralPurposeOutput = 1, Alternate = 2, Analog = 3
      } Mode_t;

      static const uint32_t MODE_MASK = 0x3;

      typedef enum OutputType
        : uint32_t
          {
            PushPull = 0, OpenDrain = 1
      } OutputType_t;

      typedef enum OutputSpeed
        : uint32_t
          {
            LowSpeed_2MHz = 0,
        MediumSpeed_25MHz = 1,
        FastSpeed_50MHz = 2,
        HighSpeed_100MHz = 3
      } OutputSpeed_t;

      static const uint32_t OUTPUT_SPEED_MASK = 0x3;

      typedef enum PullUpPullDown
        : uint32_t
          {
            None = 0, PullUp = 1, PullDown = 2
      } PullUpPullDown_t;

      static const uint32_t PULL_UP_PULL_DOWN_MASK = 0x3;

      typedef uint32_t alternateFunction_t;

      static const uint32_t ALTERNATE_FUNCTION_MASK = 0xF;

      // ======================================================================

      // ----- Port memory mapped registers -----------------------------------

      class PortRegisters
      {
      public:
        // --------------------------------------------------------------------

        //const static address_t MEMORY_BASE = hal::stm32f4::PeripheralAddressMap::GPIO;
        static const hal::cortexm::address_t MEMORY_BASE = 0x40020000UL;
        static const hal::cortexm::address_t MEMORY_OFFSET = 0x00000400UL;

        PortRegisters() = delete;

        // ----- Memory map ---------------------------------------------------

        hal::cortexm::regReadWrite_t moder; // 0x0000
        hal::cortexm::regReadWrite_t otyper; // 0x0004
        hal::cortexm::regReadWrite_t ospeedr; // 0x0008
        hal::cortexm::regReadWrite_t pupdr; // 0x000C
        hal::cortexm::regReadOnly_t idr; // 0x0010
        hal::cortexm::regReadWrite_t odr; // 0x0014
        hal::cortexm::regWriteOnly_t bssr; // 0x0018
        hal::cortexm::regReadWrite_t lckr; // 0x001C
        hal::cortexm::regReadWrite_t afr[2]; // 0x0020-24

        // ----- Member functions ---------------------------------------------

        // 2 bits / pin
        hal::cortexm::reg32_t
        readMode(void);

        void
        writeMode(const hal::cortexm::reg32_t value);

        // 1 bit / pin
        hal::cortexm::reg16_t
        readOutputType(void);

        void
        writeOutputType(const hal::cortexm::reg16_t value);

        // 2 bits / pin
        hal::cortexm::reg32_t
        readOutputSpeed(void);

        void
        writeOutputSpeed(const hal::cortexm::reg32_t value);

        // 2 bits / pin
        hal::cortexm::reg32_t
        readPullUpPullDown(void);

        void
        writePullUpPullDown(const hal::cortexm::reg32_t value);

        // 1 bit / pin
        hal::cortexm::reg16_t
        readInputData(void);

        // 1 bit / pin
        hal::cortexm::reg16_t
        readOutputData(void);

        void
        writeOutputData(const hal::cortexm::reg16_t value);

        void
        writeSetReset(const hal::cortexm::reg32_t value);

        hal::cortexm::reg32_t
        readConfigurationLock(void);

        void
        writeConfigurationLock(const hal::cortexm::reg32_t value);

        hal::cortexm::reg32_t
        readAlternateFunction(index_t index);

        void
        writeAlternateFunction(const index_t index,
            const hal::cortexm::reg32_t value);
      };

      // ----- Inline member function definitions -----------------------------

      hal::cortexm::reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readMode(void)
      {
        return this->moder;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeMode(const hal::cortexm::reg32_t value)
      {
        this->moder = value;
      }

      // 1 bit / pin
      hal::cortexm::reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputType(void)
      {
        return this->odr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputType(const hal::cortexm::reg16_t value)
      {
        this->odr = value;
      }

      // 2 bits / pin
      hal::cortexm::reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputSpeed(void)
      {
        return this->ospeedr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputSpeed(const hal::cortexm::reg32_t value)
      {
        this->ospeedr = value;
      }

      // 2 bits / pin
      hal::cortexm::reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readPullUpPullDown(void)
      {
        return this->pupdr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writePullUpPullDown(const hal::cortexm::reg32_t value)
      {
        this->pupdr = value;
      }

      // 1 bit / pin
      hal::cortexm::reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readInputData(void)
      {
        return this->idr;
      }

      // 1 bit / pin
      hal::cortexm::reg16_t
      inline __attribute__((always_inline))
      PortRegisters::readOutputData(void)
      {
        return this->odr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeOutputData(const hal::cortexm::reg16_t value)
      {
        this->odr = value;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeSetReset(const hal::cortexm::reg32_t value)
      {
        this->bssr = value;
      }

      hal::cortexm::reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readConfigurationLock(void)
      {
        return this->lckr;
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeConfigurationLock(const hal::cortexm::reg32_t value)
      {
        this->lckr = value;
      }

      hal::cortexm::reg32_t
      inline __attribute__((always_inline))
      PortRegisters::readAlternateFunction(const index_t index)
      {
        return this->afr[index];
      }

      void
      inline __attribute__((always_inline))
      PortRegisters::writeAlternateFunction(const index_t index,
          const hal::cortexm::reg32_t value)
      {
        this->afr[index] = value;
      }

    // ========================================================================
    }// namespace gpio
  } // namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIODEFINITIONS_H_