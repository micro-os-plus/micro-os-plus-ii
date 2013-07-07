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
      os::core::Stack::element_t m_stack[hal::arch::MIN_STACK_SIZE
          / sizeof(os::core::Stack::element_t)];

    };

#pragma GCC diagnostic pop

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
