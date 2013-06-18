//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Scheduler definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"

//#include "portable/core/include/PlatformBase.h"
//#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    Scheduler::Scheduler()
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

    }

    /// \details
    Scheduler::~Scheduler()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif

    }

    /// \details
    /// If the ID is valid, just return it, the thread was already registered.
    /// Otherwise... TBD
    Scheduler::threadId_t
    Scheduler::registerThread(Thread* pThread)
    {
      threadId_t id = pThread->getId();
      if (id != NO_ID)
        {
          return id;
        }
      // TBD
      return 0;
    }

    /// \details
    /// If the thread is still registered, deregister it.
    Scheduler::threadId_t
    Scheduler::deregisterThread(Thread* pThread)
    {
      if (pThread->getId() != NO_ID)
        {
          // TBD
        }
      return NO_ID;
    }

    void
    Scheduler::run(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif

    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

