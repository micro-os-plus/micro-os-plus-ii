//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M implementation of interrupts critical section.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/InterruptsCriticalSection.h"
#include "hal/architecture/arm/cortexm/include/Cpu.h"

// ----------------------------------------------------------------------------

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    // ========================================================================

    /// \details
    /// Store the current interrupt priority (BASEPRI) in the
    /// local private variable,
    /// and set a the new value, supposedly higher.
    InterruptsCriticalSection::InterruptsCriticalSection(void)
    {
      // Preserve the current priority locally.
      m_basepri = Cpu::getBASEPRI();

      // Set new priority. Always increase, never decrease
      Cpu::setBASEPRI_MAX(configMAX_SYSCALL_INTERRUPT_PRIORITY);
    }

    /// \details
    /// Restore the interrupt priority (BASEPRI) from the
    /// local private variable.
    InterruptsCriticalSection::~InterruptsCriticalSection()
    {
      // Restore the priority saved by the constructor.
      Cpu::setBASEPRI(m_basepri);
    }

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  // ========================================================================
  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
