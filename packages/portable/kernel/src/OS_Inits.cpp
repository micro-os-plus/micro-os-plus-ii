/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/kernel/include/OS_Defines.h"

#include "portable/devices/debug/include/Debug.h"

// Dynamically generated
#include "portable/kernel/include/OS_Inits_Defines.h"

namespace os
{
  namespace core
  {
    void
    earlyInitialise(void) __attribute__((constructor(OS_INTEGER_EARLYINITIALISE_INIT_PRIORITY)));
  }
}

namespace os
{
  namespace core
  {
    // This runs before the first constructor
    void
    earlyInitialise(void)
    {
      // clock init
      os::device::Debug::earlyInitialise();
      // other inits
    }
  }
}

os::device::Debug debug __attribute__((init_priority(OS_INTEGER_DEBUG_INIT_PRIORITY)));

