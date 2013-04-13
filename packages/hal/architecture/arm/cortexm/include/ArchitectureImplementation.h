//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"
#include "hal/architecture/arm/cortexm/include/FamilyImplementationSelector.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Cortex-M architecture implementation.
    ///
    /// \details
    /// This class provides generic Cortex-M architecture support.
    class ArchitectureImplementation : public os::core::ArchitectureBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureImplementation() = default;

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

#if defined(DEBUG)
      /// \brief Put architecture specific greeting on the trace device.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      /// @} end of name Public member functions
    };

    // ------------------------------------------------------------------------

    /// \details
    /// Use the family implementation initialisation code.
    inline __attribute__((always_inline))
    void
    ArchitectureImplementation::initialiseSystem(void)
    {
      hal::cortexm::FamilyImplementation::initialiseSystem();
    }

    /// \details
    /// Use the family implementation reset code.
    inline __attribute__((always_inline))
    void
    ArchitectureImplementation::resetSystem(void)
    {
      hal::cortexm::FamilyImplementation::resetSystem();
    }

  } // namespace cortexm

  // --------------------------------------------------------------------------

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    typedef hal::cortexm::ArchitectureImplementation ArchitectureImplementation;
  }

  // ==========================================================================

} // namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
