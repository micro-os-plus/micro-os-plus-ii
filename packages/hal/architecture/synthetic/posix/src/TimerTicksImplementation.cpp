//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of TimerTicks implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/XCDL_SchedulerDefines.h"

#include "portable/diagnostics/include/Trace.h"

#include "hal/architecture/synthetic/posix/include/TimerTicksImplementation.h"
#include "portable/core/include/TimerTicks.h"


#include <sys/time.h>

namespace hal
{
  namespace posix
  {

    // ========================================================================

    TimerTicksImplementation::TimerTicksImplementation(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      sigemptyset(&m_signalSet);
      sigaddset(&m_signalSet, timer::SIGNAL_NUMBER);
    }

    TimerTicksImplementation::~TimerTicksImplementation()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif

    }

    void
    TimerTicksImplementation::initialise(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // block signal
      sigprocmask(SIG_BLOCK, &m_signalSet, NULL);

      // set handler
      struct sigaction sa;
#if defined(__APPLE__)
      sa.__sigaction_u.__sa_handler = signalHandler;
#else
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif
      sa.sa_handler = signalHandler;
#pragma GCC diagnostic pop
#endif
      sigemptyset(&sa.sa_mask);
      sa.sa_flags = SA_RESTART;

      if (sigaction(timer::SIGNAL_NUMBER, &sa, NULL) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("sigaction() failed ");
          os::diag::trace.putNewLine();
#endif
        }

      // set timer
      struct itimerval tv;
      timerclear(&tv.it_value);
      tv.it_value.tv_sec = 0;
      tv.it_value.tv_usec = 1000000 / OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND;
      tv.it_interval.tv_sec = 0;
      tv.it_interval.tv_usec = 1000000 / OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND;
#if defined(__linux__)
#define TIMER   0
#else
#define TIMER   ITIMER_REAL
#endif
      if (setitimer(TIMER, &tv, NULL) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("setitimer() failed ");
          os::diag::trace.putNewLine();
#endif
        }
    }

    void
    TimerTicksImplementation::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // allow signal
      if (sigprocmask(SIG_UNBLOCK, &m_signalSet, NULL) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("sigprocmask() failed ");
          os::diag::trace.putNewLine();
#endif
        }

      pause();
#if 0
      for (int i = 50; i > 0; --i)
        {
          for (int j = 100; j > 0; --j)
            {
              char c = '.';
              write(1, &c, 1);
            }
          char cn = '\n';
          write(1, &cn, 1);
        }
#endif
    }

    void
    TimerTicksImplementation::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // block signal
      sigprocmask(SIG_BLOCK, &m_signalSet, NULL);

    }

    void
    TimerTicksImplementation::acknowledgeInterrupt(void)
    {
    }

    void
    TimerTicksImplementation::signalHandler(int signalNumber)
    {
      if (signalNumber != timer::SIGNAL_NUMBER)
        {
          char ce = '?';

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

          write(1, &ce, 1);

#pragma GCC diagnostic pop

          return;
        }

#if 0
      char c = '*';
      write(1, &c, 1);
#endif

      os::timerTicks.interruptServiceRoutine();
    }

  // ========================================================================

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
