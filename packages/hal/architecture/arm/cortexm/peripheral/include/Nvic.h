//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M NVIC high level classes.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVIC_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVIC_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/peripheral/include/NvicHardware.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================
    /// \headerfile Nvic.h "hal/architecture/arm/cortexm/peripheral/include/Nvic.h"
    /// \ingroup arm_cm_nvic
    /// \nosubgrouping
    ///
    /// \brief Nvic class template (static version).
    ///
    /// \details
    /// This class template provides control of the Cortex-M NVIC. You do not
    /// have to use it directly, the `hal::cortexm::Nvic` instantiation
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
    /// SysTick::configure(NNNN);
    /// SysTick::enable();
    /// \endcode
    template<hal::cortexm::address_t A_T>
      class TNvic
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TNvic(void) = default;

        /// @} end of name Constructors/destructor

        // ----- Getters ------------------------------------------------------
        /// \name Getters
        /// @{

        /// \brief Get a reference to the peripheral registers.
        ///
        /// \par Parameters
        ///    None.
        /// \return A reference to the peripheral registers.
        static nvic::Registers&
        getRegisters(void);

        /// @} end of name Getters

        /// \name Member functions
        /// @{

        /// \brief Configure the interrupt priority.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \param [in] priority An 8-bit priority value.
        /// \par Returns
        ///     Nothing.
        static void
        configurePriority(const interruptNumber_t number,
            const interruptPriority_t priority);

        /// \brief Retrieve the interrupt priority.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \return An 8-bit priority value.
        static interruptPriority_t
        retrievePriority(const interruptNumber_t number) const;

        /// \brief Enable the interrupt.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \par Returns
        ///     Nothing.
        static void
        enable(const interruptNumber_t number);

        /// \brief Disable the interrupt.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \par Returns
        ///     Nothing.
        static void
        disable(const interruptNumber_t number);

        /// \brief Set the pending bit of the interrupt.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \par Returns
        ///     Nothing.
        static void
        setPending(const interruptNumber_t number);

        /// \brief Clear the pending bit of the interrupt.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \par Returns
        ///     Nothing.
        static void
        clearPending(const interruptNumber_t number);

        /// \brief Check if the interrupt is active.
        ///
        /// \param [in] number The unsigned number of the interrupt.
        /// \retval true The interrupt is active.
        /// \retval false The interrupt is not active.
        static bool
        isActive(const interruptNumber_t number) const;

        /// @} end of name Member functions

        // --------------------------------------------------------------------

      private:
        /// \name Private members
        /// @{

        /// \brief The address of the peripheral hardware registers.
        ///
        /// \details
        /// This value is the peripheral base address.
        /// For convenient access, it is represented as a reference.
        static constexpr nvic::Registers& m_registers =
            *reinterpret_cast<nvic::Registers*>(A_T);

        /// @} end of name Private members
      };

    // ----- Inline member function definitions -------------------------------

    template<hal::cortexm::address_t A_T>
      inline nvic::Registers&
      __attribute__((always_inline))
      TNvic<A_T>::getRegisters(void)
      {
        return m_registers;
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TNvic<A_T>::configurePriority(const interruptNumber_t number,
          const interruptPriority_t priority)
      {
        m_registers.writeInterruptPriority(number, priority);
      }

    template<hal::cortexm::address_t A_T>
      inline interruptPriority_t
      __attribute__((always_inline))
      TNvic<A_T>::retrievePriority(const interruptNumber_t number) const
      {
        return m_registers.readInterruptPriority(number);
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TNvic<A_T>::enable(const interruptNumber_t number)
      {
        index_t index = number / 32;
        bitNumber_t bitNumber = number % 32;
        m_registers.writeInterruptSetEnable(index, 1 << bitNumber);
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TNvic<A_T>::disable(const interruptNumber_t number)
      {
        index_t index = number / 32;
        bitNumber_t bitNumber = number % 32;
        m_registers.writeInterruptClearEnable(index, 1 << bitNumber);
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TNvic<A_T>::setPending(const interruptNumber_t number)
      {
        index_t index = number / 32;
        bitNumber_t bitNumber = number % 32;
        m_registers.writeInterruptSetPending(index, 1 << bitNumber);
      }

    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TNvic<A_T>::clearPending(const interruptNumber_t number)
      {
        index_t index = number / 32;
        bitNumber_t bitNumber = number % 32;
        m_registers.writeInterruptClearPending(index, 1 << bitNumber);
      }

    template<hal::cortexm::address_t A_T>
      inline bool
      __attribute__((always_inline))
      TNvic<A_T>::isActive(const interruptNumber_t number) const
      {
        index_t index = number / 32;
        bitNumber_t bitNumber = number % 32;
        return ((m_registers.readInterruptActiveBit(index) & (1 << bitNumber))
            != 0);
      }

    // ------------------------------------------------------------------------

    /// \ingroup arm_cm_nvic
    /// \brief Nvic class based on the TNvic template.
    ///
    /// \details
    /// Use this static class to access the SysTick peripheral.
    typedef TNvic<nvic::Registers::MEMORY_BASE_ADDRESS> Nvic;

  // ==========================================================================
  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVIC_H_
