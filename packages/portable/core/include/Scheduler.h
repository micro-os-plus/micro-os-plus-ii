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
      typedef unsigned int threadId_t;

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
      constexpr threadId_t NO_ID = 0;

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

      /// \brief Constant with the number of scheduler ticks per second.
      constexpr uint32_t TICKS_PER_SECOND =
          OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND;

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

      /// \headerfile Scheduler.h "portable/core/include/Scheduler.h"
      /// \ingroup core
      /// \nosubgrouping
      ///
      /// \brief Registered threads.
      ///
      /// \details
      /// This class is used by the scheduler to manage the registered threads.
      /// It currently uses an array of pointer to threads. New threads
      /// are simply added to the end. Removing threads triggers a copy
      /// of the following elements one step to the left.
      ///
      /// \warning This class is intended to be used in context with
      /// interrupts disabled, it does not provide its own synchronisation.
      class RegisteredThreads
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        RegisteredThreads(void);

        /// \brief Destructor.
        ~RegisteredThreads(void);

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Add a thread to the end of the array.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \retval True                The thread was added.
        /// \retval False               The thread was not added.
        bool
        pushBack(Thread* pThread);

        /// \brief Remove the thread from the array.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \retval True                The thread was removed.
        /// \retval False               The thread was not removed.
        bool
        remove(Thread* pThread);

        /// \brief Get the count of registered threads.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     An integer with the number of registered threads
        threadCount_t
        getCount(void) const;

        /// \brief Get the size of array.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     An integer with the size of array.
        threadCount_t
        getSize(void) const;

        /// \brief Check if an ID is already in use by a registered thread.
        ///
        /// \param [in] id              The ID to check.
        /// \retval True                The ID is in use or NO_ID.
        /// \retval False               The ID can be used for a new thread.
        bool
        isIdInUse(threadId_t id);

        /// @} end of Public member functions

        /// \name Operators
        /// @{

        /// \brief Subscripting operator.
        ///
        /// \param [in] index           The position of the element to return, starting from 0.
        /// \return                     Pointer to the thread.
        Thread*
        operator[](int index);

        /// @} end of Operators

        /// \name Iterators
        /// @{

        /// \brief Iterator begin.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     A pointer to the first element.
        Thread* volatile *
        begin(void);

        /// \brief Iterator end.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     A pointer <b>after</b> the last element.
        Thread* volatile *
        end(void);

        /// @} end of Iterators

      private:

        /// \name Private member functions
        /// @{

        /// \brief Find if a thread is already in the array.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \retval -1                  The thread is not in the array.
        /// \retval >0                  The index where the thread is stored in the array.
        int
        find(Thread* pThread);

        /// @} end of Private member functions

        /// \name Private member variables
        /// @{

        /// \brief Array of pointers to threads.
        Thread* volatile m_array[MAX_THREADS];

        /// \brief The number of registered threads.
        threadCount_t volatile m_count;

        /// @} end of Private member variables
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

      inline Thread* volatile *
      __attribute__((always_inline))
      RegisteredThreads::begin(void)
      {
        return &m_array[0];
      }

      /// \details
      ///
      /// The end is given by the actual content, not by the array size.
      inline Thread* volatile *
      __attribute__((always_inline))
      RegisteredThreads::end(void)
      {
        return &m_array[m_count];
      }

      // ======================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \headerfile Scheduler.h "portable/core/include/Scheduler.h"
      /// \ingroup core
      /// \nosubgrouping
      ///
      /// \brief Active threads.
      ///
      /// \details
      /// This class is used by the scheduler to manage the active threads.
      /// It currently uses an array of pointers to threads.
      ///
      /// New threads
      /// are inserted in order of decreasing priorities. Round robin
      /// is implemented by inserting same priorities in the order of
      /// the calls, i.e. before the next thread with lower priority.
      /// Removing threads triggers a copy
      /// of the following elements one step to the left.
      class ActiveThreads
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        ActiveThreads(void);

        /// \brief Destructor.
        ~ActiveThreads();

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Insert a thread into the array, in decreasing priority order.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \par Returns
        ///    Nothing.
        void
        insert(Thread* pThread);

        /// \brief Remove the thread from the array.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \retval True                The thread was removed.
        /// \retval False               The thread was not removed.
        void
        remove(Thread* pThread);

        /// \brief Get the top thread (with the highest priority).
        ///
        /// \par Parameters
        ///    None.
        /// \return                     A pointer to the thread.
        Thread*
        getTop(void);

        /// \brief Get the count of active threads.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     An integer with the number of active threads.
        threadCount_t
        getCount(void) const;

        /// \brief Get the size of array.
        ///
        /// \par Parameters
        ///    None.
        /// \return                     An integer with the size of array.
        threadCount_t
        getSize(void) const;

        /// @} end of Public member functions

      private:

        /// \name Private member functions
        /// @{

        /// \brief Find if a thread is already in the array.
        ///
        /// \param [in] pThread         Pointer to the thread.
        /// \retval -1                  The thread is not in the array.
        /// \retval >0                  The index where the thread is stored in the array.

        int
        find(Thread* pThread);

        /// @} end of Private member functions

        /// \name Private member variables
        /// @{

        /// \brief Array of pointers to threads.
        Thread* volatile m_array[MAX_THREADS];

        /// \brief The number of registered threads.
        threadCount_t volatile m_count;

        /// @} end of Private member variables
      };

