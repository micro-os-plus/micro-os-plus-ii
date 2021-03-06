//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Thread definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Thread.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"

#include "portable/core/include/TimerBase.h"

//#include "portable/core/include/PlatformBase.h"
//#include "portable/core/include/Architecture.h"

//#define OS_DEBUG_THREAD         (1)

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Store the stack reference and the priority
    /// in the private member variables.
    ///
    /// \warning Be sure that the stack methods are not called from this
    /// constructor! (see initialise())
    Thread::Thread(const char* const pName, threadEntryPoint0_t entryPoint,
        Stack& stack, priority_t priority) :
        NamedObject(pName), //
        m_stack(stack) // copy reference
    {
#if defined(DEBUG)
      os::diag::trace.putStringAndAddress("os::core::Thread::Thread()", this,
          pName);
#endif

      initialise(reinterpret_cast<threadEntryPoint1_t>(entryPoint), nullptr,
          priority);
    }

    /// \details
    /// Store the stack reference and the priority
    /// in the private member variables.
    ///
    /// \warning Be sure that the stack methods are not called from this
    /// constructor! (see initialise())
    Thread::Thread(const char* const pName, threadEntryPoint1_t entryPoint,
        void* pParameters, Stack& stack, priority_t priority) :
        NamedObject(pName), //
        m_stack(stack) // copy reference
    {
#if defined(DEBUG)
      os::diag::trace.putStringAndAddress("os::core::Thread::Thread()", this,
          pName);
#endif

      initialise(entryPoint, pParameters, priority);
    }

    /// \details
    /// Perform the cleanups.
    Thread::~Thread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif

      cleanup();
    }

    /// \details
    /// Initialise all member variables.
    ///
    /// \warning Do not use the stack yet! Due to the C++
    /// initialisation order, in the (not recommended) case when
    /// the Stack object is a member of
    /// the derived class, it is
    /// constructed after the base class, so at this moment the reference
    /// may be to an object not yet constructed.
    void
    Thread::initialise(threadEntryPoint1_t entryPoint, void* pParameters,
        priority_t priority)
    {
      m_id = scheduler::NO_ID;
      m_initialPriority = priority;
      m_staticPriority = priority;

      m_state = thread::State::NOT_STARTED;

      m_isAttentionRequested = false;

      // Normally not used directly, added for completeness
      m_entryPointAddress = entryPoint;
      m_entryPointParameter = pParameters;
    }

    /// \details
    /// Initialise all thread data, create the new stack context
    /// and register the thread to the scheduler with a new identity.
    /// It can be called not only after object creation, but also
    /// after the thread terminates, either normally or with stop().
    bool
    Thread::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif
      if (m_id != scheduler::NO_ID)
        {
          // already started
          return true;
        }

      m_isAttentionRequested = false;

      m_staticPriority = m_initialPriority;

      m_pJoiner = nullptr;

      m_stack.initialise();

      m_context.create(m_stack.getStart(), m_stack.getSizeBytes(),
          (trampoline3_t) trampoline3, (void*) m_entryPointAddress,
          (void*) m_entryPointParameter, (void*) this);

      m_state = thread::State::RUNNING;
      bool wasRegistered = os::scheduler.registerThread(this);
#if defined(DEBUG)
      if (!wasRegistered)
        {
          os::diag::trace.putString("cannot register thread \"");
          os::diag::trace.putString(getName());
          os::diag::trace.putString("\"");
          os::diag::trace.putNewLine();
        }
