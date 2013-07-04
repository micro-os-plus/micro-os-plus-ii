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

#define _XOPEN_SOURCE
#include <ucontext.h>

#include <errno.h>

namespace hal
{
  namespace posix
  {
    // ========================================================================

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

      /// \brief Default constructor.
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

      // ======================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \headerfile ArchitectureImplementation.h "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"
      /// \ingroup posix
      /// \nosubgrouping
      ///
      /// \brief POSIX context handling.
      ///
      /// \details
      /// This class provides generic POSIX context handling support.
      class ThreadContext
      {

      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        ThreadContext();

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Create the initial context in the local storage.
        ///
        /// \param [in] pStackBottom    Pointer to the first stack element.
        /// \param [in] stackSize       Size of stack in elements.
        /// \param [in] entryPoint      Pointer to thread code.
        /// \param [in] pParameters     Pointer to thread parameters.
        /// \par Returns
        ///    Nothing.
        void
        create(hal::arch::stackElement_t* pStackBottom,
            hal::arch::stackSize_t stackSize,
            os::core::threadEntryPoint_t entryPoint, void* pParameters);

        /// \brief Save the current context in the local storage.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        void
        save();

        /// \brief Restore the current context from the local storage.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        void
        restore();

        /// @} end of name Public member functions

      private:
        /// \brief The context storage.
        ucontext_t m_context;

        /// \brief The C error indicator storage.
        int m_error;
      };
    };

#pragma GCC diagnostic pop

    // ========================================================================

    /// \details
    /// Used only to explicitly initialise m_error.
    inline
    __attribute__((always_inline))
    ArchitectureImplementation::ThreadContext::ThreadContext(void)
    {
      m_error = 0;
    }

    /// \details
    /// Preserve errno and get context.
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::ThreadContext::save(void)
    {
      m_error = errno;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

      getcontext(&m_context);

#pragma GCC diagnostic pop

    }

    /// \details
    /// Restore context and errno.
    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::ThreadContext::restore(void)
    {
      errno = m_error;

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

      setcontext(&m_context);

#pragma GCC diagnostic pop

    }

  // ========================================================================

  }// namespace posix

  // ------------------------------------------------------------------------

  namespace arch
  {
    typedef hal::posix::ArchitectureImplementation ArchitectureImplementation;
  }

// ========================================================================

}// namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
