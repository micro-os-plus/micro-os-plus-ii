//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of architecture implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "hal/architecture/synthetic/posix/include/InterruptsCriticalSection.h"
#include "hal/architecture/synthetic/posix/include/TimerTicksImplementation.h"

namespace hal
{
  namespace posix
  {

    // ========================================================================

    /// \details
    /// Store the current signal status in the local private variable,
    /// and block the signal used by the ticks timer.
    InterruptsCriticalSection::InterruptsCriticalSection(void)
    {
      sigset_t set;
      sigemptyset(&set);
      sigaddset(&set, timer::SIGNAL_NUMBER);

      sigprocmask(SIG_BLOCK, &set, &m_status);
    }

    /// \details
    /// Restore the signal status from the local private variable.
    InterruptsCriticalSection::~InterruptsCriticalSection()
    {
      sigprocmask(SIG_SETMASK, &m_status, nullptr);
    }

  // ==========================================================================

  }// namespace posix
}    // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
