//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F40XX interrupt vectors.
///
/// \details
/// These is the STM32F40XX specific part of the interrupt vectors table,
/// and is allocated by the linker after family and architecture vectors.
///
/// The `interruptVectors` array contains pointers to the interrupt handlers.
/// By default,
/// uninitialised pointers are filled in with the address of the local
/// `Default()` handler, defined as an weak alias.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

// Since weak references can point only to symbols defined in the
// same compilation unit, we bring all pieces that form the
// interrupt vectors together here.
// The order should not be a problem, since each piece goes to a specific
// linker section.
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/include/InterruptVectors.cpp.h"

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

      /// \brief FPU Global Handler.
      extern void
      FPUGlobal(void);

    /// @} end of name Interrupt handlers

    /// @} end of ingroup stm32f40xx_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    // ------------------------------------------------------------------------

    /// \ingroup stm32f40xx_irq
    /// \brief STM32F40XX specific interrupt vectors.
    /// \showinitializer
    __attribute__ ((section(".device_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // 81: FPU Global
        reinterpret_cast<interruptVector_t>(InterruptHandler::FPUGlobal)

        };

    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \name Interrupt handlers
      /// @} end of name Interrupt handlers

      /// \ingroup stm32f40xx_irq
      /// \brief Default interrupt handler.
      ///
      /// \details
      /// All undefined interrupt handlers are routed to this function,
      /// via weak references, and from here to the architecture Default().
      /// This additional indirection is required since weak references
      /// can point only to symbols defined in the same compilation unit.
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

    /// @} end of name Interrupt handlers

    }// namespace InterruptHandler

  // --------------------------------------------------------------------------

  }// namespace stm32f40xx
} // namespace hal

// ----------------------------------------------------------------------------

// #pragma weak InterruptHandler::FPUGlobal = InterruptHandler::Default
#pragma weak _ZN3hal10stm32f40xx16InterruptHandler9FPUGlobalEv = _ZN3hal10stm32f40xx16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX)
