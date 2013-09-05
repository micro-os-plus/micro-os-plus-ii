//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer ticks definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/TimerTicks.h"
#include "portable/core/include/TimerSeconds.h"
#include "portable/core/include/Scheduler.h"

//#define OS_DEBUG_TIMERTICKS_ISR_MARK_SECONDS (1)

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Call the TimerBase constructor with the current array.
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

    /// \details
    /// Call the implementation code.
    void
    TimerTicks::initialise(void)
    {
      m_implementation.initialise();
    }

    /// \details
    /// Call the implementation code.
    void
    TimerTicks::start(void)
    {
      m_implementation.start();
    }

    /// \details
    /// Call the implementation code.
    void
    TimerTicks::stop(void)
    {
      m_implementation.stop();
    }

    /// \details
    /// Called from the interrupt handler, for each tick interrupt.
    /// Basically call the TimerBase code.
    void
    TimerTicks::interruptServiceRoutine(void)
    {
      m_implementation.acknowledgeInterrupt();

      TimerBase::interruptServiceRoutine();

      // Call the derived timer ISR
      os::timerSeconds.interruptServiceRoutine();

#if defined(DEBUG) && defined(OS_DEBUG_TIMERTICKS_ISR_MARK_SECONDS)

      static int i = 0;

      if ((i++ % OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND)== 0){
        os::diag::trace.putChar('!');
        if (os::scheduler.isLocked())
          {
            os::diag::trace.putChar('L');
          }
      }

#endif /* defined(DEBUG) && defined(OS_DEBUG_TIMERTICKS_ISR_MARK_SECONDS) */

  }

// --------------------------------------------------------------------------
}// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
