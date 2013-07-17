//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief System timers base.

#ifndef OS_PORTABLE_CORE_TIMERBASE_H_
#define OS_PORTABLE_CORE_TIMERBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include <stdint.h>

#include "portable/diagnostics/include/Trace.h"
#include "portable/core/include/Thread.h"

namespace os
{
  namespace core
  {
    namespace timer
    {
      /// \name Types and constants
      /// @{

      // signed
      typedef int count_t;

      // unsigned
      typedef uint32_t ticks_t;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      typedef struct
      {
        ticks_t volatile ticks;
        Thread* volatile pThread;

      } Element;

#pragma GCC diagnostic pop


    /// @} end of name Types and constants

    }// namespace timer

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TimerBase Stack.h "portable/core/include/TimerBase.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief System timers base.
    ///
    /// \details
    /// Provide common support for all system timers.
    class TimerBase
    {
    public:
      /// \name Types and constants
      /// @{

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pArray    Pointer to the beginning of the timer array.
      /// \param [in] size      Number of timer elements.
      TimerBase(timer::Element* const pArray, timer::count_t const size);

      ~TimerBase();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      timer::count_t
      getCount(void) const;

      timer::ticks_t
      getTicks(void) const;

      void
      sleep(timer::ticks_t);

      // used in interrupt routines
      void
      interruptTick(void);

      /// @} end of Public member functions

    protected:

      /// \name Protected member functions
      /// @{

      int
      find(Thread* pThread);

      void
      remove(int index);

      bool
      insert(timer::ticks_t ticks, Thread* pThread);

      /// @} end of Protected member functions

      /// \name Protected member variables
      /// @{

      /// \brief Pointer to the beginning of the stack area.
      // the array of timeouts
      timer::Element* const m_pArray;

      // the size of m_pArray, in elements
      timer::count_t const m_size;

      // the number of slots used from m_pArray
      timer::count_t volatile m_count;

      /// @} end of Protected member variables

    private:

      /// \brief the current number of ticks counted by the timer.
      ///
      /// \details
      /// A 32 bit unsigned will hold about 49 days at 1000 ticks/second
      /// and then will start again from 0.
      timer::ticks_t volatile m_ticks;
    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    inline
    __attribute__((always_inline))
    TimerBase::TimerBase(timer::Element* const pArray,
        timer::count_t const size)
        : m_pArray(pArray), m_size(size)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

      m_count = 0;
      m_ticks = 0;
    }

    inline
    __attribute__((always_inline))
    TimerBase::~TimerBase()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    inline timer::count_t
    __attribute__((always_inline))
    TimerBase::getCount(void) const
    {
      return m_count;
    }

    inline timer::ticks_t
    __attribute__((always_inline))
    TimerBase::getTicks(void) const
    {
      return m_ticks;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_TIMERBASE_H_
