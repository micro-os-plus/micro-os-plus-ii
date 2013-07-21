//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M3 interrupt numbers.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM3_INTERRUPTNUMBERS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM3_INTERRUPTNUMBERS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/InterruptNumbersBase.h"

namespace hal
{
  namespace cortexm3
  {
    // ========================================================================

    /// \headerfile InterruptNumbers.h "hal/architecture/arm/cortexm/cortexm3/include/InterruptNumbers.h"
    /// \ingroup arm_cm3_irq
    /// \nosubgrouping
    ///
    /// \brief Cortex-M3 architecture interrupt numbers.
    ///
    /// \details
    /// Interrupt numbers defined by the  Cortex-M3
    /// architecture.
    class InterruptNumber : public hal::cortexm::InterruptNumberBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      InterruptNumber(void) = delete;

      /// @} end of name Constructors/destructor

      /// \name Interrupt numbers
      /// @{

      ///  Non Maskable Interrupt
      static constexpr interruptNumber_t NonMaskableInt = -14;

      /// HardFault Interrupt
      static constexpr interruptNumber_t HardFault = -13;

      /// Memory Management Interrupt
      static constexpr interruptNumber_t MemoryManagement = -12;

      /// Bus Fault Interrupt
      static constexpr interruptNumber_t BusFault = -11;

      /// Usage Fault Interrupt
      static constexpr interruptNumber_t UsageFault = -10;

      /// SV Call Interrupt
      static constexpr interruptNumber_t ServiceCall = -5;

      /// Debug Monitor Interrupt
      static constexpr interruptNumber_t DebugMonitor = -4;

      /// Pend SV Interrupt
      static constexpr interruptNumber_t PendService = -2;

      /// System Tick Interrupt
      static constexpr interruptNumber_t SystemTick = -1;

      /// @} end of name Interrupt numbers

    };

    // ========================================================================

  } // namespace cortexm3
} // namespace hal

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3

#endif // HAL_ARCHITECTURE_ARM_CORTEXM_CORTEXM3_INTERRUPTNUMBERS_H_
