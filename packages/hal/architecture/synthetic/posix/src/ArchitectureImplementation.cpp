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

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"

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

    void
    ArchitectureImplementation::yield(void)
    {
      ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().save();
      os::scheduler.performContextSwitch();
      ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().restore();
    }

    // ========================================================================

    /// \details
    /// A null stack will prevent creating a new context.
    void
    ThreadContext::create(hal::arch::stackElement_t* pStackBottom,
        hal::arch::stackSize_t stackSizeBytes,
        os::core::threadEntryPoint_t entryPoint, void* pParameters)
    {
#if defined(DEBUG)
      os::diag::trace.putString("create sb=");
      os::diag::trace.putHex((void*) pStackBottom);
      os::diag::trace.putString(", ss=");
      os::diag::trace.putDec((int) stackSizeBytes);
      os::diag::trace.putString(", ep=");
      os::diag::trace.putHex((void*) entryPoint);
      os::diag::trace.putString(", pp=");
      os::diag::trace.putHex(pParameters);
      os::diag::trace.putNewLine();
#endif

#pragma GCC diagnostic push
//#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//#endif

      if (pStackBottom != nullptr && stackSizeBytes != 0)
        {
#if 1
          // fetch current context
          if (getcontext(&m_context) != 0)
            {
#if defined(DEBUG)
              os::diag::trace.putString("getcontext failed with ");
              os::diag::trace.putString(strerror(errno));
              os::diag::trace.putNewLine();
#endif
            }
#endif

          // remove parent link
          m_context.uc_link = 0;

          // configure new stack, if not the main thread
          m_context.uc_stack.ss_sp = pStackBottom;
          m_context.uc_stack.ss_size = stackSizeBytes;
          m_context.uc_stack.ss_flags = 0;

          // configure entry point with one argument
          // warning: no error returned
          makecontext(&m_context, (void
          (*)())entryPoint, 1, pParameters);
        }

#pragma GCC diagnostic pop

      return;
    }

    /// \details
    /// Preserve errno and get context.
    void
    ThreadContext::save(void)
    {
      m_error = errno;

#pragma GCC diagnostic push
//#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//#endif

      if (getcontext(&m_context) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("getcontext failed with ");
          os::diag::trace.putString(strerror(errno));
          os::diag::trace.putNewLine();
#endif
        }

#pragma GCC diagnostic pop

    }

    /// \details
    /// Restore context and errno.
    void
    ThreadContext::restore(void)
    {
      errno = m_error;

#pragma GCC diagnostic push
//#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//#endif

      if (setcontext(&m_context) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("setcontext failed with ");
          os::diag::trace.putString(strerror(errno));
          os::diag::trace.putNewLine();
#endif
        }

#pragma GCC diagnostic pop

    }

  // --------------------------------------------------------------------------

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
