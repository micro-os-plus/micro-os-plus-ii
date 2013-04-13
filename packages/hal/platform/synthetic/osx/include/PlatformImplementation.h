//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_PLATFORM_SYNTHETIC_OSX_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_SYNTHETIC_OSX_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace osx
    {
      // ======================================================================

      /// \headerfile PlatformImplementation.h "hal/platform/synthetic/osx/include/PlatformImplementation.h"
      /// \ingroup osx
      /// \nosubgrouping
      ///
      /// \brief OS X platform implementation class.
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

        // TODO: add more platform members
      };
    } // namespace osx

    // ------------------------------------------------------------------------

    typedef osx::PlatformImplementation PlatformImplementation;

    // ========================================================================

  } // namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX)

#endif // HAL_PLATFORM_SYNTHETIC_OSX_PLATFORMIMPLEMENTATION_H_
