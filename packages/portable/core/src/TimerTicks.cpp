//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer ticks definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/TimerTicks.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    TimerTicks::TimerTicks(void)
        : TimerBase(m_array, sizeof(m_array) / sizeof(m_array[0]))
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif
    }

    TimerTicks::~TimerTicks()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    void
    TimerTicks::initialise(void)
    {
      m_implementation.initialise();
    }

    void
    TimerTicks::start(void)
    {
      m_implementation.start();
    }

    void
    TimerTicks::stop(void)
    {
      m_implementation.stop();
    }

    void
    TimerTicks::interruptServiceRoutine(void)
    {
      m_implementation.acknowledgeInterrupt();

      interruptTick();

#if defined(DEBUG) && defined(OS_DEBUG_OSTIMERTICKS_ISR_MARK_SECONDS)

  if ((i++ % OS_CFGINT_TICK_RATE_HZ) == 0)
    {
      OSDeviceDebug::putChar('!');
      if (OSSchedulerLock::isSet())
        OSDeviceDebug::putChar('L');
    }

#endif /* defined(DEBUG) && defined(OS_DEBUG_OSTIMERTICKS_ISR_MARK_SECONDS) */

    }

  // --------------------------------------------------------------------------
  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
