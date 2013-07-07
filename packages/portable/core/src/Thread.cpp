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
#if defined(_DEBUG)
          os::diag::trace.putString("pri1=");
          os::diag::trace.putDec(m_staticPriority);
          os::diag::trace.putString(" @");
          os::diag::trace.putHex((void*)&m_staticPriority);
          os::diag::trace.putNewLine();
#endif

      // Normally not used directly, added for completeness
      m_entryPointAddress = entryPoint;
      m_entryPointParameter = pParameters;

      m_stack.initialise();

      m_trampolineParameters.pThread = this;
      m_trampolineParameters.entryPoint = entryPoint;
      m_trampolineParameters.pParameters = pParameters;

      m_context.create(m_stack.getStart(), m_stack.getSize(),
          (threadEntryPoint_t) trampoline, &m_trampolineParameters);
#if defined(_DEBUG)
          os::diag::trace.putString("pri2=");
          os::diag::trace.putDec(m_staticPriority);
          os::diag::trace.putNewLine();
#endif
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

    /// \details
    /// This function is needed to ensure that the thread cleanup code
    /// is always called after the thread code is completed, and
    /// control is passed to the next thread.
    void
    Thread::trampoline(trampolineParameters_t* pTrampolineParameters)
    {
      // call the desired code with the given parameters
      (*pTrampolineParameters->entryPoint)(pTrampolineParameters->pParameters);

      // deregister the thread and make sure it'll never be used
      pTrampolineParameters->pThread->cleanup();

      // TODO: notify threads waiting to join

      // pass control to next thread
      os::scheduler.yield();
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

