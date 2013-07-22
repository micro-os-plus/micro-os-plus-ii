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

      /// \brief Count of threads.
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
      constexpr threadId_t NO_ID = 0xFF;

      // ----------------------------------------------------------------------

      /// \brief Constant with the maximum number of user threads.
      constexpr threadCount_t MAX_USER_THREADS =
          OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS;

      /// \brief Constant with the number of system threads
      /// (currently two, main & idle).
      constexpr threadCount_t SYSTEM_THREADS =
          OS_INTEGER_CORE_SCHEDULER_SYSTEMTHREADS;

      /// \brief Constant with the maximum number of threads to accommodate.
      constexpr threadCount_t MAX_THREADS = SYSTEM_THREADS + MAX_USER_THREADS;

      constexpr int TICKS_PER_SECOND = OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND;

      // ----------------------------------------------------------------------

      /// \brief Idle task priority.
      ///
      /// \details
      /// Must be below MIN priority.
      constexpr threadPriority_t IDLE_PRIORITY = 0x00;

      /// \brief Priority of main() default thread.
      ///
      /// \details
      /// Must be below MIN priority.
      constexpr threadPriority_t MAIN_PRIORITY = IDLE_PRIORITY + 1;

      /// \brief Minimum priority.
      ///
      /// \details
      /// Must be above IDLE priority.
      constexpr threadPriority_t MIN_PRIORITY = MAIN_PRIORITY + 1;

      /// \brief Maximum priority.
      ///
      /// \details
      /// Must be above MIN priority.
      constexpr threadPriority_t MAX_PRIORITY = 0xFF;

      /// \brief Default priority.
      ///
      /// \details
      /// Computed as average between MIN and MAX priorities.
      constexpr threadPriority_t DEFAULT_PRIORITY = ((MAX_PRIORITY
          - MIN_PRIORITY) / 2 + 1);

      // ======================================================================

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

        Thread*
        operator[](int index);

#if 0
        Thread* volatile *
        begin(void);

        Thread* volatile *
        end(void);
#endif

      private:

        friend Thread* volatile *
        begin(RegisteredThreads& registeredThreads);

        friend Thread* volatile *
        end(RegisteredThreads& registeredThreads);

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

      inline Thread*
      __attribute__((always_inline))
      RegisteredThreads::operator[](int index)
      {
        return m_array[index];
      }

#if 0
      inline Thread* volatile *
      __attribute__((always_inline))
      RegisteredThreads::begin(void)
        {
          return &m_array[0];
        }

      inline Thread* volatile *
      __attribute__((always_inline))
      RegisteredThreads::end(void)
        {
          return &m_array[m_count];
        }
#else

      // required by GCC 4.6, otherwise 'for' with iterator does not work

      inline Thread* volatile *
      __attribute__((always_inline))
      begin(RegisteredThreads& registeredThreads)
      {
        return &registeredThreads.m_array[0];
      }

      inline Thread* volatile *
      __attribute__((always_inline))
      end(RegisteredThreads& registeredThreads)
      {
        return &registeredThreads.m_array[registeredThreads.m_count];
      }
#endif

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
        Thread*
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

        Thread* volatile m_array[MAX_THREADS];

        threadCount_t volatile m_count;
      };

#pragma GCC diagnostic pop

      // ----------------------------------------------------------------------

      inline Thread*
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

      typedef uint32_t lockCounter_t;

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

#if defined(DEBUG) || defined(__DOXYGEN__)
      void
      putGreeting(void);
#endif

      /// \brief Register thread to the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \retval       NO_ID if the thread could not be registered.
      /// \retval       The newly allocated thread ID, if successful.
      scheduler::threadId_t
      registerThread(Thread* pThread);

      /// \brief Deregister thread from the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \return NO_ID.
      scheduler::threadId_t
      deregisterThread(Thread* pThread);

      void
      start(void);

      void
      stop(void);

      bool
      isRunning(void) const;

      void
      yield(void);

      Thread*
      getCurrentThread(void);

      void
      lock(void);

      void
      unlock(void);

      bool
      isLocked(void) const;

      /// @} end of Public member functions

      // ----------------------------------------------------------------------

#if __GNUC__ == 4 && __GNUC_MINOR__ == 6
      // GCC 4.6 does not allow C++11 friends to typedefs,
      // so we have to make this public.
    public:
#else
    private:
#if !defined(__DOXYGEN__)
      // Doxygen complains "no uniquely matching class member found"
      friend hal::arch::ArchitectureImplementation;
#endif
#endif

      /// \name Private member functions
      /// @{

      void
      performContextSwitchFromInterrupt(void);

      /// @} end of Private member functions

      // ----------------------------------------------------------------------

    private:

      friend class MainThread;

      friend class Thread;

      /// \name Private member functions
      /// @{

      void
      setCurrentThread(Thread* pThread);

      // NOT synchronised
      void
      suspendThread(Thread* pThread);

      // NOT synchronised
      void
      resumeThread(Thread* pThread);

      /// @} end of Private member functions

      /// \name Private member variables
      /// @{

      /// \details
      /// Although the constructor sets this to nullptr,
      /// the MainThread will immediately set it to a valid value.
      Thread* volatile m_pCurrentThread;

      bool volatile m_isRunning;

      scheduler::RegisteredThreads m_registered;

      scheduler::ActiveThreads m_active;

      lockCounter_t volatile m_lockCounter;

      /// @} end of Private member variables
    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    inline bool
    __attribute__((always_inline))
    Scheduler::isRunning(void) const
    {
      return m_isRunning;
    }

    inline Thread*
    __attribute__((always_inline))
    Scheduler::getCurrentThread(void)
    {
      return m_pCurrentThread;
    }

    inline void
    __attribute__((always_inline))
    Scheduler::setCurrentThread(Thread* pThread)
    {
      m_pCurrentThread = pThread;
    }

    inline void
    __attribute__((always_inline))
    Scheduler::lock(void)
    {
      m_lockCounter++;
    }

    inline void
    __attribute__((always_inline))
    Scheduler::unlock(void)
    {
      m_lockCounter--;
    }

    inline bool
    __attribute__((always_inline))
    Scheduler::isLocked(void) const
    {
      return (m_lockCounter != 0);
    }

    inline void
    __attribute__((always_inline))
    Scheduler::suspendThread(Thread* pThread)
    {
      m_active.remove(pThread);
    }

    inline void
    __attribute__((always_inline))
    Scheduler::resumeThread(Thread* pThread)
    {
      m_active.insert(pThread);
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
