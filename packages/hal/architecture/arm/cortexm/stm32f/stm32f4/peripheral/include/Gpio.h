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

        static
        void
        setPinHigh(void);

        static
        void
        setPinLow(void);
      };

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      void
      inline __attribute__((always_inline))
      TGpio<Port_T, Bit_T>::setPinHigh(void)
      {
        m_portRegisters.writeSetReset(
            static_cast<hal::cortexm::reg32_t>(m_bitMask));
      }

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      void
      inline __attribute__((always_inline))
      TGpio<Port_T, Bit_T>::setPinLow(void)
      {
        // write to the upper half
        m_portRegisters.writeSetReset(
            static_cast<hal::cortexm::reg32_t>(m_bitMask) << 16);
      }

    // ========================================================================

    class Gpio
    {
    public:
      Gpio(const gpio::portNumber_t portNumber,
          const gpio::bitNumber_t bitNumber);

      // ----------------------------------------------------------------------

      gpio::bitNumber_t
      getBitNumber(void);

      gpio::portNumber_t
      getPortNumber(void);

      // ----------------------------------------------------------------------
      void
      configureMode(gpio::Mode_t value);

      gpio::Mode_t
      readMode(void);

      void
      configureOutputType(gpio::OutputType_t value);

      gpio::OutputType_t
      readOutputType(void);

      void
      configureOutputSpeed(gpio::OutputSpeed_t value);

      gpio::OutputSpeed_t
      readOutputSpeed(void);

      void
      configurePullUpPullDown(gpio::PullUpPullDown_t value);

      gpio::PullUpPullDown_t
      readPullUpPullDown(void);

      void
      configureAlternateFunction(gpio::alternateFunction_t value);

      gpio::alternateFunction_t
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

    gpio::bitNumber_t
    inline __attribute__((always_inline))
    Gpio::getBitNumber(void)
    {
      return m_bitNumber;
    }

    gpio::portNumber_t
    inline __attribute__((always_inline))
    Gpio::getPortNumber(void)
    {
      return m_portNumber;
    }

    void
    inline __attribute__((always_inline))
    Gpio::configureMode(gpio::Mode_t value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readMode();
      current &= ~(gpio::MODE_MASK << (2 * m_bitNumber));

      m_portRegisters.writeMode(
          current | ((value & gpio::MODE_MASK) << (2 * m_bitNumber)));
    }

    gpio::Mode_t
    inline __attribute__((always_inline))
    Gpio::readMode(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readMode();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::Mode_t>(current & gpio::MODE_MASK);
    }

    void
    inline __attribute__((always_inline))
    Gpio::configureOutputType(gpio::OutputType_t value)
    {
      hal::cortexm::address_t otyperAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.otyper);

      hal::cortexm::bitband::setPeripheralBitWord(otyperAddress, m_bitNumber,
          value);
    }

    gpio::OutputType_t
    inline __attribute__((always_inline))
    Gpio::readOutputType(void)
    {
      hal::cortexm::address_t otyperAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.otyper);

      return static_cast<gpio::OutputType_t>(hal::cortexm::bitband::getPeripheralBitWord(
          otyperAddress, m_bitNumber));
    }

    void
    inline __attribute__((always_inline))
    Gpio::configureOutputSpeed(gpio::OutputSpeed_t value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readOutputSpeed();
      current &= ~(gpio::OUTPUT_SPEED_MASK << (2 * m_bitNumber));

      m_portRegisters.writeOutputSpeed(
          current | ((value & gpio::OUTPUT_SPEED_MASK) << (2 * m_bitNumber)));
    }

    gpio::OutputSpeed_t
    inline __attribute__((always_inline))
    Gpio::readOutputSpeed(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readOutputSpeed();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::OutputSpeed_t>(current & gpio::OUTPUT_SPEED_MASK);
    }

    void
    inline __attribute__((always_inline))
    Gpio::configurePullUpPullDown(gpio::PullUpPullDown_t value)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readPullUpPullDown();
      current &= ~(gpio::PULL_UP_PULL_DOWN_MASK << (2 * m_bitNumber));

      m_portRegisters.writePullUpPullDown(
          current
              | ((value & gpio::PULL_UP_PULL_DOWN_MASK) << (2 * m_bitNumber)));
    }

    gpio::PullUpPullDown_t
    inline __attribute__((always_inline))
    Gpio::readPullUpPullDown(void)
    {
      hal::cortexm::reg32_t current;
      current = m_portRegisters.readPullUpPullDown();
      current >>= (2 * m_bitNumber);

      return static_cast<gpio::PullUpPullDown_t>(current
          & gpio::PULL_UP_PULL_DOWN_MASK);
    }

    void
    inline __attribute__((always_inline))
    Gpio::configureAlternateFunction(gpio::alternateFunction_t value)
    {
      hal::cortexm::reg32_t current;

      if (m_bitNumber < 8)
        {
          current = m_portRegisters.readAlternateFunction(0);
          current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * m_bitNumber));

          m_portRegisters.writeAlternateFunction(0,
              current
                  | ((value & gpio::ALTERNATE_FUNCTION_MASK)
                      << (4 * m_bitNumber)));
        }
      else
        {
          current = m_portRegisters.readAlternateFunction(1);
          current &=
              ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * (m_bitNumber - 8)));

          m_portRegisters.writeAlternateFunction(1,
              current
                  | ((value & gpio::ALTERNATE_FUNCTION_MASK)
                      << (4 * (m_bitNumber - 8))));
        }
    }

    gpio::alternateFunction_t
    inline __attribute__((always_inline))
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

      return static_cast<gpio::alternateFunction_t>(current
          & gpio::ALTERNATE_FUNCTION_MASK);
    }

    // ------------------------------------------------------------------------

    void
    inline __attribute__((always_inline))
    Gpio::setPinHigh(void)
    {
      m_portRegisters.writeSetReset(
          static_cast<hal::cortexm::reg32_t>(m_bitMask));
    }

    void
    inline __attribute__((always_inline))
    Gpio::setPinLow(void)
    {
      // write to the upper half
      m_portRegisters.writeSetReset(
          static_cast<hal::cortexm::reg32_t>(m_bitMask) << 16);
    }

    void
    inline __attribute__((always_inline))
    Gpio::togglePin(void)
    {
      hal::cortexm::address_t idrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.idr);

      uint32_t oldValue;
      oldValue = hal::cortexm::bitband::getPeripheralBitWord(idrAddress,
          m_bitNumber);

      uint32_t newValue = ~oldValue;
      hal::cortexm::bitband::setPeripheralBitWord(idrAddress, m_bitNumber,
          newValue);
    }

    bool
    inline __attribute__((always_inline))
    Gpio::isPinHigh(void)
    {
      hal::cortexm::address_t idrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.idr);

      return (hal::cortexm::bitband::getPeripheralBitWord(idrAddress,
          m_bitNumber) != 0);
    }

    bool
    inline __attribute__((always_inline))
    Gpio::isPinLow(void)
    {
      hal::cortexm::address_t idrAddress =
          reinterpret_cast<hal::cortexm::address_t>(&m_portRegisters.idr);

      return (hal::cortexm::bitband::getPeripheralBitWord(idrAddress,
          m_bitNumber) == 0);
    }

  // ==========================================================================
  }// namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
