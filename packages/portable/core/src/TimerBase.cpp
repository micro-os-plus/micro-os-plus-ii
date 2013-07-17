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
//#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    void
    TimerBase::sleep(timer::ticks_t ticks)
    {
      if (ticks == 0)
        return;

      timer::ticks_t beginTicks = getTicks();

      if (os::scheduler.isLocked())
        {
          while ((getTicks() - beginTicks) < ticks)
            {
              // TODO: watchdogReset()
            }

          return;
        }

      Thread* pThread = os::scheduler.getCurrentThread();

      if (pThread->isAttentionRequested())
        {
          // return immediately if attention was requested
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
            }

          insert(ticks, pThread);
          // ----- Critical section end ---------------------------------------
        }

      while ((getTicks() - beginTicks) < ticks)
        {
          pThread->suspend();

          if (pThread->isAttentionRequested())
            {
              // return immediately if attention was requested
              return;
            }
        }

      return;
    }

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
              os::diag::trace.putString("OSTimer::insert() already in ");
              os::diag::trace.putHex(pThread);
              os::diag::trace.putChar(' ');
              os::diag::trace.putString(pThread->getName());
              os::diag::trace.putChar(' ');
              os::diag::trace.putDec((int) p->ticks);
              os::diag::trace.putNewLine();
            }
        }

#endif

      p = m_pArray;
      i = 0;
      if (cnt > 0)
        {
          // find position where to insert
          for (i = 0; i < cnt; ++i, ++p)
            {
              if (ticks < p->ticks)
                {
                  p->ticks -= ticks; // adjust current
                  break;
                }
              ticks -= p->ticks;
            }
          // return i = position where to insert,
          // may be count, i.e. not found, end of array

          // move right to make space
          timer::Element* q;
          int j;
          for (j = cnt, q = &m_pArray[j]; j > i; j--, q--)
            {
              *q = *(q - 1);
            }
        }

      // fill in timer::element_t
      p->ticks = ticks;
      p->pThread = pThread;

      m_count++;

      return true;
    }

    // called from the interrupt routine to notify time events
    void
    TimerBase::interruptTick(void)
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

          if (--(p->ticks) == 0)
            {
              do
                {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
                  os::diag::trace.putString("Tick() ");
                  os::diag::trace.putHex(p);
                  os::diag::trace.putNewLine();
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)

                  // sleep period completed, resume the thread
                  p->pThread->resumeFromInterrupt();

                  // remove top element from the array
                  // MANDATORY, otherwise infinite loop!
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
