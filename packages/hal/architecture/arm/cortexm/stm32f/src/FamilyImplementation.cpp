//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The generic STM32F initialisation code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++.
    void
    FamilyImplementation::initialiseSystem(void)
    {
      SystemInit();
    }

    /// \details
    /// The generic STM32F software reset code.
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
#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)
      uint32_t ul = *((uint32_t*)(0xE0042000));
      uint16_t devid = ul & 0x0FFF;
      os::diag::trace.putString("STM32");
      if (devid == 0x0410)
        {
          os::diag::trace.putString("F1 MD");
        }
      else if (devid == 0x0414)
        {
          os::diag::trace.putString("F1 HD");
        }
      else if (devid == 0x0430)
        {
          os::diag::trace.putString("F1 XL");
        }
      else if (devid == 0x0418)
        {
          os::diag::trace.putString("F1 CL");
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
      os::diag::trace.putDec(*((uint16_t*)(0x1FFFF7E0)));
      os::diag::trace.putString("K Flash");
      os::diag::trace.putNewLine();
      os::diag::trace.putString("UID=");
      os::diag::trace.putHex(*((uint32_t*)(0x1FFFF7F4)));
      os::diag::trace.putHex(*((uint32_t*)(0x1FFFF7F0)));
      os::diag::trace.putHex(*((uint16_t*)(0x1FFFF7EC)));
      os::diag::trace.putHex(*((uint16_t*)(0x1FFFF7E8)));
      os::diag::trace.putNewLine();
#else
      os::diag::trace.putString("Cortex-M");
      os::diag::trace.putNewLine();
#endif
    }
#endif

  // --------------------------------------------------------------------------

  }
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
