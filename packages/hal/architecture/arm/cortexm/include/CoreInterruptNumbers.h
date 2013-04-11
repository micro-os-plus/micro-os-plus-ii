//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_COREINTERRUPTNUMBERS_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_COREINTERRUPTNUMBERS_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

namespace hal
{
  namespace cortexm
  {

    /// \ingroup arm_cm
    /// @{

    /// \headerfile CoreInterruptNumbers.h "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M architecture interrupt numbers base
    ///
    /// \details
    /// Common definitions for all Cortex-M architectures.
    class CoreInterruptNumberBase
    {
    public:

      /// \brief Type of an interrupt number (a signed integer).
      typedef int interruptNumber_t;

      /// \brief Deleted constructor
      CoreInterruptNumberBase() = delete;
    };

    /// \headerfile CoreInterruptNumbers.h "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M0 architecture interrupt numbers
    ///
    /// \details
    /// Interrupt numbers defined by the Cortex-M0
    /// light architecture.
    class CortexM0InterruptNumber : public CoreInterruptNumberBase
    {
    public:
      /// \brief Deleted constructor
      CortexM0InterruptNumber() = delete;

      /// \name Interrupt numbers
      /// @{

      ///  Non Maskable Interrupt
      static const interruptNumber_t NonMaskableInt = -14;

      /// HardFault Interrupt
      static const interruptNumber_t HardFault = -13;

      /// SV Call Interrupt
      static const interruptNumber_t SVCall = -5;

      /// Pend SV Interrupt
      static const interruptNumber_t PendSV = -2;

      /// System Tick Interrupt
      static const interruptNumber_t SysTick = -1;

      /// @} end of name Interrupt numbers

    };

    /// \headerfile CoreInterruptNumbers.h "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M0+ architecture interrupt numbers
    ///
    /// \details
    /// Interrupt numbers defined by the Cortex-M0+
    /// light architecture (same as those of Cortex-M0).
    class CortexM0plusInterruptNumber : public CortexM0InterruptNumber
    {
    public:
      /// \brief Deleted constructor
      CortexM0plusInterruptNumber() = delete;

    };

    /// \headerfile CoreInterruptNumbers.h "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M3 architecture interrupt numbers
    ///
    /// \details
    /// Interrupt numbers defined by the  Cortex-M3
    /// architecture.
    class CortexM3InterruptNumber : public CoreInterruptNumberBase
    {
    public:
      /// \brief Deleted constructor
      CortexM3InterruptNumber() = delete;

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
      static const interruptNumber_t SVCall = -5;

      /// Debug Monitor Interrupt
      static const interruptNumber_t DebugMonitor = -4;

      /// Pend SV Interrupt
      static const interruptNumber_t PendSV = -2;

      /// System Tick Interrupt
      static const interruptNumber_t SysTick = -1;

      /// @} end of name Interrupt numbers

    };

    /// \headerfile CoreInterruptNumbers.h "hal/architecture/arm/cortexm/include/CoreInterruptNumbers.h"
    /// \nosubgrouping
    ///
    /// \brief ARM Cortex-M4 architecture interrupt numbers
    ///
    /// \details
    /// Interrupt numbers defined by the Cortex-M4
    /// architecture (same as those of Cortex-M3).
    class CortexM4InterruptNumber : public CortexM3InterruptNumber
    {
    public:
      /// \brief Deleted constructor
      CortexM4InterruptNumber() = delete;

    };

  /// @} end of ingroup arm_cm

  }
}

#endif // OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_COREINTERRUPTNUMBERS_H_
