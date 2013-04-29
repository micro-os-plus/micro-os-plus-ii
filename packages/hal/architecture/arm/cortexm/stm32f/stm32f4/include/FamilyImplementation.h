//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 declarations of family implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_FAMILYIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_FAMILYIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyBase.h"

namespace hal
{
  namespace stm32f4
  {
    // ------------------------------------------------------------------------

    /// \ingroup stm32f4
    /// \headerfile FamilyImplementation.h "hal/architecture/arm/cortexm/stm32f4/include/FamilyImplementation.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F4 family implementation.
    class FamilyImplementation
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      FamilyImplementation() = delete;

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

  } // namespace stm32f4

  // --------------------------------------------------------------------------

  namespace cortexm
  {
    typedef hal::stm32f4::FamilyImplementation FamilyImplementation;
  }

  // ==========================================================================
}

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F4
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_FAMILYIMPLEMENTATION_H_
