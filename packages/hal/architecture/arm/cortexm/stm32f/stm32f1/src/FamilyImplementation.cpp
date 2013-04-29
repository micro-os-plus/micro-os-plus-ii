//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F1 definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/include/FamilyImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x.h"

namespace hal
{
  namespace stm32f1
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The STM32F1 initialisation code.
    /// Currently it is implemented using the CMSIS C routine.
    /// \todo Implement this in C++.
    void
    FamilyImplementation::initialiseSystem(void)
    {
      SystemInit();
    }

    /// \details
    /// The STM32F1 software reset code.
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
      uint32_t ul = *((uint32_t*) (0xE0042000));
      uint16_t devid = ul & 0x0FFF;
      os::diag::trace.putString("STM32");

      if (ul != 0)
        {
          // The IDs are from 31.6.1 of RM0008 reference manual
          if (devid == 0x0410)
            {
              os::diag::trace.putString("F1 MD");
            }
          else if (devid == 0x0412)
            {
              os::diag::trace.putString("F1 LD");
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
          os::diag::trace.putHex((uint16_t) (ul >> 16));
        }
      else
        {
          os::diag::trace.putString("F1xx no DEV_ID");
        }
      os::diag::trace.putString(", ");
      os::diag::trace.putDec(*((uint16_t*) (0x1FFFF7E0)));
      os::diag::trace.putString("K Flash");
      os::diag::trace.putNewLine();
      os::diag::trace.putString("UID=");
      os::diag::trace.putHex(*((uint32_t*) (0x1FFFF7F4)));
      os::diag::trace.putHex(*((uint32_t*) (0x1FFFF7F0)));
      os::diag::trace.putHex(*((uint16_t*) (0x1FFFF7EC)));
      os::diag::trace.putHex(*((uint16_t*) (0x1FFFF7E8)));
      os::diag::trace.putNewLine();
    }
#endif

  // --------------------------------------------------------------------------

  }// namespace stm32f1
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)
