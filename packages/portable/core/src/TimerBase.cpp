//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer base definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/TimerBase.h"
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/CriticalSections.h"

#include "portable/core/include/Thread.h"

//#include "portable/core/include/PlatformBase.h"
#include "portable/core/include/Architecture.h"

//#define OS_DEBUG_TIMERBASE	(1)

namespace os
{
  namespace core
  {
    // ========================================================================

#if 0
    /// \details
    /// Insert the current thread with the given number of ticks in the
    /// timer counters storage, and suspend the current thread repeately
    /// until the number of ticks elapsed.
    ///
    /// In case the thread was requested attention, the sleep is
    /// cancelled as soon as possible.
    ///
    /// If the scheduler is locked, this call is still functional, but
    /// using a busy wait until the ticks elapse.
    void
    TimerBase::sleep(timer::ticks_t ticks)
    {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE)
      os::diag::trace.putString("TimerBase::sleep(");
      os::diag::trace.putDec(ticks);
      os::diag::trace.putString(")");
      os::diag::trace.putNewLine();
#endif
      if (ticks == 0)
        return;

      timer::ticks_t beginTicks = getCurrentTicks();

      if (os::scheduler.isLocked())
        {
          // If the scheduler is locked we can only busy wait for the ticks
          while ((getCurrentTicks() - beginTicks) < ticks)
            {
              os::architecture.resetWatchdog();
            }

          return;
        }

      Thread* pThread = os::scheduler.getCurrentThread();

      for (;;)
        {
          timer::ticks_t nowTicks = getCurrentTicks();
          if ((nowTicks - beginTicks) >= ticks)
            {
              return;
            }

          if (pThread->isAttentionRequested())
            {
              // Return immediately if attention was requested
              return;
            }

          pThread->suspendWithTimeout(ticks - (nowTicks - beginTicks), *this);
        }
    }
#endif

#if 0
    /// \details
    /// Iterate through the array and return the index in case the
    /// thread is found.
    int
    TimerBase::find(Thread* pThread)
      {
        timer::count_t count = m_count;

        timer::Element* p;
        p = m_pArray;

        for (int i = 0; i < count; ++i, ++p)
          {
            if (pThread == p->pThread)
              {
                return i;
              }
          }

        return -1;
      }

    /// \details
    /// Move all subsequent elements one step to the left. This is not
    /// particularly efficient, especially when called with index=0,
    /// but with just a few entries in the array it should be ok.
    void
    TimerBase::remove(int index)
      {
        if (index < 0)
        return;

        timer::count_t count = m_count;
        if (index >= count)
          {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE)
            os::diag::trace.putString("TimerBase::remove() out of range");
            os::diag::trace.putNewLine();
#endif
            return;
          }

        if (count > 0)
          {
            if (count > 1)
              {
                timer::Element* p;
                p = &m_pArray[index];

                for (; index < count - 1; index++, p++)
                  {
                    *p = *(p + 1);
                  }
              }
            m_count--;
          }
      }

#else

    /// \details
    /// Move all subsequent elements one step to the left. This is not
    /// particularly efficient,
    /// but with just a few entries in the array it should be ok.
    void
    TimerBase::removeFirst(void)
    {
      timer::count_t count = m_count;

      if (count > 0)
        {
          if (count > 1)
            {
              // If at least two elements are present, we have to move
              // the array elements

              timer::Element* p = m_pArray;

              for (int index = 0; index < count - 1; index++, p++)
                {
                  // Move remaining elements one step to the left
                  *p = *(p + 1);
                }
            }

          // We removed one element, the count is decremented
          m_count--;
        }
    }

    /// \details
    /// Find the position of the thread in the array and remove it
    /// by moving all following elements one step to the left.
    void
    TimerBase::remove(Thread* pThread)
    {
      timer::count_t count = m_count;

      // Check if there are any elements in the array
      if (count == 0)
        {
          // There are not, nothing to do
          return;
        }

      // Try to find the location of the thread in the array
      timer::Element* p = m_pArray;

      int index;
      for (index = 0; index < count; ++index, ++p)
        {
          if (pThread == p->pThread)
            {
              // Got it, index remembers the position
              break;
            }
        }

      // If we reached the end of the world, the thread is not in,
      // so nothing to remove
      if (index == count)
        return;

      if (count > 1)
        {
          // If at least two elements, we might need to move
          // part of the array

          // The search left the pointer on the element we
          // want to remove, p = &m_pArray[index];

          for (; index < count - 1; index++, p++)
            {
              // Move remaining elements one step to the left
              *p = *(p + 1);
            }
        }

      // We removed one element, the count is decremented
      m_count--;

    }

