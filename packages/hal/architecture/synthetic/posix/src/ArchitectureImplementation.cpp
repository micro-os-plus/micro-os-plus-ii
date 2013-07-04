//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of architecture implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#include <sys/utsname.h>

namespace hal
{
  namespace posix
  {
    // ------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)
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

    // ========================================================================

    void
    ArchitectureImplementation::ThreadContext::create(
        hal::arch::stackElement_t* pStackBottom,
        hal::arch::stackSize_t stackSize,
        os::core::threadEntryPoint_t entryPoint, void* pParameters)
    {
      m_context.uc_link = 0;
      m_context.uc_stack.ss_sp = pStackBottom;
      m_context.uc_stack.ss_size = stackSize * sizeof(hal::arch::stackElement_t);
      m_context.uc_stack.ss_flags = 0;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

      makecontext(&m_context, (void
      (*)())entryPoint, 1, pParameters);

#pragma GCC diagnostic pop

      return;
    }

  // --------------------------------------------------------------------------

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
