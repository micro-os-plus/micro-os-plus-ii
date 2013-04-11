//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

namespace hal
{
  namespace cortexm
  {
    /// \brief Cortex-M architecture implementation.
    class ArchitectureImplementation
    {
    public:
      /// \brief Deleted constructor.
      ArchitectureImplementation() = default;

#if defined(DEBUG)
      /// \brief Put architecture specific greeting on the trace device.
      /// \par Returns
      static void
      putGreeting(void);
#endif
    };
  }

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    typedef hal::cortexm::ArchitectureImplementation ArchitectureImplementation;
  }
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
