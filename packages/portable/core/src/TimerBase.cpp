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

#include "portable/core/include/Architecture.h"

#if defined(DEBUG)
//#define OS_DEBUG_TIMERBASE_INSERT	(1)
#define OS_DEBUG_TIMERBASE_REMOVE      (1)
//#define OS_DEBUG_TIMERBASE_INTERRUPTTICK (1)
#endif

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \details
    /// Move all subsequent elements one step to the left. This is not
    /// particularly efficient,
    /// but with just a few entries in the array it should be ok.
    ///
    /// \note Must be executed in a critical section.
    void
    TimerBase::removeFirst(void)
    {
      timer::count_t count = m_count;

      // Check if there are any elements in the array
      if (count <= 0)
        {
          // There are not, nothing to do
          return;
        }

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

          p->ticks = 0;
          p->pThread = nullptr;
        }

      // We removed one element, the count is decremented
      m_count--;

    }

    /// \details
    /// Find the position of the thread in the array and remove it
    /// by moving all following elements one step to the left.
    ///
    /// \note Must be executed in a critical section.
    void
    TimerBase::remove(Thread* pThread)
    {
      timer::count_t count = m_count;

      // Check if there are any elements in the array
      if (count <= 0)
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

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_REMOVE)
      os::diag::trace.putString(" tr(");
      os::diag::trace.putString(p->pThread->getName());
      os::diag::trace.putString(",");
      os::diag::trace.putDec(p->ticks);
      os::diag::trace.putString("@");
      os::diag::trace.putDec(index);
      os::diag::trace.putString(") ");
#endif

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

          p->ticks = 0;
          p->pThread = nullptr;
        }

      // We removed one element, the count is decremented
      m_count--;

    }

    /// \details
    /// Insert a new element in a position so that the ticks used to
    /// sleep are ordered ascending. The value stored for the ticks is
    /// relative to the previous element.
    ///
    /// In case two threads need to be waked-up at the same time, the
    /// second one inserted will have a ticks value of 0, and the
    /// ticks interrupt routine must process all elements until
    /// a non zero is encountered.
    ///
    /// \note Must be executed in a critical section.
    bool
    TimerBase::insert(timer::ticks_t ticks, Thread* pThread)
    {
      if (ticks == 0)
        {
          return false;
        }

      int count = m_count;

      if (count >= m_size)
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

      for (i = 0; i < count; ++i, ++p)
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

              // Do not return, to report multiple occurrences
            }
        }

#endif

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INSERT)
      timer::ticks_t saveTicks = ticks;
#endif

      p = m_pArray;
      i = 0;
      if (count > 0)
        {
          // Find position where to insert
          for (i = 0; i < count; ++i, ++p)
            {
              // If ticks and p->ticks are zero, the search continues and
              // the new 0 will be inserted before the next non-zero entry.
              if (ticks < p->ticks)
                {
                  p->ticks -= ticks; // adjust current
                  break;
                }
              // If multiple threads use the same value,
              // ticks turns to 0.
              ticks -= p->ticks;
            }
          // Here i = position where to insert, but it
          // may also be count, i.e. not found, end of array

          // Move all elements right to make space.
          // count is guaranteed less than size
          int j = count;
          timer::Element* q = &m_pArray[count];
          for (; j > i; j--, q--)
            {
              *q = *(q - 1);
            }
        }

#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INSERT)
      os::diag::trace.putString(" ti(");
      os::diag::trace.putString(pThread->getName());
      os::diag::trace.putString(",");
      os::diag::trace.putDec(saveTicks);
      os::diag::trace.putString(">");
      os::diag::trace.putDec(ticks);
      os::diag::trace.putString("@");
      os::diag::trace.putDec(i);
      os::diag::trace.putString("/");
      os::diag::trace.putDec(count+1);
      os::diag::trace.putString(") ");
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
    TimerBase::interruptServiceRoutine(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      os::diag::trace.putChar('[');
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
      // Increment the perpetual ticks counter. Will obviously overflow
      // and start from 0.
      m_ticks++;

      // Decrement timer and eventually wake-up thread
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
                  os::diag::trace.putString(" tw(");
                  os::diag::trace.putString(p->pThread->getName());
                  os::diag::trace.putString(",");
                  os::diag::trace.putDec(m_count);
                  os::diag::trace.putString(") ");
#endif // defined(DEBUG) && defined(OS_DEBUG_TIMERBASE_INTERRUPTTICK)
                  // Sleep period completed, wake-up the thread
                  p->pThread->wakeupNoInterrupts();

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

    TimeoutGuard::TimeoutGuard(timer::ticks_t beginTicks, timer::ticks_t ticks,
        TimerBase& timer, Thread* pThread) :
        m_timer(timer), m_pThread(pThread)
    {
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      timer::ticks_t nowTicks = timer.getCurrentTicks();
      if ((nowTicks - beginTicks) >= ticks)
        {
          m_didTimeout = true;
        }
      else
        {
          // Normally the entry should not be there, but for just in case
          timer.remove(pThread);

          timer.insert(ticks, pThread);

          m_didTimeout = false;
        }
      // ----- Critical section end -------------------------------------------
    }

    TimeoutGuard::~TimeoutGuard()
    {
      // ----- Critical section begin -----------------------------------------
      os::core::scheduler::InterruptsCriticalSection cs;

      m_timer.remove(m_pThread);
      // ----- Critical section end -------------------------------------------
    }

  // ==========================================================================

  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
