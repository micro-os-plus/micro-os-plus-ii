//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)
#include "hal/architecture/arm/cortexm/stm32f/stm32f1/lib/stm/include/stm32f10x.h"
#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"
#else
#error "Missing family cmsis"
#endif

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
#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F1)

      uint32_t ul = *((uint32_t*)(0xE0042000));
      uint16_t devid = ul & 0x0FFF;
      os::diag::trace.putString("STM32");

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

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)

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
#else
      os::diag::trace.putString("Cortex-M");
      os::diag::trace.putNewLine();
#endif
    }
#endif

  // --------------------------------------------------------------------------

  } // namespace stm32f
} // namespace hal

extern "C" void
assert_failed(unsigned char*func, int lineno);

void
assert_failed(unsigned char*func __attribute__((unused)),
    int lineno __attribute__((unused)))
{
#if defined(DEBUG) || defined(__DOXYGEN__)
  os::diag::trace.putString(func);
  os::diag::trace.putString(" ");
  os::diag::trace.putDec(lineno);
  os::diag::trace.putNewLine();
#endif

  hal::cortexm::FamilyImplementation::resetSystem();
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
