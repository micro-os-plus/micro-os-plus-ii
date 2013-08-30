//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/MainThread.h"

int
main()
{

#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  os::scheduler.start();

  os::scheduler.yield();

  //os::mainThread.sleepFor(0);

  os::scheduler.stop();

  return 0;
}

