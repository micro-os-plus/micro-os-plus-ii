/*
 *      Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/core/include/OS_Defines.h"

#include "portable/devices/debug/include/Debug.h"

namespace os
{
  namespace core
  {

    class EarlyInitialisation
    {
    public:
      EarlyInitialisation();
    };

    EarlyInitialisation::EarlyInitialisation()
    {
      // clock init
      os::device::Debug::earlyInitialise();
      // other inits
    }
  }
}

// This should be the first constructor ever called
static os::core::EarlyInitialisation earlyInitialisation;

// For convenience, the debug constructor is also called early
os::device::Debug debug;

