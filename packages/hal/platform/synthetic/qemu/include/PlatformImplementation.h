//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU declarations of the synthetic platform class.

#ifndef HAL_PLATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_QEMU) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/PlatformBase.h"

namespace hal
{
  namespace qemu
  {
    // ========================================================================

    /// \headerfile PlatformImplementation.h "hal/platform/synthetic/qemu/include/PlatformImplementation.h"
    /// \ingroup osx
    /// \nosubgrouping
    ///
    /// \brief OS X platform implementation class.
    class PlatformImplementation : public hal::cortexm::PlatformBase
    {
    public:

    };
  // ==========================================================================
  }// namespace qemu

  namespace platform
  {
    // ------------------------------------------------------------------------

    using PlatformImplementation = qemu::PlatformImplementation;

  // --------------------------------------------------------------------------
  }// namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_QEMU)
#endif // HAL_PLATFORM_SYNTHETIC_QEMU_PLATFORMIMPLEMENTATION_H_
