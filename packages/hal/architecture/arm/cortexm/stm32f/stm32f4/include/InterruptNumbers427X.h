//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F427X class of sub-family interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS427X_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS427X_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F427X) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptNumbersBase.h"

namespace hal
{
  namespace stm32f427x
  {
    // ========================================================================

    /// \ingroup stm32f4_irq
    /// \headerfile InterruptNumbers427X.h "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptNumbers427X.h"
    /// \nosubgrouping
    ///
    /// \brief STM32F427X family interrupt numbers.
    ///
    /// \details
    /// The STM32F427X family is part of the STM32F4 series, so it inherits
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
      static const interruptNumber_t UART7Global = 82; ///< UART7 global interrupt
      static const interruptNumber_t UART8Global = 83; ///< UART8 global interrupt
      static const interruptNumber_t SPI4Global = 84; ///< SPI4 global Interrupt
      static const interruptNumber_t SPI5Global = 85; ///< SPI5 global Interrupt
      static const interruptNumber_t SPI6Global = 86; ///< SPI6 global Interrupt

      /// @} end of name Interrupt numbers

    };

  // ========================================================================

  }// namespace stm32f40xx

  namespace stm32f4
  {
    typedef hal::stm32f427x::InterruptNumber InterruptNumber;
  }

} // namespace os

#endif // OS_INCLUDE_HAL_MCU_FAMILY_STM32F427X
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_INTERRUPTNUMBERS427X_H_
