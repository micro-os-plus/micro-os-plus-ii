//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core thread.

#ifndef OS_PORTABLE_CORE_THREAD_H_
#define OS_PORTABLE_CORE_THREAD_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

#include "portable/core/include/Architecture.h"

#include "portable/core/include/NamedObject.h"
#include "portable/core/include/Stack.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/TimerBase.h"
#include "portable/core/include/TimerTicks.h"

#include "portable/core/include/Error.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    namespace thread
    {
      typedef unsigned int state_t;

      class State
      {
      public:
        static constexpr state_t NOT_STARTED = 0;
        static constexpr state_t RUNNING = (1 << 0);
        static constexpr state_t SLEEPING = (1 << 1);
        static constexpr state_t SUSPENDED = (1 << 2);
        static constexpr state_t TERMINATED = (1 << 3);

        State(void) = delete;
      };

    }
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class Thread Thread.h "portable/core/include/Thread.h"
    /// \ingroup core_thread
    /// \nosubgrouping
    ///
    /// \brief Core thread.
    ///
    /// \details
    /// The class Thread provides a mechanism to create a new
    /// thread of execution, to join with a thread
    /// (i.e., wait for a thread to complete), and to
    /// perform other operations that manage and
    /// query the state of a thread. A thread object
    /// uniquely represents a particular thread of execution.
    ///
    /// Similarly to standard C++11 threads, µOS++ threads have a user
    /// defined function that performs the thread specific actions.
    /// If this function is reentrant, it can be used for several
    /// threads at the same time. To differentiate between threads,
    /// this function
    /// must have a single pointer parameter, and the Thread
    /// constructor should be able to pass different pointers to
    /// different threads.
    ///
    /// In addition to the standard C+11 threads, µOS++ threads
    /// must have an explicit stack, stored either in a static memory
    /// area or in an area dynamically allocated on the heap.
    ///
    /// For a better control, after construction µOS++ threads
    /// remain in a stopped state until an explicit call to
    /// the start() member function is performed.
    ///
    /// During the active life span of a thread, it can be either
    /// running or sleeping. Running threads are in the scheduler
    /// active threads list, and compete, based on priority and
    /// scheduler policies (like round-robin) for the processor.
    /// Sleeping threads are suspended from active duty, by calling
    /// the suspend() member function, usually waiting
    /// for an external event to occur, event that should call the
    /// resume() member function.
    ///
    /// Also specific to µOS++ threads is an out of band mechanism
    /// allowing to notify the thread that special attention is
    /// required for various user defined reasons (for
    /// example a cancellation request).
    ///
    /// The scheduler allocates the CPU to threads based on a
    /// priority, currently static (i.e. does not change by itself
    /// in time), with higher values meaning more likely to get the
    /// CPU.
    ///
    /// In addition to user threads, there are two system threads,
    /// - the os::mainThread, to perform the code in the main() function
    /// - the os::idleThread, a thread with the lowest possible
    /// priority, to be executed when
    /// no other thread is active.
    ///
    /// For identification reasons, each thread has a unique ID,
    /// allocated by the scheduler when the thread is started, and
    /// cleared when the thread is terminated or stopped.
    ///
    /// Like other system objects in µOS++, the Thread object is
    /// derived from NamedObject, which makes possible to assign a
    /// name to each thread, making threads even easier to identify,
    /// for example during debugging sessions.
    ///
    /// \example portable/core/tests/src/threads.cpp
    /// \example portable/core/tests/include/FakeScheduler.h
    /// \example portable/core/tests/src/FakeScheduler.cpp
    class Thread : public NamedObject
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Thread priority type.
      ///
      /// \details
      /// Redefined here, based on scheduler definitions.
      typedef scheduler::threadPriority_t priority_t;

      /// \brief Thread ID.
      ///
      /// \details
      /// Redefined here, based on scheduler definitions.
      typedef scheduler::threadId_t id_t;

      //static constexpr id_t NO_ID = scheduler::NO_ID;

      /// \brief Thread context.
      ///
      /// \details
      /// Redefined here, based on architecture definitions.
      typedef hal::arch::ThreadContext Context;

      /// \brief Pointer to trampoline function.
      ///
      /// \details
      /// The three parameters are
      /// - the entry point address
      /// - the parameter to be used when calling the entry point
      /// - the associated thread.
      typedef void
      (*trampoline3_t)(void*, void*, void*);

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pName             Pointer to the null terminated thread name.
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] stack             Reference to the stack object.
      /// \param [in] priority          Initial priority.
      Thread(const char* const pName, threadEntryPoint0_t entryPoint,
          Stack& stack, priority_t priority = scheduler::DEFAULT_PRIORITY);

      /// \brief Constructor.
      ///
      /// \param [in] pName             Pointer to the null terminated thread name.
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed to the thread.
      /// \param [in] stack             Reference to the stack object.
      /// \param [in] priority          Initial priority.
      Thread(const char* const pName, threadEntryPoint1_t entryPoint,
          void* pParameters, Stack& stack, priority_t priority =
              scheduler::DEFAULT_PRIORITY);

      /// \brief Template Constructor.
      ///
      /// \param [in] pName             Pointer to the null terminated thread name.
      /// \param [in] function          A lambda to be called with one parameter.
      /// \param [in] pObject           Pointer to the parameters passed to the thread.
      /// \param [in] stack             Reference to the stack object.
      /// \param [in] priority          Initial priority.
      template<class Lambda_T, class Object_T>
        Thread(const char* const pName, Lambda_T function, Object_T* pObject,
            Stack& stack, priority_t priority = scheduler::DEFAULT_PRIORITY);

      /// \brief Destructor.
      ~Thread();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Get the thread stack object.
      ///
      /// \par Parameters
      ///    None.
      /// \return Reference to the stack object.
      Stack&
      getStack(void);

      /// \brief Get the thread priority.
      ///
      /// \par Parameters
      ///    None.
      /// \return The current thread priority.
      priority_t
      getPriority(void) volatile;

      /// \brief Set the thread priority.
      ///
      /// \param [in] priority  The new priority.
      /// \par Returns
      ///    Nothing.
      void
      setPriority(priority_t priority);

      /// \brief Get the thread ID.
      ///
      /// \par Parameters
      ///    None.
      /// \retval NO_ID         The thread was terminated or stopped.
      /// \retval value         The current thread ID.
      id_t
      getId(void) const;

      /// \brief Get the thread entry point address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The thread entry point address.
      threadEntryPoint1_t
      getEntryPointAddress(void) const;

      /// \brief Get the thread entry point parameter.
      ///
      /// \par Parameters
      ///    None.
      /// \return The thread entry point parameter.
      void*
      getEntryPointParameter(void) const;

      /// \brief Start the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \retval true          The thread was started.
      /// \retval false         Otherwise.
      bool
      start(void);

      /// \brief Stop the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      stop(void);

      /// \brief Join the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      join(void);

      /// \brief Get state.
      ///
      /// \par Parameters
      ///    None.
      /// \return The thread state.
      thread::state_t
      getState(void);

      /// \brief Suspend the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      suspend(void);

      /// \brief Resume the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      resume(void);

      /// \brief Check if the thread is waiting for attention.
      ///
      /// \par Parameters
      ///    None.
      /// \retval true          The thread is waiting for attention.
      /// \retval false         Otherwise.
      bool
      isAttentionRequested(void) const;

      /// \brief Request the thread for special attention.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      requestAttention(void);

      /// \brief Acknowledge that special attention was provided.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      acknowledgeAttention(void);

      /// \brief Get the context object.
      ///
      /// \par Parameters
      ///    None.
      /// \return Reference to the context (architecture dependent content).
      Context&
      getContext(void);

      /// \brief Static trampoline used to execute the thread.
      ///
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed
      ///                               to the thread code.
      /// \param [in] pThread           Pointer to the thread object.
      static void
      trampoline3(threadEntryPoint1_t entryPoint, void* pParameters,
          Thread* pThread);

      /// \brief Get the error number.
      ///
      /// \par Parameters
      ///    None.
      /// \retval 0     Success.
      /// \retval <0    Failure, a negative integer to identify the error.
      errorNumber_t
      getError(void);

      /// \brief Set the error number.
      ///
      /// \param [in] error   A negative integer or zero.
      /// \par Returns
      ///    Nothing.
      void
      setError(errorNumber_t error);

      /// \brief Sleep for a number of ticks.
      ///
      /// \param [in] ticks   The number of counter ticks to sleep.
      /// \param [in] timer   The timer to use.
      /// \par Returns
      ///    Nothing.
      void
      sleepFor(timer::ticks_t ticks, TimerBase& timer = os::timerTicks);

      /// \brief Sleep while a condition is met, up to a number of ticks.
      ///
      /// \param [in] predicate   The condition to test.
      /// \param [in] ticks       The number of counter ticks to sleep.
      /// \param [in] timer       The timer to use.
      /// \par Returns
      ///    Nothing.
      template<class Predicate_T>
        void
        sleepWhile(Predicate_T predicate, timer::ticks_t ticks = 0,
            TimerBase& timer = os::timerTicks);

      /// \brief Wakeup the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      wakeup(void);

      /// @} end of Public member functions

    private:

      /// \name Private friends
      /// @{

      friend Scheduler;

      /// @} end of Private friends

      /// \name Private member functions
      /// @{

      /// \brief Initialise the thread.
      ///
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed
      ///                               to the thread code.
      /// \param [in] priority          Initial priority.
      void
      initialise(threadEntryPoint1_t entryPoint, void* pParameters,
          priority_t priority);

      /// \brief Clean thread internals after the code is terminated.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      cleanup(void);

      /// \brief Set the thread ID.
      ///
      /// \param [in] id        The new thread id.
      /// \par Returns
      ///    Nothing.
      void
      setId(id_t id);

      /// \brief Sleep while a condition is met, up to a number of ticks.
      ///
      /// \param [in] predicate   The condition to test.
      /// \param [in] ticks       The number of counter ticks to sleep.
      /// \param [in] timer       The timer to use.
      /// \par Returns
      ///    Nothing.
      template<class Predicate_T>
        void
        internalSleepWhile(Predicate_T predicate, timer::ticks_t ticks = 0,
            TimerBase& timer = os::timerTicks);

      /// \brief Sleep, possibly with timeout.
      ///
      /// \param [in] ticks             The number of counter ticks to sleep.
      /// \param [in] timer             The timer to use.
      /// \param [in] beginTicks        The number of ticks at the beginning.
      /// \retval true                  The sleep was terminated with timeout.
      /// \retval false                 Otherwise.
      bool
      didSleepTimeout(timer::ticks_t ticks, TimerBase& timer,
          timer::ticks_t beginTicks);

      /// @} end of Private member functions

      /// \name Private member variables
      /// @{

      /// \brief Thread state.
      thread::state_t volatile m_state;

      /// \brief Boolean to remember when special attention is requested.
      bool volatile m_isAttentionRequested;

      /// \brief Storage for the architecture dependent context.
      Context m_context;

      /// \brief The stack object.
      Stack& m_stack;

      /// \brief The current thread static priority.
      priority_t volatile m_staticPriority;

      /// \brief The initial priority given via the constructor.
      priority_t volatile m_initialPriority;

      /// \brief The error code provided by the last call.
      /// Can indicate success or one of the multiple failure reasons.
      errorNumber_t m_error;

      /// \brief The ID used by the scheduler to identify the thread.
      ///
      /// \details
      /// It is set to a unique value only between start() and
      /// stop() (or thread termination).
      id_t m_id;

      /// \brief The address of the function to call for execution.
      threadEntryPoint1_t m_entryPointAddress;

      /// \brief The parameter passed when calling the entry point.
      void* m_entryPointParameter;

      /// \brief Pointer to the thread that requested to join().
      volatile Thread* m_pJoiner;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// Cast the lambda to an entryPoint pointer, copy the stack object
    /// and process like the regular non-template call.
    ///
    /// When the thread is used as a member in another object,
    /// the recommended usage pattern is:
    /// \code{.cpp}
    /// Task::Task() :
    ///   m_thread([] (Task* pTask) { pTask->threadMain();}, this)
    /// {
    ///   ...
    /// }
    /// \endcode
    ///
    /// \warning Be sure that the stack methods are not called from this
    /// constructor! (see initialise())
    template<class Lambda_T, class Object_T>
      Thread::Thread(const char* const pName, Lambda_T function,
          Object_T* pObject, Stack& stack, priority_t priority)
          : NamedObject(pName), //
          m_stack(stack) // copy constructor!
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress("os::core::Thread::Thread()", this,
            pName);
