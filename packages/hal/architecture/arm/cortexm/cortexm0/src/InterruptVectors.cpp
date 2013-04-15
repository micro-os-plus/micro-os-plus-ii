//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief ARM Cortex-M0 interrupt vectors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/InterruptNumbersBase.h"

// Needed for the reference to __stack
#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      /// \ingroup arm_cm0_irq
      /// @{

      /// \name Interrupt handlers
      /// @{

      /// \brief Reset Handler.
      extern void
      Reset(void);

      /// \brief NMI Handler.
      extern void
      NMI(void);

      /// \brief Hard Fault Handler.
      extern void
      HardFault(void);

      /// \brief ServiceCall Handler.
      extern void
      ServiceCall(void);

      /// \brief PendService Handler.
      extern void
      PendService(void);

      /// \brief SystemTick Handler.
      extern void
      SystemTick(void);

      /// @} end of name Interrupt handlers

      /// @} end of ingroup arm_cm0_irq

    }// namespace InterruptHandler

    // ------------------------------------------------------------------------
  } // namespace cortexm
} // namespace hal

namespace hal
{
  namespace cortexm0
  {
    // ------------------------------------------------------------------------

    typedef hal::cortexm::interruptVector_t interruptVector_t;

    /// \ingroup arm_cm0_irq
    /// \showinitializer
    /// \brief ARM Cortex-M0/M0+ core interrupt vector array.
    ///
    /// \details
    /// These are the first interrupt vectors, common to all Cortex-M0
    /// and Cortex-M0+ devices.
    ///
    /// The table starts with the initial address of the stack,
    /// immediately followed by the address of the reset handler.
    ///
    /// Priority | Acronym | Address
    /// ---------|---------|--------
    /// - | - | 0x0000_0000
    /// -3 | Reset | 0x0000_0004
    /// -2 | NMI | 0x0000_0008
    /// -1 | HardFault | 0x0000_000C
    /// - | - |  0x0000_0010-0x0000_0028
    /// 3 | SVCall |  0x0000_002C
    /// - | - |  0x0000_0030-0x0000_0034
    /// 5 | PendSV |  0x0000_0038
    /// 6 | SystemTick |  0x0000_003C
    ///
    /// After this table each manufacturer adds specific vectors
    /// (see the manufacturer pages).
    __attribute__ ((section(".core_isr_vectors")))
    interruptVector_t interruptVectors[] =
      { //
        // Top of stack
        reinterpret_cast<interruptVector_t>(&__stack),

        // Reset Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::Reset),
        // NMI Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::NMI),
        // Hard Fault Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::HardFault),

        // Reserved
        0, 0, 0, 0, 0, 0, 0,

        // ServiceCall Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::ServiceCall),

        0, 0, // Reserved

        // PendService Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::PendService),
        // SystemTick Handler
        reinterpret_cast<interruptVector_t>(hal::cortexm::InterruptHandler::SystemTick)

      };

    // ------------------------------------------------------------------------

  } // namespace cortexm0
} // namespace hal

// ----------------------------------------------------------------------------

#include "hal/architecture/arm/cortexm/include/DefaultInterruptHandler.cpp.h"

// ----------------------------------------------------------------------------

// Unfortunately '#pragma weak' is not C++ friendly, so we need
// to manually mangle the function names.

// #pragma weak InterruptHandler::NMI = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler3NMIEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::HardFault = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler9HardFaultEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::ServiceCall = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler11ServiceCallEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PendService = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler11PendServiceEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SystemTick = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler10SystemTickEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0)
