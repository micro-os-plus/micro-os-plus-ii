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
#include "hal/architecture/arm/cortexm/peripheral/include/BitBand.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/MemoryMap.h"

namespace hal
{
  namespace stm32f4
  {
    namespace gpio
    {

      typedef hal::cortexm::portNumber_t portNumber_t;
      typedef hal::cortexm::bitNumber_t bitNumber_t;
      typedef hal::cortexm::index_t index_t;

      typedef hal::cortexm::bitband::bitValue_t bitValue_t;
      typedef hal::cortexm::reg16_t reg16_t;
      typedef hal::cortexm::reg32_t reg32_t;
    }

    // Forward declaration, to help find friends.
    class GpioPin;

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      class TGpioPin;

    namespace gpio
    {
      /// \addtogroup stm32f4_gpio
      /// @{

      // ----------------------------------------------------------------------

      typedef uint32_t mode_t;

      /// \brief Port modes (2 bits/pin).
      enum class Mode
        : mode_t
          {
            Input = 0, Output = 1, Alternate = 2, Analog = 3
      };

      /// \brief Mask to isolate the port mode bits.
      static const mode_t MODE_MASK = 0x3U;

      // ----------------------------------------------------------------------

      typedef uint32_t outputType_t;

      /// \brief Output type (1 bit/pin).
      enum class OutputType
        : outputType_t
          {
            PushPull = 0, OpenDrain = 1
      };

      // ----------------------------------------------------------------------

      typedef uint32_t outputSpeed_t;

      /// \brief Output Speed (2 bits/pin).
      enum class OutputSpeed
        : outputSpeed_t
          {
            Low_2MHz = 0, Medium_25MHz = 1, Fast_50MHz = 2, High_100MHz = 3
      };

      /// \brief Mask to isolate the port output speed bits.
      static const outputSpeed_t OUTPUT_SPEED_MASK = 0x3U;

      // ----------------------------------------------------------------------

      typedef uint32_t resistors_t;

      /// \brief Pull up/Pull down resistors (2 bits/pin).
      enum class Resistors
        : resistors_t
          {
            None = 0, PullUp = 1, PullDown = 2
      };

      /// \brief Mask to isolate the port pull up/pull down bits.
      static const resistors_t RESISTORS_MASK = 0x3U;

      // ----------------------------------------------------------------------

      typedef uint32_t alternateFunction_t;

      /// \brief Alternate functions (4 bits/pin).
      enum class AlternateFunction
        : alternateFunction_t
          {
            AF0 = 0,
        AF1,
        AF2,
        AF3,
        AF4,
        AF5,
        AF6,
        AF7,
        AF8,
        AF9,
        AF10,
        AF11,
        AF12,
        AF13,
        AF14,
        AF15
      };

      /// \brief Mask to isolate the alternate function bits.
      static const alternateFunction_t ALTERNATE_FUNCTION_MASK = 0xFU;

      /// @} end of addtogroup stm32f4_gpio

      // ======================================================================

      /// \headerfile GpioHardware.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/GpioHardware.h"
      /// \ingroup stm32f4_gpio
      /// \nosubgrouping
      ///
      /// \brief GPIO port memory mapped registers.
      ///
      /// \warning This class is packed and mapped over a specific port memory
      ///       area. DO NOT change the members order or add new data members.
      class __attribute__((packed)) PortRegisters
      {
      public:
        // --------------------------------------------------------------------

        /// \name Constructors/destructor
        /// @{

        /// \brief Deleted constructor
        PortRegisters() = delete;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        // 2 bits / pin
        /// \brief Read mode register.
        reg32_t
        readMode(void);

        /// \brief Write mode register.
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

        // 1 bit / pin, high part = reset, low part = set
        void
        writeSetReset(const reg32_t value);

        // 1 bit / pin + 1 global lock
        reg32_t
        readConfigurationLock(void);

        void
        writeConfigurationLock(const reg32_t value);

        // 4 bits / pin
        reg32_t
        readAlternateFunction(index_t index);

