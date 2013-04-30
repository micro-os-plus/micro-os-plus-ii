//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Base declarations for Cortex-M platform classes.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"
#include "hal/architecture/include/FamilyImplementation.h"
#include "portable/core/include/XCDL_GreetingDefines.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile PlatformBase.h "hal/architecture/arm/cortexm/include/PlatformBase.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Base for all Cortex-M platform implementation classes.
    ///
    /// \details
    /// This class is used only to provide default architecture
    /// functionality,
    /// so that specific platform implementations need to overwrite
    /// only functions that provide additional functionality.
    class PlatformBase : public os::core::PlatformBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      PlatformBase() = default;

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

      /// @} end of Public member functions

    };

#if defined(DEBUG) || defined(__DOXYGEN__)

    /// \details
    /// Display the platform greeting lines (if available)
    /// and call the family function.
    inline __attribute__((always_inline))
    void
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
      hal::cortexm::FamilyImplementation::putGreeting();
    }

#endif

  // ==========================================================================

  }// namespace cortexm
} // namespace hal

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMBASE_H_
