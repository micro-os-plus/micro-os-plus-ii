//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M declarations of architecture implementation.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"

// Include architecture definitions, like various types.
#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

#include "hal/architecture/arm/cortexm/include/TimerTicksImplementation.h"
#include "hal/architecture/arm/cortexm/include/ThreadContext.h"
#include "hal/architecture/arm/cortexm/include/InterruptsCriticalSection.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementationSelector.h"

#elif defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU)

#include "hal/architecture/arm/cortexm/qemu/include/FamilyImplementation.h"

#elif defined(OS_INCLUDE_HAL_ARCHITECTURE_FAMILY_CUSTOM)

// Include one of the supported families,
// copied to the build folder by the XCDL procedure.
#include "hal/architecture/include/FamilyImplementation.h"

//    copyFiles=[
//        ('../include/FamilyImplementation.h', 'include/hal/architecture/include/FamilyImplementation.h'),
//    ],

#else

#error "missing FamilyImplementation.h"

#endif

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Cortex-M architecture implementation.
    ///
    /// \details
    /// This class provides generic Cortex-M architecture support.
    class ArchitectureImplementation : public os::core::ArchitectureBase
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureImplementation(void) = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Initialise the hardware.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      initialiseSystem(void);

      /// \brief Software reset the processor.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      __attribute__((noreturn))
      resetSystem(void);

      /// \brief Initialise the scheduler.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      initialiseScheduler(void);

#if defined(DEBUG) || defined(__DOXYGEN__)
      /// \brief Put architecture specific greeting on the trace device.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      static void
      yield(void);

      static void
      waitForInterrupt(void);

      /// \brief Busy wait microseconds.
      ///
      /// \param [in] micros     The number of microseconds to sleep.
      /// \par Returns
      ///    Nothing.
      static void
      busyWaitMicros(uint32_t micros);

      /// \brief Reset watchdog.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      resetWatchdog(void);

      /// @} end of name Public member functions

      //ThreadContext context;
    };

    // ------------------------------------------------------------------------

    /// \details
    /// Use the family implementation initialisation code.
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::initialiseSystem(void)
    {
      // Double word stack alignment
      (*((volatile unsigned long *) 0xe000ed14)) |= (1 << 9);

      hal::cortexm::FamilyImplementation::initialiseSystem();
    }

    /// \details
    /// Use the family implementation reset code.
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::resetSystem(void)
    {
      hal::cortexm::FamilyImplementation::resetSystem();
    }

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::yield(void)
    {
      // Set a PendSV to request a context switch.
      // portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
      (*((volatile unsigned long *) 0xe000ed04)) = (1UL << 28UL);

      // Barriers are normally not required but do ensure the code is completely
      // within the specified behaviour for the architecture.
      __asm volatile( " dsb     \n" );
      __asm volatile( " isb     \n" );
    }

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::waitForInterrupt(void)
    {
      __asm volatile( " wfi     \n" );
    }

  // ==========================================================================

  }// namespace cortexm

  // --------------------------------------------------------------------------

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    using ArchitectureImplementation = hal::cortexm::ArchitectureImplementation;
  }

// ============================================================================

}// namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
