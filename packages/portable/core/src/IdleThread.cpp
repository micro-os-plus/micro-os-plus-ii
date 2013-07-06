//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Idle thread definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/IdleThread.h"
#include "portable/core/include/Scheduler.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

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

