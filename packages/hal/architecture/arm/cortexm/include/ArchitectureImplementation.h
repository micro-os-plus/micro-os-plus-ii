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

//#include "portable/core/include/Stack.h"

#define OS_DEBUG_THREADCONTEXT  (1)

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

      static void
      contextSwitch(void);

      static hal::arch::stackElement_t** ms_ppStack;

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
      __asm volatile( "dsb" );
      __asm volatile( "isb" );
    }

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::waitForInterrupt(void)
    {
    }

    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Cortex-M context handling.
    ///
    /// \details
    /// This class provides generic Cortex-M context handling support.
    class ThreadContext
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Default constructor.
      ThreadContext(void);
      ~ThreadContext(void);

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

#if 0
      /// \brief Create the initial context in the stack object.
      ///
      /// \param [in] pStackTop Pointer to the last stack element.
      /// \param [in] entryPoint Pointer to thread code.
      /// \param [in] pParameters Pointer to thread parameters.
      /// \par Returns
      ///    Nothing.
      static hal::arch::stackElement_t*
      createInitial(hal::arch::stackElement_t* pStackTop,
          os::core::threadEntryPoint_t entryPoint, void* pParameters);
#endif

      /// \brief Create the initial context in the local storage.
      ///
      /// \param [in] pStackBottom    Pointer to the first stack element.
      /// \param [in] stackSizeBytes  Size of stack in bytes.
      /// \param [in] trampolineEntryPoint      Pointer to trampoline code.
      /// \param [in] p1              First parameter.
      /// \param [in] p2              Second parameter.
      /// \param [in] p3              Third parameter.
      /// \par Returns
      ///    Nothing.
      void
      create(hal::arch::stackElement_t* pStackBottom,
          hal::arch::stackSize_t stackSizeBytes,
          os::core::trampoline3_t trampolineEntryPoint, void* p1, void* p2,
          void* p3);

#if 0
      /// \brief Save the current context on the stack.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      save(void);
#endif

      /// \brief Save the current context in the local storage.
      ///
      /// \par Parameters
      ///    None.
      /// \retval true  Context saved, returns for the first time
      /// \retval false Context restored, returns for the second time
      ///    Nothing.
      bool
      save(void);

      /// \brief Restore the current context from the stack.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      restore(void);

      hal::arch::stackElement_t**
      getPPStack(void);

      /// @} end of name Public member functions

    private:

      hal::arch::stackElement_t* m_pStack;
    };

    // ------------------------------------------------------------------------

    /// \details
    /// TBD
    inline hal::arch::stackElement_t**
    __attribute__((always_inline))
    ThreadContext::getPPStack(void)
    {
      return &m_pStack;
    }

    /// \details
    /// TBD
    inline bool
    __attribute__((always_inline))
    ThreadContext::save(void)
    {
      // TBD
      return true;
    }

    /// \details
    /// TBD
    inline void
    __attribute__((always_inline))
    ThreadContext::restore(void)
    {
      // TBD
    }

    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
    /// \ingroup arm_cm
    /// \nosubgrouping
    ///
    /// \brief Implementation of the interrupts critical section.
    ///
    /// \details
    /// This class is used to create a critical section where the timer ticks
    /// are disabled.
    /// It uses the RAII paradigm, i.e. it blocks the signals in
    /// the constructor and restores them to the initial state in the
    /// destructor.
    ///
    /// Embedded calls are allowed, without other depth limitations other
    /// than the available stack.
    class InterruptsCriticalSection
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor
      InterruptsCriticalSection(void);

      /// \brief Destructor
      ~InterruptsCriticalSection();

      /// @} end of name Constructors/destructor

    private:
      /// \name Private member variables
      /// @{

      basepri_t m_basepri;

      /// @} end of Private member variables

    };

  // ==========================================================================

  }// namespace cortexm

  // --------------------------------------------------------------------------

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    using ArchitectureImplementation = hal::cortexm::ArchitectureImplementation;

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    using ThreadContext = hal::cortexm::ThreadContext;
    using TimerTicksImplementation = hal::cortexm::TimerTicksImplementation;
    using InterruptsCriticalSection = hal::cortexm::InterruptsCriticalSection;

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }

// ==========================================================================

}// namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
