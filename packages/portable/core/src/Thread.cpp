//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Thread definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"

//#include "portable/core/include/PlatformBase.h"
//#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Store the stack reference and the priority
    /// in the private member variables.
    Thread::Thread(const char* const pName, threadEntryPoint_t entryPoint,
        void* pParameters, Stack::element_t* const pStack,
        Stack::size_t const stackSizeBytes, priority_t priority)
        : NamedObject(pName), //
        m_stack(pStack, stackSizeBytes)
    {
#if defined(DEBUG)
#if defined(OS_DEBUG_THREAD)
      os::diag::trace.putConstructorWithName();
#else
      os::diag::trace.putStringAndAddress("os::core::Thread::Thread()", this,
          pName);
#endif
#endif

      initialise(entryPoint, pParameters, priority);
    }

    /// \details
    /// Perform the cleanups.
    Thread::~Thread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif

      cleanup();
    }

    /// \details
    /// Call the architecture function.
    void
    Thread::initialise(threadEntryPoint_t entryPoint, void* pParameters,
        priority_t priority)
    {
      m_id = scheduler::NO_ID;
      m_initialPriority = priority;
      m_staticPriority = priority;
      m_isSuspended = true;
      m_isAttentionRequested = false;

      // Normally not used directly, added for completeness
      m_entryPointAddress = entryPoint;
      m_entryPointParameter = pParameters;
    }

    void
    Thread::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif
      if (m_id != scheduler::NO_ID)
        // already started
        return;

      m_isSuspended = false;
      m_isAttentionRequested = false;

      m_staticPriority = m_initialPriority;

      m_pJoiner = nullptr;

      m_stack.initialise();

      m_context.create(m_stack.getStart(), m_stack.getSize(),
          (trampoline3_t) trampoline3, (void*) m_entryPointAddress,
          (void*) m_entryPointParameter, (void*) this);

      m_id = os::scheduler.registerThread(this);
#if defined(DEBUG)
      if (m_id == scheduler::NO_ID)
        {
          os::diag::trace.putString("cannot register thread \"");
          os::diag::trace.putString(getName());
          os::diag::trace.putString("\"");
          os::diag::trace.putNewLine();
        }
#endif

    }

    void
    Thread::cleanup()
    {
      m_isSuspended = true;

      if (m_id != scheduler::NO_ID)
        {
          os::scheduler.deregisterThread(this);

          // clear the id, to mark that the thread was de-registered
          m_id = scheduler::NO_ID;
        }

      m_pJoiner = nullptr;
    }

    /// \details
    /// Suspend the thread and remove it from the ready list.
    void
    Thread::suspend(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      m_isSuspended = true;

      // suspend should always yield, to remove the current thread
      // from the active list, otherwise loops waiting for a condition
      // will hang
      os::scheduler.yield();
    }

    /// \details
    /// Resume the thread by inserting it into the ready list.
    void
    Thread::resumeFromInterrupt(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      m_isSuspended = false;
      os::scheduler.resumeThread(this);
    }

    /// \details
    /// Resume the thread by inserting it into the ready list.
    void
    Thread::resume(void)
    {
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;
      resumeFromInterrupt();
      // ----- Critical section end -------------------------------------------
    }

    /// \details
    /// Block until the thread has completed.
    void
    Thread::join(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif

      if (m_pJoiner == nullptr)
        {
          // When the thread quits, it'll resume this joiner
          m_pJoiner = os::scheduler.getCurrentThread();
        }
#if defined(DEBUG)
      else
        {
          os::diag::trace.putString("Multiple join() not allowed.");
          os::diag::trace.putNewLine();

          return;
        }
#endif

      while (m_id != scheduler::NO_ID)
        {
          // Suspend the thread calling join(), not the thread
          // to be joined!
          os::scheduler.getCurrentThread()->suspend();
        }
    }

    /// \details
    /// Directly starting the thread entry point is not enough, since it can
    /// return, and we need a place to perform thread cleanup operations.
    ///
    /// \note Must be public, to be accessible from custom schedulers.
    void
    Thread::trampoline3(threadEntryPoint_t entryPoint, void* pParameters,
        Thread* pThread)
    {
      // call the actual thread code
      (*entryPoint)(pParameters);

        { // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

          Thread* pJoiner = const_cast<Thread*>(pThread->m_pJoiner);
          if (pJoiner != nullptr)
            {
              // Resume thread waiting to join, if any
              pJoiner->resumeFromInterrupt();
            }
          // deregister the given thread and make sure it'll never be used
          pThread->cleanup();

        } // ----- Critical section end ---------------------------------------

      // pass control to the next thread
      os::scheduler.yield();
    }

    void
    Thread::requestAttention(void)
    {
      m_isAttentionRequested = true;
    }

    void
    Thread::acknowledgeAttention(void)
    {
      m_isAttentionRequested = false;
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
