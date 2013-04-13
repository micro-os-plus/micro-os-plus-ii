//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM4_INTERRUPTNUMBERS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM4_INTERRUPTNUMBERS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/InterruptNumbersBase.h"

namespace hal
{
  namespace cortexm4
  {
    // ========================================================================

    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/cortexm4/include/InterruptNumbers.h"
    /// \ingroup arm_cm4_irq
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M4 architecture interrupt numbers.
    ///
    /// \details
    /// Interrupt numbers defined by the  Cortex-M4
    /// architecture.
    class InterruptNumber : public hal::cortexm::InterruptNumberBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      InterruptNumber() = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      ///  Non Maskable Interrupt
      static const interruptNumber_t NonMaskableInt = -14;

      /// HardFault Interrupt
      static const interruptNumber_t HardFault = -13;

      /// Memory Management Interrupt
      static const interruptNumber_t MemoryManagement = -12;

      /// Bus Fault Interrupt
      static const interruptNumber_t BusFault = -11;

      /// Usage Fault Interrupt
      static const interruptNumber_t UsageFault = -10;

      /// SV Call Interrupt
      static const interruptNumber_t ServiceCall = -5;

      /// Debug Monitor Interrupt
      static const interruptNumber_t DebugMonitor = -4;

      /// Pend SV Interrupt
      static const interruptNumber_t PendService = -2;

      /// System Tick Interrupt
      static const interruptNumber_t SystemTick = -1;

      /// @} end of name Interrupt numbers

    };

  } // namespace cortexm4
} // namespace hal

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM4_INTERRUPTNUMBERS_H_
