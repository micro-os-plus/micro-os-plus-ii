//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M NVIC memory mapped registers & definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVICHARDWARE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVICHARDWARE_H_

/// \addtogroup arm_cm_nvic
/// \details
/// ARMv7-M provides an interrupt controller as an integral part
/// of the ARMv7-M exception model.
///
/// The ARMv7-M NVIC architecture supports up to 496 (IRQ[495:0])
/// discrete interrupts.
///
/// All NVIC interrupts have a programmable priority value and an
/// associated exception number as part of the ARMv7-M exception
/// model and its prioritization policy.
///
/// The NVIC supports the following features:
/// -     NVIC interrupts can be enabled and disabled by writing
///       to their corresponding Interrupt Set-Enable or Interrupt
///       Clear-Enable register bit-field. The registers use a
///       write-1-to-enable and write-1-to-clear policy, both
///       registers reading back the current enabled state of the
///       corresponding (32) interrupts.
///
///       When an interrupt is disabled, interrupt assertion will
///       cause the interrupt to become Pending, however, the
///       interrupt will not activate. If an interrupt is Active
///       when it is disabled, it remains in its Active state
///       until cleared by reset or an exception return. Clearing
///       the enable bit prevents new activations of the associated
///       interrupt.
///
///       Interrupt enable bits can be hard-wired to zero where
///       the associated interrupt line does not exist, or
///       hard-wired to one where the associated interrupt
///       line cannot be disabled.
///
/// -   NVIC interrupts can be pended/un-pended using a complementary
///     pair of registers to those used to enable/disable the
///     interrupts, named the Set-Pending Register and Clear-Pending
///     Register respectively. The registers use a write-1-to-enable
///     and write-1-to-clear policy, both registers reading back the
///     current pended state of the corresponding (32) interrupts.
///     The Clear-Pending Register has no effect on the execution
///     status of an Active interrupt.
///
///     It is IMPLEMENTATION DEFINED for each interrupt line supported,
///     whether an interrupt supports setting and/or clearing of the
///     associated pend bit under software control.
///
/// -   Active bit status is provided to allow software to determine
///     whether an interrupt is Inactive, Active, Pending, or Active
///     and Pending.
///
/// -   NVIC interrupts are prioritized by updating an 8-bit field
///     within a 32-bit register (each register supporting four
///     interrupts). Priorities are maintained according to the ARMv7-M
///     prioritization scheme. See Exception priorities and pre-emption
///     on page B1-17.
///
/// In addition to an external hardware event or setting the appropriate
/// bit in the Set-Pending registers, an external interrupt can be pended
/// from software by writing its interrupt number (ExceptionNumber - 16)
/// to the Software Trigger Interrupt Register described in Software
/// Trigger Interrupt Register (STIR) on page B3-23.
///
/// (Excerpts from *ARMv7-M Architecture Reference Manual*,
/// chapter B3.4).

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

#include "hal/architecture/arm/cortexm/include/MemoryMap.h"

namespace hal
{
  namespace cortexm
  {
    namespace nvic
    {

      // ----------------------------------------------------------------------

      /// \ingroup arm_cm_nvic
      /// \brief Type of an NVIC interrupt number.
      ///
      /// \details
      ///  This is an unsigned integer,
      /// from 0 to +495)
      /// It is different from `hal::cortexm::interruptNumber_t` which is
      /// signed, to accommodate system interrupts.
      typedef uint16_t interruptNumber_t;

      // ----------------------------------------------------------------------

      // ======================================================================

      /// \headerfile NvicHardware.h "hal/architecture/arm/cortexm/peripheral/include/NvicHardware.h"
      /// \ingroup arm_cm_nvic
      /// \nosubgrouping
      ///
      /// \brief NVIC memory mapped registers.
      ///
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
        Registers(void) = delete;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Write the Interrupt Set Enable register.
        ///
        /// \param [in] index The index of the register to write.
        /// \param [in] mask A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeInterruptSetEnable(const index_t index, const reg32_t mask);

        /// \brief Read the Interrupt Set Enable register.
        ///
        /// \param [in] index The index of the register to read.
        /// \return A 32-bit mask.
        reg32_t
        readInterruptSetEnable(const index_t index) const;

        /// \brief Write the Interrupt Clear Enable register.
        ///
        /// \param [in] index The index of the register to write.
        /// \param [in] mask A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeInterruptClearEnable(const index_t index, const reg32_t mask);

