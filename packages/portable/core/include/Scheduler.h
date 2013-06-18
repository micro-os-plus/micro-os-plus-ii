//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Portable scheduler definitions.

#ifndef OS_PORTABLE_CORE_SCHEDULER_H_
#define OS_PORTABLE_CORE_SCHEDULER_H_

#include "portable/core/include/ConfigDefines.h"

#include <stdint.h>

namespace os
{
  namespace core
  {
    class Thread;

    /// \headerfile Scheduler.h "portable/core/include/Scheduler.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Scheduler.
    ///
    /// \details
    /// This is the definition of the scheduler.
    class Scheduler
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Priority type.
      ///
      /// \details
      /// A single byte should be more than enough, even for
      /// larger embedded systems.
      typedef uint8_t threadPriority_t;

      /// \brief Idle task priority.
      ///
      /// \details
      /// Must be below MIN priority.
      static const threadPriority_t IDLE_PRIORITY = 0x00;

      /// \brief Minimum priority.
      ///
      /// \details
      /// Must be above IDLE priority.
      static const threadPriority_t MIN_PRIORITY = IDLE_PRIORITY + 1;

      /// \brief Maximum priority.
      ///
      /// \details
      /// Must be above MIN priority.
      static const threadPriority_t MAX_PRIORITY = 0xFF;

      /// \brief Default priority.
      ///
      /// \details
      /// Computed as average between MIN and MAX priorities.
      static const threadPriority_t DEFAULT_PRIORITY = ((MAX_PRIORITY - MIN_PRIORITY)
          / 2 + 1);

      /// \brief Thread ID.
      ///
      /// \details
      /// A unique value identifying each thread.
      typedef uint8_t threadId_t;

      /// \brief No valid ID.
      ///
      /// \details
      /// Value returned by threads that are not registered to the
      /// scheduler.
      static const threadId_t NO_ID = 0xFF;

      /// @} end of name Types and constants
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      Scheduler();

      /// \brief Destructor.
      ~Scheduler();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Register thread to the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \retval       NO_ID if the thread could not be registered.
      /// \retval       The newly allocated thread ID, if successful.
      threadId_t
      registerThread(Thread* pThread);

      /// \brief Deregister thread from the scheduler lists.
      ///
      /// \param [in] pThread Pointer to the thread.
      /// \return NO_ID.
      threadId_t
      deregisterThread(Thread* pThread);

      void
      run(void);

      void
      yield(void);

      /// @} end of Public member functions

    private:
      // TBD
    };

    inline void
    Scheduler::yield(void)
    {

    }

  } // namespace core
} // namespace os

namespace os
{
  // Declaration of the external instantiation of `scheduler`.
  // The object instantiation is in `EarlyInitialisations.cpp`.
  extern os::core::Scheduler scheduler;
}

#endif // OS_PORTABLE_CORE_SCHEDULER_H_
