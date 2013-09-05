//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M definitions of TimerTicks implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/XCDL_SchedulerDefines.h"

#include "portable/diagnostics/include/Trace.h"

#include "hal/architecture/arm/cortexm/include/TimerTicksImplementation.h"
#include "portable/core/include/TimerTicks.h"
#include "hal/architecture/arm/cortexm/include/Cpu.h"
#include "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"
#include "portable/core/include/Scheduler.h"

//#include <sys/time.h>

namespace hal
{
  namespace cortexm
  {

    // ========================================================================

    /// \details
    TimerTicksImplementation::TimerTicksImplementation(void)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif

    }

    TimerTicksImplementation::~TimerTicksImplementation()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    void
    TimerTicksImplementation::initialise(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // Make SysTick the lowest priority interrupts (same as PendSV).
      //portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;
      (*((volatile unsigned long *) 0xe000ed20)) |=
          (((unsigned long) configKERNEL_INTERRUPT_PRIORITY) << 24UL );

      // According to 'SysTick usage hints and tips'
      // The correct initialisation sequence for the SysTick counter is:
      // 1. Program reload value.
      // 2. Clear current value.
      // 3. Program Control and Status register

      // Configure SysTick to interrupt at the requested rate. */
      // portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
#if defined(OS_INCLUDE_HAL_BOARD_OLIMEX_STM32H103)
      (*((volatile unsigned long *) 0xe000e014)) = (72000000 / 1000) - 1UL;
#else
      (*((volatile unsigned long *) 0xe000e014)) = (8000000 / 1000) - 1UL;
#endif

      // A write of any value sets the register to 0.
      (*((volatile unsigned long *) 0xe000e018)) = 1;

      // portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;
      (*((volatile unsigned long *) 0xe000e010)) = (1UL << 2UL) | (1UL << 1UL);
    }

    /// \details
    void
    TimerTicksImplementation::start(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

#if 1
      //      portNVIC_SYSTICK_CTRL_REG |=  portNVIC_SYSTICK_ENABLE_BIT;
      (*((volatile unsigned long *) 0xe000e010)) |= (1UL << 0UL);
#endif
    }

    /// \details
    void
    TimerTicksImplementation::stop(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      // portNVIC_SYSTICK_CTRL_REG &= ~portNVIC_SYSTICK_ENABLE_BIT;
      (*((volatile unsigned long *) 0xe000e010)) &= ~(1UL << 0UL);
    }

    namespace InterruptHandler
    {
      void
      SystemTick(void)
      {
#if 0
        os::diag::trace.putChar('.');
#else
        // Using setBASEPRI is cheaper than using critical sections
        // since there is no need to save the current BASEPRI (having
        // the lowest priority we know it is 0).
        Cpu::setBASEPRI(configMAX_SYSCALL_INTERRUPT_PRIORITY);

        // Call the ticks timer ISR
        os::timerTicks.interruptServiceRoutine();

#if 1
        if (os::scheduler.isPreemptionAllowed())
          {
            // Set a PendSV to request a context switch.
            // portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
            (*((volatile unsigned long *) 0xe000ed04)) = (1UL << 28UL);
          }
#endif
        Cpu::setBASEPRI(0);
#endif
      }
    } // namespace InterruptHandler

  // ========================================================================

  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
