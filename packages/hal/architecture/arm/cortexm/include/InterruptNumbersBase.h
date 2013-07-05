//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M base for all architecture interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTNUMBERSBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTNUMBERSBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \ingroup arm_cm_irq
    /// @{

    /// \headerfile InterruptNumbersBase.h "hal/architecture/arm/cortexm/include/InterruptNumbersBase.h"
    /// \nosubgrouping
    ///
    /// \brief Cortex-M architecture interrupt numbers base.
    ///
    /// \details
    /// Common definitions for all Cortex-M architectures.
    class InterruptNumberBase
    {
    public:

      /// \brief Type of an interrupt number (a signed integer).
      typedef hal::cortexm::interruptNumber_t interruptNumber_t;

      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      InterruptNumberBase(void) = delete;

      /// @} end of name Constructors/destructor
    };

  /// @} end of ingroup arm_cm

    // ========================================================================

  } // namespace cortexm
} // namespace hal

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_INTERRUPTNUMBERSBASE_H_
