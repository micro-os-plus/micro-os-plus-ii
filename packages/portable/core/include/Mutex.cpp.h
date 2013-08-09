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
    /// Not recommended for regular applications, use the named
    /// constructor instead.
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
    /// until notified by another task at unlock().
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
            pThread->setError(Error::ATTENTION_REQUESTED);

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

                pThread->setError(Error::NONE);

                return;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task

                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();

                    pThread->setError(Error::NONE);
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

        for (;;)
          {
            pThread->suspend();
            // The resume details are not used here

            // check attention
            if (pThread->isAttentionRequested())
              {
                // Return immediately if attention was requested
                pThread->setError(Error::ATTENTION_REQUESTED);

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

                pThread->setError(Error::NONE);

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
      }

    /// \details
    /// Attempt to obtain ownership of the mutex for the calling thread
    /// without blocking. If ownership is not obtained, there is no
    /// effect and tryLock() immediately returns.
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
            pThread->setError(Error::ATTENTION_REQUESTED);

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
                pThread->setError(Error::NONE);

                return true;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task
                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();

                    pThread->setError(Error::NONE);

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
    /// Release the calling thread’s ownership of the mutex. Requires that
    /// the calling thread owns the mutex.
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
                    pThread->setError(Error::NONE);

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

            // Resume waiting threads
            m_notifier.resumeAll();
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

        pThread->setError(Error::NONE);
      }

    /// \details
    /// Attempt to obtain ownership of the mutex for the calling thread.
    /// If the mutex is free, return immediately. Otherwise block for
    /// a limited period of time. If during this period the mutex is
    /// freed, acquire it and return true. Otherwise return false.
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

        // Remember the time when we entered this function
        os::core::timer::ticks_t beginTicks = timer.getCurrentTicks();

        for (;;)
          {
            if (tryLock())
              {
                // Got it!

                // Error already set by tryLock() to NONE
                return true;
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
                pThread->setError(Error::ATTENTION_REQUESTED);

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

            pThread->suspendWithTimeout(ticks - (nowTicks - beginTicks), timer);

              {
                // ----- Critical section begin -------------------------------
                CriticalSectionLock cs;

                m_notifier.remove(pThread);
                // ----- Critical section end ---------------------------------
              }
          } // loop
      }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
