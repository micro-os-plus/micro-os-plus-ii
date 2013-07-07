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

#define _XOPEN_SOURCE 600L
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
      ArchitectureImplementation(void) = default;

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

      static void
      yield(void);

      /// @} end of name Public member functions

    };

    // ========================================================================

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
      ThreadContext(void);

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Create the initial context in the local storage.
      ///
      /// \param [in] pStackBottom    Pointer to the first stack element.
      /// \param [in] stackSizeBytes  Size of stack in bytes.
      /// \param [in] entryPoint      Pointer to thread code.
      /// \param [in] pParameters     Pointer to thread parameters.
      /// \par Returns
      ///    Nothing.
      void
      create(hal::arch::stackElement_t* pStackBottom,
          hal::arch::stackSize_t stackSizeBytes,
          os::core::threadEntryPoint_t entryPoint, void* pParameters);

      /// \brief Save the current context in the local storage.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      save(void);

      /// \brief Restore the current context from the local storage.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      restore(void);

      /// @} end of name Public member functions

    private:
      /// \brief The context storage.
      ucontext_t m_context;

#if defined(__APPLE__) || defined(OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX)

      // On OS X, for unknown reasons, the context does not include
      // the machine context, but only a pointer, so we reserve some
      // space to avoid overwriting next variables.
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif
      _STRUCT_MCONTEXT64 m_mcontext;
#pragma GCC diagnostic pop

#endif

      /// \brief The C error indicator storage.
      int m_error;
    };

#pragma GCC diagnostic pop

    /// \details
    /// Used only to explicitly initialise m_error.
    inline
    __attribute__((always_inline))
    ThreadContext::ThreadContext(void)
    {
      m_error = 0;
    }


  // ========================================================================

  }// namespace posix

  // ------------------------------------------------------------------------

  namespace arch
  {
    typedef hal::posix::ArchitectureImplementation ArchitectureImplementation;
    typedef hal::posix::ThreadContext ThreadContext;
  }

// ========================================================================

}// namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
