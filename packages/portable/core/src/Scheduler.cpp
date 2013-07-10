//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Scheduler definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/IdleThread.h"

//#include "portable/core/include/PlatformBase.h"
#include "portable/core/include/Architecture.h"

#if !defined(OS_INCLUDE_CORE_SCHEDULER_CUSTOM)

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \details
    Scheduler::Scheduler(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      m_isRunning = false;

      m_pCurrentThread = nullptr;
    }

    /// \details
    Scheduler::~Scheduler()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif

    }

    void
    Scheduler::run(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif

#if defined(DEBUG)
      if (m_pCurrentThread == nullptr)
        {
          os::diag::trace.putString("no current thread");
        }
#endif

      m_isRunning = true;

      // pass control to the thread with the highest priority
      yield();
    }

    void
    Scheduler::performContextSwitch(void)
    {
      hal::arch::ArchitectureImplementation::resetWatchdog();

      Thread* pThread = (Thread*) m_pCurrentThread;

      // Remove the running thread from the top of the active list
      m_active.remove(pThread);

      // Eventually reinsert it at the end of the list (round robin)

      if (pThread->getId() != scheduler::NO_ID)
        {
          // if not suspended and not waiting
          m_active.insert(pThread);
        }

      // Select the next running thread from the top of the active list
      m_pCurrentThread = m_active.getTop();
    }

    namespace scheduler
    {
      // ======================================================================

      /// \details
      /// Clear the array of known threads.
      RegisteredThreads::RegisteredThreads(void)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif
        m_count = 0;

        threadCount_t i;
        for (i = 0; i < getSize(); ++i)
          {
            m_array[i] = nullptr;
          }
      }

      /// \details
      /// If the ID is valid, just return it, the thread was already registered.
      /// Otherwise find an empty slot in the array and
      /// store the pointer to the thread there.
      threadId_t
      RegisteredThreads::add(Thread* pThread)
      {
        // TODO: add synchronisation

        threadId_t id = pThread->getId();
        if (id != NO_ID)
          {
            return id;
          }

        // here id = NO_ID;
        if (m_count >= getSize())
          {
#if defined(DEBUG)
            os::diag::trace.putString("RegisteredThreads full!");
            os::diag::trace.putNewLine();
#endif
            return NO_ID;
          }

        threadCount_t i;
        // find an empty slot
        for (i = 0; i < getSize(); ++i)
          {
            if (m_array[i] == nullptr)
              {
                // found an empty slot, register thread
                m_array[i] = pThread;

                // generate thread id from index
                id = static_cast<threadId_t>(i);
                m_count++;

                break;
              }
          }

        return id;
      }

      /// \details
      /// If the thread is still registered, deregister it.
      threadId_t
      RegisteredThreads::remove(Thread* pThread)
      {
        // TODO: add synchronisation

        threadId_t id;
        id = pThread->getId();
        if (id == NO_ID)
          {
            // already deregistered
            return id;
          }

        threadCount_t i;
        for (i = 0; i < getSize(); ++i)
          {
            if (m_array[i] == pThread)
              {
                m_array[i] = nullptr;
                m_count--;

                break;
              }
          }

        return NO_ID;
      }

      // ======================================================================

      ActiveThreads::ActiveThreads(void)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif
        m_count = 0;

        threadCount_t i;
        for (i = 0; i < getSize(); ++i)
          {
            m_array[i] = nullptr;
          }
      }

      // Used only in insert() and remove(), so better inline it,
      // if appropriate.
      inline int
      ActiveThreads::find(Thread* pThread)
      {
        int i;
        for (i = 0; i < m_count; ++i)
          {
            if (m_array[i] == pThread)
              return i;
          }

        return -1; // thread not found
      }

      void
      ActiveThreads::insert(Thread* pThread)
      {
        int i;

        // Check if already in
        i = find(pThread);
        if (i != -1)
          {
            return; // already in, we're done
          }

        threadPriority_t prio = pThread->getPriority();

        for (i = 0; i < m_count; ++i)
          {
            // If threads with identical priority exist, insert at the end
            // in other words, insert before thread with higher priority.
            if (prio > m_array[i]->getPriority())
              break;
          }

        if (i < m_count)
          {
            // i is the place where to insert

            int j;
            // shift array right to make space
            for (j = m_count; j > i; j--)
              {
                m_array[j] = m_array[j - 1];
              }
          }

        // but i might also be == ms_count, i.e. we insert at the end

        m_array[i] = pThread;
        m_count++;
      }

      void
      ActiveThreads::remove(Thread* pThread)
      {
        if (pThread == &idleThread)
          return; // do not remove the idle thread

        int i;

        // Try to find the thread in the active list
        i = find(pThread);
        if (i == -1)
          {
            return; // thread not found, nothing to remove
          }

        // Remove the thread by copying the list one step to the left
        for (; i < m_count - 1; ++i)
          {
            m_array[i] = m_array[i + 1];
          }
        m_count--;
        // clear the pointer (only for aesthetics)
        m_array[m_count] = nullptr;
      }

    // ========================================================================
    }// namespace scheduler
  } // namespace core
} //namespace os

#endif // !defined(OS_INCLUDE_CORE_SCHEDULER_CUSTOM)

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
