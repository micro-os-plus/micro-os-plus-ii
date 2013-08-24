//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of thread context.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "hal/architecture/synthetic/posix/include/ThreadContext.h"

namespace hal
{
  namespace posix
  {
    // ========================================================================

#if defined(DEBUG)
//#define OS_DEBUG_THREADCONTEXT  1
#endif

    /// \details
    /// Used to explicitly initialise m_error and the m_saved flag.
    ThreadContext::ThreadContext(void)
    {
      m_error = 0;
      m_saved = false;

#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putString(" ctx @");
      os::diag::trace.putHex((void*) &m_context);
#if defined(__APPLE__)
      os::diag::trace.putString(", mctx @");
      os::diag::trace.putHex((void*) &m_context.__mcontext_data);
      os::diag::trace.putString(", sz=");
      os::diag::trace.putDec(sizeof(m_context.__mcontext_data));
#endif
      os::diag::trace.putNewLine();
#endif
    }

    ThreadContext::~ThreadContext()
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    /// A null stack will prevent creating a new context (used by main thread
    /// which is already running).
    ///
    /// The trampolineEntryPoint is pointing to the thread trampoline,
    /// a small routine used to gain control after the thread main code
    /// terminates.
    void
    ThreadContext::create(hal::arch::stackElement_t* pStackBottom,
        hal::arch::stackSize_t stackSizeBytes,
        os::core::trampoline3_t trampolineEntryPoint, void* p1, void* p2,
        void* p3)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
      os::diag::trace.putString("ThreadContext::create()");
      os::diag::trace.putString(" stack=");
      os::diag::trace.putHex((void*) pStackBottom);
      os::diag::trace.putString("-");
      os::diag::trace.putHex(
          (void*) (pStackBottom
              + stackSizeBytes / sizeof(hal::arch::stackElement_t)));
      os::diag::trace.putString(", size=");
      os::diag::trace.putDec(stackSizeBytes);
      os::diag::trace.putString(", entry=");
      os::diag::trace.putHex((void*) trampolineEntryPoint);
      os::diag::trace.putString(", p1=");
      os::diag::trace.putHex(p1);
      os::diag::trace.putString(", p2=");
      os::diag::trace.putHex(p2);
      os::diag::trace.putString(", p3=");
      os::diag::trace.putHex(p3);
      os::diag::trace.putNewLine();
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

      if (pStackBottom != nullptr && stackSizeBytes != 0)
        {
          // Fetch the current context and store it in the private member.
          if (getcontext(&m_context) != 0)
            {
#if defined(DEBUG)
              os::diag::trace.putString("getcontext failed with ");
              os::diag::trace.putString(strerror(errno));
              os::diag::trace.putNewLine();
#endif
            }

          // The context in itself is not needed, but makecontext()
          // requires a context obtained by getcontext(), so we got it and
          // now we modify it to suit our needs.

          // Remove the parent link.
          m_context.uc_link = 0;

          // Configure the new stack (for the main thread both values are 0)
          m_context.uc_stack.ss_sp = pStackBottom;
          m_context.uc_stack.ss_size = stackSizeBytes;
          m_context.uc_stack.ss_flags = 0;

          // Used to avoid a complex casts below,
          // that might confuse the Eclipse formatter.
          typedef void
          (*mfunc)();

          // Configure the entry point with three arguments
          // warning: no error returned
          makecontext(&m_context, (mfunc) trampolineEntryPoint, 3, p1, p2, p3);
        }

#pragma GCC diagnostic pop

      // restore() will set it anyway to false, but for just in case.
      m_saved = false;

      return;
    }

  // ==========================================================================

  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
