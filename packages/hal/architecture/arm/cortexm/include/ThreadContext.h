//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M declarations of thread context.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_THREADCONTEXT_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_THREADCONTEXT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"
#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    /// \headerfile ThreadContext.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
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
#endif

      hal::arch::stackElement_t**
      getPPStack(void);

      static void
      prepareSwitch(void);

      static hal::arch::stackElement_t** ms_ppStack;

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

#if 0
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
#endif

  // ==========================================================================

}// namespace cortexm
}// namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

// ============================================================================

namespace hal
{
  namespace arch
  {
    using ThreadContext = hal::cortexm::ThreadContext;
  } // namespace arch
}// namspace hal

// ============================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_THREADCONTEXT_H_
