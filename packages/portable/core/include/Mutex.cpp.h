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
    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::TMutex(void)
          : NamedObject()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress("os::core::TMutex::TMutex()", this);
#endif
        m_owningThread = nullptr;

        m_notifier.clear();
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::TMutex(const char* const pName)
          : NamedObject(pName)
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress("os::core::TMutex::TMutex()", this,
            pName);
#endif
        m_owningThread = nullptr;

        m_notifier.clear();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      TMutex<CriticalSectionLock_T, Notifier_T>::~TMutex()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress("os::core::TMutex::~TMutex()", this,
            getName());
#endif
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      void
      TMutex<CriticalSectionLock_T, Notifier_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TMutex::lock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
                return;
              }
            else if (m_owningThread == pThread)
              {
#if defined(DEBUG)
                os::diag::trace.putString("os::core::TMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" recursion not allowed");
                os::diag::trace.putNewLine();
#endif
                // Error,
                return;
              }
            else
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString("os::core::TMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
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

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
                return;
              }

            // TODO: check attention requests

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString("os::core::TMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
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

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TMutex::tryLock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
                return true;
              }
            else if (m_owningThread == pThread)
              {
#if defined(DEBUG)
                os::diag::trace.putString("os::core::TMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" recursion not allowed");
                os::diag::trace.putNewLine();
#endif
                // Error,
                return false;
              }
            else
              {
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" already owned by \"");
                os::diag::trace.putString(m_owningThread->getName());
                os::diag::trace.putString("\"");
                os::diag::trace.putNewLine();
#endif
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
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread != pThread)
              {
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString(
                    "os::core::TRecursiveMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" not owner");
                os::diag::trace.putNewLine();
#endif
                // Error, not owner
                return;
              }

            // Release ownership
            m_owningThread = nullptr;

            // Resume waiting threads
            m_notifier.resumeAll();
            m_notifier.clear();

            // ----- critical section end -------------------------------------
          }

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" released by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif
        // Finally give the next thread waiting for the mutex a chance to run.
        os::scheduler.yield();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      bool
      TMutex<CriticalSectionLock_T, Notifier_T>::tryLockFor(
          timer::ticks_t ticks __attribute__((unused)),
          TimerBase& timer __attribute__((unused)))
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndName("os::core::TMutex::tryLockFor()",
            getName());
#endif
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
    template<class CriticalSectionLock_T, class Notifier_T>
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::TRecursiveMutex(void)
          : NamedObject()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TRecursiveMutex::TRecursiveMutex()", this);
#endif
        m_owningThread = nullptr;
        m_count = 0;

        m_notifier.clear();
      }

    /// \details
    /// Construct a named mutex.
    template<class CriticalSectionLock_T, class Notifier_T>
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::TRecursiveMutex(
          const char* const pName)
          : NamedObject(pName)
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TRecursiveMutex::TRecursiveMutex()", this, pName);
#endif
        m_owningThread = nullptr;
        m_count = 0;

        m_notifier.clear();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::~TRecursiveMutex()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TRecursiveMutex::~TRecursiveMutex()", this, getName());
#endif
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      void
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TRecursiveMutex::lock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_count = 1;
                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TRecursiveMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
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
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TRecursiveMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" depth exceeded");
                    os::diag::trace.putNewLine();
#endif
                    // Error,
                  }
                return;
              }
            else
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TRecursiveMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
                    // TODO: error, array size exceeded
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
                m_count = 1;
                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TRecursiveMutex::lock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
                return;
              }

            // TODO: check attention requests

            if (!m_notifier.hasElement(pThread))
              {
                if (!m_notifier.pushBack(pThread))
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TRecursiveMutex::lock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" size exceeded");
                    os::diag::trace.putNewLine();
