//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX default platform declarations.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_PLATFORMIMPLEMENTATIONDEFAULT_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_PLATFORMIMPLEMENTATIONDEFAULT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"
#include "portable/core/include/XCDL_GreetingDefines.h"

#include "portable/diagnostics/include/Trace.h"

namespace hal
{
  namespace posix
  {
    // ========================================================================

    /// \headerfile PlatformImplementationDefault.h "hal/architecture/synthetic/posix/include/PlatformImplementationDefault.h"
    /// \ingroup posix
    /// \nosubgrouping
    ///
    /// \brief Default for all POSIX platform implementations.
    ///
    /// \details
    /// This class is used only to provide default platform
    /// functionality,
    /// so that specific platform implementations need to overwrite
    /// only functions that provide additional functionality.
    class PlatformImplementationDefault : public os::core::PlatformBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      PlatformImplementationDefault(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

#if defined(DEBUG) || defined(__DOXYGEN__)
      /// \brief Write the platform greeting on the trace device.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      /// \brief Pass the main() return code to the calling environment.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      exit(void);

      /// @} end of Public member functions

    };

    /// \details
    /// Default empty implementation. Overwrite this
    /// with actual platform specific exit code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    PlatformImplementationDefault::exit(void)
    {
      // This must be empty for POSIX, since the process exits
      // orderly by itself, and EarlyInitialisation destructors
      // should not interfere with this.
    }

  // ==========================================================================

  }// namespace posix
} // namespace hal

#if !defined(__DOXYGEN__)
namespace hal
{
  namespace platform
  {
     using PlatformImplementation = hal::posix::PlatformImplementationDefault;
  }// namespace platform
} // namespace hal
#endif // !defined(__DOXYGEN__)

#endif // OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_PLATFORMIMPLEMENTATIONDEFAULT_H_
