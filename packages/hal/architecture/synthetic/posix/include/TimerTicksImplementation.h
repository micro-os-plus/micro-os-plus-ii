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

namespace hal
{
  namespace posix
  {

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    // ========================================================================

    class TimerTicksImplementation
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      TimerTicksImplementation(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      static void
      initialise(void);

      static void
      start(void);

      static void
      stop(void);

      static void
      acknowledgeInterrupt(void);

      /// @} end of name Public member functions

    };

  // ==========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

  }// namespace posix
}      // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_TIMERTICKSIMPLEMENTATION_H_
