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
    /// \brief Cortex-M architecture implementation.
    class ArchitectureImplementation : public os::core::ArchitectureBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureImplementation() = default;

      /// @}

      static void
      initialiseSystem(void);

      static void
      resetSystem(void);

#if defined(DEBUG)
      /// \brief Put architecture specific greeting on the trace device.
      /// \par Returns
      static void
      putGreeting(void);
#endif
    };

    inline __attribute__((always_inline))
    void
    ArchitectureImplementation::initialiseSystem(void)
    {
      hal::cortexm::FamilyImplementation::initialiseSystem();
    }

    inline __attribute__((always_inline))
    void
    ArchitectureImplementation::resetSystem(void)
    {
      hal::cortexm::FamilyImplementation::resetSystem();
    }

  }

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    typedef hal::cortexm::ArchitectureImplementation ArchitectureImplementation;
  }
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
