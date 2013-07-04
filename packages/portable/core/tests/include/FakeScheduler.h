//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Fake scheduler used to test thread creation.

// Fake scheduler used to test thread creation.
// It does not switch threads, it just runs each thread until completion.

#ifndef OS_PORTABLE_CORE_TESTS_SIMPLESCHEDULER_H_
#define OS_PORTABLE_CORE_TESTS_SIMPLESCHEDULER_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/XCDL_SchedulerDefines.h"

#include <stdint.h>

namespace os
{
  namespace core
  {
    class Thread;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \headerfile FakeScheduler.h "portable/core/tests/include/FakeScheduler.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief FakeScheduler.
    ///
    /// \details
    /// This is the definition of the fake scheduler. It does not
    /// switch between tasks, it just executes each one until completion.
    class FakeScheduler
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Priority type.
      ///
      /// \details
      /// A single byte should be more than enough, even for
      /// larger embedded systems.
      typedef uint8_t threadPriority_t;

      /// \brief Idle task priority.
      ///
      /// \details
      /// Must be below MIN priority.
      static const threadPriority_t IDLE_PRIORITY = 0x00;

      /// \brief Minimum priority.
      ///
      /// \details
      /// Must be above IDLE priority.
      static const threadPriority_t MIN_PRIORITY = IDLE_PRIORITY + 1;

      /// \brief Maximum priority.
      ///
      /// \details
      /// Must be above MIN priority.
      static const threadPriority_t MAX_PRIORITY = 0xFF;

      /// \brief Default priority.
      ///
      /// \details
      /// Computed as average between MIN and MAX priorities.
      static const threadPriority_t DEFAULT_PRIORITY = ((MAX_PRIORITY - MIN_PRIORITY)
          / 2 + 1);

      /// \brief Thread ID.
      ///
      /// \details
      /// A unique value identifying each thread.
      typedef uint8_t threadId_t;

      /// \brief No valid ID.
      ///
      /// \details
      /// Value returned by threads that are not registered to the
      /// scheduler.
      static const threadId_t NO_ID = 0xFF;

      /// \brief Thread count.
      ///
      /// \details
      /// A counter/index used to iterate between threads.
      typedef uint32_t threadCount_t;

      /// @} end of name Types and constants
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      FakeScheduler();

      /// \brief Destructor.
      ~FakeScheduler();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Register thread to the scheduler lists.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \retval       NO_ID if the thread could not be registered.
      /// \retval       The newly allocated thread ID, if successful.
      threadId_t
      registerThread(Thread* pThread);

      /// \brief Deregister thread from the scheduler lists.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \retval       NO_ID if the thread was not registered.
      /// \retval       The thread ID, if successful.
      threadId_t
      deregisterThread(Thread* pThread);

      /// \brief Run all registered threads.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      run(void);

      /// \brief Yield the core to another thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      yield(void);

      /// \brief Return the number of entries in the threads array.
      ///
      /// \par Parameters
      ///    None.
      /// \return The size of the array.
      threadCount_t
      getThreadsArraySize(void);

      /// @} end of Public member functions

    private:
      Thread* m_threads[OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS];
      threadCount_t m_threadCount;
    };

#pragma GCC diagnostic pop

    /// \details
    /// Stop the current thread and continue execution
    /// with the thread with the highest priority.
    /// (does nothing for the fake scheduler)
    inline void
    __attribute__((always_inline))
    FakeScheduler::yield(void)
    {
      // return to the current thread
    }

    inline FakeScheduler::threadCount_t
    __attribute__((always_inline))
    FakeScheduler::getThreadsArraySize(void)
    {
      return sizeof(m_threads) / sizeof(m_threads[0]);
    }

    // ------------------------------------------------------------------------
    // Make this the default scheduler
    typedef os::core::FakeScheduler Scheduler;

  } // namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_TESTS_SIMPLESCHEDULER_H_