//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base definitions for implementations of the platform classes.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/PlatformBase.h"
#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

#if defined(DEBUG)

    /// \details
    /// Call the architecture function.
    void
    PlatformBase::putGreeting(void)
    {
      os::architecture.putGreeting();
    }

#endif

    // ------------------------------------------------------------------------
  } // namespace core
} //namespace os

