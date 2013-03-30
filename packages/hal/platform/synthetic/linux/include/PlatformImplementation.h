//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_LINUX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace linux
    {
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

        // TODO: add more platfrom members
      };
    }

    typedef linux::PlatformImplementation PlatformImplementation_t;
  }
}

#endif // defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX)

#endif // HAL_PLATFORM_SYNTHETIC_LINUX_PLATFORMIMPLEMENTATION_H_
