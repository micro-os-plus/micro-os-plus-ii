//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_XXXXX) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace xxxxx
    {
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

#if defined(__HAS_PLATFORM_INITS)

        // Redefine, if default architecture is not enough
        static void
        initialiseSystem(void);

        // Redefine, if default architecture is not enough
        static void
        resetSystem(void);

#endif

        // TODO: add more platfrom members
      };
    }

    typedef xxxx::PlatformImplementation PlatformImplementation;
  }
}

#endif // defined(OS_INCLUDE_HAL_BOARD_XXXXX)

#endif // HAL_PLATFORM_XXXXX_PLATFORMIMPLEMENTATION_H_
