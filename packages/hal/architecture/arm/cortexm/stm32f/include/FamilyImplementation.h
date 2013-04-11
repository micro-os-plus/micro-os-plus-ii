//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    /// \ingroup stm32f
    /// \headerfile FamilyImplementation.h "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementation.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F family implementation.
    class FamilyImplementation
    {
    public:
      /// \brief Deleted constructor
      FamilyImplementation() = delete;

      static void
      initialiseSystem(void);

      static void
      resetSystem(void);

    };

  }
  // --------------------------------------------------------------------------

  namespace cortexm
  {
    typedef hal::stm32f::FamilyImplementation FamilyImplementation;
  }
}

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYIMPLEMENTATION_H_
