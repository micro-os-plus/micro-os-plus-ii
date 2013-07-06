//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Idle thread.

#ifndef OS_PORTABLE_CORE_IDLETHREAD_H_
#define OS_PORTABLE_CORE_IDLETHREAD_H_

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

    /// \header IdleThread.h "portable/core/include/IdleThread.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Idle thread.
    ///
    /// \details
    /// This is the definition of the idle thread.
    class IdleThread : public Thread
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      IdleThread(void);

      /// \brief Destructor.
      ~IdleThread();

      /// @} end of name Constructors/destructor

      void
      threadMain(void);

    private:
      os::core::Stack::element_t m_stack[10000];

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// The main thread has no entry point, no parameters, no stack
    /// and very low priority.
    inline
    IdleThread::IdleThread(void)
        : Thread("idle", [](IdleThread* p)
          { p->threadMain();}, this, m_stack,
            sizeof(m_stack) / sizeof(m_stack[0]),
            os::core::Scheduler::IDLE_PRIORITY)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructorWithName();
#endif
      // TODO: add code
    }

    inline
    IdleThread::~IdleThread()
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
  // Declaration of the external instantiation of `IdleThread`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern os::core::IdleThread idleThread;
}

#endif // OS_PORTABLE_CORE_IDLETHREAD_H_
