//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F40XX array of interrupt vectors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace stm32f40xx
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f40xx_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief FPU global Handler.
      extern void
      FPUGlobal(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f40xx_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f40xx_irq
    /// \showinitializer
    /// \brief STM32F40XX specific interrupt vectors.
    __attribute__ ((section(".device_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // 81: FPU global
        reinterpret_cast<interruptVector_t>(InterruptHandler::FPUGlobal)

        // TODO: do we have to add something to boot in RAM mode
        };

    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup stm32f40xx_irq
      /// \name Interrupt handlers
      /// \brief Default interrupt handler.
      ///
      /// \details
      /// All undefined interrupt handlers are routed to this function,
      /// via weak references, and from here to the architecture Default.
      __attribute__ ((naked))
      void
      Default(void)
      {
        // jump to the os::cortexm::defaultInterruptHandler()
        asm volatile (
            " b _ZN3hal7cortexm16InterruptHandler7DefaultEv \n"
            ::
        );
      }
    } // namespace InterruptHandler

  // --------------------------------------------------------------------------

  }// namespace stm32f40xx
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::FPUGlobal = InterruptHandler::Default
#pragma weak _ZN3hal10stm32f40xx16InterruptHandler9FPUGlobalEv = _ZN3hal10stm32f40xx16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
