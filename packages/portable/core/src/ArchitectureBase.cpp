//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base definitions for implementations of the architecture classes.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/ArchitectureBase.h"
#include "portable/core/include/Scheduler.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)

    /// \details
    /// Default output the scheduler greeting.
    void
    ArchitectureBase::putGreeting(void)
    {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
      os::scheduler.putGreeting();
#endif
    }

#endif // defined(DEBUG)
  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