#pragma GCC diagnostic pop

      // ----------------------------------------------------------------------

      /// \details
      /// After
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
    /// \brief The system scheduler.
    ///
    /// \details
    /// This class implements the default scheduler. It does not implement
    /// any special scheduling policy by itself, but uses the two support
    /// classes os::core::scheduler::RegisteredThreads and
    /// os::core::scheduler::ActiveThreads for this.
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

      /// \brief Put a greeting string on the trace output.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      putGreeting(void);

#endif

      /// \brief Start the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      start(void);

      /// \brief Stop the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      stop(void);

      /// \brief Check if the scheduler is running.
      ///
      /// \par Parameters
      ///    None.
      /// \retval True                The scheduler was started.
      /// \retval False               The scheduler is stopped.
      bool
      isRunning(void) const;

      /// \brief Yield (relinquish) control to the next thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      yield(void);

      /// \brief Get a pointer to the current thread.
      ///
      /// \par Parameters
      ///    None.
      /// \return                     A pointer to the current thread.
      Thread*
      getCurrentThread(void);

      /// \brief Lock the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      lock(void);

      /// \brief Unlock the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      unlock(void);

      /// \brief Check if the scheduler is locked.
      ///
      /// \par Parameters
      ///    None.
      /// \retval True                The scheduler is locked.
      /// \retval False               The scheduler is not locked.
      bool
      isLocked(void) const;

      /// @} end of Public member functions

      // ----------------------------------------------------------------------

    private:

      friend class MainThread;

      friend class Thread;

#if !defined(__DOXYGEN__)
      // Doxygen complains "no uniquely matching class member found"
      friend hal::arch::ArchitectureImplementation;
#endif

      /// \name Private member functions
      /// @{

      /// \brief Register a thread to the scheduler.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \retval True          The thread was registered.
      /// \retval False         The thread was not registered.
      bool
      registerThread(Thread* pThread);

      /// \brief Deregister a thread from the scheduler lists.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \retval True          The thread was deregistered.
      /// \retval False         The thread was not deregistered.
      bool
      deregisterThread(Thread* pThread);

      /// \brief Prepare context switch.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      prepareContextSwitchFromInterrupt(void);

#if 0
      // NOT synchronised
      void
      suspendThread(Thread* pThread);
#endif

      /// \brief Resume a thread.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \par Returns
      ///    Nothing.
      void
      resumeThreadFromInterrupt(Thread* pThread);

      /// @} end of Private member functions

      /// \name Private member variables
      /// @{

      /// \brief The pointer to the current thread.
      ///
      /// \details
      /// Set by prepareContextSwitchFromInterrupt() to the m_active.getTop().
      ///
      /// The constructor sets this to main thread.
      Thread* volatile m_pCurrentThread;

      /// \brief Recursive lock. When 0, the scheduler is allowed to
      /// perform context switches.
      lockCounter_t volatile m_lockCounter;

      /// \brief Flag to tell if the scheduler was started or not.
      bool volatile m_isRunning;

      /// \brief An autoincrement counter used to set thread IDs.
      scheduler::threadId_t m_lastUsedId;

      /// \brief An instance of the class that manages the active threads.
      scheduler::ActiveThreads m_active;

      /// \brief An instance of the class that manages the registered threads.
      scheduler::RegisteredThreads m_registered;

      /// @} end of Private member variables
    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// This flag is set by start() and reset by stop().
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

    /// \details
    /// Locking can be done recursively for up to 2^32 levels.
    inline void
    __attribute__((always_inline))
    Scheduler::lock(void)
    {
      m_lockCounter++;
    }

    /// \details
    /// Unlocking can be done recursively for up to 2^32 levels.
    inline void
    __attribute__((always_inline))
    Scheduler::unlock(void)
    {
      m_lockCounter--;
    }

    /// \details
    /// The decision is based on the value of a counter, incremented for each
    /// lock() and decremented for each unlock(). A value of 0 means the
    /// scheduler is not locked.
    inline bool
    __attribute__((always_inline))
    Scheduler::isLocked(void) const
    {
      return (m_lockCounter != 0);
    }

#if 0
    inline void
    __attribute__((always_inline))
    Scheduler::suspendThread(Thread* pThread)
      {
        m_active.remove(pThread);
      }
#endif

    /// \details
    /// Insert the thread into the active list.
    inline void
    __attribute__((always_inline))
    Scheduler::resumeThreadFromInterrupt(Thread* pThread)
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
