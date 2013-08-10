//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base declarations for implementations of the platform classes.

#ifndef OS_PORTABLE_CORE_PLATFORMBASE_H_
#define OS_PORTABLE_CORE_PLATFORMBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    /// \headerfile PlatformBase.h "portable/core/include/PlatformBase.h"
    /// \ingroup core_port
    /// \nosubgrouping
    ///
    /// \brief Base for all platform implementation classes.
    ///
    /// \details
    /// This class is used only to provide default architecture
    /// functionality,
    /// so that specific platform implementations need to overwrite
    /// only functions that provide additional functionality.
    class PlatformBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      PlatformBase(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Initialise the hardware.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      initialiseSystem(void);

      /// \brief Software reset the processor.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      resetSystem(void);

#if defined(DEBUG)
      /// \brief Write the platform greeting on the trace device.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      /// @} end of Public member functions

    };

    // ------------------------------------------------------------------------

    /// \details
    /// Default implementation that uses the architecture
    /// initialisations. Overwrite this
    /// with actual platform specific system initialisation code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    PlatformBase::initialiseSystem(void)
    {
      os::architecture.initialiseSystem();
    }

    /// \details
    /// Default implementation that uses the architecture
    /// reset code. Overwrite this
    /// with actual platform specific system reset code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    PlatformBase::resetSystem(void)
    {
      os::architecture.resetSystem();
    }

  // ========================================================================

  }
}

#endif // OS_PORTABLE_CORE_PLATFORMBASE_H_
