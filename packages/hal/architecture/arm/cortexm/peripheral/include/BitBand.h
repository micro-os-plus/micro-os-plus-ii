//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M bit-banding classes.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBAND_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBAND_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace cortexm
  {
    static const address_t PERIPHERAL_BASE = 0x40000000UL;
    static const address_t PERIPHERAL_BITBAND_BASE = 0x42000000UL;

    namespace bitband
    {

      typedef uint32_t bitValue_t;

    } // namespace bitband

    // ========================================================================

    /// \headerfile BitBand.h "hal/architecture/arm/cortexm/peripheral/include/BitBand.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Bit banding class (static version).
    ///
    /// \details
    /// This class has only static member functions. One trick is that
    /// the generic address can be an unsigned, a reference or a pointer,
    /// and is automatically casted to address_t.

    class BitBand
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      BitBand() = delete;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Read one peripheral bit.
      template<typename A_T>
        static bitband::bitValue_t
        readPeripheralBitValue(A_T genericAddress, bitNumber_t bitNumber);

      /// \brief Write one peripheral bit.
      template<typename A_T>
        static void
        writePeripheralBitValue(A_T genericAddress, bitNumber_t bitNumber,
            bitband::bitValue_t value);

      /// \brief Set one peripheral bit to 1.
      template<typename A_T>
        static void
        setPeripheralBit(A_T genericAddress, bitNumber_t bitNumber);

      /// \brief Clear one peripheral bit to 0.
      template<typename A_T>
        static void
        clearPeripheralBit(A_T genericAddress, bitNumber_t bitNumber);

      /// @} end of name Public member functions

    private:
      /// \name Private member functions
      /// @{

      /// \brief Compute the peripheral bit band address.
      template<typename A_T>
        static address_t
        computePeripheralBitWordAddress(A_T genericAddress,
            bitNumber_t bitNumber);

      /// @} end of name Private member functions
    };

    // ----- Inline member function definitions -------------------------------

    /// \details
    /// Each peripheral bit has a separate word in the bit-band space.
    template<typename A_T>
      address_t
      inline __attribute__((always_inline))
      BitBand::computePeripheralBitWordAddress(A_T genericAddress,
          bitNumber_t bitNumber)
      {
        // The generic address can be an unsigned, a reference or a pointer,
        // so the first step is to cast it to an address_t (an unsigned).
        address_t registerAddress =
            reinterpret_cast<hal::cortexm::address_t>(genericAddress);

        // Then compute the offset in the peripheral address space
        address_t const peripheralOffset = registerAddress - PERIPHERAL_BASE;

        // Each bit will have its own location, so, since there are 8 bits
        // in a byte, first multiply the address by 8 and add the bit number
        // and then multiply by 4 to make each address an word offset.
        address_t const bitWordOffset = ((peripheralOffset * 8) + bitNumber)
            * 4;

        // Finally add the bit-banding base address and return the result
        return PERIPHERAL_BITBAND_BASE + bitWordOffset;
      }

    /// \details
    /// Compute the bit-banding address and return the corresponding
    /// bit as a word.
    template<typename A_T>
      bitband::bitValue_t
      inline __attribute__((always_inline))
      BitBand::readPeripheralBitValue(A_T genericAddress, bitNumber_t bitNumber)
      {
        const address_t bitWordAddress = computePeripheralBitWordAddress(
            genericAddress, bitNumber);

        volatile address_t* const bitWordPointer =
            reinterpret_cast<uint32_t*>(bitWordAddress);

        // return only the least significant bit, all other are 0
        return *bitWordPointer;
      }

    /// \details
    /// Compute the bit-banding address and write the corresponding
    /// bit as a word.
    template<typename A_T>
      void
      inline __attribute__((always_inline))
      BitBand::writePeripheralBitValue(A_T genericAddress,
          bitNumber_t bitNumber, bitband::bitValue_t value)
      {
        const address_t bitWordAddress = computePeripheralBitWordAddress(
            genericAddress, bitNumber);

        volatile address_t* const bitWordPointer =
            reinterpret_cast<uint32_t*>(bitWordAddress);

        // only the least significant bit is used, all other are ignored
        *bitWordPointer = value;
      }

    /// \details
    /// Compute the bit-banding address and set the corresponding
    /// bit to 1.
    template<typename A_T>
      void
      inline __attribute__((always_inline))
      BitBand::setPeripheralBit(A_T genericAddress, bitNumber_t bitNumber)
      {
        writePeripheralBitValue(genericAddress, bitNumber, 1);
      }

    /// \details
    /// Compute the bit-banding address and secleart the corresponding
    /// bit to 0.
    template<typename A_T>
      void
      inline __attribute__((always_inline))
      BitBand::clearPeripheralBit(A_T genericAddress, bitNumber_t bitNumber)
      {
        writePeripheralBitValue(genericAddress, bitNumber, 0);
      }

  // ==========================================================================

  }// namespace cortexm
} // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBAND_H_
