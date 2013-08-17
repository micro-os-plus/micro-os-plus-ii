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

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#if defined(__APPLE__)
#define _XOPEN_SOURCE 600L
#endif
#include <ucontext.h>

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#include "portable/core/include/ArchitectureBase.h"

// Include architecture definitions, like various types.
#include "hal/architecture/synthetic/posix/include/ArchitectureDefinitions.h"

#include "hal/architecture/synthetic/posix/include/TimerTicksImplementation.h"

#include "portable/language/cpp/include/cstdlib.h"

#include <errno.h>
#include <unistd.h>

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

      static void
      waitForInterrupt(void);

      /// \brief Software reset the processor.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      static void
      __attribute__((noreturn))
      resetSystem(void);

      /// \brief Busy wait microseconds.
      ///
      /// \param [in] micros     The number of microseconds to sleep.
      /// \par Returns
      ///    Nothing.
      static void
      busyWaitMicros(uint32_t micros);

      /// @} end of name Public member functions

    };

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::resetSystem(void)
    {
      ::abort();
    }

    inline void
    __attribute__((always_inline))
    ArchitectureImplementation::waitForInterrupt(void)
    {
      pause();
    }

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

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
          os::core::trampoline3_t trampolineEntryPoint, void* p1, void* p2, void* p3);

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

    // ========================================================================

    /// \headerfile ArchitectureImplementation.h "hal/architecture/synthetic/posix/include/ArchitectureImplementation.h"
    /// \ingroup posix
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

      /// \brief Storage for the signal status
      sigset_t m_status;

      /// @} end of Private member variables

    };

  // ==========================================================================

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  }// namespace posix

  // --------------------------------------------------------------------------

  namespace arch
  {
    using ArchitectureImplementation = hal::posix::ArchitectureImplementation;

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

    using ThreadContext = hal::posix::ThreadContext;
    using TimerTicksImplementation = hal::posix::TimerTicksImplementation;
    using InterruptsCriticalSection = hal::posix::InterruptsCriticalSection;

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  } // namespace arch

// ============================================================================

}// namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX)
#endif // HAL_ARCHITECTURE_SYNTHETIC_POSIX_ARCHITECTUREIMPLEMENTATION_H_
