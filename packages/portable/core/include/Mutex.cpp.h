//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core mutex definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Mutex.h"
#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Error.h"

//#define OS_DEBUG_MUTEX          (1)

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
    /// Not recommended for regular applications (use the named
    /// constructor instead).
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::TGenericMutex(
          void)
          : NamedObject()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TGenericMutex::TGenericMutex()", this);
#endif
        m_owningThread = nullptr;

        m_policy.initialise();

        m_notifier.clear();
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::TGenericMutex(
          const char* const pName)
          : NamedObject(pName)
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TGenericMutex::TGenericMutex()", this, pName);
#endif
        m_owningThread = nullptr;

        m_policy.initialise();

        m_notifier.clear();
      }

    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::~TGenericMutex()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TGenericMutex::~TGenericMutex()", this, getName());
#endif
      }

    /// \details
    /// If the mutex is free, acquire it. Otherwise suspend
    /// until the thread that owns the mutex calls unlock(),
    /// which will resume all waiting threads.
    ///
    /// For a non-recursive mutex, the second lock() from the same thread
    /// will fail with RECURSION_DEPTH_EXCEEDED.
    ///
    /// A recursive mutex allows multiple lock() calls from the same thread,
    /// but after a certain limit (currently MAX_INT) it will also fail with
    /// RECURSION_DEPTH_EXCEEDED.
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      void
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

        pThread->setError(Error::UNKNOWN);

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::lock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

        // check attention
        if (pThread->isAttentionRequested())
          {
            // Return immediately if attention was requested
            pThread->setError(Error::CANCELLED);

            return;
          }

          {
            // ----- Critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;

                m_policy.initialise();
                m_policy.recursiveLock();

                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TGenericMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif

                pThread->setError(Error::SUCCEEDED);

                return;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task

                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();

                    pThread->setError(Error::SUCCEEDED);
                  }
                else
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TGenericMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" too many embedded locks");
                    os::diag::trace.putNewLine();
#endif
                    pThread->setError(Error::RECURSION_DEPTH_EXCEEDED);
                  }

                return;
              }
            else
              {
                // try to add waiting thread to the list
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TGenericMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
                    pThread->setError(Error::INTERNAL_SIZE_EXCEEDED);

                    return;
                  }
              }
            // ----- Critical section end -------------------------------------
          }

        // The mutex is busy, we have to wait for another thread to
        // release it; the current thread is in the notification list,
        // we can suspend

#if 1
            pThread->sleepWhile([=]()
              {
                // check attention
                if (pThread->isAttentionRequested())
                  {
                    // Return immediately if attention was requested
                    pThread->setError(Error::CANCELLED);

                    return false;
                  }

                // ----- Critical section begin -----------------------------------
                CriticalSectionLock cs;

                if (m_owningThread == nullptr)
                  {
                    // The mutex is free, acquire it
                    m_owningThread = pThread;

                    m_policy.initialise();
                    m_policy.recursiveLock();

                    m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TGenericMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif

                pThread->setError(Error::SUCCEEDED);

                return false;
              }

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                os::diag::trace.putString(
                    "os::core::TGenericMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" size exceeded");
                os::diag::trace.putNewLine();
#endif
                pThread->setError(Error::INTERNAL_SIZE_EXCEEDED);

                return false;
              }
          }
        // ----- Critical section end -------------------------------------
        return true;
      });
#else
            for (;;)
              {
            pThread->sleep();
            // The resume details are not used here

            // check attention
            if (pThread->isAttentionRequested())
              {
                // Return immediately if attention was requested
                pThread->setError(Error::CANCELLED);

                return;
              }

            // ----- Critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is free, acquire it
                m_owningThread = pThread;

                m_policy.initialise();
                m_policy.recursiveLock();

                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TGenericMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif

                pThread->setError(Error::SUCCEEDED);

                return;
              }

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TGenericMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
                    pThread->setError(Error::INTERNAL_SIZE_EXCEEDED);

                    return;
                  }
              }
            // ----- Critical section end -------------------------------------
              } // loop
#endif
      }

    /// \details
    /// Attempt to obtain ownership of the mutex for the calling thread
    /// without blocking. If ownership is not obtained, there is no
    /// effect and tryLock() returns with BUSY. One way or another,
    /// tryLock() always returns immediately.
    ///
    /// For a non-recursive mutex, attempts to tryLock() again from
    /// the same thread fail with RECURSION_DEPTH_EXCEEDED. Similarly
    /// for a recursive mutex, attempts to tryLock() again from the
    /// same thread but past a certain limit, will fail with
    /// RECURSION_DEPTH_EXCEEDED.

    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      bool
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::tryLock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

        pThread->setError(Error::UNKNOWN);

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::tryLock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

        // check attention
        if (pThread->isAttentionRequested())
          {
            // Return immediately if attention was requested
            pThread->setError(Error::CANCELLED);

            return false;
          }

          {
            // ----- Critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;

                m_policy.initialise();
                m_policy.recursiveLock();

                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TGenericMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
                pThread->setError(Error::SUCCEEDED);

                return true;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task
                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();

                    pThread->setError(Error::SUCCEEDED);

                    return true;
                  }
                else
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TGenericMutex::tryLock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" too many embedded locks");
                    os::diag::trace.putNewLine();
