//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX declarations of architecture implementation.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"

// Include architecture definitions, like various types.
#include "hal/architecture/synthetic/posix/include/ArchitectureDefinitions.h"

namespace hal
{
  namespace posix
  {
    // ======================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"
    /// \ingroup posix
    /// \nosubgrouping
    ///
    /// \brief Generic POSIX architecture implementation class.
    ///
    /// \details
    /// This class provides generic POSIX architecture support.
    class ArchitectureImplementation : public os::core::ArchitectureBase
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Deleted constructor.
      ArchitectureImplementation() = default;

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

#if defined(DEBUG)
      /// \brief Put architecture greeting.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      putGreeting(void);
#endif

      /// @} end of name Public member functions

      /// \headerfile ArchitectureImplementation.h "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"
      /// \ingroup posix
      /// \nosubgrouping
      ///
      /// \brief POSIX context handling.
      ///
      /// \details
      /// This class provides generic POSIX context handling support.
      class Context
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        Context() = default;

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

  } // namespace posix

  // ------------------------------------------------------------------------

  namespace arch
  {
    typedef hal::posix::ArchitectureImplementation ArchitectureImplementation;
  }

// ========================================================================

}// namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
