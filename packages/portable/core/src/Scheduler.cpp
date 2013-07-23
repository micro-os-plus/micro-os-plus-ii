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
    /// Very important here is to initialise the current thread to point
    /// to main thread, so when the first
    /// context switch will occur, the main thread context will be
    /// saved properly.
    Scheduler::Scheduler(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      // Not running until start()
      m_isRunning = false;

      // start by pointing to the main thread
      m_pCurrentThread = &mainThread;

      // Not locked
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
    /// \details
    /// This is printed during startup, after the platform greetings.
    void
    Scheduler::putGreeting(void)
    {
      os::diag::trace.putString("Cooperative scheduler, ");
      os::diag::trace.putDec(os::core::scheduler::TICKS_PER_SECOND);
      os::diag::trace.putString(" ticks/second.");
      os::diag::trace.putNewLine();
    }
#endif

    /// \details
    /// Manually start the main thread (register to the scheduler and
    /// prepare), the idle thread and then activate all registered
    /// threads.
    ///
    /// Finally initialise the system timers and set m_isRunning = true.
    ///
    /// From this moment on, the scheduler will start switching threads
    /// and the system timers to count ticks.
    ///
    /// \note The default priority of the main thread is just above the
    /// idle thread priority, so start() will return, but only when
    /// all other threads rich the suspended state.
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

      // Initialise and start the system timer
      os::timerTicks.initialise();
      os::timerTicks.start();

      // Mark that the scheduler is running
      m_isRunning = true;

      // Relinquish control to the thread with the highest priority
      yield();

      // This will return, but only when all other threads have
      // nothing to do.
    }

    /// \details
    /// Stop the system timer and set the m_isRunning flag to false.
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

    /// \details
    /// If the scheduler is not running or is locked, do nothing,
    /// i.e. return immediately to the calling thread.
    ///
    /// Otherwise call the architecture implementation.
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
    ///
    /// The result is left in the m_pCurrentThread pointer and
    /// will be used by context.resume() shortly.
    ///
    /// \note An InterruptsCriticalSection is needed when called from
    /// a user context.
    void
    Scheduler::prepareContextSwitchFromInterrupt(void)
    {
      // This should be the only place where the watchdog is reset.
      // When the scheduler is not running, it is also used in sleep().
      hal::arch::ArchitectureImplementation::resetWatchdog();

      if (!m_isRunning || isLocked())
        {
          // If the scheduler is not running, or is locked,
          // do not change the current thread
          return;
        }

      // Since the constructor set this to MainThread, this will
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
          // If not suspended and not terminated, insert again
          // Th
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
    /// Find an ID that is not in use, assign it to the thread
    /// and, if the scheduler is running, add the thread to the active list.
    /// The entire logic is performed in a critical section.
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
    /// In a critical section, deregister the thread.
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

      RegisteredThreads::~RegisteredThreads()
      {
#if defined(DEBUG)
        os::diag::trace.putDestructor();
#endif
      }

      /// \details
      /// Linear search of the array for the given pointer to thread.
      /// Used only in pushBack() and remove(), so allow the
      /// compiler to inline it, if appropriate.
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

      /// \details
      /// Check if the ID is the special NO_ID value, or if
      /// it matches an ID used by any of the registered threads.
      bool
      RegisteredThreads::isIdInUse(threadId_t id)
      {
        if (id == NO_ID)
          {
            return true;
          }

        // Iterate for all threads in this collection
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

      /// \details
      /// Clear the array of active threads.
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

        // This will guarantee that we have at least one thread in the list
        // and getTop() will be valid.
        // remove() will never take the idleThread() out of the array.
        insert(&idleThread);
      }

      ActiveThreads::~ActiveThreads()
      {
#if defined(DEBUG)
        os::diag::trace.putDestructor();
#endif
      }

      /// \details
      /// Linear search of the array for the given pointer to thread.
      /// Used only in insert() and remove(), so better inline it,
      /// if appropriate.
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

      /// \details
      /// Check if the thread is already in the array.
      /// If not, find the position of the first thread with lower priority
      /// and move all subsequent pointers (if any) one step to the right,
      /// to make place for the new element.
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

        // Find the position of the first thread with lower priority. In case
        // several threads with the same priority are present, this
        // ensures a round robin policy.
        for (i = 0; i < m_count; ++i)
          {
            if (prio > m_array[i]->getPriority())
              break;
          }

        if (i < m_count)
          {
            // i is the place where to insert

            int j;
            // shift the remaining array elements right to make space
            for (j = m_count; j > i; j--)
              {
                m_array[j] = m_array[j - 1];
              }
          }

        // but i might also be == ms_count, i.e. we insert at the end

        m_array[i] = pThread;
        m_count++;
      }

      /// \details
      /// This is somehow the opposite of insert, it finds the location
      /// of the desired thread and copies the subsequent elements one step
      /// to the left.
      /// \note The idle thread is never removed, to guarantee getTop()
      /// always returns a valid pointer.
      void
      ActiveThreads::remove(Thread* pThread)
      {
        if (pThread == &idleThread)
          {
            // do not remove the idle thread
            return;
          }

        // Try to find the thread in the active list
        int i = find(pThread);
        if (i == -1)
          {
            return; // thread not found, nothing to remove
          }

        // Remove the thread by copying the array one step to the left
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
