//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Scheduler definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/MainThread.h"
#include "portable/core/include/IdleThread.h"
#include "portable/core/include/TimerTicks.h"

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

      // start by pointing to the main thread, so when the first
      // context switch will occur, the main thread context will be
      // saved properly.
      m_pCurrentThread = &mainThread;

      m_lockCounter = 0;

      m_lastUsedId = scheduler::NO_ID;
    }

    /// \details
    Scheduler::~Scheduler()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif

    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    Scheduler::putGreeting(void)
    {
      os::diag::trace.putString("Cooperative scheduler, ");
      os::diag::trace.putDec(os::core::scheduler::TICKS_PER_SECOND);
      os::diag::trace.putString(" ticks/second.");
      os::diag::trace.putNewLine();
    }
#endif

    void
    Scheduler::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Scheduler::start()");
      os::diag::trace.putNewLine();
#endif

#if defined(DEBUG)
      if (m_pCurrentThread == nullptr)
        {
          os::diag::trace.putString("no current thread");
        }
#endif

      // start the two system threads
      os::mainThread.start();
      os::idleThread.start();

      // activate all non suspended threads
      for (auto pThread : m_registered)
        {
          if (!pThread->isSuspended())
            {
              m_active.insert(pThread);
            }
        }

      os::timerTicks.initialise();

      m_isRunning = true;

      os::timerTicks.start();

      // pass control to the thread with the highest priority
      yield();
    }

    void
    Scheduler::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Scheduler::stop()");
      os::diag::trace.putNewLine();
#endif

      // TODO: add code to kill all threads (except main)
      // in case they are still running

      os::timerTicks.stop();

      m_isRunning = false;
    }

    void
    Scheduler::yield(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_SCHEDULER)
      os::diag::trace.putString(" yield() ");
#endif
      if (!m_isRunning || isLocked())
        {
          // if the scheduler is locked, do not change the current thread
          return;
        }

      hal::arch::ArchitectureImplementation::yield();
    }

    /// \details
    /// If running and not locked, remove the current thread
    /// from the active list,
    /// eventually reinsert it at the end, for round robin reasons,
    /// and select the top thread.
    /// The result is left in the m_pCurrentThread pointer and
    /// will be used by context.resume() shortly.
    /// \note No synchronisation required while running from
    /// interrupt contexts.
    void
    Scheduler::performContextSwitchFromInterrupt(void)
    {
      hal::arch::ArchitectureImplementation::resetWatchdog();

      if (!m_isRunning || isLocked())
        {
          // if the scheduler is not running, or is locked,
          // do not change the current thread
          return;
        }

      // As long as MainThread was constructed, this will
      // always point to a thread.
      Thread* pThread = (Thread*) m_pCurrentThread;

#if defined(DEBUG) && defined(OS_DEBUG_SCHEDULER)
      os::diag::trace.putString(" switch <<< ");
      os::diag::trace.putString(pThread->getName());
#endif

      // Remove the running thread from the top of the active list
      m_active.remove(pThread);

      // Eventually reinsert it at the end of the list (round robin)

      if ((!pThread->isSuspended()) && (pThread->getId() != scheduler::NO_ID))
        {
          // if not suspended and not waiting
          m_active.insert(pThread);
        }

      // Select the next running thread from the top of the active list
      m_pCurrentThread = m_active.getTop();
#if defined(DEBUG) && defined(OS_DEBUG_SCHEDULER)
      os::diag::trace.putString(" >>> ");
      os::diag::trace.putString(m_pCurrentThread->getName());
      os::diag::trace.putNewLine();
#endif
    }

    /// \details
    /// If the ID is valid, just return, the thread was already registered.
    /// Otherwise find an ID that is not in use, assign it to the thread
    /// and, if the scheduler is running, add thread to the active list.
    bool
    Scheduler::registerThread(Thread* pThread)
    {
#if defined(DEBUG)
      os::diag::trace.putStringAndName("Scheduler::registerThread()",
          pThread->getName());
#endif

      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      bool wasRegistered = m_registered.pushBack(pThread);
      if (wasRegistered)
        {
          do
            {
              ++m_lastUsedId;
            }
          while (m_registered.isIdInUse(m_lastUsedId));

          pThread->setId(m_lastUsedId);

          if (os::scheduler.isRunning())
            {
              // if the scheduler is running, all new threads are active
              m_active.insert(pThread);
            }
        }
      // ----- Critical section end -------------------------------------------

      return wasRegistered;
    }

    /// \details
    /// If the thread is still registered, deregister it.
    bool
    Scheduler::deregisterThread(Thread * pThread)
    {
#if defined(DEBUG)
      os::diag::trace.putStringAndName("Scheduler::deregisterThread()",
          pThread->getName());
#endif

      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      bool wasDeregistered = m_registered.remove(pThread);
      return wasDeregistered;
      // ----- Critical section end -------------------------------------------
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

        for (threadCount_t i = 0; i < getSize(); ++i)
          {
            m_array[i] = nullptr;
          }
      }

      // Used only in add() and remove(), so better inline it,
      // if appropriate.
      inline int
      RegisteredThreads::find(Thread* pThread)
      {
        for (int i = 0; i < m_count; ++i)
          {
            if (m_array[i] == pThread)
              return i;
          }

        return -1; // thread not found
      }

      /// \details
      /// Check if the thread was already registered.
      /// If not, check if there is still space in the array and
      /// store the pointer to the thread there.
      bool
      RegisteredThreads::pushBack(Thread* pThread)
      {
        // Try to find the thread in the registered list
        int i = find(pThread);
        if (i != -1)
          {
            return false; // thread found, no need to add again
          }

        if (m_count >= getSize())
          {
#if defined(DEBUG)
            os::diag::trace.putString("RegisteredThreads::add() full!");
            os::diag::trace.putNewLine();
#endif
            return false;
          }

        m_array[m_count++] = pThread;

        return true;
      }

      /// \details
      /// If the thread is still registered, deregister it.
      bool
      RegisteredThreads::remove(Thread* pThread)
      {
        // Try to find the thread in the registered list
        int i = find(pThread);
        if (i == -1)
          {
            return false; // thread not found, nothing to remove
          }

        // Remove the thread by copying the list one step to the left
        for (; i < m_count - 1; ++i)
          {
            m_array[i] = m_array[i + 1];
          }
        m_count--;

        // clear the pointer (only for aesthetics)
        m_array[m_count] = nullptr;

        return true;
      }

      bool
      RegisteredThreads::isIdInUse(threadId_t id)
      {
        if (id == NO_ID)
          {
            return true;
          }

        for (auto pThread : *this)
          {
            if (pThread->getId() == id)
              {
                return true;
              }
          }

        return false;
      }

      // ======================================================================

      ActiveThreads::ActiveThreads(void)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif
        m_count = 0;

        for (threadCount_t i = 0; i < getSize(); ++i)
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
        // Check if already in
        int i = find(pThread);
        if (i != -1)
          {
            return; // already in, we're done
          }

        threadPriority_t prio = pThread->getPriority();

        for (i = 0; i < m_count; ++i)
          {
            // If threads with identical priority exist, insert at the end
            // in other words, insert before the next thread with lower priority.
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
          {
            // do not remove the idle thread, to be sure there is
            // always one entry, to be returned by getTop();
            return;
          }

        // Try to find the thread in the active list
        int i = find(pThread);
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
