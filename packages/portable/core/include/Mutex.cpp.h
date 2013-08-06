//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Mutex definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Mutex.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"

//#include "portable/core/include/CriticalSections.h"

//#include "portable/core/include/PlatformBase.h"
//#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \details
    /// Construct an anonymous mutex.
    ///
    /// \note Provided only to meet the C++11 requirement
    /// that the mutex type shall be DefaultConstructible.
    /// Not recommended for regular applications, use the named
    /// constructor instead.
    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::TMutex(void)
          : NamedObject()
      {
        m_owningThread = nullptr;

        m_notifier.clear();
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::TMutex(
          const char* const pName)
          : NamedObject(pName)
      {
        m_owningThread = nullptr;

        m_notifier.clear();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::~TMutex()
      {
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      void
      TMutex<CriticalSectionLock_T, Notifier_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_notifier.clear();

                return;
              }
            else if (m_owningThread == pThread)
              {
                // Error,
                return;
              }
            else
              {
                if (!m_notifier.pushBack(pThread))
                  {
                    // TODO: error, array exceeded
                  }
              }
            // ----- critical section end -------------------------------------
          }

        for (;;)
          {
            pThread->suspend();

            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_notifier.clear();

                return;
              }

            // TODO: check attention requests

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
                    // TODO: error, array exceeded
                  }
              }
            // ----- critical section end -------------------------------------
          }
      }

    /// \details
    /// Attempts to obtain ownership of the mutex for the calling thread
    /// without blocking. If ownership is not obtained, there is no
    /// effect and tryLock() immediately returns.
    template<class CriticalSectionLock_T, class Notifier_T>
      bool
      TMutex<CriticalSectionLock_T, Notifier_T>::tryLock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_notifier.clear();

                return true;
              }
            else if (m_owningThread == pThread)
              {
                // Error,
                return false;
              }

            // ----- critical section end -------------------------------------
          }

        return false;
      }

    /// \details
    /// Release the calling thread’s ownership of the mutex. Requires that
    /// the calling thread owns the mutex.
    ///
    /// This operation synchronises with (1.10) subsequent lock
    /// operations that obtain ownership on the same object.
    template<class CriticalSectionLock_T, class Notifier_T>
      void
      TMutex<CriticalSectionLock_T, Notifier_T>::unlock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == pThread)
              {
                // Error, not owner
                return;
              }

            // Release ownership
            m_owningThread = nullptr;

            // Resume waiting threads
            m_notifier.resumeAll();
            m_notifier.clear()  ;

            // ----- critical section end -------------------------------------
          }

        // Finally give the next thread waiting for the mutex a chance to run.
        os::scheduler.yield();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      bool
      TMutex<CriticalSectionLock_T, Notifier_T>::tryLockFor(
          timer::ticks_t ticks __attribute__((unused)),
          TimerBase& timer __attribute__((unused)))
      {
        return true;
      }

    // ========================================================================

    /// \details
    /// Construct an anonymous mutex.
    ///
    /// \note Provided only to meet the C++11 requirement
    /// that the mutex type shall be DefaultConstructible.
    /// Not recommended for regular applications, use the named
    /// constructor instead.
    template<class CriticalSectionLock_T, int NotifySize_T>
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::TRecursiveMutex(
          void)
          : NamedObject()
      {
        m_owningThread = nullptr;

        m_count = 0;

        m_notifyCount = 0;
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T, int NotifySize_T>
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::TRecursiveMutex(
          const char* const pName)
          : NamedObject(pName)
      {
        m_owningThread = nullptr;

        m_count = 0;

        m_notifyCount = 0;
      }

    template<class CriticalSectionLock_T, int NotifySize_T>
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::~TRecursiveMutex()
      {
      }

    template<class CriticalSectionLock_T, int NotifySize_T>
      void
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_count = 0;
                m_notifyCount = 0;

                return;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task
                if (m_count != MAX_COUNT)
                  {
                    m_count++;
                  }
                else
                  {
                    // Error,
                  }
                return;
              }
            else
              {
                if (m_notifyCount < NOTIFY_ARRAY_SIZE)
                  {
                    m_notifyArray[m_notifyCount].pThread = pThread;
                    ++m_notifyCount;
                  }
                else
                  {
                    // TODO: error, array exceeded
                  }
              }
            // ----- critical section end -------------------------------------
          }

        for (;;)
          {
            pThread->suspend();

            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_count = 0;
                m_notifyCount = 0;

                return;
              }

            // TODO: check attention requests

            count_t i;
            for (i = 0; i < m_notifyCount; ++i)
              {
                // check if the thread is already in the list
                if (m_notifyArray[m_notifyCount].pThread == pThread)
                  break;
              }

            if (i == m_notifyCount)
              {
                // Add pThread to the list of suspended threads
                if (m_notifyCount < NOTIFY_ARRAY_SIZE)
                  {
                    m_notifyArray[m_notifyCount].pThread = pThread;
                    ++m_notifyCount;
                  }
                else
                  {
                    // TODO: error, array exceeded
                  }
              }
            // ----- critical section end -------------------------------------
          }
      }

    /// \details
    /// Attempts to obtain ownership of the mutex for the calling thread
    /// without blocking. If ownership is not obtained, there is no
    /// effect and tryLock() immediately returns.
    template<class CriticalSectionLock_T, int NotifySize_T>
      bool
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::tryLock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_count = 1;
                m_notifyCount = 0;

                return true;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task
                if (m_count != MAX_COUNT)
                  {
                    m_count++;

                    return true;
                  }
              }

            // ----- critical section end -------------------------------------
          }

        return false;
      }

    /// \details
    /// Release the calling thread’s ownership of the mutex. Requires that
    /// the calling thread owns the mutex.
    ///
    /// This operation synchronises with (1.10) subsequent lock
    /// operations that obtain ownership on the same object.
    template<class CriticalSectionLock_T, int NotifySize_T>
      void
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::unlock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == pThread)
              {
                // Error, not owner
                return;
              }

            if (m_count == 0)
              {
                // Error, counter out of sync
                return;
              }

            if (--m_count != 0)
              {
                // More levels of ownership to be released
                return;
              }

            // Counter reached 0, release ownership
            m_owningThread = nullptr;

            // Resume waiting threads
            for (count_t i = 0; i < m_notifyCount; ++i)
              {
                // no context switches will happen inside critical section
                m_notifyArray[m_notifyCount].pThread->resume();
              }

            m_notifyCount = 0;

            // ----- critical section end -------------------------------------
          }

        // Finally give the next thread waiting for the mutex a chance to run.
        os::scheduler.yield();
      }

    template<class CriticalSectionLock_T, int NotifySize_T>
      bool
      TRecursiveMutex<CriticalSectionLock_T, NotifySize_T>::tryLockFor(
          timer::ticks_t ticks __attribute__((unused)),
          TimerBase& timer __attribute__((unused)))
      {
        return true;
      }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
