//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M System Timer (SysTick) high level classes.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_SYSTICK_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_SYSTICK_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/peripheral/include/SysTickHardware.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile SysTick.h "hal/architecture/arm/cortexm/peripheral/include/SysTick.h"
    /// \ingroup arm_cm_systick
    /// \nosubgrouping
    ///
    /// \brief SysTick class template (static version).
    ///
    /// \details
    /// This class template provides control of the Cortex-M SysTick. You do not
    /// have to use it directly, the `hal::cortexm::SysTick` instantiation
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
      class TSysTick
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TSysTick(void) = default;

        /// @} end of name Constructors/destructor

        // ----- Getters --------------------------------------------------------
        /// \name Getters
        /// @{

        /// \brief Get a reference to the peripheral registers.
        ///
        /// \par Parameters
        ///    None.
        /// \return A reference to the peripheral registers.
        static systick::Registers&
        getRegisters(void);

        /// @} end of name Getters

        /// \name Member functions
        /// @{

        /// \brief Enable the clock for one AHB1 connected peripheral.
        ///
        /// \param [in] number The number of the bit in the register.
        /// \par Returns
        ///    Nothing.
        static void
        configure(systick::reloadValue_t number);

        /// \brief Enable the system timer to generate interrupts.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        enableInterrupts(void);

        /// \brief Disable the system timer to generate interrupts.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        disableInterrupts(void);

        /// \brief Enable the system timer.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        enable(void);

        /// \brief Disable the system timer.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        disable(void);

        /// \brief Retrieve the calibration value.
        ///
        /// \par Parameters
        ///     None.
        /// \return A 32-bit value.
        ///     Nothing.
        static systick::calibrationValue_t
        retrieveCalibration(void);

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
        static constexpr systick::Registers& m_registers =
            *reinterpret_cast<systick::Registers*>(A_T);

        /// @} end of name Private members
      };

    // ----- Inline member function definitions -------------------------------

    template<hal::cortexm::address_t A_T>
      inline systick::Registers&
      __attribute__((always_inline))
      TSysTick<A_T>::getRegisters(void)
      {
        return m_registers;
      }

    /// \details
    /// Configure the given timer value, clear counter and enable interrupts.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TSysTick<A_T>::configure(systick::reloadValue_t number)
      {
        systick::reloadValue_t val;
        if (number > systick::ReloadMask)
          {
            val = systick::ReloadMask;
          }
        else
          {
            val = (number & systick::ReloadMask) - 1;
          }

        m_registers.writeReloadValue(val);
        m_registers.clearCurrentValue();

        // enable core clock and the interrupts
        m_registers.writeControlAndStatus(
            systick::CtrlMask::ClockSourceCore
                | systick::CtrlMask::TickInterruptEnable);
      }

    /// \details
    /// Perform read/modify/write on the control and status register.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TSysTick<A_T>::enable(void)
      {
        reg32_t val = m_registers.readControlAndStatus();
        val |= systick::CtrlMask::Enable;
        m_registers.writeControlAndStatus(val);
      }

    /// \details
    /// Perform read/modify/write on the control and status register.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TSysTick<A_T>::disable(void)
      {
        reg32_t val = m_registers.readControlAndStatus();
        val &= ~systick::CtrlMask::Enable;
        m_registers.writeControlAndStatus(val);
      }

    /// \details
    /// Perform read/modify/write on the control and status register.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TSysTick<A_T>::enableInterrupts(void)
      {
        reg32_t val = m_registers.readControlAndStatus();
        val |= systick::CtrlMask::TickInterruptEnable;
        m_registers.writeControlAndStatus(val);
      }

    /// \details
    /// Perform read/modify/write on the control and status register.
    template<hal::cortexm::address_t A_T>
      inline void
      __attribute__((always_inline))
      TSysTick<A_T>::disableInterrupts(void)
      {
        reg32_t val = m_registers.readControlAndStatus();
        val &= ~systick::CtrlMask::TickInterruptEnable;
        m_registers.writeControlAndStatus(val);
      }

    /// \details
    /// Ignore the two status bits and return only the lower 3 bytes.
    /// If the value reads as 0, the calibration value is not known.
    template<hal::cortexm::address_t A_T>
      inline systick::calibrationValue_t
      __attribute__((always_inline))
      TSysTick<A_T>::retrieveCalibration(void)
      {
        reg32_t val = m_registers.readCalibrationValue();
        // Keep only the low 3 bytes.
        return (val & systick::CalibMask::TenMs);
      }

    // ------------------------------------------------------------------------

    /// \ingroup arm_cm_systick
    /// \brief SysTick class based on the TSysTick template.
    ///
    /// \details
    /// Use this static class to access the SysTick peripheral.
    typedef TSysTick<systick::Registers::MEMORY_BASE_ADDRESS> SysTick;

  // ==========================================================================
  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_SYSTICK_H_
