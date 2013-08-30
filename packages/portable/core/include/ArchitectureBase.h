//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base declarations for implementations of the architecture classes.

#ifndef OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
#define OS_PORTABLE_CORE_ARCHITECTUREBASE_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/cstdint.h"

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

      /// \brief Initialise the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      initialiseScheduler(void);

#if defined(DEBUG) || defined(__DOXYGEN__)

      /// \brief Put architecture greeting.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);

#endif // defined(DEBUG)

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

      /// \brief Check if in interrupt context.
      ///
      /// \par Parameters
      ///    None.
      /// \retval true          Running in interrupt context.
      /// \retval false         Otherwise.
      static bool
      isInterruptContext(void);

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
    ///
    /// \note If the platform calls this, then
    /// be sure this does not remain empty, but performs the
    /// actual reset code, since it is also called from abort().
    inline void
    __attribute__((always_inline))
    __attribute__((noreturn))
    ArchitectureBase::resetSystem(void)
    {
    }

    /// \details
    /// Empty inline function, so no code is generated. Overwrite this
    /// with actual architecture specific system reset code.
    inline void
    __attribute__((always_inline))
    ArchitectureBase::initialiseScheduler(void)
    {
    }

#pragma GCC diagnostic pop


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

    inline bool
    __attribute__((always_inline))
    ArchitectureBase::isInterruptContext(void)
    {
      return false;
    }

  // ========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_ARCHITECTUREBASE_H_
