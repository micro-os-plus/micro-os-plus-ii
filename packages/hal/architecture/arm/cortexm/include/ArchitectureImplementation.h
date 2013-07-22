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

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyImplementationSelector.h"

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
      resetSystem(void);

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

      /// @} end of name Public member functions

      /// \headerfile ArchitectureImplementation.h "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
      /// \ingroup arm_cm
      /// \nosubgrouping
      ///
      /// \brief Cortex-M context handling.
      ///
      /// \details
      /// This class provides generic Cortex-M context handling support.
      class Context
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        Context(void) = default;

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

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

        /// \brief Save the current context on the stack.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        save(void);

        /// \brief Restore the current context from the stack.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        restore(void);

        /// @} end of name Public member functions

      };

      Context context;
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

    /// \details
    /// TBD
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::Context::save(void)
    {
      // TBD
    }

    /// \details
    /// TBD
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::Context::restore(void)
    {
      // TBD
    }

  } // namespace cortexm

  // --------------------------------------------------------------------------

  namespace arch
  {
    /// \brief Generic ArchitectureImplementation, pointing to specific one.
    typedef hal::cortexm::ArchitectureImplementation ArchitectureImplementation;
  }

// ==========================================================================

}// namspace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_ARCHITECTUREIMPLEMENTATION_H_
