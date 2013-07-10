//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Idle thread definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/IdleThread.h"
#include "portable/core/include/Scheduler.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// The main thread has no entry point, no parameters, no stack
    /// and very low priority.
    IdleThread::IdleThread(void)
        : Thread("idle", [](IdleThread* p)
          { p->threadMain();}, (IdleThread*) this, m_stack, sizeof(m_stack),
            os::core::Scheduler::IDLE_PRIORITY)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructorWithName();
#endif
      // TODO: add code
    }

    IdleThread::~IdleThread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif
    }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

    void
    IdleThread::threadMain(void)
    {
      for (;;)
        {
          os::scheduler.yield();
        }
    }

#pragma GCC diagnostic pop

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