#endif
        initialise(reinterpret_cast<threadEntryPoint1_t>(*function),
            static_cast<void*>(pObject), priority);

      }

    /// \details
    /// Return the reference to the stack object as stored in the private
    /// member variable.
    inline Stack&
    __attribute__((always_inline))
    Thread::getStack(void)
    {
      return m_stack;
    }

    /// \details
    /// Return the current thread static priority as stored in the private
    /// member variable.
    inline Thread::priority_t
    __attribute__((always_inline))
    Thread::getPriority(void) volatile
    {
      return m_staticPriority;
    }

    /// \details
    /// Set the new static priority in the private
    /// member variable.
    inline void
    __attribute__((always_inline))
    Thread::setPriority(priority_t priority)
    {
      m_staticPriority = priority;
    }

    /// \details
    /// Return the current thread ID, as assigned by the scheduler
    /// when the thread was registered. Threads are registered each time
    /// they are started, and deregistered when terminated or  stopped.
    inline Thread::id_t
    __attribute__((always_inline))
    Thread::getId(void) const
    {
      return m_id;
    }

    /// \details
    /// Set the thread ID, as assigned by the scheduler
    /// when the thread was registered.
    inline void
    __attribute__((always_inline))
    Thread::setId(Thread::id_t id)
    {
      m_id = id;
    }

    /// \details
    /// Return the address of the code used for the thread.
    ///
    /// \note This
    /// value is set at construct time and there is no
    /// public method to change it during the life span of the thread.
    inline threadEntryPoint1_t
    __attribute__((always_inline))
    Thread::getEntryPointAddress(void) const
    {
      return m_entryPointAddress;
    }

    /// \details
    /// Return the parameter used when calling the thread code. When
    /// the thread entry point is a member function of
    /// of another C++ class, this is typically a
    /// pointer to the actual object.
    ///
    /// \note This
    /// value is set at construct time and there is no
    /// public method to change it during the life span of the thread.
    inline void*
    __attribute__((always_inline))
    Thread::getEntryPointParameter(void) const
    {
      return m_entryPointParameter;
    }

    inline Thread::Context&
    __attribute__((always_inline))
    Thread::getContext()
    {
      return m_context;
    }

    inline thread::state_t
    __attribute__((always_inline))
    Thread::getState(void)
    {
      return m_state;
    }

    inline bool
    __attribute__((always_inline))
    Thread::isAttentionRequested(void) const
    {
      return m_isAttentionRequested;
    }

    /// \details
    /// The actual error codes are defined in the os::core::Error class.
    inline errorNumber_t
    __attribute__((always_inline))
    Thread::getError(void)
    {
      return m_error;
    }

    /// \details
    /// The actual error codes are defined in the os::core::Error class.
    inline void
    __attribute__((always_inline))
    Thread::setError(errorNumber_t error)
    {
      m_error = error;
    }

    /// \details
    /// This is the actual implementation of the thread synchronisation
    /// primitive, used both in the public sleepWhile() and sleepFor().
    ///
    /// Overhead is low, so being always inlined does not have an
    /// significant overhead, the predicate is expanded only one here,
    /// and the actual sleep code is performed as a separate
    /// function.
    template<class Predicate_T>
      inline void
      __attribute__((always_inline))
      Thread::internalSleepWhile(Predicate_T predicate, timer::ticks_t ticks,
          TimerBase& timer)
      {
        if (m_state == thread::State::RUNNING)
          {

            // Remember the moment when this function was started,
            // to be able to compute the timeout.
            timer::ticks_t beginTicks = timer.getCurrentTicks();

            // TODO: make it run when the scheduler is disabled

            // loop while the predicate is still true
            while (predicate())
              {
                // perform the sleep and, if timeout, break
                if (didSleepTimeout(ticks, timer, beginTicks))
                  {
                    break;
                  }
              }
          }
      }

    /// \details
    /// The public complete synchronisation function. It might
    /// display some debug info and call the internal primitive.
    template<class Predicate_T>
      inline void
      __attribute__((always_inline))
      Thread::sleepWhile(Predicate_T predicate, timer::ticks_t ticks,
          TimerBase& timer)
      {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
        if (ticks != 0)
          {
            os::diag::trace.putString("Thread::sleepWhile(");
            os::diag::trace.putDec(ticks);
            os::diag::trace.putString(")");
            os::diag::trace.putNewLine();
          }
        else
          {
            os::diag::trace.putString("Thread::sleepWhile()");
            os::diag::trace.putNewLine();
          }
#endif

        internalSleepWhile(predicate, ticks, timer);
      }

// ==========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_THREAD_H_
