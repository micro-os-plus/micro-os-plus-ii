//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Error definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    void
    Error::clear(void)
    {
      os::scheduler.getCurrentThread()->setError(NONE);
    }

    Error&
    Error::operator=(errorNumber_t error)
    {

      os::scheduler.getCurrentThread()->setError(error);

      return *this;
    }

    bool
    Error::operator==(errorNumber_t error)
    {
      return (os::scheduler.getCurrentThread()->getError() == error);
    }

    bool
    Error::operator!=(errorNumber_t error)
    {
      return (os::scheduler.getCurrentThread()->getError() == error);
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