        void
        writeAlternateFunction(const index_t index, const reg32_t value);

        /// @} end of Public member functions

        /// \name Memory definitions
        /// @{

        /// \brief Base address of the first port.
        static const hal::cortexm::address_t MEMORY_BASE =
            MemoryMap::GPIOA_BASE_ADDRESS;
        /// \brief Offset between successive ports.
        static const hal::cortexm::address_t MEMORY_OFFSET =
            MemoryMap::GPIO_OFFSET;

        /// @} end of name Memory definitions

      private:
        // The GpioPin classes need to take the addresses of some registers
        // for bit-band operations.
        template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
          friend class hal::stm32f4::TGpioPin;

        friend class hal::stm32f4::GpioPin;

        /// \name Memory mapped registers
        /// @{

        /// \brief 0x0000 - Mode register.
        hal::cortexm::regReadWrite_t moder;
        /// \brief 0x0004 - Output type register.
        hal::cortexm::regReadWrite_t otyper;
        /// \brief 0x0008 - Output speed register.
        hal::cortexm::regReadWrite_t ospeedr;
        /// \brief 0x000C - Pull up/pull down register.
        hal::cortexm::regReadWrite_t pupdr;
        /// \brief 0x0010 - Input data register.
        hal::cortexm::regReadOnly_t idr;
        /// \brief 0x0014 - Output data register.
        hal::cortexm::regReadWrite_t odr;
        /// \brief 0x0018 - Bit set/reset register.
        hal::cortexm::regWriteOnly_t bssr;
        /// \brief 0x001C - Lock register.
        hal::cortexm::regReadWrite_t lckr;
        /// \brief 0x0020-0x0024 - Alternate functions registers.
        hal::cortexm::regReadWrite_t afr[2];

        /// @} end of name Memory mapped registers

      };

      // ----- Inline member function definitions -----------------------------

      inline reg32_t
      __attribute__((always_inline))
      PortRegisters::readMode(void)
      {
        return this->moder;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeMode(const reg32_t value)
      {
        this->moder = value;
      }

      // 1 bit / pin
      inline reg16_t
      __attribute__((always_inline))
      PortRegisters::readOutputType(void)
      {
        return this->odr;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeOutputType(const reg16_t value)
      {
        this->odr = value;
      }

      // 2 bits / pin
      inline reg32_t
      __attribute__((always_inline))
      PortRegisters::readOutputSpeed(void)
      {
        return this->ospeedr;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeOutputSpeed(const reg32_t value)
      {
        this->ospeedr = value;
      }

      // 2 bits / pin
      inline reg32_t
      __attribute__((always_inline))
      PortRegisters::readPullUpPullDown(void)
      {
        return this->pupdr;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writePullUpPullDown(const reg32_t value)
      {
        this->pupdr = value;
      }

      // 1 bit / pin
      inline reg16_t
      __attribute__((always_inline))
      PortRegisters::readInputData(void)
      {
        return this->idr;
      }

      // 1 bit / pin
      inline reg16_t
      __attribute__((always_inline))
      PortRegisters::readOutputData(void)
      {
        return this->odr;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeOutputData(const reg16_t value)
      {
        this->odr = value;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeSetReset(const reg32_t value)
      {
        this->bssr = value;
      }

      inline reg32_t
      __attribute__((always_inline))
      PortRegisters::readConfigurationLock(void)
      {
        return this->lckr;
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeConfigurationLock(const reg32_t value)
      {
        this->lckr = value;
      }

      inline reg32_t
      __attribute__((always_inline))
      PortRegisters::readAlternateFunction(const index_t index)
      {
        return this->afr[index];
      }

      inline void
      __attribute__((always_inline))
      PortRegisters::writeAlternateFunction(const index_t index,
          const reg32_t value)
      {
        this->afr[index] = value;
      }

    // ========================================================================
    }// namespace gpio
  } // namespace stm32f4
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIODEFINITIONS_H_
