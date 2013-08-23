//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU declarations of family implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_FAMILYIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_FAMILYIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU) || defined(__DOXYGEN__)

namespace hal
{
  namespace qemu
  {
    // ------------------------------------------------------------------------

    /// \ingroup qemu
    /// \headerfile FamilyImplementation.h "hal/architecture/arm/cortexm/qemu/include/FamilyImplementation.h"
    /// \nosubgrouping
    ///
    /// \brief QEMU family implementation.
    ///
    /// \details
    /// ???
    class FamilyImplementation
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      FamilyImplementation(void) = delete;

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
      __attribute__((noreturn))
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

  } // namespace qemu

  // --------------------------------------------------------------------------

  namespace cortexm
  {
    using FamilyImplementation = hal::qemu::FamilyImplementation ;
  }

  // ==========================================================================
}

#endif // OS_INCLUDE_HAL_MCU_FAMILY_QEMU
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_FAMILYIMPLEMENTATION_H_
