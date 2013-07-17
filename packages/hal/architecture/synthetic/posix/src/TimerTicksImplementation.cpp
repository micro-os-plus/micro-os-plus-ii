//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of TimerTicks implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

#include "hal/architecture/synthetic/posix/include/TimerTicksImplementation.h"


namespace hal
{
  namespace posix
  {

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    // ========================================================================

    void
    TimerTicksImplementation::initialise(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
    }

    void
    TimerTicksImplementation::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
    }

    void
    TimerTicksImplementation::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
    }


    void
    TimerTicksImplementation::acknowledgeInterrupt(void)
    {
    }

    // ========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
