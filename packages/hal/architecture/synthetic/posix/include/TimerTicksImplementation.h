//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX declarations of TimerTicks implementation.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_TIMERTICKSIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_TIMERTICKSIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

// Platform headers
#include <signal.h>

namespace hal
{
  namespace posix
  {
    namespace timer
    {
      // constexpr int SIGNAL_NUMBER = SIGVTALRM;
      constexpr int SIGNAL_NUMBER = SIGALRM;

    } // namespace timer

    // ========================================================================

    /// \class TimerTicksImplementation TimerTicksImplementation.h "hal/architecture/synthetic/posix/include/Thread.h"
    /// \ingroup posix
    /// \nosubgrouping
    ///
    /// \brief Implementation of the ticks timer.
    ///
    /// \details
    /// The ticks timer uses the POSIX signals, SIGALRM in particular,
    /// configured with the setitimer() system call to generate interrupts
    /// at the desired rate
    /// (usually 1000 ticks per second).
    ///
    /// The timer does not generate preemptive context switches (the POSIX
    /// signal processing does not allow this, or it would be too complicated
    /// to implement with a separate signal stack and context copied from/to
    /// here).
    ///
    /// \note The timer uses the POSIX timer ITIMER_REAL, i.e. the normal time,
    /// which, under heavy processor load might not be very accurate, but
    /// simple measurements showed it is accurate more than enough for
    /// simulation purposes.
    class TimerTicksImplementation
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      TimerTicksImplementation(void);

      /// \brief Destructor.
      ~TimerTicksImplementation();

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

      /// \brief Acknowledge interrupt.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      acknowledgeInterrupt(void);

      /// @} end of name Public member functions

    private:

      /// \name Private static functions
      /// @{

      static void
      signalHandler(int signalNumber);

      /// @} end of Private static functions

      /// \name Private member variables
      /// @{

      /// \brief Signal set data.
      sigset_t m_signalSet;

      /// @} end of Private member variables

    };

  // ==========================================================================

  }// namespace posix
}      // namespace hal

// ============================================================================

#if !defined(__DOXYGEN__)
namespace hal
{
  namespace arch
  {
    using TimerTicksImplementation = hal::posix::TimerTicksImplementation;
  } // namespace arch
} // namespace hal
#endif // !defined(__DOXYGEN__)
// ============================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_TIMERTICKSIMPLEMENTATION_H_
