//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/FamilyImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"

namespace hal
{
  namespace stm32f4
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The STM32F4 initialisation code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++.
    void
    FamilyImplementation::initialiseSystem(void)
    {
      SystemInit();
    }

    /// \details
    /// The  STM32F4 software reset code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++.
    void
    FamilyImplementation::resetSystem(void)
    {
      NVIC_SystemReset();
    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    FamilyImplementation::putGreeting(void)
    {
      uint32_t ul = *((uint32_t*)(0xE0042000));
      uint16_t devid = ul & 0x0FFF;
      os::diag::trace.putString("STM32");
      if (devid == 0x0413)
        {
          os::diag::trace.putString("F4[01]X");
        }
      else if (devid == 0x0411)
        {
          os::diag::trace.putString("F4[01]X early");
        }
      else if (devid == 0x0419)
        {
          os::diag::trace.putString("F4[23]X");
        }
      else
        {
          os::diag::trace.putString("??");
        }
      os::diag::trace.putString(", DEV_ID=");
      os::diag::trace.putHex(devid);
      os::diag::trace.putString(", REV_ID=");
      os::diag::trace.putHex((uint16_t)(ul >> 16));
      os::diag::trace.putString(", ");
      os::diag::trace.putDec(*((uint16_t*)(0x1FFF7A22)));
      os::diag::trace.putString("K Flash");
      os::diag::trace.putNewLine();
      os::diag::trace.putString("UID=");
      os::diag::trace.putHex(*((uint32_t*)(0x1FFF7A18)));
      os::diag::trace.putHex(*((uint32_t*)(0x1FFF7A14)));
      os::diag::trace.putHex(*((uint32_t*)(0x1FFF7A10)));
      os::diag::trace.putNewLine();
    }
#endif

  // --------------------------------------------------------------------------

  } // namespace stm32f4
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
