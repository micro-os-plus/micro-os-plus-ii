//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Idle thread.

#ifndef OS_PORTABLE_CORE_IDLETHREAD_H_
#define OS_PORTABLE_CORE_IDLETHREAD_H_

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

    /// \headerfile IdleThread.h "portable/core/include/IdleThread.h"
    /// \ingroup core_thread
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

    private:

      /// \name Private friends
      /// @{

      /// \brief The idle thread main code.
      void
      threadMain(void);

      /// @} end of Private friends

      /// \name Private member variables
      /// @{

      /// \brief The idle thread stack.
      /// \warning Defining it inside a class derived from another class
      /// that needs a reference to it
      /// is potentially wrong, since it is constructed after the
      /// parent class, but in this case we do not use the reference
      /// to the stack in the constructor.
      TStaticStack<hal::arch::MIN_STACK_SIZE> m_stack;

      /// @} end of Private member variables

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

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_IDLETHREAD_H_
