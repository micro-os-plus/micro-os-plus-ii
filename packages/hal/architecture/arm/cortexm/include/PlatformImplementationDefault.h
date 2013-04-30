//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Default declarations for the platform implementation.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_

#include "portable/core/include/ConfigDefines.h"

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile PlatformImplementationDefault.h "hal/architecture/arm/cortexm/include/PlatformImplementationDefault.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Default platform implementation class.
    ///
    /// \details
    /// For boards that do not have special requirements, copy this
    /// file to the build folder as PlatformImplementation.h.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

      // TODO: add more platform members, like initialiseSystem()
    };

  // ==========================================================================
  }// namespace cortexm

  namespace platform
  {
    // ------------------------------------------------------------------------

    typedef cortexm::PlatformImplementation PlatformImplementation;

  // --------------------------------------------------------------------------
  }// namespace platform
} // namespace hal

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT_H_
