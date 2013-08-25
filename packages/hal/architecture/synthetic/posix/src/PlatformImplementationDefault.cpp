//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX default platform definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "hal/architecture/synthetic/posix/include/PlatformImplementationDefault.h"
#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#include "portable/diagnostics/include/Trace.h"

// Platform headers
#include <sys/utsname.h>

namespace hal
{
  namespace posix
  {
    // ========================================================================

#if defined(DEBUG) || defined(__DOXYGEN__)
    /// \details
    /// Write a POSIX specific greeting to the Trace device. If `uname()`
    /// returns a valid response, write detailed response.
    void
    PlatformImplementationDefault::putGreeting(void)
    {
      struct utsname name;

      if (::uname(&name) != -1)
        {
          os::diag::trace.putString("POSIX synthetic, running on ");
          os::diag::trace.putString(name.machine);
          os::diag::trace.putString(" ");
          os::diag::trace.putString(name.sysname);
          os::diag::trace.putString(" ");
          os::diag::trace.putString(name.release);
          os::diag::trace.putString(".");
        }
      else
        {
          os::diag::trace.putString("POSIX synthetic.");
        }
      os::diag::trace.putNewLine();

      // Then call the architecture specific greetings
      os::architecture.putGreeting();
    }
#endif // defined(DEBUG)
  // ==========================================================================

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
