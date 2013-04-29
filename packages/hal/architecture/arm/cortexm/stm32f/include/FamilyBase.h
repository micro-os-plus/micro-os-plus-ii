//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F declarations of family base class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

namespace hal
{
  namespace stm32f
  {
    // ------------------------------------------------------------------------

    /// \ingroup stm32f
    /// \headerfile FamilyBase.h "hal/architecture/arm/cortexm/stm32f/include/FamilyBase.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F family base.
    class FamilyBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      FamilyBase() = delete;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Initialise the hardware.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      initialiseSystem(void);

      /// \brief Software reset the processor.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      resetSystem(void);

#if defined(DEBUG) || defined(__DOXYGEN__)
      /// \brief Put family specific greeting on the trace device.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      /// @} end of Public member functions

    };

  // ==========================================================================
  }// namespace stm32f
}// namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYBASE_H_
