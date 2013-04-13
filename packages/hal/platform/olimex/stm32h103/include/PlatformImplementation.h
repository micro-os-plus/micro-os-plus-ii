//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-H103 declarations of the board class.

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
      // ======================================================================

      /// \headerfile PlatformImplementation.h "hal/platform/olimex/stm32h103/include/PlatformImplementation.h"
      /// \ingroup stm32fh103
      /// \nosubgrouping
      ///
      /// \brief Olimex STM32F-H103 board implementation class.
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

        // TODO: add more platform members, like initialiseSystem()
      };
    } // namespace stm32h103

    // ------------------------------------------------------------------------

    typedef stm32h103::PlatformImplementation PlatformImplementation;

    // ========================================================================

  } // namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103)

#endif // HAL_PLATFORM_OLIMEX_STM32H103_PLATFORMIMPLEMENTATION_H_
