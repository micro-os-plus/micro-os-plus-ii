//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 Independent Watchdog high level classes.
///

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDG_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDG_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/IwdgHardware.h"

//#include "hal/architecture/arm/cortexm/peripheral/include/BitBanding.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================
#if 0
    /// \headerfile Iwdg.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Iwdg.h"
    /// \ingroup stm32f4_iwdg
    /// \nosubgrouping
    ///
    /// \brief IWDG class (static version).
    ///
    /// \details
    /// This class template provides full control of a STM32F4 GPIO pin.
    /// It is intended for most common cases when both the port number
    /// and the bit number are constants known at compile time.
    ///
    /// For performance reasons, all member functions are inline and very
    /// simple, performing just the required memory access(es).
    ///
    /// Using it is typical for static classes, although a default
    /// constructor is provided, so you can instantiate it as well.
    ///
    /// \code{.cpp}
    /// template class hal::stm32f4::TGpioPin<XPORT, XBIT>;
    /// typedef class hal::stm32f4::TGpioPin<XPORT, XBIT> XGPIO;
    ///
    /// XGPIO::setPinHigh();
    /// \endcode
    class Iwdg
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        Iwdg() = default;

        /// @} end of name Constructors/destructor

        // ----- Getters --------------------------------------------------------
        /// \name Getters
        /// @{

        /// \brief Get a reference to the port registers.
        ///
        /// \par Parameters
        ///    None.
        /// \return A reference to the port registers.
        static iwdg::Registers&
        getRegisters(void);

        /// @} end of name Getters

        // ----- Configuration functions ----------------------------------------
        /// \name Configuration functions
        /// @{

        /// @} end of name Configuration functions

        /// \name Member functions
        /// @{

        /// \brief Start the watchdog.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        start(void);

        /// \brief Reload the watchdog.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        reload(void);

        /// @} end of name Member functions

        // ----------------------------------------------------------------------

      private:
        /// \name Private members
        /// @{

        /// \brief The address of the device hardware registers.
        ///
        /// \details
        /// This value is the device base address.
        /// For convenient access, it is represented as a reference.
        static constexpr iwdg::Registers& m_registers =
        *reinterpret_cast<iwdg::Registers*>(0);//(iwdg::Registers::MEMORY_BASE_ADDRESS);

        /// @} end of name Private members
      };

    // ----- Inline member function definitions -------------------------------

    inline iwdg::Registers&
    __attribute__((always_inline))
    Iwdg::getRegisters(void)
      {
        return m_registers;
      }

    inline void
    __attribute__((always_inline))
    Iwdg::start(void)
      {
        m_registers.writeKey(iwdg::START_KEY);
      }

    inline void
    __attribute__((always_inline))
    Iwdg::reload(void)
      {
        m_registers.writeKey(iwdg::RELOAD_KEY);
      }
#else
    /// \headerfile Iwdg.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Iwdg.h"
    /// \ingroup stm32f4_iwdg
    /// \nosubgrouping
    ///
    /// \brief Independent Watchdog class template (static version).
    ///
    /// \details
    /// This class template provides control of the STM32F4 IWDG. You do not
    /// have to use it directly, the `hal::stm32f4::Iwdg` instantiation
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
    /// hal::stm32f4::Iwdg::reload();
    /// \endcode
    template<hal::cortexm::address_t A_T>
      class TIwdg
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TIwdg() = default;

        /// @} end of name Constructors/destructor

        // ----- Getters --------------------------------------------------------
        /// \name Getters
        /// @{

        /// \brief Get a reference to the peripheral registers.
        ///
        /// \par Parameters
        ///    None.
        /// \return A reference to the peripheral registers.
        static iwdg::Registers&
        getRegisters(void);

        /// @} end of name Getters

        // ----- Configuration functions ----------------------------------------
        /// \name Configuration functions
        /// @{

        static void
        configurePrescaler(iwdg::PrescalerDivider);

        static iwdg::PrescalerDivider
        retrievePrescaler(void);

        static void
        configureReload(iwdg::reloadValue_t value);

        static iwdg::reloadValue_t
        retrieveReload(void);

        /// @} end of name Configuration functions

        /// \name Member functions
        /// @{

        /// \brief Start the watchdog downcounter.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        start(void);

        /// \brief Reload the watchdog downcounter.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        reload(void);

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
        static constexpr iwdg::Registers& m_registers =
            *reinterpret_cast<iwdg::Registers*>(A_T);

        /// @} end of name Private members
      };

    // ----- Inline member function definitions -------------------------------

    template<hal::cortexm::address_t A_T>
      inline iwdg::Registers&
      __attribute__((always_inline))
      TIwdg<A_T>::getRegisters(void)
      {
        return m_registers;
      }

    /// \details
    /// When the independent watchdog is started by writing the value
    /// 0xCCCC in the Key register (IWDG_KR), the counter starts
    /// counting down from the reset value of 0xFFF. When it reaches
    /// the end of count value (0x000) a reset signal is generated
    /// (IWDG reset).
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TIwdg<A_T>::start(void)
      {
        m_registers.writeKey(iwdg::START_KEY);
      }

    /// \details
    /// Whenever the key value 0xAAAA is written in the IWDG_KR register,
    /// the IWDG_RLR value is reloaded in the counter and the watchdog
    /// reset is prevented.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TIwdg<A_T>::reload(void)
      {
        m_registers.writeKey(iwdg::RELOAD_KEY);
      }

    // ------------------------------------------------------------------------

    /// \ingroup stm32f4_iwdg
    /// \brief IWDG class based on the template.
    ///
    /// \details
    /// Use this static class to access the IWDG peripheral.
    typedef TIwdg<iwdg::Registers::MEMORY_BASE_ADDRESS> Iwdg;

#endif
  // ==========================================================================
  }// namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDG_H_