#endif

    /// \details
    /// Insert a new element in a position so that the ticks used to
    /// sleep are ordered ascending. The value stored for the ticks is
    /// relative to the previous element.
    ///
    /// In case two threads need to be waked-up at the same time, the
    /// second one inserted will have a ticks value of 0, and the
    /// ticks interrupt routine must process all elements until
    /// a non zero is encountered.
    bool
    TimerBase::insert(timer::ticks_t ticks, Thread* pThread)
    {
      if (ticks == 0)
        {
          return false;
        }

      int cnt;
      cnt = m_count;

      if (cnt == m_size)
        {
#if defined(DEBUG)
          os::diag::trace.putString("TimerBase::insert() full");
          os::diag::trace.putNewLine();
#endif
          return false;
        }

      volatile timer::Element* p;
      int i;

#if defined(DEBUG)

      p = m_pArray;

      for (i = 0; i < cnt; ++i, ++p)
        {
          if (p->pThread == pThread)
            {
              os::diag::trace.putString("TimerBase::insert() already in ");
              os::diag::trace.putHex(pThread);
              os::diag::trace.putChar(' ');
              os::diag::trace.putString(pThread->getName());
              os::diag::trace.putChar(' ');
              os::diag::trace.putDec(p->ticks);
              os::diag::trace.putNewLine();
            }
        }

#endif

      p = m_pArray;
      i = 0;
      if (cnt > 0)
        {
          // Find position where to insert
          for (i = 0; i < cnt; ++i, ++p)
            {
              if (ticks < p->ticks)
                {
                  p->ticks -= ticks; // adjust current
                  break;
                }
              ticks -= p->ticks;
            }
          // Here i = position where to insert, but it
          // may also be count, i.e. not found, end of array

          // Move all elements right to make space
          timer::Element* q;
          int j;
          for (j = cnt, q = &m_pArray[j]; j > i; j--, q--)
            {
              *q = *(q - 1);
            }
        }

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE)
      os::diag::trace.putString("TimerBase::insert() cnt=");
      os::diag::trace.putDec(cnt);
      os::diag::trace.putNewLine();
#endif

      // Fill in timer::element_t
      p->ticks = ticks;
      p->pThread = pThread;

      m_count++;

      return true;
    }

    /// \details
    /// This routine is called from the timer interrupt service routine
    /// to count ticks and to wake-up the sleeping threads when their
    /// associated counters reach zero.
    ///
    /// Due to the way ticks are stored relatively to the previous element,
    /// only the top counter needs to be decremented. When zero is
    /// reached, the thread related to the current element and the threads
    /// related to all following elements with ticks=0 will be waked-up.
    void
    TimerBase::processTickFromInterrupt(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      os::diag::trace.putChar('[');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      m_ticks++;

      // decrement timer and eventually wake-up thread
      if (m_count > 0) // is there anything in the list?
        {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
          os::diag::trace.putChar('*');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
          volatile timer::Element* p;
          p = m_pArray;

          // Decrement the counter associated with the first element
          if (--(p->ticks) == 0)
            {
              do
                {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
                  os::diag::trace.putString("Tick() resume ");
                  os::diag::trace.putString(p->pThread->getName());
                  os::diag::trace.putNewLine();
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
                  // sleep period completed, resume the thread
                  //p->pThread->resumeFromInterrupt(ResumeDetails::TIMER);
                  p->pThread->wakeup();

                  // Remove the top element from the array

                  // MANDATORY, otherwise this routine hangs with
                  // an infinite loop!
                  removeFirst();
                }
              while ((p->ticks == 0) && (m_count > 0));
            }
        }

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      os::diag::trace.putChar(']');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
    }

    // ========================================================================

    TimeoutGuard::TimeoutGuard(timer::ticks_t ticks, TimerBase& timer)
        : m_timer(timer)
    {
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      Thread* pThread = os::scheduler.getCurrentThread();

      // Normally the entry should not be there, but for just in case
      timer.remove(pThread);

      timer.insert(ticks, pThread);
      // ----- Critical section end -------------------------------------------
    }

    TimeoutGuard::~TimeoutGuard()
    {
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      Thread* pThread = os::scheduler.getCurrentThread();

      m_timer.remove(pThread);
      // ----- Critical section end -------------------------------------------
    }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
