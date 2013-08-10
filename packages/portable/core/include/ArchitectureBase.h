//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base declarations for implementations of the architecture classes.

#ifndef OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
#define OS_PORTABLE_CORE_ARCHITECTUREBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include <stdint.h>

namespace os
{
  namespace core
  {
    // Common definitions for all architectures

    typedef void
    (*threadEntryPoint0_t)(void);

    typedef void
    (*threadEntryPoint1_t)(void*);

    typedef void
    (*trampoline3_t)(void*, void*, void*);

    // ========================================================================

    /// \headerfile ArchitectureBase.h "portable/core/include/ArchitectureBase.h"
    /// \ingroup core_port
    /// \nosubgrouping
    ///
    /// \brief Base for all architecture implementation classes.
    ///
    /// \details
    /// This class is used only to provide default empty functions,
    /// so that specific architecture implementations need to overwrite
    /// only functions that provide functionality.
    class ArchitectureBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureBase(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public static functions
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
      __attribute__((noreturn))
      resetSystem(void);

      /// \brief Put architecture greeting.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);

      /// \brief Reset watchdog.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      resetWatchdog(void);

      /// \brief Busy wait microseconds.
      ///
      /// \param [in] micros     The number of microseconds to sleep.
      /// \par Returns
      ///    Nothing.
      static void
      busyWaitMicros(uint32_t micros);

      /// @} end of Public member functions

    };

    // ------------------------------------------------------------------------

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific system initialisation code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::initialiseSystem(void)
    {
    }

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Winvalid-noreturn"
#endif

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific system reset code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::resetSystem(void)
    {
    }

#pragma GCC diagnostic pop

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::putGreeting(void)
    {
    }

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::resetWatchdog(void)
    {
    }

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::busyWaitMicros(uint32_t micros __attribute__((unused)))
    {
    }

  // ========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
