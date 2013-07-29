//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Definition of system abort().

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/abort.h"

#include "portable/diagnostics/include/Trace.h"

#include "portable/core/include/Platform.h"

namespace os
{
  namespace std
  {

    /// \details
    /// The program is terminated without executing destructors
    /// for objects of automatic, thread, or
    /// static storage duration and without calling functions
    /// passed to atexit() (3.6.3).
    ///
    /// The local implementation just calls the platform reset function.
    void
    abort(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // The platform reset will abruptly end the application,
      // without running any C++ destructors or cleanups.
      os::platform.resetSystem();
      // As defined in the declaration, it should never return
    }

  } // namespace std
} // namespace os
