//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_PLATFORM_OLIMEX_STM32H103_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_OLIMEX_STM32H103_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace stm32h103
    {
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

        // TODO: add more platfrom members
      };
    }

    typedef stm32h103::PlatformImplementation PlatformImplementation;
  }
}

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103)

#endif // HAL_PLATFORM_OLIMEX_STM32H103_PLATFORMIMPLEMENTATION_H_
