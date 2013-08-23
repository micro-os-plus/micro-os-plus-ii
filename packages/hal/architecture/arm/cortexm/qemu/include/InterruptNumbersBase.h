//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_INTERRUPTNUMBERSBASE_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_INTERRUPTNUMBERSBASE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/cortexm3/include/InterruptNumbers.h"

namespace hal
{
  namespace qemu
  {
    // ========================================================================

    /// \ingroup qemu
    /// \headerfile InterruptNumbersBase.h "hal/architecture/arm/cortexm/stm32f/stm32f1/include/InterruptNumbersBase.h"
    /// \nosubgrouping
    ///
    /// \brief QEMU family interrupt numbers.
    ///
    /// \details
    /// The QEMU family is based on Cortex-M3, so it inherits
    /// all Cortex-M3 interrupt numbers.
    class InterruptNumber : public hal::cortexm3::InterruptNumber
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumber(void) = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{


      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace qemu
} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_QEMU
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_INTERRUPTNUMBERSBASE_H_
