//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 GPIO high level class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/GpioDefinitions.h"

#include "hal/architecture/arm/cortexm/peripheral/include/BitBanding.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================

    class Gpio
    {
    public:
      Gpio(const gpio::portNumber_t portNumber,
          const gpio::bitNumber_t bitNumber);

      // ----------------------------------------------------------------------

      gpio::PortRegisters&
      getPortRegisters(void);

      gpio::bitNumber_t
      getBitNumber(void);

      gpio::portNumber_t
      getPortNumber(void);

      // ----------------------------------------------------------------------
      void
      configureMode(gpio::Mode value);

      gpio::Mode
      readMode(void);

      void
      configureOutputType(gpio::OutputType value);

      gpio::OutputType
      readOutputType(void);

      void
      configureOutputSpeed(gpio::OutputSpeed value);

      gpio::OutputSpeed
      readOutputSpeed(void);

      void
      configurePullUpPullDown(gpio::Resistors value);

      gpio::Resistors
      readPullUpPullDown(void);

      void
      configureAlternateFunction(gpio::AlternateFunction value);

      gpio::AlternateFunction
      readAlternateFunction(void);

      // TODO: add configure lock

      // ----------------------------------------------------------------------

      void
      setPinHigh(void);

      void
      setPinLow(void);

      void
      togglePin(void);

      //
      bool
      isPinHigh(void);

      bool
      isPinLow(void);

      // ----------------------------------------------------------------------

    private:
      gpio::PortRegisters& m_portRegisters;
      const hal::cortexm::reg16_t m_bitMask;

      const gpio::portNumber_t m_portNumber;
      const gpio::bitNumber_t m_bitNumber;

    };

    // ------------------------------------------------------------------------

    inline
    Gpio::Gpio(gpio::portNumber_t portNumber, gpio::bitNumber_t bitNumber)
        : //
        m_portRegisters(
            *reinterpret_cast<gpio::PortRegisters*>(gpio::PortRegisters::MEMORY_BASE
                + (portNumber * gpio::PortRegisters::MEMORY_OFFSET))), //
        m_bitMask(1 << bitNumber), //
        m_portNumber(portNumber), //
        m_bitNumber(bitNumber) //
    {
    }

    inline gpio::PortRegisters&
    __attribute__((always_inline))
    Gpio::getPortRegisters(void)
    {
      return m_portRegisters;
    }

    inline gpio::bitNumber_t
    __attribute__((always_inline))
    Gpio::getBitNumber(void)
    {
      return m_bitNumber;
    }

    inline gpio::portNumber_t
    __attribute__((always_inline))
    Gpio::getPortNumber(void)
    {
      return m_portNumber;
    }

    inline void
    __attribute__((always_inline))
    Gpio::configureMode(gpio::Mode value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readMode();
      current &= ~(gpio::MODE_MASK << (2 * m_bitNumber));

      hal::cortexm::reg32_t newValue;
      newValue = static_cast<hal::cortexm::reg32_t>(value);
      newValue = (newValue & gpio::MODE_MASK) << (2 * m_bitNumber);

      m_portRegisters.writeMode(current | newValue);
    }

    inline gpio::Mode
    __attribute__((always_inline))
    Gpio::readMode(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readMode();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::Mode>(current & gpio::MODE_MASK);
    }

    inline void
    __attribute__((always_inline))
    Gpio::configureOutputType(gpio::OutputType value)
    {
      hal::cortexm::address_t otyperAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.otyper);

      hal::cortexm::reg32_t newValue;
      newValue = static_cast<hal::cortexm::reg32_t>(value);

      hal::cortexm::bitband::setPeripheralBitWord(otyperAddress, m_bitNumber,
          newValue);
    }

    inline gpio::OutputType
    __attribute__((always_inline))
    Gpio::readOutputType(void)
    {
      hal::cortexm::address_t otyperAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.otyper);

      return static_cast<gpio::OutputType>(hal::cortexm::bitband::getPeripheralBitWord(
          otyperAddress, m_bitNumber));
    }

    inline void
    __attribute__((always_inline))
    Gpio::configureOutputSpeed(gpio::OutputSpeed value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readOutputSpeed();
      current &= ~(gpio::OUTPUT_SPEED_MASK << (2 * m_bitNumber));

      hal::cortexm::reg32_t newValue;
      newValue = static_cast<hal::cortexm::reg32_t>(value);
      newValue = (newValue & gpio::OUTPUT_SPEED_MASK) << (2 * m_bitNumber);

      m_portRegisters.writeOutputSpeed(current | newValue);
    }

    inline gpio::OutputSpeed
    __attribute__((always_inline))
    Gpio::readOutputSpeed(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readOutputSpeed();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::OutputSpeed>(current & gpio::OUTPUT_SPEED_MASK);
    }

    inline void
    __attribute__((always_inline))
    Gpio::configurePullUpPullDown(gpio::Resistors value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readPullUpPullDown();
      current &= ~(gpio::RESISTORS_MASK << (2 * m_bitNumber));

      hal::cortexm::reg32_t newValue;
      newValue = static_cast<hal::cortexm::reg32_t>(value);
      newValue = (newValue & gpio::RESISTORS_MASK) << (2 * m_bitNumber);

      m_portRegisters.writePullUpPullDown(current | newValue);
    }

    inline gpio::Resistors
    __attribute__((always_inline))
    Gpio::readPullUpPullDown(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readPullUpPullDown();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::Resistors>(current & gpio::RESISTORS_MASK);
    }

    inline void
    __attribute__((always_inline))
    Gpio::configureAlternateFunction(gpio::AlternateFunction value)
    {
      hal::cortexm::reg32_t current;

      hal::cortexm::reg32_t newValue;
      newValue = static_cast<hal::cortexm::reg32_t>(value);

      if (m_bitNumber < 8)
        {
          current = m_portRegisters.readAlternateFunction(0);
          current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * m_bitNumber));

          newValue = (newValue & gpio::ALTERNATE_FUNCTION_MASK)
              << (4 * m_bitNumber);
          m_portRegisters.writeAlternateFunction(0, current | newValue);
        }
      else
        {
          current = m_portRegisters.readAlternateFunction(1);
          current &=
              ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * (m_bitNumber - 8)));

          newValue = (newValue & gpio::ALTERNATE_FUNCTION_MASK)
              << (4 * (m_bitNumber - 8));
          m_portRegisters.writeAlternateFunction(1, current | newValue);
        }
    }

    inline gpio::AlternateFunction
    __attribute__((always_inline))
    Gpio::readAlternateFunction(void)
    {
      hal::cortexm::reg32_t current;

      if (m_bitNumber < 8)
        {
          current = m_portRegisters.readAlternateFunction(0);
          current >>= (4 * m_bitNumber);
        }
      else
        {
          current = m_portRegisters.readAlternateFunction(1);
          current >>= (4 * (m_bitNumber - 8));
        }

      return static_cast<gpio::AlternateFunction>(current
          & gpio::ALTERNATE_FUNCTION_MASK);
    }

    // ------------------------------------------------------------------------

    inline void
    __attribute__((always_inline))
    Gpio::setPinHigh(void)
    {
      m_portRegisters.writeSetReset(
          static_cast<hal::cortexm::reg32_t>(m_bitMask));
    }

    inline void
    __attribute__((always_inline))
    Gpio::setPinLow(void)
    {
      // write to the upper half
      m_portRegisters.writeSetReset(
          static_cast<hal::cortexm::reg32_t>(m_bitMask) << 16);
    }

    inline void
    __attribute__((always_inline))
    Gpio::togglePin(void)
    {
      hal::cortexm::address_t odrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.odr);

      uint32_t oldValue;
      oldValue = hal::cortexm::bitband::getPeripheralBitWord(odrAddress,
          m_bitNumber);

      uint32_t newValue = ~oldValue;
      hal::cortexm::bitband::setPeripheralBitWord(odrAddress, m_bitNumber,
          newValue);
    }

    inline bool
    __attribute__((always_inline))
    Gpio::isPinHigh(void)
    {
      hal::cortexm::address_t idrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.idr);

      return (hal::cortexm::bitband::getPeripheralBitWord(idrAddress,
          m_bitNumber) != 0);
    }

    inline bool
    __attribute__((always_inline))
    Gpio::isPinLow(void)
    {
      hal::cortexm::address_t idrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.idr);

      return (hal::cortexm::bitband::getPeripheralBitWord(idrAddress,
          m_bitNumber) == 0);
    }

    // ========================================================================

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      class TGpio
      {
      private:
        static const gpio::portNumber_t m_portNumber = Port_T;

        static constexpr gpio::PortRegisters& m_portRegisters =
            *reinterpret_cast<gpio::PortRegisters*>(gpio::PortRegisters::MEMORY_BASE
                + (m_portNumber * gpio::PortRegisters::MEMORY_OFFSET));

        static const gpio::bitNumber_t m_bitNumber = Bit_T;

        // intentionally 16-bit, to trigger error if m_bitNumber>16
        static constexpr hal::cortexm::reg16_t m_bitMask = (1 << m_bitNumber);

      public:
        TGpio() = default; // = delete;

        static void
        setPinHigh(void);

        static void
        setPinLow(void);
      };

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpio<Port_T, Bit_T>::setPinHigh(void)
      {
        m_portRegisters.writeSetReset(
            static_cast<hal::cortexm::reg32_t>(m_bitMask));
      }

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpio<Port_T, Bit_T>::setPinLow(void)
      {
        // write to the upper half
        m_portRegisters.writeSetReset(
            static_cast<hal::cortexm::reg32_t>(m_bitMask) << 16);
      }

  // ==========================================================================
  }// namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