#endif
                    pThread->setError(Error::RECURSION_DEPTH_EXCEEDED);

                  }
              }
            else
              {
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TGenericMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" already owned by \"");
                os::diag::trace.putString(m_owningThread->getName());
                os::diag::trace.putString("\"");
                os::diag::trace.putNewLine();
#endif

                pThread->setError(Error::BUSY);

              }

            // ----- Critical section end -------------------------------------
          }

        return false;
      }
    /// \details
    /// Attempt to obtain ownership of the mutex for the calling thread.
    /// If the mutex is free, acquire it and return true immediately.
    /// Otherwise block for
    /// a limited period of time. If during this period the mutex is
    /// freed, acquire it and return true. Otherwise return false.
    ///
    /// The period of time is always given in ticks specific to the
    /// timer used (for example the ticks timer counts scheduler ticks,
    /// the RTC timer counts seconds).
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      bool
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::tryLockFor(
          timer::ticks_t ticks, TimerBase& timer)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

        pThread->setError(Error::UNKNOWN);

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::tryLockFor()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

#if 1

        pThread->sleepWhile([=]()
          {
            tryLock();
            if (pThread->getError() != Error::BUSY)
              {
                return false;
              }

              {
                // ----- Critical section begin -------------------------------
            CriticalSectionLock cs;

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
            os::diag::trace.putString(
                "os::core::TGenericMutex::tryLockFor()");
            os::diag::trace.putString(" \"");
            os::diag::trace.putString(getName());
            os::diag::trace.putString("\" by \"");
            os::diag::trace.putString(pThread->getName());
            os::diag::trace.putString("\" size exceeded");
            os::diag::trace.putNewLine();
#endif
            pThread->setError(Error::INTERNAL_SIZE_EXCEEDED);

            return false;
          }
      }
    // ----- Critical section end ---------------------------------
  }
return true;
}, ticks, timer);

          {
            // ----- Critical section begin -------------------------------
            CriticalSectionLock cs;

            m_notifier.remove(pThread);
            // ----- Critical section end ---------------------------------
          }

        return pThread->getError() == Error::SUCCEEDED;
#else
        // Remember the time when we entered this function
        os::core::timer::ticks_t beginTicks = timer.getCurrentTicks();

        for (;;)
          {
            if (tryLock())
              {
                // Got it!

                // Error already set by tryLock() to SUCCEEDED
                return true;
              }
            if (pThread->getError() != Error::BUSY)
              {
                return false;
              }
            os::core::timer::ticks_t nowTicks = timer.getCurrentTicks();

            if ((nowTicks - beginTicks) >= ticks)
              {
                // timeout expired, mutex not acquired
                pThread->setError(Error::TIMEOUT);

                return false;
              }

            // check attention
            if (pThread->isAttentionRequested())
              {
                // Return immediately if attention was requested
                pThread->setError(Error::CANCELLED);

                return false;
              }

              {
                // ----- Critical section begin -------------------------------
                CriticalSectionLock cs;

                if (!m_notifier.hasElement(pThread))
                  {
                    if (!m_notifier.pushBack(pThread))
                      {
#if defined(DEBUG)
                        os::diag::trace.putString(
                            "os::core::TGenericMutex::lock()");
                        os::diag::trace.putString(" \"");
                        os::diag::trace.putString(getName());
                        os::diag::trace.putString("\" by \"");
                        os::diag::trace.putString(pThread->getName());
                        os::diag::trace.putString("\" size exceeded");
                        os::diag::trace.putNewLine();
#endif
                        pThread->setError(Error::INTERNAL_SIZE_EXCEEDED);

                        return false;
                      }
                  }
                // ----- Critical section end ---------------------------------
              }

            pThread->sleepFor(ticks - (nowTicks - beginTicks), timer);
            // the resume details are not used here

              {
                // ----- Critical section begin -------------------------------
                CriticalSectionLock cs;

                m_notifier.remove(pThread);
                // ----- Critical section end ---------------------------------
              }
          } // loop
#endif
      }

    /// \details
    /// Release the calling thread’s ownership of the mutex. If
    /// the calling thread does not own the mutex, the NOT_OWNER error
    /// is returned.
    ///
    /// This operation synchronises with (1.10) subsequent lock
    /// operations that obtain ownership on the same object.
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      void
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::unlock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

        pThread->setError(Error::UNKNOWN);

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- Critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread != pThread)
              {
#if defined(DEBUG)
                os::diag::trace.putString("os::core::TGenericMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" not owner");
                os::diag::trace.putNewLine();
#endif
                pThread->setError(Error::NOT_OWNER);

                return;
              }

            if (m_policy.isRecursiveUnlockPossible())
              {
                m_policy.recursiveUnlock();

                if (!m_policy.isRecursiveUnlockComplete())
                  {
                    // More levels of ownership to be released
                    pThread->setError(Error::SUCCEEDED);

                    return;
                  }
              }
            else
              {
#if defined(DEBUG)
                os::diag::trace.putString("os::core::TGenericMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" out of sync");
                os::diag::trace.putNewLine();
#endif
                pThread->setError(Error::OUT_OF_SYNC);

                return;
              }

            // Counter reached 0, release ownership
            m_owningThread = nullptr;

            // Wake-up sleeping threads
            m_notifier.wakeupAll();
            m_notifier.clear();

            // ----- Critical section end -------------------------------------
          }

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" released by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

        // Finally give the next thread waiting for the mutex a chance to run.
        os::scheduler.yield();

        pThread->setError(Error::SUCCEEDED);
      }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
