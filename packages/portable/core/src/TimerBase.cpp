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

//#include "portable/core/include/PlatformBase.h"
#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

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

      timer::ticks_t beginTicks = getTicks();

      if (os::scheduler.isLocked())
        {
          // If the scheduler is locked we can only busy wait for the ticks
          while ((getTicks() - beginTicks) < ticks)
            {
              hal::arch::ArchitectureImplementation::resetWatchdog();
            }

          return;
        }

      Thread* pThread = os::scheduler.getCurrentThread();

      if (pThread->isAttentionRequested())
        {
          // Return immediately if attention was requested
          return;
        }

        {
          // ----- Critical section begin -------------------------------------
          os::core::scheduler::InterruptsCriticalSection cs;

          int index = find(pThread);
          if (index >= 0)
            {
              // Normally the entry should not be there, but for just in case
              remove(index);
#if defined(DEBUG)
              os::diag::trace.putString(" snrt sleep() ");
#endif
            }

          insert(ticks, pThread);
          // ----- Critical section end ---------------------------------------
        }

      // Wait for the ticks to elapse, possibly with multiple suspend calls
      while ((getTicks() - beginTicks) < ticks)
        {
          pThread->suspend();

          if (pThread->isAttentionRequested())
            {
              // Return immediately if attention was requested
              return;
            }
        }

      return;
    }

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
      timer::count_t count = m_count;
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

    /// \details
    /// Insert a new element in a position so that the ticks used to
    /// sleep are ordered ascending. The value stored for the ticks is
    /// relative to the previous element.
    ///
    /// In case two threads need to be resumed at the same time, the
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
    /// to count ticks and to resume the suspended threads when their
    /// associated counters reach zero.
    ///
    /// Due to the way ticks are stored relatively to the previous element,
    /// only the top counter needs to be decremented. When zero is
    /// reached, the thread related to the current element and the threads
    /// related to all following elements with ticks=0 will be resumed.
    void
    TimerBase::processTickFromInterrupt(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      os::diag::trace.putChar('[');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      m_ticks++;

      // decrement timer and eventually resume thread
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
                  p->pThread->resumeFromInterrupt();

                  // Remove the top element from the array
                  // MANDATORY, otherwise the routine hangs with
                  // an infinite loop!
                  remove(0);
                }
              while ((p->ticks == 0) && (m_count > 0));
            }
        }

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      os::diag::trace.putChar(']');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
