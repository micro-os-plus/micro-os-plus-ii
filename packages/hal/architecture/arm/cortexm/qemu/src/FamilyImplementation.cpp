//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/qemu/include/FamilyImplementation.h"

#include "portable/diagnostics/include/Trace.h"

#include "hal/architecture/arm/cortexm/qemu/diagnostics/include/SemiHosting.h"

namespace hal
{
  namespace qemu
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The QEMU initialisation code.
    void
    FamilyImplementation::initialiseSystem(void)
    {
      //SystemInit();
    }

    /// \details
    /// The QEMU software reset code.
    void
    FamilyImplementation::resetSystem(void)
    {
      //NVIC_SystemReset();
      diag::SemiHosting::exit(0);
    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    FamilyImplementation::putGreeting(void)
    {
      os::diag::trace.putString("Synthetic ARM Cortex-M3");
      os::diag::trace.putNewLine();
    }
#endif

  // --------------------------------------------------------------------------

  }// namespace qemu
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU)
