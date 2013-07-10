//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable scheduler definitions.

#ifndef OS_PORTABLE_CORE_SCHEDULER_H_
#define OS_PORTABLE_CORE_SCHEDULER_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/XCDL_SchedulerDefines.h"

#if defined(OS_INCLUDE_CORE_SCHEDULER_CUSTOM)

// To use a custom scheduler, define this to the actual header location
#include OS_STRING_CORE_SCHEDULER_CUSTOM_HEADER

#else

#include "portable/core/include/Architecture.h"

#include <stdint.h>

namespace os
{
  namespace core
  {
    class Thread;

    namespace scheduler
    {
      /// \brief Thread ID.
      ///
      /// \details
      /// A unique value identifying each thread.
      typedef uint8_t threadId_t;

      typedef int threadCount_t;

      // ----------------------------------------------------------------------

      /// \brief Priority type.
      ///
      /// \details
      /// A single byte should be more than enough, even for
      /// larger embedded systems.
      typedef uint8_t threadPriority_t;

      /// \brief No valid ID.
      ///
      /// \details
      /// Value returned by threads that are not registered to the
      /// scheduler.
      static const threadId_t NO_ID = 0xFF;

      // ----------------------------------------------------------------------

      static const threadCount_t MAX_USER_THREADS =
          OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS;

      // main & idle
      static const threadCount_t SYSTEM_THREADS = 2;

      static const threadCount_t MAX_THREADS = SYSTEM_THREADS
          + MAX_USER_THREADS;

      // ----------------------------------------------------------------------

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      class RegisteredThreads
      {
      public:
        RegisteredThreads(void);

        threadId_t
        add(Thread* pThread);

        threadId_t
        remove(Thread* pThread);

        // return the number of known threads
        threadCount_t
        getCount(void) const;

        threadCount_t
        getSize(void) const;

      private:

        Thread* volatile m_array[MAX_THREADS];

        threadCount_t volatile m_count;

      };

#pragma GCC diagnostic pop

      // ----------------------------------------------------------------------

      inline scheduler::threadCount_t
      __attribute__((always_inline))
      RegisteredThreads::getCount(void) const
      {
        return m_count;
      }

      inline scheduler::threadCount_t
      __attribute__((always_inline))
      RegisteredThreads::getSize(void) const
      {
        return sizeof(m_array) / sizeof(m_array[0]);
      }

      // ======================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      class ActiveThreads
      {
      public:
        ActiveThreads(void);

        // insert thread into the active list
        void
        insert(Thread* pThread);

        // delete thread from the active list
        void
        remove(Thread* pThread);

        // return the first thread from active list (thread with higher priority)
        volatile Thread*
        getTop(void);

        // return the number of active threads
        threadCount_t
        getCount(void) const;

        threadCount_t
        getSize(void) const;

      private:
        // find if pThread is in the ready threads array
        int
        find(Thread* pThread);

        volatile Thread* volatile m_array[MAX_THREADS];

        threadCount_t volatile m_count;
      };

#pragma GCC diagnostic pop

      // ----------------------------------------------------------------------

      inline volatile Thread*
      __attribute__((always_inline))
      ActiveThreads::getTop(void)
      {
        return m_array[0];
      }

      inline scheduler::threadCount_t
      __attribute__((always_inline))
      ActiveThreads::getCount(void) const
      {
        return m_count;
      }

      inline scheduler::threadCount_t
      __attribute__((always_inline))
      ActiveThreads::getSize(void) const
      {
        return sizeof(m_array) / sizeof(m_array[0]);
      }

    // ========================================================================

    }// namespace scheduler

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \headerfile Scheduler.h "portable/core/include/Scheduler.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Scheduler.
    ///
    /// \details
    /// This is the definition of the scheduler.
    class Scheduler
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Priority type.
      ///
      /// \details
      /// A single byte should be more than enough, even for
      /// larger embedded systems.
      typedef scheduler::threadPriority_t threadPriority_t;

