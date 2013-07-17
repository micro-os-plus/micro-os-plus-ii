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
    namespace timer
    {
    /// \name Types and constants
    /// @{

    /// @} end of name Types and constants

    }// namespace timer

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class TimerTicks Stack.h "portable/core/include/TimerTicks.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief System timers base.
    ///
    /// \details
    /// Provide common support for all system timers.
    class TimerTicks : public TimerBase
    {
    public:
      /// \name Types and constants
      /// @{

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      TimerTicks(void);

      ~TimerTicks();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      void
      initialise(void);

      void
      start(void);

      void
      stop(void);

      // called each time a tick expire
      // increment the current ticks number, and call the OSTimer::interruptTick.
      void
      interruptServiceRoutine(void);

      /// @} end of Public member functions

    private:
      timer::Element m_array[7];

      hal::arch::TimerTicksImplementation m_implementation;
    };

#pragma GCC diagnostic pop

  // ------------------------------------------------------------------------

  // --
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
