//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

// Needed for the reference to __stack
#include "../ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    namespace InterruptHandler
    {
      extern void
      Reset(void);

      extern void
      NMI(void);

      extern void
      HardFault(void);

      extern void
      SVC(void);

      extern void
      PendSV(void);

      extern void
      SysTick(void);
    }

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0P)

    // ------------------------------------------------------------------------
    /// \brief ARM Cortex-M0/M0+ Core Interrupt vectors
    __attribute__ ((section(".core_isr_vectors")))
    interruptVector_t coreInterruptVectors[] =
      { //
        // Top of stack
        reinterpret_cast<interruptVector_t>(&__stack),

        // Reset Handler
        reinterpret_cast<interruptVector_t>(Reset_Handler),
        // NMI Handler
        reinterpret_cast<interruptVector_t>(NMI_Handler),
        // Hard Fault Handler
        reinterpret_cast<interruptVector_t>(HardFault_Handler),

        // Reserved
        0,
        // Reserved
        0,
        // Reserved
        0,
        // Reserved
        0,
        // Reserved
        0,
        // Reserved
        0,
        // Reserved
        0,

        // SVCall Handler
        reinterpret_cast<interruptVector_t>(SVC_Handler),

        0,// Reserved
        // Reserved
        0,

        // PendSV Handler
        reinterpret_cast<interruptVector_t>(PendSV_Handler),
        // SysTick Handler
        reinterpret_cast<interruptVector_t>(SysTick_Handler)

      };
    // ------------------------------------------------------------------------

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)

    namespace InterruptHandler
    {
      extern void
      MemManage(void);

      extern void
      BusFault(void);

      extern void
      UsageFault(void);

      extern void
      DebugMon(void);
    }

    // ------------------------------------------------------------------------
    /// \brief ARM Cortex-M3/M4 Core Interrupt vectors
    __attribute__ ((section(".core_isr_vectors")))
    interruptVector_t coreInterruptVectors[] =
      { //
        // Top of stack
        reinterpret_cast<interruptVector_t>(&__stack),

        // Reset Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::Reset),
            // NMI Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::NMI),
            // Hard Fault Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::HardFault),

            // MPU Fault Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::MemManage),
            // Bus Fault Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::BusFault),
            // Usage Fault Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::UsageFault),

            // Reserved
            0,
            // Reserved
            0,
            // Reserved
            0,
            // Reserved
            0,

            // SVCall Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::SVC),

            // Debug Monitor Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::DebugMon),

            // Reserved
            0,

            // PendSV Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::PendSV),
            // SysTick Handler
            reinterpret_cast<interruptVector_t>(InterruptHandler::SysTick)

        };

    // ------------------------------------------------------------------------

#else
#error "Unsupported ARM Cortex-M architecture"
#endif

    namespace InterruptHandler
    {

      /// \brief Default interrupt handler
      void
      Default(void)
      {
#if defined(DEBUG)

        os::diag::trace.putNewLine();
        os::diag::trace.putString(__PRETTY_FUNCTION__);
        os::diag::trace.putNewLine();

        for (;;)
          ;
#else
        // soft reset
        os::platform.resetSystem();
#endif
      }

    } // namespace InterruptHandler

  // --------------------------------------------------------------------------
  // Unfortunately '#pragma weak' is not C++ friendly, so we need
  // to manually mangle the function names.

// #pragma weak InterruptHandler::NMI = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler3NMIEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::HardFault = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler9HardFaultEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SVC = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler3SVCEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::PendSV = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler6PendSVEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::SysTick = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler7SysTickEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

  // --------------------------------------------------------------------------

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)

// #pragma weak InterruptHandler::MemManage = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler9MemManageEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::BusFault = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler8BusFaultEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::UsageFaultr = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler10UsageFaultEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

// #pragma weak InterruptHandler::DebugMon = InterruptHandler::Default
#pragma weak _ZN3hal7cortexm16InterruptHandler8DebugMonEv = _ZN3hal7cortexm16InterruptHandler7DefaultEv

#endif

  // --------------------------------------------------------------------------

  }
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
