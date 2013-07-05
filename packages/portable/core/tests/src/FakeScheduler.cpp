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

    /// \details
    /// If the ID is valid, just return it, the thread was already registered.
    /// Otherwise find an empty slot in the array and
    /// store the pointer to the thread there.
    FakeScheduler::threadId_t
    FakeScheduler::registerThread(Thread* pThread)
    {
      threadId_t id = pThread->getId();
      if (id != NO_ID)
        {
          return id;
        }

      // here id = NO_ID;

      threadCount_t i;
      // find an empty slot
      for (i = 0; i < getThreadsArraySize(); ++i)
        {
          if (m_threads[i] == nullptr)
            {
              // register thread
              m_threads[i] = pThread;

              // generate thread id
              id = static_cast<threadId_t>(m_threadCount);
              m_threadCount++;

              break;
            }
        }

      return id;
    }

    /// \details
    /// If the thread is still registered, deregister it.
    FakeScheduler::threadId_t
    FakeScheduler::deregisterThread(Thread* pThread)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif
      threadId_t id;
      id = pThread->getId();
      if (id != NO_ID)
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
      return NO_ID;
    }

    /// \details
    /// Run all threads, in priority order, each one until completion.
    void
    FakeScheduler::run(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunction();
#endif

      threadPriority_t pri;
      for (pri = MAX_PRIORITY; pri >= MAIN_PRIORITY; pri--)
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
                          Thread::trampolineParameters_t pPar;
                          pPar.pThread = pThread;
                          pPar.entryPoint = p;
                          pPar.pParameters = pThread->getEntryPointParameter();
                          Thread::trampoline(&pPar);
                          //(*p)(pThread->getEntryPointParameter());
                        }
                    }
                }
            }
        }
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

