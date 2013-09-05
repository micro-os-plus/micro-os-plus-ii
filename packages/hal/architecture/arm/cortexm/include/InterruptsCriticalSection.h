//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M interrupts critical section.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTSCRITICALSECTION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTSCRITICALSECTION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/ArchitectureBase.h"

// Include architecture definitions, like various types.
#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"


namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile InterruptsCriticalSection.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Implementation of the interrupts critical section.
    ///
    /// \details
    /// This class is used to create a critical section where the timer ticks
    /// are disabled.
    /// It uses the RAII paradigm, i.e. it blocks the signals in
    /// the constructor and restores them to the initial state in the
    /// destructor.
    ///
    /// Embedded calls are allowed, without other depth limitations other
    /// than the available stack.
    class InterruptsCriticalSection
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor
      InterruptsCriticalSection(void);

      /// \brief Destructor
      ~InterruptsCriticalSection();

      /// @} end of name Constructors/destructor

    private:
      /// \name Private member variables
      /// @{

      basepri_t m_basepri;

      /// @} end of Private member variables

    };

  // ==========================================================================

  }// namespace cortexm

  // --------------------------------------------------------------------------

  namespace arch
  {
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    using InterruptsCriticalSection = hal::cortexm::InterruptsCriticalSection;

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }

// ==========================================================================

}// namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTSCRITICALSECTION_H_
