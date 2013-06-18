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
        Stack::size_t const stackSize, priority_t priority)
        : NamedObject(pName), //
        m_stack(pStack, stackSize)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructorWithName();
#endif

      initialise(entryPoint, pParameters, priority);

      m_id = scheduler.registerThread(this);
    }

    Thread::~Thread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif

      m_id = scheduler.deregisterThread(this);
    }

    /// \details
    /// Call the architecture function.
    void
    Thread::initialise(threadEntryPoint_t entryPoint,
        void* pParameters, priority_t priority)
    {
      m_id = Scheduler::NO_ID;
      m_staticPriority = priority;

      m_stack.initialise(entryPoint, pParameters);
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