      /// \brief Idle task priority.
      ///
      /// \details
      /// Must be below MIN priority.
      static const threadPriority_t IDLE_PRIORITY = 0x00;

      /// \brief Priority of main() default thread.
      ///
      /// \details
      /// Must be below MIN priority.
      static const threadPriority_t MAIN_PRIORITY = IDLE_PRIORITY + 1;

      /// \brief Minimum priority.
      ///
      /// \details
      /// Must be above IDLE priority.
      static const threadPriority_t MIN_PRIORITY = MAIN_PRIORITY + 1;

      /// \brief Maximum priority.
      ///
      /// \details
      /// Must be above MIN priority.
      static const threadPriority_t MAX_PRIORITY = 0xFF;

      /// \brief Default priority.
      ///
      /// \details
      /// Computed as average between MIN and MAX priorities.
      static const threadPriority_t DEFAULT_PRIORITY = ((MAX_PRIORITY
          - MIN_PRIORITY) / 2 + 1);

      /// \brief Thread ID.
      ///
      /// \details
      /// A unique value identifying each thread.
      typedef scheduler::threadId_t threadId_t;

      typedef scheduler::threadCount_t threadCount_t;

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      Scheduler(void);

      /// \brief Destructor.
      ~Scheduler();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Register thread to the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \retval       NO_ID if the thread could not be registered.
      /// \retval       The newly allocated thread ID, if successful.
      threadId_t
      registerThread(Thread* pThread);

      /// \brief Deregister thread from the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \return NO_ID.
      threadId_t
      deregisterThread(Thread* pThread);

      void
      run(void);

      bool
      isRunning(void) const;

      void
      yield(void);

      volatile Thread*
      getCurrentThread(void) volatile;

      // public since the below friend does not work in 4.6
      //friend hal::arch::ArchitectureImplementation;

      /// @} end of Public member functions

      // ----------------------------------------------------------------------

#if __GNUC__ == 4 && __GNUC_MINOR__ == 6
      // GCC 4.6 does not allow C++11 friends to typedefs,
      // so we have to make this public.
    public:
#else
    private:
      friend hal::arch::ArchitectureImplementation;
#endif

      void
      performContextSwitch(void);

      // ----------------------------------------------------------------------

    private:

      friend class MainThread;

      void
      setCurrentThread(Thread* pThread);

      volatile Thread* volatile m_pCurrentThread;

      bool volatile m_isRunning;

      scheduler::RegisteredThreads m_registered;

      scheduler::ActiveThreads m_active;
    };

#pragma GCC diagnostic pop

    // ========================================================================

    inline bool
    __attribute__((always_inline))
    Scheduler::isRunning(void) const
    {
      return m_isRunning;
    }

    /// \details
    /// If the ID is valid, just return it, the thread was already registered.
    /// Otherwise... TBD
    inline Scheduler::threadId_t
    __attribute__((always_inline))
    Scheduler::registerThread(Thread* pThread)
    {
      threadId_t id = m_registered.add(pThread);
      if (id != scheduler::NO_ID)
        {
          m_active.insert(pThread);
        }
      return id;
    }

    /// \details
    /// If the thread is still registered, deregister it.
    inline Scheduler::threadId_t
    __attribute__((always_inline))
    Scheduler::deregisterThread(Thread* pThread)
    {
      threadId_t id =  m_registered.remove(pThread);
      return id;
    }

    inline void
    __attribute__((always_inline))
    Scheduler::yield(void)
    {
      hal::arch::ArchitectureImplementation::yield();
    }

    inline volatile Thread*
    __attribute__((always_inline))
    Scheduler::getCurrentThread(void) volatile
    {
      return m_pCurrentThread;
    }

    inline void
    __attribute__((always_inline))
    Scheduler::setCurrentThread(Thread* pThread)
    {
      m_pCurrentThread = pThread;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif

namespace os
{
  // Declaration of the external instantiation of `Scheduler`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern os::core::Scheduler scheduler;
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

#endif // OS_PORTABLE_CORE_SCHEDULER_H_
