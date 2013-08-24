//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX declarations of architecture implementation.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"

#include "hal/architecture/synthetic/posix/include/ArchitectureDefinitions.h"

// Support architecture classes required by portable part
#include "hal/architecture/synthetic/posix/include/InterruptsCriticalSection.h"
#include "hal/architecture/synthetic/posix/include/ThreadContext.h"
#include "hal/architecture/synthetic/posix/include/TimerTicksImplementation.h"

#include "portable/language/cpp/include/cstdlib.h"

#include <unistd.h>

namespace hal
{
  namespace posix
  {
    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"
    /// \ingroup posix
    /// \nosubgrouping
    ///
    /// \brief Generic POSIX architecture implementation class.
    ///
    /// \details
    /// This class provides generic POSIX architecture support.
    class ArchitectureImplementation : public os::core::ArchitectureBase
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      ArchitectureImplementation(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

#if defined(DEBUG)
      /// \brief Put architecture greeting.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      static void
      yield(void);

      static void
      waitForInterrupt(void);

      /// \brief Software reset the processor.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      __attribute__((noreturn))
      resetSystem(void);

      /// \brief Busy wait microseconds.
      ///
      /// \param [in] micros     The number of microseconds to sleep.
      /// \par Returns
      ///    Nothing.
      static void
      busyWaitMicros(uint32_t micros);

      /// @} end of name Public member functions

    };

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::resetSystem(void)
    {
      ::abort();
    }

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::waitForInterrupt(void)
    {
      pause();
    }

  // ========================================================================

  }// namespace posix
}      // namespace hal

// ============================================================================

#if !defined(__DOXYGEN__)
namespace hal
{
  namespace arch
  {
    using ArchitectureImplementation = hal::posix::ArchitectureImplementation;
  } // namespace arch
} // namespace hal
#endif // !defined(__DOXYGEN__)
// ============================================================================

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
