//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of architecture implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include <string.h>

#include "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"
#include "portable/core/include/Thread.h"

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
          os::diag::trace.putString(".");
        }
      else
        {
          os::diag::trace.putString("POSIX synthetic.");
        }
      os::diag::trace.putNewLine();

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
      os::scheduler.putGreeting();
#endif

    }
#endif

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    // ========================================================================

    InterruptsCriticalSection::InterruptsCriticalSection(void)
    {
      // TODO: save status
      sigset_t set;
      sigemptyset(&set);
      sigaddset(&set, timer::SIGNAL_NUMBER);

      sigprocmask(SIG_BLOCK, &set, &m_status);
    }

    InterruptsCriticalSection::~InterruptsCriticalSection()
    {
      // TODO: restore status
      sigprocmask(SIG_SETMASK, &m_status, NULL);
    }

    // ========================================================================

#if defined(DEBUG)
//#define OS_DEBUG_THREADCONTEXT  1
#endif

    /// \details
    /// Used only to explicitly initialise m_error.
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

    /// \details
    /// Used only to explicitly initialise m_error.
    ThreadContext::~ThreadContext()
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
      os::diag::trace.putDestructor();
#endif
    }

    typedef void
    (*mfunc)();

    /// \details
    /// A null stack will prevent creating a new context.
    void
    ThreadContext::create(hal::arch::stackElement_t* pStackBottom,
        hal::arch::stackSize_t stackSizeBytes,
        os::core::trampoline3_t entryPoint, void* p1, void* p2, void* p3)
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
      os::diag::trace.putHex((void*) entryPoint);
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
          // fetch current context
          if (getcontext(&m_context) != 0)
            {
#if defined(DEBUG)
              os::diag::trace.putString("getcontext failed with ");
              os::diag::trace.putString(strerror(errno));
              os::diag::trace.putNewLine();
#endif
            }

          // remove parent link
          m_context.uc_link = 0;

          // configure new stack, if not the main thread
          m_context.uc_stack.ss_sp = pStackBottom;
          m_context.uc_stack.ss_size = stackSizeBytes;
          m_context.uc_stack.ss_flags = 0;

          // configure entry point with one argument
          // warning: no error returned
          makecontext(&m_context, (mfunc) entryPoint, 3, p1, p2, p3);
        }

#pragma GCC diagnostic pop

      m_saved = false;

      return;
    }

    /// \details
    /// Preserve errno and get context.
    /// \warning Due to some compiler complicated reasons, it could not be
    /// inlined, so its content was manually inlined in yield().
    inline bool
    __attribute__((always_inline))
    ThreadContext::save(void)
    {
      m_error = errno;
      m_saved = true;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

      // This function will return twice, the second time after setcontext()
      if (getcontext(&m_context) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("getcontext failed with ");
          os::diag::trace.putString(strerror(errno));
          os::diag::trace.putNewLine();
#endif
        }

#pragma GCC diagnostic pop

      // Set to false by restore()
      return m_saved;
    }

    /// \details
    /// Restore context and errno.
    inline void
    __attribute__((always_inline))
    ThreadContext::restore(void)
    {
      errno = m_error;
      m_saved = false;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

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

    // ========================================================================

    /// \details
    /// Save the current context, perform the context switch
    /// and return to the next thread selected by the scheduler.
    ///
    /// \note save() uses the classical trick of entering once
    /// and returning twice, the second time after restore().
    void
    ArchitectureImplementation::yield(void)
    {
#if 0
      if ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().save())
#else
      // ----- inline Context.save() begin ------------------------------------

      // getcontext() is like setjmp(), it cannot be used from
      // a separate function that returns before longjmp(),
      // so we manually inline the content of Context.save()

      os::core::Thread::Context& context =
          (((os::core::Thread*) os::scheduler.getCurrentThread())->getContext());

      context.m_error = errno;
      context.m_saved = true;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
      getcontext(&context.m_context);
#pragma GCC diagnostic pop

      // ----- inline Context.save() end --------------------------------------

      // save()/getcontext() are functions that return twice
      if (context.m_saved)
#endif
        {
          // First time after saving the context, when we have to
          // select the next context
            { // ---- InterruptsCriticalSection begin -------------------------
              os::core::scheduler::InterruptsCriticalSection cs;

              os::scheduler.performContextSwitchFromInterrupt();
            } // ---- InterruptsCriticalSection end ---------------------------
          // and resume from there
          ((os::core::Thread*) os::scheduler.getCurrentThread())->getContext().restore();
        }
      else
        {
          // Then after restore, when we just return to the new thread
        }
    }

  // ==========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }// namespace posix
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
