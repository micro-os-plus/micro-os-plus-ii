//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 Independent Watchdog memory mapped registers & definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDGHARDWARE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDGHARDWARE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/peripheral/include/BitBand.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/MemoryMap.h"

namespace hal
{
  namespace stm32f4
  {
    namespace iwdg
    {

      typedef hal::cortexm::portNumber_t portNumber_t;
      typedef hal::cortexm::bitNumber_t bitNumber_t;
      typedef hal::cortexm::index_t index_t;

      typedef hal::cortexm::bitband::bitValue_t bitValue_t;
      typedef hal::cortexm::reg16_t reg16_t;
      typedef hal::cortexm::reg32_t reg32_t;
    }

    namespace iwdg
    {
      /// \addtogroup stm32f4_iwdg
      /// @{

      // ----------------------------------------------------------------------

      static const reg16_t ACCESS_KEY = 0x5555U;
      static const reg16_t START_KEY = 0xCCCCU;
      static const reg16_t RELOAD_KEY = 0xAAAAU;

      // ----------------------------------------------------------------------

      /// \brief Prescaler divider type.
      typedef uint32_t prescalerDivider_t;

      /// \brief Prescaler divider values.
      enum class PrescalerDivider
        : prescalerDivider_t
          {
            _4 = 0, _8, _16, _32, _64, _128, _256, _256b
      };

      // ----------------------------------------------------------------------

        /// \brief Reload register type.
      typedef uint16_t reloadValue_t;

      // ----------------------------------------------------------------------

      /// @} end of addtogroup stm32f4_iwdg

      // ======================================================================

      /// \headerfile IwdgHardware.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/IwdgHardware.h"
      /// \ingroup stm32f4_iwdg
      /// \nosubgrouping
      ///
      /// \brief IWDG memory mapped registers.
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

        /// \brief Write the key register.
        ///
        /// \param [in] value A 16-bit value.
        /// \par Returns
        ///    Nothing.
        void
        writeKey(const reg16_t value);

        /// \brief Read the prescaler register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 3-bit value.
        reg16_t
        readPrescaler(void);

        /// \brief Write the prescaler register.
        ///
        /// \param [in] value A 3-bit value.
        /// \par Returns
        ///    Nothing.
        void
        writePrescaler(const reg16_t value);

        /// \brief Read the reload register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 12-bit value.
        reg16_t
        readReload(void);

        /// \brief Write the reload register.
        ///
        /// \param [in] value A 12-bit value.
        /// \par Returns
        ///    Nothing.
        void
        writeReload(const reg16_t value);

        /// \brief Read the status register.
        ///
        /// \par Parameters
        ///    None.
        /// \return A 2-bit value.
        reg16_t
        readStatus(void);

        /// @} end of Public member functions

        /// \name Memory definitions
        /// @{

        /// \brief Base address of the device.
        static const hal::cortexm::address_t MEMORY_BASE_ADDRESS =
            MemoryMap::IWDG_BASE_ADDRESS;

        /// @} end of name Memory definitions

      private:
        /// \name Private memory mapped registers
        /// @{

        /// \brief 0x0000 - Key register.
        hal::cortexm::regWriteOnly_t kr;
        /// \brief 0x0004 - Prescaler register.
        hal::cortexm::regReadWrite_t pr;
        /// \brief 0x0008 - Reload register.
        hal::cortexm::regReadWrite_t rlr;
        /// \brief 0x000C - Status register.
        hal::cortexm::regReadOnly_t sr;

        /// @} end of name Memory mapped registers

      };

      // ----- Inline member function definitions -----------------------------

      inline void
      __attribute__((always_inline))
      Registers::writeKey(const reg16_t value)
      {
        this->kr = value;
      }

      inline reg16_t
      __attribute__((always_inline))
      Registers::readPrescaler(void)
      {
        return this->pr;
      }

      inline void
      __attribute__((always_inline))
      Registers::writePrescaler(const reg16_t value)
      {
        this->pr = value;
      }

      inline reg16_t
      __attribute__((always_inline))
      Registers::readReload(void)
      {
        return this->rlr;
      }

      inline void
      __attribute__((always_inline))
      Registers::writeReload(const reg16_t value)
      {
        this->rlr = value;
      }

      inline reg16_t
      __attribute__((always_inline))
      Registers::readStatus(void)
      {
        return this->sr;
      }

    // ========================================================================
    }// namespace iwdg
  } // namespace stm32f4
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_IWDGHARDWARE_H_
