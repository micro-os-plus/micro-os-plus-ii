//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX declarations of thread context implementation.

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_THREADCONTEXT_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_THREADCONTEXT_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX) || defined(__DOXYGEN__)

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/ArchitectureBase.h"
#include "hal/architecture/synthetic/posix/include/ArchitectureDefinitions.h"
#include "portable/diagnostics/include/Trace.h"

// Platform headers
#if defined(__APPLE__) && !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE 600L
#endif
#include <ucontext.h>
#include <errno.h>
// for strerror()
#include <string.h>

namespace hal
{
  namespace posix
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \headerfile ThreadContext.h "hal/architecture/synthetic/posix/include/ThreadContext.h"
    /// \ingroup posix
    /// \nosubgrouping
    ///
    /// \brief POSIX context handling.
    ///
    /// \details
    /// This class provides generic POSIX context handling support.
    ///
    /// It uses the makecontext()/getcontext()/setcontext() family of functions.
    ///
    class ThreadContext
    {

    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ThreadContext(void);

      /// \brief Destructor.
      ~ThreadContext();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

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

      /// \brief Save the current context in the local storage.
      ///
      /// \par Parameters
      ///    None.
      /// \retval true  Context saved, returns for the first time
      /// \retval false Context restored, returns for the second time
      ///    Nothing.
      bool
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

      /// \name Private friends
      /// @{

      /// \brief Required for manual inlines in yield()
      friend class ArchitectureImplementation;

      /// @} end of Private friends

      /// \name Private member variables
      /// @{

      /// \brief The context storage.
      ucontext_t m_context;

      /// \brief The C error indicator storage.
      int m_error;

      /// \brief Flag used to differentiate the two save() return cases.
      bool volatile m_saved;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

#if defined(COMPILER_INLINES_GETCONTEXT)
    // Actually not used, since the compiler refuses to inline
    // functions using getcontext(), so the code was manually copied
    // to yield()

    /// \details
    /// Preserve errno and get the context.
    /// \warning Due to some compiler complicated reasons, it could not be
    /// inlined, so its content will be manually inlined in yield().
    inline bool
    __attribute__((always_inline))
    ThreadContext::save(void)
      {
        m_error = errno;
        m_saved = true;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

        // This function will return twice, the second time after setcontext()
        if (getcontext(&m_context) != 0)
          {
#if defined(DEBUG)
            os::diag::trace.putString("getcontext failed with ");
            os::diag::trace.putString(strerror(errno));
            os::diag::trace.putNewLine();
#endif
          }

#pragma GCC diagnostic pop

        // Set to false by restore()
        return m_saved;
      }
#endif

    /// \details
    /// Restore context and errno.
    inline void
    __attribute__((always_inline))
    ThreadContext::restore(void)
    {
      errno = m_error;
      m_saved = false;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

      if (setcontext(&m_context) != 0)
        {
#if defined(DEBUG)
          os::diag::trace.putString("setcontext failed with ");
          os::diag::trace.putString(strerror(errno));
          os::diag::trace.putNewLine();
#endif
        }

#pragma GCC diagnostic pop

    }

  // ========================================================================

  }// namespace posix
}      // namespace hal

// ============================================================================

namespace hal
{
  namespace arch
  {
    using ThreadContext = hal::posix::ThreadContext;
  } // namespace arch
} // namespace hal

// ============================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_THREADCONTEXT_H_
