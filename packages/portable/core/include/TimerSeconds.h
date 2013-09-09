//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer seconds.

#ifndef OS_PORTABLE_CORE_TIMERSECONDS_H_
#define OS_PORTABLE_CORE_TIMERSECONDS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/XCDL_SchedulerDefines.h"

#include "portable/core/include/TimerBase.h"

#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TimerSeconds TimerTicks.h "portable/core/include/TimerSeconds.h"
    /// \ingroup core_timer
    /// \nosubgrouping
    ///
    /// \brief System seconds timer.
    ///
    /// \details
    /// System timer counting seconds, derived from scheduler ticks.
    ///
    class TimerSeconds : public TimerBase
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief The size of the array to store timer elements.
      static constexpr timer::count_t ARRAY_SIZE =
      OS_INTEGER_CORE_SCHEDULER_TIMERTICKSSIZE;

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      TimerSeconds(void);

      /// \brief Destructor.
      ~TimerSeconds();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Initialise the timer.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      initialise(void);

      /// \brief Start the timer.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      start(void);

      /// \brief Stop the timer.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      stop(void);

      /// \brief Timer interrupt service routine.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      interruptServiceRoutine(void);

      /// @} end of Public member functions

    private:
      /// \name Private member variables
      /// @{

      /// \brief Array of elements to store timer data.
      timer::Element m_array[ARRAY_SIZE];

      timer::ticks_t m_ticks;

      /// \brief Instance of the implementation class.
      // hal::arch::TimerTicksImplementation m_implementation;

      /// @} end of Private member variables
    };

#pragma GCC diagnostic pop

  // ==========================================================================

  }// namespace core
} // namespace os

namespace os
{
  // Declaration of the external instantiation of `Scheduler`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern os::core::TimerSeconds timerSeconds;
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_TIMERSECONDS_H_
