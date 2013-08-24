//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX declarations of interrupt critical sections.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_INTERRUPTSCRITICALSECTION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_INTERRUPTSCRITICALSECTION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include <signal.h>

namespace hal
{
  namespace posix
  {

    // ========================================================================

    /// \headerfile InterruptsCriticalSection.h "hal/architecture/synthetic/posix/include/InterruptsCriticalSection.h"
    /// \ingroup posix
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

      /// \brief Storage for the signal status
      sigset_t m_status;

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
    using InterruptsCriticalSection = hal::posix::InterruptsCriticalSection;
  } // namespace arch
} // namespace hal
#endif // !defined(__DOXYGEN__)
// ============================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_INTERRUPTSCRITICALSECTION_H_
