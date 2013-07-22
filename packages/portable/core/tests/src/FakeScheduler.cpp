//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Fake scheduler definitions.

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/tests/include/FakeScheduler.h"
#include "portable/core/include/Thread.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Iterate the storage array and clear all entries.
    FakeScheduler::FakeScheduler(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      m_threadCount = 0;
      threadCount_t i;
      for (i = 0; i < getThreadsArraySize(); ++i)
        {
          m_threads[i] = nullptr;
        }
    }

    /// \details
    FakeScheduler::~FakeScheduler()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    FakeScheduler::putGreeting(void)
    {
      os::diag::trace.putString("Custom fake scheduler, runs each thread to completion.");
      os::diag::trace.putNewLine();
    }
#endif

    /// \details
    /// If the ID is valid, just return it, the thread was already registered.
    /// Otherwise find an empty slot in the array and
    /// store the pointer to the thread there.
    scheduler::threadId_t
    FakeScheduler::registerThread(Thread* pThread)
    {
      scheduler::threadId_t id = pThread->getId();
      if (id != scheduler::NO_ID)
        {
          return id;
        }

      // here id = NO_ID;
      if (m_threadCount >= getThreadsArraySize())
        {
#if defined(DEBUG)
          os::diag::trace.putString("RegisteredThreads full!");
          os::diag::trace.putNewLine();
#endif
          return scheduler::NO_ID;
        }

      threadCount_t i;
      // find an empty slot
      for (i = 0; i < getThreadsArraySize(); ++i)
        {
          if (m_threads[i] == nullptr)
            {
              // register thread
              m_threads[i] = pThread;

              // generate thread id
              id = static_cast<scheduler::threadId_t>(i);
              m_threadCount++;

              break;
            }
        }

      return id;
    }

    /// \details
    /// If the thread is still registered, deregister it.
    scheduler::threadId_t
    FakeScheduler::deregisterThread(Thread* pThread)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif
      scheduler::threadId_t id;
      id = pThread->getId();
      if (id != scheduler::NO_ID)
        {
          threadCount_t i;
          for (i = 0; i < getThreadsArraySize(); ++i)
            {
              if (m_threads[i] == pThread)
                {
                  m_threads[i] = nullptr;
                  m_threadCount--;

                  break;
                }
            }

          return id;
        }
      return scheduler::NO_ID;
    }

    /// \details
    /// Run all threads, in priority order, each one until completion.
    void
    FakeScheduler::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif

      scheduler::threadPriority_t pri;
      for (pri = scheduler::MAX_PRIORITY; pri >= scheduler::MAIN_PRIORITY; pri--)
        {
          threadCount_t i;
          for (i = 0; i < getThreadsArraySize(); ++i)
            {
              Thread* pThread = m_threads[i];
              if (pThread != nullptr)
                {
                  if (pThread->getPriority() == pri)
                    {
                      os::core::threadEntryPoint_t p =
                          pThread->getEntryPointAddress();
                      if (p != nullptr)
                        {
                          Thread::trampoline3(p,
                              pThread->getEntryPointParameter(), pThread);
                        }
                    }
                }
            }
        }
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