        /// \brief Read the Interrupt Clear Enable register.
        ///
        /// \param [in] index The index of the register to read.
        /// \return A 32-bit mask.
        reg32_t
        readInterruptClearEnable(const index_t index) const;

        /// \brief Write the Interrupt Set Pending register.
        ///
        /// \param [in] index The index of the register to write.
        /// \param [in] mask A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeInterruptSetPending(const index_t index, const reg32_t mask);

        /// \brief Read the Interrupt Set Pending register.
        ///
        /// \param [in] index The index of the register to read.
        /// \return A 32-bit mask.
        reg32_t
        readInterruptSetPending(const index_t index) const;

        /// \brief Write the Interrupt Clear Pending register.
        ///
        /// \param [in] index The index of the register to write.
        /// \param [in] mask A 32-bit mask.
        /// \par Returns
        ///    Nothing.
        void
        writeInterruptClearPending(const index_t index, const reg32_t mask);

        /// \brief Read the Interrupt Clear Pending register.
        ///
        /// \param [in] index The index of the register to read.
        /// \return A 32-bit mask.
        reg32_t
        readInterruptClearPending(const index_t index) const;

        /// \brief Read the Interrupt Active Bit register.
        ///
        /// \param [in] index The index of the register to read.
        /// \return A 32-bit mask.
        reg32_t
        readInterruptActiveBit(const index_t index) const;

        /// \brief Write an Interrupt Priority byte.
        ///
        /// \param [in] number The number of the interrupt to write.
        /// \param [in] priority An 8-bit priority value.
        /// \par Returns
        ///    Nothing.
        void
        writeInterruptPriority(const interruptNumber_t number,
            const interruptPriority_t priority) const;

        /// \brief Read an Interrupt Priority byte.
        ///
        /// \param [in] number The number of the interrupt to read.
        /// \return An 8-bit priority value.
        interruptPriority_t
        readInterruptPriority(const interruptNumber_t number) const;

        /// \brief Write Software Trigger Interrupt register.
        ///
        /// \param [in] value A 10-bit unsigned value.
        /// \par Returns
        ///    Nothing.
        void
        writeSoftwareTriggerInterrupt(const interruptNumber_t value);

        /// @} end of Public member functions

        /// \name Memory definitions
        /// @{

        /// \brief Base address of the peripheral.
        static constexpr hal::cortexm::address_t MEMORY_BASE_ADDRESS =
            MemoryMap::NVIC_BASE_ADDRESS;

        /// @} end of name Memory definitions

      private:
        /// \name Private memory mapped registers
        /// @{

        /// \brief 0x0000 - Interrupt Set Enable registers.
        hal::cortexm::regReadWrite_t iser[8];
        hal::cortexm::regNotAllocated_t reserved0[24];

        /// \brief 0x0080 - Interrupt Clear Enable registers.
        hal::cortexm::regReadWrite_t icer[8];
        hal::cortexm::regNotAllocated_t reserved1[24];

        /// \brief 0x0100 - Interrupt Set Pending registers.
        hal::cortexm::regReadWrite_t ispr[8];
        hal::cortexm::regNotAllocated_t reserved2[24];

        /// \brief 0x0180 - Interrupt Clear Pending registers.
        hal::cortexm::regReadWrite_t icpr[8];
        hal::cortexm::regNotAllocated_t reserved3[24];

        /// \brief 0x0200 - Interrupt Active Bit registers.
        hal::cortexm::regReadOnly_t iabr[8];
        hal::cortexm::regNotAllocated_t reserved4[56];

        /// \brief 0x0300 - Interrupt Priority registers (8-bit/level).
        hal::cortexm::reg8_t ip[240];
        hal::cortexm::regNotAllocated_t reserved5[644];

        /// \brief 0x0E00 - Software Trigger Interrupt register.
        hal::cortexm::regWriteOnly_t stir;

        /// @} end of name Memory mapped registers

      };

      // ----- Inline member function definitions -----------------------------

      /// \details
      /// Enable one or more interrupts within a group of 32.
      /// Each bit represents an interrupt number from N to N+31
      /// (starting at
      /// interrupt 0, 32, 64, etc).
      ///
      /// Writing a 1 will enable the associated interrupt.
      ///
      /// Writing a 0 has no effect.
      inline void
      __attribute__((always_inline))
      Registers::writeInterruptSetEnable(const index_t index,
          const reg32_t mask)
      {
        this->iser[index] = mask;
      }

