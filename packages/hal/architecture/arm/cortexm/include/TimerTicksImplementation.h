//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M declarations of TimerTicks implementation.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_TIMERTICKSIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_TIMERTICKSIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

namespace hal
{
  namespace cortexm
  {
    namespace timer
    {

    }// namespace timer

    // ========================================================================

    /// \class TimerTicksImplementation TimerTicksImplementation.h "hal/architecture/arm/cortexm/include/Thread.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Implementation of the ticks timer.
    ///
    /// \details
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

      /// @} end of Private member variables

    };

    /// \details
    /// Not needed, SysTick can be configured to re-trigger automatically,
    /// without program intervention.
    inline void
    __attribute__((always_inline))
    TimerTicksImplementation::acknowledgeInterrupt(void)
    {
    }

  // ==========================================================================

  }// namespace cortexm
}      // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_TIMERTICKSIMPLEMENTATION_H_
