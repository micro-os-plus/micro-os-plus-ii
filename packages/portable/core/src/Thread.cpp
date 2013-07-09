//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Thread definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"

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
      os::diag::trace.putConstructorWithName();
#endif

      initialise(entryPoint, pParameters, priority);

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
      m_staticPriority = priority;

      // Normally not used directly, added for completeness
      m_entryPointAddress = entryPoint;
      m_entryPointParameter = pParameters;

      m_stack.initialise();

      m_context.create(m_stack.getStart(), m_stack.getSize(),
          (trampoline3_t) trampoline3, (void*) entryPoint, (void*) pParameters,
          (void*) this);
    }

    /// \details
    /// Block until the thread has completed.
    void
    Thread::join(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif

#if 1
      // TODO: implement with events
      while (m_id != scheduler::NO_ID)
        {
          os::scheduler.yield();
        }
#endif
    }


    void
    Thread::trampoline3(threadEntryPoint_t entryPoint, void* pParameters,
        Thread* pThread)
    {
      // call the thread code
      (*entryPoint)(pParameters);

      // deregister the thread and make sure it'll never be used
      pThread->cleanup();

      // TODO: notify threads waiting to join

      // pass control to next thread
      os::scheduler.yield();
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

