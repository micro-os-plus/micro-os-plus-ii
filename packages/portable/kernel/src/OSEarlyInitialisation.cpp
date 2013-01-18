/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/kernel/include/OS_Defines.h"

#include "portable/devices/debug/include/Debug.h"

namespace os
{
  namespace core
  {

    class OSEarlyInitialisation
    {
    public:
      OSEarlyInitialisation();
    };

    OSEarlyInitialisation::OSEarlyInitialisation()
    {
      // clock init
      os::device::Debug::earlyInitialise();
      // other inits
    }
  }
}

// This should be the first constructor ever called
static os::core::OSEarlyInitialisation earlyInitialisation;

// For convenience, the debug constructor is also called early
os::device::Debug debug;

