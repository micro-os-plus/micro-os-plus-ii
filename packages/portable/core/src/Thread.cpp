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
        Stack& stack, priority_t priority)
        : NamedObject(pName), //
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
        void* pParameters, Stack& stack, priority_t priority)
        : NamedObject(pName), //
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

#if 0
      m_isSuspended = true;
      m_isSleeping = true;
#endif

      m_isAttentionRequested = false;

      //m_resumeDetails = 0;

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

#if 0
      m_isSuspended = false;
      m_isSleeping = false;
#endif

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
#if 0
      m_isSuspended = true;
#endif
      m_state = thread::State::TERMINATED;

      if (m_id != scheduler::NO_ID)
        {
          os::scheduler.deregisterThread(this);

          // clear the id, to mark that the thread was de-registered
          m_id = scheduler::NO_ID;
        }

      m_pJoiner = nullptr;
    }

#if 1
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

          os::scheduler.resumeThreadFromInterrupt(this);
          // ----- Critical section end ---------------------------------------
        }
    }

#else
    /// \details
    /// Suspend the thread, remove it from the active list and
    /// yield to the next thread.
    ///
    /// \warning Currently cannot be called from interrupt contexts.
    /// \todo Check if interrupt context and call yield only if not.
    resumeDetails_t
    Thread::suspend(void)
      {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
        os::diag::trace.putMemberFunctionWithName();
#endif
        m_isSuspended = true;

        // Clear the detail flags
        m_resumeDetails = 0;

        // suspend should always yield, to remove the current thread
        // from the active list, otherwise loops waiting for a condition
        // will hang
        os::scheduler.yield();

        return m_resumeDetails;
      }

    resumeDetails_t
    Thread::suspendWithTimeout(timer::ticks_t ticks, TimerBase& timer)
      {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
        os::diag::trace.putMemberFunctionWithName();
#endif

        // ----- Timeout guard begin --------------------------------------------
        TimeoutGuard tg(ticks, timer);

        return suspend();
        // ----- Timeout guard end ----------------------------------------------
      }

    /// \details
    /// Resume the thread by inserting it into the active list.
    ///
    /// It assumes it is called from an interrupt context, and
    /// no other synchronisations are performed.
    void
    Thread::resumeFromInterrupt(resumeDetails_t detail)
      {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
        os::diag::trace.putMemberFunctionWithName();
#endif
        m_isSuspended = false;

        // Add the detail flags. Be sure it is atomic.
        m_resumeDetails |= detail;

        os::scheduler.resumeThreadFromInterrupt(this);
      }

    /// \details
    /// Resume the thread by inserting it into the active list.
    ///
    /// It assumes it is called from a thread context, so it
    /// disables/enables interrupts.
    void
    Thread::resume(resumeDetails_t detail)
      {
        // ----- Critical section begin -----------------------------------------
        os::core::scheduler::InterruptsCriticalSection cs;

        resumeFromInterrupt(detail);
        // ----- Critical section end -------------------------------------------
      }
#endif

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
#if 1
      Thread* pThread = os::scheduler.getCurrentThread();

      pThread->sleepWhile([=]()
        {
          return (m_id != scheduler::NO_ID);
        });
#else
      // TODO: change to sleepWhile()
      while (m_id != scheduler::NO_ID)
        {
          // TODO: Study if we should consider attention requests. How?

          // Suspend the thread calling join(), not the thread
          // to be joined!
          os::scheduler.getCurrentThread()->sleepFor(1);
        }
#endif
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

#if 0
    thread::wakeupDetails_t
    Thread::sleep(void)
      {
        // Clear the detail flags
        m_wakeupDetails = 0;

#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
        os::diag::trace.putString("Thread::sleep()");
        os::diag::trace.putNewLine();
#endif

        if (m_state != thread::State::RUNNING)
          {
            return m_wakeupDetails;
          }

        if (isAttentionRequested())
          {
            // Return immediately if attention was requested
            return m_wakeupDetails;
          }

#if 0
        m_isSuspended = true;
        m_isSleeping = true;
#endif

        m_state = thread::State::SLEEPING;

        os::scheduler.yield();

        return m_wakeupDetails;
      }
