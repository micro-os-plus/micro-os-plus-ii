//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#include <sys/utsname.h>

namespace hal
{
  namespace arch
  {
    namespace posix
    {
      // ----------------------------------------------------------------------

#if defined(DEBUG)
      /// \details
      /// Write a POSIX specific greeting to the Trace device. If `uname()`
      /// returns a valid response, write detailed response.
      void
      ArchitectureImplementation::putGreeting(void)
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
          }
        else
          {
            os::diag::trace.putString("POSIX synthetic");
          }
        os::diag::trace.putNewLine();
      }
#endif

      // ----------------------------------------------------------------------

    } // namespace posix
  } // namespace arch
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
