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

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/FamilyDefinitions.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/GpioDefinitions.h"

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
        static constexpr reg16_t m_bitMask = (1 << m_bitNumber);

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
        m_portRegisters.writeSetReset(static_cast<reg32_t>(m_bitMask));
      }

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      void
      inline __attribute__((always_inline))
      TGpio<Port_T, Bit_T>::setPinLow(void)
      {
        // write to the upper half
        m_portRegisters.writeSetReset(static_cast<reg32_t>(m_bitMask) << 16);
      }

    // ========================================================================

    class Gpio
    {
    public:
      Gpio(const gpio::portNumber_t portNumber,
          const gpio::bitNumber_t bitNumber);

      void
      setPinHigh(void);

      void
      setPinLow(void);

    private:
      gpio::PortRegisters& m_portRegisters;
      const reg16_t m_bitMask;

      const gpio::portNumber_t m_portNumber;
      const gpio::bitNumber_t m_bitNumber;

    };

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

    void
    inline __attribute__((always_inline))
    Gpio::setPinHigh(void)
    {
      m_portRegisters.writeSetReset(static_cast<reg32_t>(m_bitMask));
    }

    void
    inline __attribute__((always_inline))
    Gpio::setPinLow(void)
    {
      // write to the upper half
      m_portRegisters.writeSetReset(static_cast<reg32_t>(m_bitMask) << 16);
    }

  // ==========================================================================
  }// namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