      /// \details
      /// The register reads back with the current enable state,
      /// within a group of 32 interrupts.
      ///
      /// Reading a 1 means the interrupt is enabled.
      ///
      /// Reading a 0 means the interrupt is disabled.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readInterruptSetEnable(const index_t index) const
      {
        return this->iser[index];
      }

      /// \details
      /// Disable one or more interrupts within a group of 32.
      /// Each bit represents an interrupt number from N to N+31
      /// (starting at
      /// interrupt 0, 32, 64, etc).
      ///
      /// Writing a 1 will disable the associated interrupt.
      ///
      /// Writing a 0 has no effect.
      inline void
      __attribute__((always_inline))
      Registers::writeInterruptClearEnable(const index_t index,
          const reg32_t mask)
      {
        this->icer[index] = mask;
      }

      /// \details
      /// The register reads back with the current enable state,
      /// within a group of 32 interrupts.
      ///
      /// Reading a 1 means the interrupt is enabled.
      ///
      /// Reading a 0 means the interrupt is disabled.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readInterruptClearEnable(const index_t index) const
      {
        return this->icer[index];
      }

      /// \details
      /// Writing a 1 to a bit pends the associated interrupt
      /// under software control. Each bit represents an interrupt
      /// number from N to N+31 (starting at interrupt 0, 32, 64, etc).
      ///
      /// Writing a 0 to a bit has no effect on the associated interrupt.
      inline void
      __attribute__((always_inline))
      Registers::writeInterruptSetPending(const index_t index,
          const reg32_t mask)
      {
        this->ispr[index] = mask;
      }

      /// \details
      /// The register reads back with the current pending state
      /// within a group of 32 interrupts.
      ///
      /// Reading a 1 means the interrupt is pending.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readInterruptSetPending(const index_t index) const
      {
        return this->ispr[index];
      }

      /// \details
      /// Writing a 1 to a bit un-pends the associated interrupt
      /// under software control. Each bit represents an interrupt
      /// number from N to N+31 (starting at interrupt 0, 32, 64, etc).
      ///
      /// Writing a 0 to a bit has no effect on the associated interrupt.
      inline void
      __attribute__((always_inline))
      Registers::writeInterruptClearPending(const index_t index,
          const reg32_t mask)
      {
        this->icpr[index] = mask;
      }

      /// \details
      /// The register reads back with the current pending state
      /// within a group of 32 interrupts.
      ///
      /// Reading a 1 means the interrupt is pending.
      inline reg32_t
      __attribute__((always_inline))
      Registers::readInterruptClearPending(const index_t index) const
      {
        return this->icpr[index];
      }

      /// \details
      /// Each bit represents the current active state for the
      /// associated interrupt within a group of 32. Each bit
      /// represents an interrupt
      /// number from N to N+31 (starting at interrupt 0, 32, 64, etc).
      inline reg32_t
      __attribute__((always_inline))
      Registers::readInterruptActiveBit(const index_t index) const
      {
        return this->iabr[index];
      }

      /// \details
      /// The priority registers are byte, aligned halfword and word accessible,
      /// but for convenience we use them as bytes.
      ///
      /// Write the priority to the corresponding interrupt.
      inline void
      __attribute__((always_inline))
      Registers::writeInterruptPriority(const interruptNumber_t number,
          const interruptPriority_t priority) const
      {
        this->ip[number] = priority;
      }

      /// \details
      /// The priority registers are byte, aligned halfword and word accessible,
      /// but for convenience we use them as bytes.
      ///
      /// Read the priority of the corresponding interrupt.
      inline interruptPriority_t
      __attribute__((always_inline))
      Registers::readInterruptPriority(const interruptNumber_t number) const
      {
        return this->ip[number];
      }

      /// \details
      /// The value written in this field is the interrupt to be
      /// triggered. This acts the same as storing to the
      /// corresponding ISPR[x] set-pending NVIC register bit.
      inline void
      __attribute__((always_inline))
      Registers::writeSoftwareTriggerInterrupt(const interruptNumber_t value)
      {
        this->stir = value;
      }

    // ========================================================================
    }// namespace nvic
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_NVICHARDWARE_H_
