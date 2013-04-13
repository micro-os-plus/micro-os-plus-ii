//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief GNU/Linux declarations of the synthetic platform class.

#ifndef HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_LINUX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace linux
    {
      // ======================================================================

      /// \headerfile PlatformImplementation.h "hal/platform/synthetic/linux/include/PlatformImplementation.h"
      /// \ingroup linux
      /// \nosubgrouping
      ///
      /// \brief GNU/Linux platform implementation class.
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

        // TODO: add more platform members
      };
    } // namespace linux

    // ------------------------------------------------------------------------

    typedef linux::PlatformImplementation PlatformImplementation;

    // ========================================================================

  } // namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX)

#endif // HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_