#endif

    /// \details
    /// Insert the current thread with the given number of ticks in the
    /// timer counters storage, and suspend the current thread repeatedly
    /// until the number of ticks elapsed.
    ///
    /// In case the thread was requested attention, the sleep is
    /// cancelled as soon as possible.
    ///
    /// If the scheduler is locked, this call is still functional, but
    /// using a busy wait until the ticks elapse.
    thread::wakeupDetails_t
    Thread::sleepFor(timer::ticks_t ticks, TimerBase& timer)
    {
      // Clear the detail flags
      m_wakeupDetails = 0;

#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putString("Thread::sleepFor(");
      os::diag::trace.putDec(ticks);
      os::diag::trace.putString(")");
      os::diag::trace.putNewLine();
#endif
      if (ticks == 0)
        {
          return m_wakeupDetails;
        }

      if (m_state != thread::State::RUNNING)
        {
          return m_wakeupDetails;
        }

      timer::ticks_t beginTicks = timer.getCurrentTicks();

      if (os::scheduler.isLocked())
        {
          // If the scheduler is locked we can only busy wait for the ticks
          while ((timer.getCurrentTicks() - beginTicks) < ticks)
            {
              os::architecture.resetWatchdog();
            }

          return m_wakeupDetails;
        }

      for (;;)
        {
#if 1
          if (didSleepTimeout(ticks, timer, beginTicks))
            {
              return m_wakeupDetails;
            }
#else
          timer::ticks_t nowTicks = timer.getCurrentTicks();
          if ((nowTicks - beginTicks) >= ticks)
            {
              return m_wakeupDetails;
            }

          if (isAttentionRequested())
            {
              // Return immediately if attention was requested
              return m_wakeupDetails;
            }

            {
              // ----- Timeout guard begin --------------------------------------------
              TimeoutGuard tg(ticks - (nowTicks - beginTicks), timer);

              m_state = thread::State::SLEEPING;

              os::scheduler.yield();
              // ----- Timeout guard end ----------------------------------------------
            }
#endif
        }
    }

    /// \details
    /// Wake-up the thread by inserting it into the active list.
    ///
    /// It assumes it is called from a thread context, so it
    /// disables/enables interrupts.
    void
    Thread::wakeup(thread::wakeupDetails_t detail)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREAD)
      os::diag::trace.putMemberFunctionWithName();
#endif
      if ((m_state == thread::State::SLEEPING)
          || (m_state == thread::State::RUNNING))
        {
          // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

#if 0
          m_isSleeping = false;
          m_isSuspended = false;
#endif
          m_state = thread::State::RUNNING;

          // Add the detail flags. Be sure it is atomic.
          m_wakeupDetails |= detail;

          os::scheduler.resumeThreadFromInterrupt(this);
          // ----- Critical section end ---------------------------------------
        }
    }

    bool
    Thread::didSleepTimeout(timer::ticks_t ticks, TimerBase& timer,
        timer::ticks_t beginTicks)
    {
      if (isAttentionRequested())
        {
          // Quit everything if attention was requested
          return false;
        }

      // If the condition is still true, we must sleep,
      // either indefinitely or for a limited number of ticks
      if (ticks != 0)
        {
          timer::ticks_t nowTicks = timer.getCurrentTicks();
          if ((nowTicks - beginTicks) >= ticks)
            {
              return false;
            }

            {
              // ----- Timeout guard begin --------------------------------------------
              TimeoutGuard tg(ticks - (nowTicks - beginTicks), timer);

              m_state = thread::State::SLEEPING;

              os::scheduler.yield();
              // ----- Timeout guard end ----------------------------------------------
            }
        }
      else
        {
          m_state = thread::State::SLEEPING;

          os::scheduler.yield();
        }

      return true;
    }

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
