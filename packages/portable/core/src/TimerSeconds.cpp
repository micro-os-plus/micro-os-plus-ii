//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer seconds definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/TimerSeconds.h"
#include "portable/core/include/Scheduler.h"

#if defined(DEBUG)
#define OS_DEBUG_TIMERSECONDS_ISR_MARK_SECONDS (1)
#endif

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Call the TimerBase constructor with the current array.
    TimerSeconds::TimerSeconds(void) :
        TimerBase(m_array, sizeof(m_array) / sizeof(m_array[0]))
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      // Force the first second at the first tick
      m_ticks = OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND;
    }

    TimerSeconds::~TimerSeconds()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    /// Call the implementation code.
    void
    TimerSeconds::initialise(void)
    {
    }

    /// \details
    /// Call the implementation code.
    void
    TimerSeconds::start(void)
    {
      m_ticks = 0;
    }

    /// \details
    /// Call the implementation code.
    void
    TimerSeconds::stop(void)
    {
    }

    /// \details
    /// Called from the interrupt handler, for each tick interrupt.
    /// Basically call the TimerBase code.
    void
    TimerSeconds::interruptServiceRoutine(void)
    {
      if (++m_ticks > OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND)
        {
          TimerBase::interruptServiceRoutine();
          m_ticks = 0;

#if defined(DEBUG) && defined(OS_DEBUG_TIMERSECONDS_ISR_MARK_SECONDS)

          os::diag::trace.putChar('!');
          if (os::scheduler.isLocked())
            {
              os::diag::trace.putChar('L');
            }

#endif /* defined(DEBUG) && defined(OS_DEBUG_TIMERSECONDS_ISR_MARK_SECONDS) */

        }
    }

  // --------------------------------------------------------------------------
  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
