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

#include <signal.h>

namespace hal
{
  namespace posix
  {

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    namespace timer
    {
      //static const int SIGNAL_NUMBER = SIGVTALRM;
      static const int SIGNAL_NUMBER = SIGALRM;

    } // namespace timer

    // ========================================================================

    class TimerTicksImplementation
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      TimerTicksImplementation(void);

      ~TimerTicksImplementation();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      void
      initialise(void);

      void
      start(void);

      void
      stop(void);

      void
      acknowledgeInterrupt(void);

      /// @} end of name Public member functions

    private:

      sigset_t m_signalSet;


      static void
      signalHandler(int signalNumber);
    };

  // ==========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }// namespace posix
}      // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_TIMERTICKSIMPLEMENTATION_H_