#endif
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
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::tryLock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TRecursiveMutex::tryLock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread == nullptr)
              {
                // The mutex is not owned, get it
                m_owningThread = pThread;
                m_count = 1;
                m_notifier.clear();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TRecursiveMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" acquired by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putChar('"');
                os::diag::trace.putNewLine();
#endif
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
                else
                  {
#if defined(DEBUG)
                    os::diag::trace.putString(
                        "os::core::TRecursiveMutex::tryLock()");
                    os::diag::trace.putString(" \"");
                    os::diag::trace.putString(getName());
                    os::diag::trace.putString("\" by \"");
                    os::diag::trace.putString(pThread->getName());
                    os::diag::trace.putString("\" depth exceeded");
                    os::diag::trace.putNewLine();
#endif
                  }
              }
            else
              {
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
                os::diag::trace.putString("os::core::TRecursiveMutex::tryLock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" already owned by \"");
                os::diag::trace.putString(m_owningThread->getName());
                os::diag::trace.putString("\"");
                os::diag::trace.putNewLine();
#endif
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
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::unlock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();
#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TRecursiveMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread != pThread)
              {
#if defined(DEBUG)
                os::diag::trace.putString(
                    "os::core::TRecursiveMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" not owner");
                os::diag::trace.putNewLine();
#endif
                // Error, not owner
                return;
              }

            if (m_count == 0)
              {
#if defined(DEBUG)
                os::diag::trace.putString(
                    "os::core::TRecursiveMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" out of sync");
                os::diag::trace.putNewLine();
#endif
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
            m_notifier.resumeAll();
            m_notifier.clear();

            // ----- critical section end -------------------------------------
          }

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TRecursiveMutex::unlock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" released by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

        // Finally give the next thread waiting for the mutex a chance to run.
        os::scheduler.yield();
      }

    template<class CriticalSectionLock_T, class Notifier_T>
      bool
      TRecursiveMutex<CriticalSectionLock_T, Notifier_T>::tryLockFor(
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
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::TGenericMutex(void)
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

    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      void
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::lock(void)
      {
        Thread* pThread = os::scheduler.getCurrentThread();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::lock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
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
                return;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task

                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();
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
                    // Error,
                  }
                return;
              }
            else
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
                    // TODO: error, array size exceeded
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
                return;
              }

            // TODO: check attention requests

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
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      bool
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::tryLock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();

#if defined(DEBUG) && defined(OS_DEBUG_MUTEX)
        os::diag::trace.putString("os::core::TGenericMutex::tryLock()");
        os::diag::trace.putString(" \"");
        os::diag::trace.putString(getName());
        os::diag::trace.putString("\" by \"");
        os::diag::trace.putString(pThread->getName());
        os::diag::trace.putChar('"');
        os::diag::trace.putNewLine();
#endif

          {
            // ----- critical section begin -----------------------------------
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
                return true;
              }
            else if (m_owningThread == pThread)
              {
                // The mutex is owned by the same task
                if (m_policy.isRecursiveLockPossible())
                  {
                    m_policy.recursiveLock();
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
    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      void
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::unlock(void) noexcept
      {
        Thread* pThread = os::scheduler.getCurrentThread();
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
            // ----- critical section begin -----------------------------------
            CriticalSectionLock cs;

            if (m_owningThread != pThread)
              {
#if defined(DEBUG)
                os::diag::trace.putString(
                    "os::core::TGenericMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" not owner");
                os::diag::trace.putNewLine();
#endif
                // Error, not owner
                return;
              }

            if (m_policy.isRecursiveUnlockPossible())
              {
                m_policy.recursiveUnlock();

                if (!m_policy.isRecursiveUnlockComplete())
                  {
                    // More levels of ownership to be released
                    return;
                  }
              }
            else
              {
#if defined(DEBUG)
                os::diag::trace.putString(
                    "os::core::TGenericMutex::unlock()");
                os::diag::trace.putString(" \"");
                os::diag::trace.putString(getName());
                os::diag::trace.putString("\" by \"");
                os::diag::trace.putString(pThread->getName());
                os::diag::trace.putString("\" out of sync");
                os::diag::trace.putNewLine();
#endif
                // Error, counter out of sync
                return;
              }


            // Counter reached 0, release ownership
            m_owningThread = nullptr;

            // Resume waiting threads
            m_notifier.resumeAll();
            m_notifier.clear();

            // ----- critical section end -------------------------------------
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
      }

    template<class CriticalSectionLock_T, class Notifier_T, class Policy_T>
      bool
      TGenericMutex<CriticalSectionLock_T, Notifier_T, Policy_T>::tryLockFor(
          timer::ticks_t ticks __attribute__((unused)),
          TimerBase& timer __attribute__((unused)))
      {
        return true;
      }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
