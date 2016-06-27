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

#include "portable/diagnostics/include/Trace.h"

#include "portable/language/cpp/include/cstdint.h"

namespace os
{
  namespace core
  {
    class Thread;

    namespace timer
    {
      /// \name Types and constants
      /// @{

      /// \brief Count of elements and size. Must be signed.
      /// \ingroup core_timer
      typedef int count_t;

      /// \brief Count of timer ticks.
      /// \ingroup core_timer
      typedef uint32_t ticks_t;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \brief The timer will keep an array of such elements.
      /// \ingroup core_timer
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
    /// \ingroup core_timer
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
      getCurrentTicks(void) const;

#if 0
      /// \brief Sleep a number of ticks.
      ///
      /// \param [in] ticks     The number of ticks to sleep.
      /// \par Returns
      ///    Nothing.
      void
      sleep(timer::ticks_t ticks);
#endif

      /// \brief The tick interrupt routine.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      interruptServiceRoutine(void);

      /// @} end of Public member functions

    protected:

      /// \name Friends
      /// @{

      friend class TimeoutGuard;
      friend class Thread;

      /// @} end of Friends

      /// \name Protected member functions
      /// @{

#if 0
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
#else

      /// \brief Remove the thread from the timer array.
      ///
      /// \param [in] pThread   Pointer to the thread.
      /// \par Returns
      ///    Nothing.
      void
      remove(Thread* pThread);

      /// \brief Remove the first element in the array.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      removeFirst(void);

#endif
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

      /// \name Private member variables
      /// @{

      /// \brief The current number of ticks counted by the timer.
      ///
      /// \details
      /// A 32 bit unsigned will hold about 49 days at 1000 ticks/second
      /// and then will roll over to 0.
      timer::ticks_t volatile m_ticks;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// Store the pointer to the real array and its size in the
    /// member variables, and initialise the number of used elements to 0.
    inline
    __attribute__((always_inline))
    TimerBase::TimerBase(timer::Element* const pArray,
        timer::count_t const size) :
        m_pArray(pArray), m_size(size)
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
    TimerBase::getCurrentTicks(void) const
    {
      return m_ticks;
    }

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TimeoutGuard Stack.h "portable/core/include/TimerBase.h"
    /// \ingroup core_timer
    /// \nosubgrouping
    ///
    /// \brief Timeout guard.
    ///
    /// \details
    /// Provide a safe timeout facility, using RAII.
    ///
    /// Insert a timer event on the constructor and remove it, if still there,
    /// on the destructor.
    class TimeoutGuard
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] beginTicks   The number of counter ticks at the beginning of the function.
      /// \param [in] ticks   The number of counter ticks.
      /// \param [in] timer   The timer to use.
      /// \param [in] pThread   Pointer to the thread affected.
      TimeoutGuard(timer::ticks_t beginTicks, timer::ticks_t ticks,
          TimerBase& timer, Thread* pThread);

      /// \brief Destructor
      ~TimeoutGuard();

      /// @} end of name Constructors/destructor

      bool
      didTimeout(void);

    private:

      /// \name Private member variables
      /// @{

      /// \brief The timer object used in the constructor.
      TimerBase& m_timer;

      /// \brief The thread object used in the constructor.
      Thread* m_pThread;

      bool m_didTimeout;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    inline bool
    __attribute__((always_inline))
    TimeoutGuard::didTimeout(void)
    {
      return m_didTimeout;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_TIMERBASE_H_
