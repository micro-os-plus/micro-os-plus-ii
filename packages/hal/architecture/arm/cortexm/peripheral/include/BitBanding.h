//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M bit-banding classes.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBANDING_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBANDING_H_

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

      // ----------------------------------------------------------------------

      address_t
      inline __attribute__((always_inline))
      getPeripheralBitWordAddress(address_t registerAddress,
          bitNumber_t bitNumber)
      {
        address_t const peripheralOffset = registerAddress - PERIPHERAL_BASE;

        // first compute the byte offset and then make it word offset
        address_t const bitWordOffset = ((peripheralOffset * 8) + bitNumber)
            * 4;

        return PERIPHERAL_BITBAND_BASE + bitWordOffset;
      }

      bitValue_t
      inline __attribute__((always_inline))
      getPeripheralBitValue(address_t registerAddress, bitNumber_t bitNumber)
      {
        const address_t bitWordAddress = getPeripheralBitWordAddress(
            registerAddress, bitNumber);

        volatile address_t* const bitWordPointer =
            reinterpret_cast<uint32_t*>(bitWordAddress);

        // return only the least significant bit, all other are 0
        return *bitWordPointer;
      }

      void
      inline __attribute__((always_inline))
      setPeripheralBitValue(address_t registerAddress, bitNumber_t bitNumber,
          bitValue_t value)
      {
        const address_t bitWordAddress = getPeripheralBitWordAddress(
            registerAddress, bitNumber);

        volatile address_t* const bitWordPointer =
            reinterpret_cast<uint32_t*>(bitWordAddress);

        // only the least significant bit is used, all other are ignored
        *bitWordPointer = value;
      }

      // ----------------------------------------------------------------------

      address_t
      inline __attribute__((always_inline))
      getPeripheralBitWordAddress(void* registerPointer, bitNumber_t bitNumber)
      {
        address_t registerAddress =
            reinterpret_cast<hal::cortexm::address_t>(registerPointer);

        address_t const peripheralOffset = registerAddress - PERIPHERAL_BASE;

        // first compute the byte offset and then make it word offset
        address_t const bitWordOffset = ((peripheralOffset * 8) + bitNumber)
            * 4;

        return PERIPHERAL_BITBAND_BASE + bitWordOffset;
      }

      bitValue_t
      inline __attribute__((always_inline))
      getPeripheralBitValue(void* registerPointer, bitNumber_t bitNumber)
      {
        const address_t bitWordAddress = getPeripheralBitWordAddress(
            registerPointer, bitNumber);

        volatile address_t* const bitWordPointer =
            reinterpret_cast<uint32_t*>(bitWordAddress);

        // return only the least significant bit, all other are 0
        return *bitWordPointer;
      }

    // ----------------------------------------------------------------------

    }// namespace bitband
  } // namespace cortexm
} // namespace hal
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PERIPHERAL_BITBANDING_H_
