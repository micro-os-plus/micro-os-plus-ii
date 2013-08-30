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

      // TODO: set the register value to 1 (or 0?)
      
      // Configure SysTick to interrupt at the requested rate. */
      // portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
      (*((volatile unsigned long *) 0xe000e014)) = (8000000 / 1000) - 1UL;

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

      //      portNVIC_SYSTICK_CTRL_REG &= ~portNVIC_SYSTICK_ENABLE_BIT;
      (*((volatile unsigned long *) 0xe000e010)) &= ~(1UL << 0UL);
    }

    namespace InterruptHandler
    {
      void
      SystemTick(void)
      {
#if 0
        hal::cortexm::diag::SemiHosting::writeChar('#');
#else
        Cpu::setBASEPRI(configMAX_SYSCALL_INTERRUPT_PRIORITY);

        // Call the ticks timer ISR
        os::timerTicks.interruptServiceRoutine();

        Cpu::setBASEPRI(0);
#endif
      }
    } // namespace InterruptHandler

  // ========================================================================

  }// namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
