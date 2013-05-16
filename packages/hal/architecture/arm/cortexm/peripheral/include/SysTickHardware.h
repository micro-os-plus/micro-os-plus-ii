//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M System Timer (SysTick) memory mapped registers & definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_SYSTICKHARDWARE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_SYSTICKHARDWARE_H_

/// \addtogroup arm_cm_systick
/// \details
/// ARMv7-M includes an architected system timer – SysTick.
///
/// SysTick provides a simple, 24-bit clear-on-write, decrementing,
/// wrap-on-zero counter with a flexible control mechanism. It can be
/// used as an RTOS tick timer which fires at a programmable rate
/// (for example 100Hz) and invokes a SysTick routine.
///
/// The timer consists of four registers:
/// -   A control and status counter to configure its clock,
///     enable the counter, enable the SysTick interrupt, and
///     determine counter status.
/// -   The reload value for the counter, used to provide the
///     counter’s wrap value.
/// -   The current value of the counter.
/// -   A calibration value register, indicating the preload
///     value necessary for a 10ms (100Hz) system clock.
///
/// When enabled, the timer will count down from the reload value
/// to zero, reload (wrap) to the value in the SysTick Reload
/// Value Register on the next clock edge, then decrement on
/// subsequent clocks. Writing a value of zero to the Reload
/// Value Register disables the counter on the next wrap.
/// When the counter transitions to zero, the COUNTFLAG status
/// bit is set. The COUNTFLAG bit clears on reads.
///
/// Writing to the Current Value Register will clear the register
/// and the COUNTFLAG status bit. The write does not trigger the
/// SysTick exception logic. On a read, the current value is the
/// value of the register at the time the register is accessed.
///
/// The calibration value TENMS allows software to scale the counter
/// to other desired clock rates within the counter’s dynamic range.
///
/// If the core is in Debug state (halted), the counter will not
/// decrement.
///
/// The timer is clocked with respect to a reference clock. The
/// reference clock can be the core clock or an external clock source.
/// Where an external clock source is used, the implementation must
/// document the relationship between the core clock and the external
/// reference. This is required for system timing calibration, taking
/// account of metastability, clock skew and jitter.
///
/// (Excerpts from *ARMv7-M Architecture Reference Manual*,
/// chapter B3.3).

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

#include "hal/architecture/arm/cortexm/include/MemoryMap.h"

namespace hal
{
  namespace cortexm
  {
    namespace systick
    {

      // ----------------------------------------------------------------------

      typedef uint32_t reloadValue_t;
      typedef uint32_t calibrationValue_t;

      // ----------------------------------------------------------------------

      enum class CtrlBit
        : reg32_t
          {
            Enable = 0,
        TickInterruptEnable = 1,
        ClockSourceCore = 2,
        CountFlag = 16,
      };

      // These are constants, to enable expressions
      class CtrlMask
      {
      public:
        CtrlMask() = delete;

        static const reg32_t Enable = (1 << CtrlBit::Enable);
        static const reg32_t TickInterruptEnable = (1
            << CtrlBit::TickInterruptEnable);
        static const reg32_t ClockSourceCore = (1 << CtrlBit::ClockSourceCore);
        static const reg32_t CountFlag = (1 << CtrlBit::CountFlag);
      };

      static const reg32_t ReloadMask = 0x00FFFFFFUL; // [23:0]

      enum class CalibBit
        : reg32_t
          {
            Skew = 30, NoRef = 31, TenMs = 0,
      };

      class CalibMask
      {
      public:
        CalibMask() = delete;

        static const reg32_t Skew = (1 << CalibBit::Skew);
        static const reg32_t NoRef = (1 << CalibBit::NoRef);
        static const reg32_t TenMs = (0x00FFFFFFUL << CalibBit::TenMs);
      };

      // ======================================================================

      /// \headerfile SysTickHardware.h "hal/architecture/arm/cortexm/peripheral/include/SysTickHardware.h"
      /// \ingroup arm_cm_systick
      /// \nosubgrouping
      ///
      /// \brief SysTick memory mapped registers.
      ///
      /// For more details, please read *ARMv7-M Architecture Reference Manual*,
      /// chapter B3.3
      ///
      /// \warning This class is packed and mapped over a specific memory
      ///       area. DO NOT change the members order or add new data members.
      class __attribute__((packed)) Registers
      {
      public:
        // --------------------------------------------------------------------

        /// \name Constructors/destructor
        /// @{

        /// \brief Deleted constructor
        Registers() = delete;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Write the Control and Status register.
        ///
        /// \param [in] value A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeControlAndStatus(const reg32_t value);

        /// \brief Read the Control and Status register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 32-bit mask.
        reg32_t
        readControlAndStatus(void);

        /// \brief Write the Reload Value register.
        ///
        /// \param [in] value A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeReloadValue(const reg32_t value);

        /// \brief Read the Reload Value register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 32-bit mask.
        reg32_t
        readReloadValue(void);

        /// \brief Clear the Current Value register.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        void
        clearCurrentValue(void);

        /// \brief Read the Current Value register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 32-bit mask.
        reg32_t
        readCurrentValue(void);

        /// \brief Read the Calibration Value register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 32-bit mask.
        reg32_t
        readCalibrationValue(void);

        /// @} end of Public member functions

        /// \name Memory definitions
        /// @{

        /// \brief Base address of the peripheral.
        static const hal::cortexm::address_t MEMORY_BASE_ADDRESS =
            MemoryMap::SysTick_BASE_ADDRESS;

        /// @} end of name Memory definitions

      private:
        /// \name Private memory mapped registers
        /// @{

        /// \brief 0x0000 - Control and Status register.
        hal::cortexm::regReadWrite_t ctrl;
        /// \brief 0x0004 - Reload Value register.
        hal::cortexm::regReadWrite_t load;
        /// \brief 0x0008 - Current Value register.
        hal::cortexm::regReadWrite_t val;
        /// \brief 0x000C - Calibration register.
        hal::cortexm::regReadOnly_t calib;

        /// @} end of name Memory mapped registers

      };

      // ----- Inline member function definitions -----------------------------

      inline void
      __attribute__((always_inline))
      Registers::writeControlAndStatus(const reg32_t value)
      {
        this->ctrl = value;
      }

      inline reg32_t
      __attribute__((always_inline))
      Registers::readControlAndStatus(void)
      {
        return this->ctrl;
      }

      /// \details
      /// Write the value to load into the Current Value register when
      /// the counter reaches 0.
      inline void
      __attribute__((always_inline))
      Registers::writeReloadValue(const reg32_t value)
      {
        this->load = value;
      }

      /// Read the value to be loaded into the Current Value register when
      /// the counter reaches 0.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readReloadValue(void)
      {
        return this->load;
      }

      /// \details
      /// The register is write-clear.
      /// A software write of any value will clear the register to 0.
      /// Unsupported bits are ignored.
      inline void
      __attribute__((always_inline))
      Registers::clearCurrentValue(void)
      {
        this->val = 0;
      }

      /// \details
      /// This is the value of the counter
      /// at the time it is sampled. The counter does not provide
      /// read-modify-write protection.
      /// Unsupported bits read as zero.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readCurrentValue(void)
      {
        return this->val;
      }

      inline reg32_t
      __attribute__((always_inline))
      Registers::readCalibrationValue(void)
      {
        return this->calib;
      }

    // ========================================================================
    }// namespace systick
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_RCCHARDWARE_H_
