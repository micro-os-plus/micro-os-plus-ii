//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS_Defines.h"

#include "../include/PlatformBase.h"
#include "../include/Architecture.h"

namespace os
{
  namespace core
  {

#if defined(DEBUG)

    void
    PlatformBase::putGreeting(void)
    {
      os::architecture.putGreeting();
    }

#endif

  } // namespace core
} //namespace os

