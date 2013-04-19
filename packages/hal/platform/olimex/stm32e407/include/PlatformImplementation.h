//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-E407 declarations of the board class.

#ifndef HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_
#define HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407) || defined(__DOXYGEN__)

#include "portable/core/include/PlatformBase.h"

namespace hal
{
  namespace platform
  {
    namespace stm32e407
    {
      // ======================================================================

      /// \headerfile PlatformImplementation.h "hal/platform/olimex/stm32fe407/include/PlatformImplementation.h"
      /// \ingroup stm32fe407
      /// \nosubgrouping
      ///
      /// \brief Olimex STM32F-E407 board implementation class.
      class PlatformImplementation : public os::core::PlatformBase
      {
      public:

#if defined(DEBUG) || defined(__DOXYGEN__)
        /// \brief Put platform specific greeting on the trace device.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        putGreeting(void);
#endif

        // TODO: add more platform members, like initialiseSystem()
      };

    } // namespace stm32e407

    // ------------------------------------------------------------------------

    typedef stm32e407::PlatformImplementation PlatformImplementation;

  // ========================================================================

  }// namespace platform
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407)
#endif // HAL_PLATFORM_OLIMEX_STM32E407_PLATFORMIMPLEMENTATION_H_
