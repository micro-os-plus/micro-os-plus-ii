//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyBase.h"
#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementationSelector.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The generic STM32F initialisation code.
    /// Overwrite it for each family with the actual code.
    void
    FamilyBase::initialiseSystem(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Missing initialiseSystem()");
      os::diag::trace.putNewLine();
#endif
    }

    /// \details
    /// The generic STM32F software reset code.
    /// Overwrite it for each family with the actual code.
    void
    FamilyBase::resetSystem(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Missing resetSystem()");
      os::diag::trace.putNewLine();
#endif
    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    FamilyBase::putGreeting(void)
    {
      os::diag::trace.putString("Cortex-M");
      os::diag::trace.putNewLine();
    }
#endif

  // --------------------------------------------------------------------------

  }// namespace stm32f
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
