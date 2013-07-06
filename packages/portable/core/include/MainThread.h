//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Main thread.

#ifndef OS_PORTABLE_CORE_MAINTHREAD_H_
#define OS_PORTABLE_CORE_MAINTHREAD_H_

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

    /// \header MainThread.h "portable/core/include/MainThread.h"
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
    MainThread::MainThread(void)
        : Thread("main()", nullptr, nullptr, nullptr, 0,
            os::core::Scheduler::MAIN_PRIORITY)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructorWithName();
#endif
      // TODO: do something so that when the first yield
      // occurs, the context is saved in this thread.
    }

    MainThread::~MainThread()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructorWithName();
#endif
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_MAINTHREAD_H_