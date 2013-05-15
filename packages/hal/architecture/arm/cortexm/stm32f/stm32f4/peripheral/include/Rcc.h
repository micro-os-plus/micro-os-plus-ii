//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 Reset and Clock Control high level classes.
///

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCC_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCC_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/RccHardware.h"

#include "hal/architecture/arm/cortexm/peripheral/include/BitBand.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================
    /// \headerfile Rcc.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Rcc.h"
    /// \ingroup stm32f4_rcc
    /// \nosubgrouping
    ///
    /// \brief Reset and Clock Control class template (static version).
    ///
    /// \details
    /// This class template provides control of the STM32F4 RCC. You do not
    /// have to use it directly, the `hal::stm32f4::Rcc` instantiation
    /// is available.
    ///
    /// For performance reasons, all member functions are inline and very
    /// simple, performing just the required memory access(es).
    ///
    /// Using it is typical for static classes, although a default
    /// constructor is provided, so you can instantiate it as well.
    ///
    /// \par Example
    /// \code{.cpp}
    /// Rcc::enableAhb1PeripheralClock(rcc::Ahb1Peripheral::GpioA);
    /// \endcode
    ///
    /// \todo Add more code, the implementation is currently minimal.
    template<hal::cortexm::address_t A_T>
      class TRcc
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TRcc() = default;

        /// @} end of name Constructors/destructor

        // ----- Getters --------------------------------------------------------
        /// \name Getters
        /// @{

        /// \brief Get a reference to the peripheral registers.
        ///
        /// \par Parameters
        ///    None.
        /// \return A reference to the peripheral registers.
        static rcc::Registers&
        getRegisters(void);

        /// @} end of name Getters

        // ----- Configuration functions ----------------------------------------
        /// \name Configuration functions
        /// @{

        /// \brief Enable the clock for one AHB1 connected peripheral.
        ///
        /// \param [in] number The number of the bit in the register.
        /// \par Returns
        ///    Nothing.
        static void
        enableAhb1PeripheralClock(rcc::Ahb1Peripheral number);

        /// \brief Disable the clock for one AHB1 connected peripheral.
        ///
        /// \param [in] number The number of the bit in the register.
        /// \par Returns
        ///    Nothing.
        static void
        disableAhb1PeripheralClock(rcc::Ahb1Peripheral number);

        /// \brief Tell if the clock of the AHB1 connected peripheral is enabled.
        ///
        /// \param [in] number The number of the bit in the register.
        /// \par Returns
        ///    Nothing.
        static bool
        isEnabledAhb1PeripheralClock(rcc::Ahb1Peripheral number);

        /// \brief Enable the clock for one GPIO port.
        ///
        /// \param [in] number The number of the GPIO port (0=GPIOA).
        /// \par Returns
        ///    Nothing.
        static void
        enableGpioPeripheralClock(gpio::portNumber_t number);

        /// \brief Disable the clock for one GPIO port.
        ///
        /// \param [in] number The number of the GPIO port (0=GPIOA).
        /// \par Returns
        ///    Nothing.
        static void
        disableGpioPeripheralClock(gpio::portNumber_t number);

        /// @} end of name Configuration functions

        /// \name Member functions
        /// @{

        /// @} end of name Member functions

        // ----------------------------------------------------------------------

      private:
        /// \name Private members
        /// @{

        /// \brief The address of the peripheral hardware registers.
        ///
        /// \details
        /// This value is the peripheral base address.
        /// For convenient access, it is represented as a reference.
        static constexpr rcc::Registers& m_registers =
            *reinterpret_cast<rcc::Registers*>(A_T);

        /// @} end of name Private members
      };

    // ----- Inline member function definitions -------------------------------

    template<hal::cortexm::address_t A_T>
      inline rcc::Registers&
      __attribute__((always_inline))
      TRcc<A_T>::getRegisters(void)
      {
        return m_registers;
      }

    /// \details
    /// Use bit-banding to set the single register bit.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TRcc<A_T>::enableAhb1PeripheralClock(rcc::Ahb1Peripheral number)
      {
        rcc::bitNumber_t bitNumber = static_cast<gpio::reg32_t>(number);

        hal::cortexm::BitBand::setPeripheralBit(&m_registers.ahb1enr,
            bitNumber);
      }

    /// \details
    /// Use bit-banding to clear the single register bit.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TRcc<A_T>::disableAhb1PeripheralClock(rcc::Ahb1Peripheral number)
      {
        rcc::bitNumber_t bitNumber = static_cast<gpio::reg32_t>(number);

        hal::cortexm::BitBand::clearPeripheralBit(&m_registers.ahb1enr,
            bitNumber);
      }

    /// \details
    /// Use bit-banding to clear the single register bit.
    template<hal::cortexm::address_t A_T>
      inline bool
      __attribute__((always_inline))
      TRcc<A_T>::isEnabledAhb1PeripheralClock(rcc::Ahb1Peripheral number)
      {
        rcc::bitNumber_t bitNumber = static_cast<gpio::reg32_t>(number);

        return (hal::cortexm::BitBand::readPeripheralBitValue(
            &m_registers.ahb1enr, bitNumber) != 0);
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TRcc<A_T>::enableGpioPeripheralClock(gpio::portNumber_t number)
      {
        // GPIO port numbers are successive
        rcc::bitNumber_t bitNumber =
            static_cast<rcc::bitNumber_t>(rcc::Ahb1Peripheral::GpioA);
        bitNumber += number;
        enableAhb1PeripheralClock(static_cast<rcc::Ahb1Peripheral>(bitNumber));
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TRcc<A_T>::disableGpioPeripheralClock(gpio::portNumber_t number)
      {
        // GPIO port numbers are successive
        rcc::bitNumber_t bitNumber =
            static_cast<rcc::bitNumber_t>(rcc::Ahb1Peripheral::GpioA);
        bitNumber += number;
        disableAhb1PeripheralClock(static_cast<rcc::Ahb1Peripheral>(bitNumber));
      }

    // ------------------------------------------------------------------------

    /// \ingroup stm32f4_rcc
    /// \brief RCC class based on the TRcc template.
    ///
    /// \details
    /// Use this static class to access the RCC peripheral.
    typedef TRcc<rcc::Registers::MEMORY_BASE_ADDRESS> Rcc;

  // ==========================================================================
  }// namespace stm32f4
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCC_H_
