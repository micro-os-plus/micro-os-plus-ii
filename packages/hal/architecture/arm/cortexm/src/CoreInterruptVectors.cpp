//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

// Needed for the reference to __stack
#include "../ldscripts/LinkerScript.h"

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {
      // ----------------------------------------------------------------------

      extern void
      Reset_Handler(void);
      extern void
      NMI_Handler(void);
      extern void
      HardFault_Handler(void);
      extern void
      SVC_Handler(void);
      extern void
      PendSV_Handler(void);
      extern void
      SysTick_Handler(void);

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0P)

      // ----------------------------------------------------------------------
      /// \brief ARM Cortex-M0/M0+ Core Interrupt vectors
      __attribute__ ((section(".core_isr_vector")))
      InterruptVector_t coreInterruptVectors[] =
        { //
          // Top of stack
          reinterpret_cast<InterruptVector_t>(&__stack),

          // Reset Handler
              reinterpret_cast<InterruptVector_t>(Reset_Handler),
              // NMI Handler
              reinterpret_cast<InterruptVector_t>(NMI_Handler),
              // Hard Fault Handler
              reinterpret_cast<InterruptVector_t>(HardFault_Handler),

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
              reinterpret_cast<InterruptVector_t>(SVC_Handler),

              0, // Reserved
              // Reserved
              0,

              // PendSV Handler
              reinterpret_cast<InterruptVector_t>(PendSV_Handler),
              // SysTick Handler
              reinterpret_cast<InterruptVector_t>(SysTick_Handler)

          };
      // ----------------------------------------------------------------------

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)

      extern void
      MemManage_Handler(void);
      extern void
      BusFault_Handler(void);
      extern void
      UsageFault_Handler(void);
      extern void
      DebugMon_Handler(void);

      // ----------------------------------------------------------------------
      /// \brief ARM Cortex-M3/M4 Core Interrupt vectors
      __attribute__ ((section(".core_isr_vector")))
      InterruptVector_t coreInterruptVectors[] =
        { //
          // Top of stack
          reinterpret_cast<InterruptVector_t>(&__stack),

          // Reset Handler
              reinterpret_cast<InterruptVector_t>(Reset_Handler),
              // NMI Handler
              reinterpret_cast<InterruptVector_t>(NMI_Handler),
              // Hard Fault Handler
              reinterpret_cast<InterruptVector_t>(HardFault_Handler),

              // MPU Fault Handler
              reinterpret_cast<InterruptVector_t>(MemManage_Handler),
              // Bus Fault Handler
              reinterpret_cast<InterruptVector_t>(BusFault_Handler),
              // Usage Fault Handler
              reinterpret_cast<InterruptVector_t>(UsageFault_Handler),

              // Reserved
              0,
              // Reserved
              0,
              // Reserved
              0,
              // Reserved
              0,

              // SVCall Handler
              reinterpret_cast<InterruptVector_t>(SVC_Handler),

              // Debug Monitor Handler
              reinterpret_cast<InterruptVector_t>(DebugMon_Handler),

              // Reserved
              0,

              // PendSV Handler
              reinterpret_cast<InterruptVector_t>(PendSV_Handler),
              // SysTick Handler
              reinterpret_cast<InterruptVector_t>(SysTick_Handler)

          };

      // ----------------------------------------------------------------------

#else
#error "Unsupported ARM Cortex-M architecture"
#endif

      /// \brief Default interrupt handler
      void
      defaultInterruptHandler(void)
      {
#if defined(DEBUG)
        for (;;)
          ;
#else
        // TODO: soft reset
#endif
      }

      void
      NMI_Handler(void)
      {
      }

      void
      HardFault_Handler(void)
      {
      }

      void
      SVC_Handler(void)
      {
      }

      void
      PendSV_Handler(void)
      {
      }

      void
      SysTick_Handler(void)
      {
      }

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)

// Unfortunately '#pragma weak' is not C++ friendly, so we need
// to manually mangle the function names.

// #pragma weak MemManage_Handler = defaultInterruptHandler
#pragma weak _ZN3hal4arch7cortexm17MemManage_HandlerEv = _ZN3hal4arch7cortexm23defaultInterruptHandlerEv

// #pragma weak BusFault_Handler = defaultInterruptHandler
#pragma weak _ZN3hal4arch7cortexm16BusFault_HandlerEv = _ZN3hal4arch7cortexm23defaultInterruptHandlerEv

// #pragma weak UsageFault_Handler = defaultInterruptHandler
#pragma weak _ZN3hal4arch7cortexm18UsageFault_HandlerEv = _ZN3hal4arch7cortexm23defaultInterruptHandlerEv

// #pragma weak DebugMon_Handler = defaultInterruptHandler
#pragma weak _ZN3hal4arch7cortexm16DebugMon_HandlerEv = _ZN3hal4arch7cortexm23defaultInterruptHandlerEv

#endif

    // ------------------------------------------------------------------------

    }
  }
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