#endif

      os::scheduler.yield();

      return wasRegistered;
    }

    /// \details
    /// Force the thread to terminate abruptly, without any notification
    /// to the application code.
    void
    Thread::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif

      m_state = thread::State::TERMINATED;
      // TODO: add code
    }

    /// \details
    /// Deregister the thread from the scheduler and clear the
    /// internal ID.
    void
    Thread::cleanup()
    {
      m_state = thread::State::TERMINATED;

      if (m_id != scheduler::NO_ID)
        {
          os::scheduler.deregisterThread(this);

          // clear the id, to mark that the thread was de-registered
          m_id = scheduler::NO_ID;
        }

      m_pJoiner = nullptr;
    }

    /// \details
    /// Suspend the thread, remove it from the active list and
    /// yield to the next thread.
    ///
    /// \warning Currently cannot be called from interrupt contexts.
    /// \todo Check if interrupt context and call yield only if not.
    void
    Thread::suspend(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      m_state = thread::State::SUSPENDED;

      // suspend should always yield, to remove the current thread
      // from the active list, otherwise loops waiting for a condition
      // will hang
      os::scheduler.yield();
    }

    /// \details
    /// Resume the thread by inserting it into the active list.
    ///
    /// It assumes it is called from a thread context, so it
    /// disables/enables interrupts.
    void
    Thread::resume(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      if (m_state == thread::State::SUSPENDED)
        {
          // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

          m_state = thread::State::RUNNING;

          os::scheduler.resumeThreadNoInterrupts(this);
          // ----- Critical section end ---------------------------------------
        }
    }

    /// \details
    /// Block until the thread code has completed.
    void
    Thread::join(void)
    {
#if defined(DEBUG)
      os::diag::trace.putMemberFunctionWithName();
#endif

      if (m_pJoiner == nullptr)
        {
          // When the thread quits, it'll wakeup() this joiner
          m_pJoiner = os::scheduler.getCurrentThread();
        }
#if defined(DEBUG)
      else
        {
          os::diag::trace.putString("Multiple join() not allowed.");
          os::diag::trace.putNewLine();

          return;
        }
#endif

      Thread* pThread = os::scheduler.getCurrentThread();

      // Wait for the thread to be terminated
      pThread->sleepWhile([=]()
        {
          // lambda return
          return (m_state != thread::State::TERMINATED);
        });

    }

    /// \details
    /// Directly starting the thread entry point is not enough, since it can
    /// return, and we need a place to perform thread cleanup operations.
    ///
    /// \note Must be public, to be accessible from custom schedulers.
    void
    Thread::trampoline3(threadEntryPoint1_t entryPoint, void* pParameters,
        Thread* pThread)
    {
      // call the actual thread code, with the pointer to the
      // thread data.
      (*entryPoint)(pParameters);

        { // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

          Thread* pJoiner = const_cast<Thread*>(pThread->m_pJoiner);
          if (pJoiner != nullptr)
            {
              // Wakeup thread waiting to join, if any
              pJoiner->wakeup();
            }
          // deregister the given thread and make sure it'll never be used
          pThread->cleanup();

        } // ----- Critical section end ---------------------------------------

      // pass control to the next thread
      os::scheduler.yield();
    }

    /// \details
    /// A typical case when a thread is requested special
    /// attention is when a monitoring thread decides that
    /// an action should be cancelled. Setting this flag informs
    /// well behaved synchronisation objects that they should
    /// not block, or break an existing block.
    /// Normally after requesting
    /// attention from a thread, that thread should also be waked-up,
    /// with an explicit call to wakeup(),
    /// to break a possible long wait.
    ///
    /// This terminating effect on blocking calls remains active
    /// as long as this flag is set, so the destination thread
    /// should call acknowledgeAttention() to cancel it as soon as
    /// it is aware of this condition
    /// and took the appropriate measures.
    void
    Thread::requestAttention(void)
    {
      m_isAttentionRequested = true;
    }

    /// \details
    /// This function clears the flag and resumes normal processing
    /// of blocking calls.
    ///
    /// It must be issued by the thread that was requested
    /// attention, as soon as it is aware of this condition
    /// and took the appropriate measures.
    void
    Thread::acknowledgeAttention(void)
    {
      m_isAttentionRequested = false;
    }

    /// \details
    /// This is the second synchronisation primitive, a subset of the
    /// more general sleepWhile(), but providing unconditional sleep
    /// periods.
    ///
    /// It is implemented on top of internalSleepWhile(), but
    /// with an always true constant condition.
    ///
    /// Passing a zero number of ticks means no timeout at all.
    ///
    /// The default timer is the scheduler ticks timer.
    void
    Thread::sleepFor(timer::ticks_t ticks, TimerBase& timer)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putString("Thread::sleepFor(");
      os::diag::trace.putDec(ticks);
      os::diag::trace.putString(")");
      os::diag::trace.putNewLine();
#endif
      if (ticks == 0)
        {
          // No ticks, no sleep.
          return;
        }

      // The function template is expanded inline here,
      // with the 'always true' condition passed as lambda.
      internalSleepWhile([]()
        { return true;}, ticks, timer);
    }

    /// \details
    /// Wake-up the thread by inserting it into the active list.
    ///
    /// \warning Must be called with interrupts disabled.
    void
    Thread::wakeupNoInterrupts(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      if ((m_state == thread::State::SLEEPING)
          || (m_state == thread::State::RUNNING))
        {
          m_state = thread::State::RUNNING;

          os::scheduler.resumeThreadNoInterrupts(this);
        }
    }

    /// \details
    /// Wake-up the thread by inserting it into the active list.
    ///
    /// It assumes it is called from a thread context, so it
    /// disables/enables interrupts.
    void
    Thread::wakeup(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      wakeupNoInterrupts();
      // ----- Critical section end -------------------------------------------
    }

    /// \details
    /// Internal function, used in sleepFor() and sleepWhile().
    ///
    /// Insert the current thread with the given number of ticks in the
    /// timer counters storage, and suspend the current thread.
    ///
    /// In case the thread did requested attention, the sleep is
    /// cancelled as soon as possible.
    ///
    /// If the scheduler is locked, this call is still functional, but
    /// using a busy wait until the ticks elapse (not yet implemented).

    bool
    Thread::didSleepTimeout(timer::ticks_t ticks, TimerBase& timer,
        timer::ticks_t beginTicks)
    {
      if (isAttentionRequested())
        {
          // Quit everything if attention was requested
          return true;
        }

      /// TODO: If the scheduler is locked, use a busy wait.

      // If the condition is still true, we must sleep,
      // either indefinitely or for a limited number of ticks
      if (ticks != 0)
        {
#if 0
          // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

          timer::ticks_t nowTicks = timer.getCurrentTicks();
          if ((nowTicks - beginTicks) >= ticks)
            {
              return true;
            }
          else
            {
              // Normally the entry should not be there, but for just in case
              timer.remove(this);

              // insert timeout
              timer.insert(ticks, this);

              // Will return either with a condition change or with a timeout
              os::scheduler.yield();

              // remove timeout
              timer.remove(this);
            }
          // ----- Critical section end ---------------------------------------

#else
          // ----- Timeout guard begin ----------------------------------------
          TimeoutGuard tg(beginTicks, ticks, timer, this);

          if (tg.didTimeout())
            return true;

          os::scheduler.yield();
          // ----- Timeout guard end ------------------------------------------
#endif
        }
      else
        {
          // If no timeout, sleep is just an yield
          os::scheduler.yield();
        }

      return false;
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
