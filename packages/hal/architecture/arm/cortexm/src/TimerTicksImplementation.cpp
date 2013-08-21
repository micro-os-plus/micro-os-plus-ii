//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M definitions of TimerTicks implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/XCDL_SchedulerDefines.h"

#include "portable/diagnostics/include/Trace.h"

#include "hal/architecture/arm/cortexm/include/TimerTicksImplementation.h"
#include "portable/core/include/TimerTicks.h"

#include <sys/time.h>

namespace hal
{
  namespace cortexm
  {

    // ========================================================================

    /// \details
    TimerTicksImplementation::TimerTicksImplementation(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

    }

    TimerTicksImplementation::~TimerTicksImplementation()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    void
    TimerTicksImplementation::initialise(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

    }

    /// \details
    void
    TimerTicksImplementation::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

    }

    /// \details
    void
    TimerTicksImplementation::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

    }

    /// \details
    /// Not needed, signals can be configured to re-trigger automatically,
    /// without program intervention.
    void
    TimerTicksImplementation::acknowledgeInterrupt(void)
    {
    }

    /// \details
    /// This is the routine called by the system as signal handler.
    /// It must be static, and have one integer parameter.
    ///
    /// Besides some diagnostics, at the end it calls the timer
    /// interrupt service routine.
    void
    TimerTicksImplementation::signalHandler(int)
    {

      // Call the ticks timer ISR
      os::timerTicks.interruptServiceRoutine();
    }

  // ========================================================================

  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
