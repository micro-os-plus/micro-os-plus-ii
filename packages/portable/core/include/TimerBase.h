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

      /// \brief Count of elements and size. Must be signed.
      typedef int count_t;

      /// \brief Count of timer ticks.
      typedef uint32_t ticks_t;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \brief The timer will keep an array of such elements.
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
    /// The main routines are sleep() that prepares the timer counters,
    /// and the routine executed on the interrupt context, used to
    /// resume threads.
    class TimerBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pArray    Pointer to the beginning of the timer array.
      /// \param [in] size      Number of timer elements.
      TimerBase(timer::Element* const pArray, timer::count_t const size);

      /// \brief Destructor.
      ~TimerBase();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{


      /// \brief Get the number of active timer elements.
      ///
      /// \par Parameters
      ///    None.
      /// \return               An integer with the number of active elements.
      timer::count_t
      getCount(void) const;

      /// \brief Get the number of ticks since the timer was started.
      ///
      /// \par Parameters
      ///    None.
      /// \return               An integer with the number of ticks.
      timer::ticks_t
      getTicks(void) const;

      /// \brief Sleep a number of ticks.
      ///
      /// \param [in] ticks     The number of ticks to sleep.
      /// \par Returns
      ///    Nothing.
      void
      sleep(timer::ticks_t ticks);

      /// \brief The tick interrupt routine.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      processTickFromInterrupt(void);

      /// @} end of Public member functions

    protected:

      /// \name Protected member functions
      /// @{

      /// \brief Find the index of a thread in the timer array.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \retval -1            Thread not found
      /// \retval >0            Index to the thread
      int
      find(Thread* pThread);

      /// \brief Remove the element at an index.
      ///
      /// \param [in] index     Index of the element to be removed.
      /// \par Returns
      ///    Nothing.
      void
      remove(int index);

      /// \brief Insert an element associated with a thread.
      ///
      /// \param [in] ticks     The number of ticks to sleep.
      /// \param [in] pThread   The associatd thread.
      bool
      insert(timer::ticks_t ticks, Thread* pThread);

      /// @} end of Protected member functions

      /// \name Protected member variables
      /// @{

      /// \brief Pointer to the beginning of the storage area,
      /// the array of timer elements.
      timer::Element* const m_pArray;

      /// \brief The size of m_pArray, in elements.
      timer::count_t const m_size;

      /// \brief The number of m_pArray used elements.
      timer::count_t volatile m_count;

      /// @} end of Protected member variables

    private:

      /// \brief The current number of ticks counted by the timer.
      ///
      /// \details
      /// A 32 bit unsigned will hold about 49 days at 1000 ticks/second
      /// and then will roll over to 0.
      timer::ticks_t volatile m_ticks;
    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// Store the pointer to the real array and its size in the
    /// member variables, and initialise the number of used elements to 0.
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
