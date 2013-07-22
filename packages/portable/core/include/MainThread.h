//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Main thread.

#ifndef OS_PORTABLE_CORE_MAINTHREAD_H_
#define OS_PORTABLE_CORE_MAINTHREAD_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Thread.h"

namespace os
{
  namespace core
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \headerfile MainThread.h "portable/core/include/MainThread.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Main thread.
    ///
    /// \details
    /// This is the definition of the thread associated to the main()
    /// function.
    /// It is used only to store the scheduler context, it has not
    /// its own stack (uses the system stack, at the end of RAM)
    /// and has no entry point, since it is started by the system.
    class MainThread : public Thread
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      MainThread(void);

      /// \brief Destructor.
      ~MainThread();

      /// @} end of name Constructors/destructor

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// The main thread has no entry point, no parameters, no stack
    /// and very low priority.
    /// Using a null stack pointer will prevent creating a new context.
    inline
    MainThread::MainThread(void)
        : Thread("main()", nullptr, nullptr, nullptr, 0,
            os::core::scheduler::MAIN_PRIORITY)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructorWithName();
#endif

      // The scheduler will automatically initialise the pointer to the
      // current thread with the address of the main thread, so
      // there is no need to call setCurrentThread(this) here.
    }

    inline
    MainThread::~MainThread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif
    }

  // ==========================================================================

  }// namespace core
} // namespace os

namespace os
{
  // Declaration of the external instantiation of `MainThread`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern os::core::MainThread mainThread;
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)

#endif // OS_PORTABLE_CORE_MAINTHREAD_H_
