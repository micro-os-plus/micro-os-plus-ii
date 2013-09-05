//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of architecture implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"
#include "portable/core/include/Thread.h"
#include "portable/diagnostics/include/Trace.h"

// Platform headers
#include <string.h>
#include <sys/utsname.h>
#include <sys/time.h>

namespace hal
{
  namespace posix
  {
    // ========================================================================

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    /// \details
    /// Save the current context, perform the context switch
    /// and return to the next thread selected by the scheduler.
    ///
    /// \note save() uses the classical trick of entering once
    /// and returning twice, the second time after restore().
    void
    ArchitectureImplementation::yield(void)
    {
#if defined(COMPILER_INLINES_GETCONTEXT)
      if ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().save())
#else
      // ----- inline Context.save() begin ------------------------------------

      // getcontext() is like setjmp(), it cannot be used from
      // a separate function that returns before longjmp(),
      // so we manually inline the content of Context.save()

      os::core::Thread::Context& context =
          (((os::core::Thread*) os::scheduler.getCurrentThread())->getContext());

      context.m_error = errno;
      context.m_saved = true;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
      getcontext(&context.m_context);
#pragma GCC diagnostic pop

      // ----- inline Context.save() end --------------------------------------

      // save()/getcontext() are functions that return twice
      if (context.m_saved)
#endif // COMPILER_INLINES_GETCONTEXT
        {
          // Here we are right after saving the context (the first return),
          // when we have to select the next context
            { // ---- InterruptsCriticalSection begin -------------------------
              os::core::scheduler::InterruptsCriticalSection cs;

              os::scheduler.prepareContextSwitchNoInterrupts();
            } // ---- InterruptsCriticalSection end ---------------------------
          // and resume from there
          ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().restore();
        }
      else
        {
          // Here we are after restore (the second return),
          // when we have nothing else to do, just return to the new thread
        }
    }
#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
    // ------------------------------------------------------------------------

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific code.
    void
    ArchitectureImplementation::busyWaitMicros(uint32_t micros)
    {
      if (micros == 0)
        return;

      timeval begTime;
      gettimeofday(&begTime, 0);

#if defined(_DEBUG)
      os::diag::trace.putChar('w');
      os::diag::trace.putDec(micros);
#endif

      long deltaMicros;
      do
        {
          timeval endTime;
          gettimeofday(&endTime, 0);
          deltaMicros = (endTime.tv_sec - begTime.tv_sec) * 1000000
              + (endTime.tv_usec - begTime.tv_usec);
        }
      while (deltaMicros < static_cast<long>(micros));

    }

  // ==========================================================================

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
