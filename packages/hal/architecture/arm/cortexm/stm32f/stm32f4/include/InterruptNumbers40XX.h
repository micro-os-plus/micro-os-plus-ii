//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F40XX class of sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS40XX_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS40XX_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptNumbersBase.h"

namespace hal
{
  namespace stm32f40xx
  {
    // ========================================================================

    /// \ingroup stm32f40xx_irq
    /// \headerfile InterruptNumbers40XX.h "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptNumbers40XX.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F40XX family interrupt numbers.
    ///
    /// \details
    /// The STM32F40XX family is part of the STM32F4 series, so it inherits
    /// all STM32F4 interrupt numbers and adds more specific ones.
    class InterruptNumber : public hal::stm32f4::InterruptNumberBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor
      InterruptNumber() = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      static const interruptNumber_t FPUGlobal = 81; ///< FPU global interrupt

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f40xx

  namespace cortexm
  {
    typedef hal::stm32f40xx::InterruptNumber InterruptNumber;
  }

} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS40XX_H_
