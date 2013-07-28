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
    ///
    /// \details
    /// This class can be used as base class for all specific family
    /// implementations.
    /// It provides not much functionality, it is given more as a sample
    /// on how to look the derived class, that must overwrite these
    /// member functions.

    class FamilyBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      FamilyBase(void) = delete;

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
      /// \brief Output family specific greetings on the trace device.
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


    /// \details
    /// Place holder for the generic STM32F initialisation code.
    /// Overwrite it for each family with the actual code.
    inline void
    __attribute__((always_inline))
    FamilyBase::initialiseSystem(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Missing initialiseSystem()");
      os::diag::trace.putNewLine();
#endif
    }

    /// \details
    /// Place holder for the generic STM32F reset code.
    /// Overwrite it for each family with the actual code.
    inline void
    __attribute__((always_inline))
    FamilyBase::resetSystem(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString("Missing resetSystem()");
      os::diag::trace.putNewLine();
#endif
    }

#if defined(DEBUG) || defined(__DOXYGEN__)
    /// \details
    /// Place holder for the family greeting code.
    /// Overwrite it for each family with the actual code.
    inline void
    __attribute__((always_inline))
    FamilyBase::putGreeting(void)
    {
      os::diag::trace.putString("STM32F Cortex-M");
      os::diag::trace.putNewLine();
    }
#endif

  // ==========================================================================
  }// namespace stm32f
}// namespace hal

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_FAMILYBASE_H_
