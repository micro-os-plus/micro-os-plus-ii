//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base declarations for generic platform classes.

#ifndef OS_PORTABLE_CORE_PLATFORMBASE_H_
#define OS_PORTABLE_CORE_PLATFORMBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/core/include/Architecture.h"

extern "C" int
main(...);

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

      /// \brief Default constructor.
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

      /// \brief Pass the main() return code to the calling environment.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      exit(void);

      /// \brief Abort execution.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      abort(void);

      /// \brief Execute the main() function.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      executeMain(void);

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
    ///
    /// \note Be sure this does not remain empty, but performs the
    /// actual reset code, since it is also called from abort().
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    PlatformBase::resetSystem(void)
    {
      os::architecture.resetSystem();
    }

    /// \details
    /// Default implementation that uses the architecture
    /// reset code. Overwrite this
    /// with actual platform specific system reset code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    PlatformBase::exit(void)
    {
      os::architecture.resetSystem();
    }

    /// \details
    /// Default implementation that uses the architecture
    /// abort code. Overwrite this
    /// with actual platform specific system reset code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    PlatformBase::abort(void)
    {
#if defined(DEBUG)
      // When debugging, an aborted program will hang,
      // for the problem to be seen.
      for (;;)
        ;
#else
      os::architecture.resetSystem();
#endif
    }

    /// \details
    /// Default implementation that uses the architecture
    /// initialisations. Overwrite this
    /// with actual platform specific system initialisation code,
    /// if the platform requires more specific functionality.
    inline void
    __attribute__((always_inline))
    PlatformBase::executeMain(void)
    {
      main(0, &"");
    }

#if defined(DEBUG) || defined(__DOXYGEN__)

    /// \details
    /// Display the XCDL defined platform greeting lines (if available)
    /// and then call the architecture function.
    inline void
    __attribute__((always_inline))
    PlatformBase::putGreeting(void)
    {
#if defined(OS_STRING_PLATFORM_GREETING_FIRST)
      os::diag::trace.putString(OS_STRING_PLATFORM_GREETING_FIRST);
      os::diag::trace.putNewLine();
#endif
#if defined(OS_STRING_PLATFORM_GREETING_SECOND)
      os::diag::trace.putString(OS_STRING_PLATFORM_GREETING_SECOND);
      os::diag::trace.putNewLine();
#endif

      // Output the architecture specific greetings.
      os::architecture.putGreeting();
    }

#endif // defined(DEBUG)
  // ==========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_PLATFORMBASE_H_
