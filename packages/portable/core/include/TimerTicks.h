//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Timer ticks.

#ifndef OS_PORTABLE_CORE_TIMERTICKS_H_
#define OS_PORTABLE_CORE_TIMERTICKS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

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

    /// \class TimerTicks TimerTicks.h "portable/core/include/TimerTicks.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief System ticks timer.
    ///
    /// \details
    /// System timer counting scheduler ticks.
    ///
    /// \example portable/core/tests/src/sleep.cpp
    class TimerTicks : public TimerBase
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
      TimerTicks(void);

      /// \brief Destructor.
      ~TimerTicks();

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

      /// \brief Instance of the implementation class.
      hal::arch::TimerTicksImplementation m_implementation;

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
  extern os::core::TimerTicks timerTicks;
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_TIMERTICKS_H_
