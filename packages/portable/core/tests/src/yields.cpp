//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS.h"

#include "portable/core/include/Thread.h"

static const os::core::Stack::size_t STACK_SIZE = 30;

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------

int
main()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

  os::scheduler.run();

  return 0;
}

