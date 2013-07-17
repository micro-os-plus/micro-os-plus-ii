//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core thread.

#ifndef OS_PORTABLE_CORE_THREAD_H_
#define OS_PORTABLE_CORE_THREAD_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

#include "portable/core/include/Architecture.h"

#include "portable/core/include/NamedObject.h"
#include "portable/core/include/Stack.h"
#include "portable/core/include/Scheduler.h"

namespace os
{
  namespace core
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class Thread Thread.h "portable/core/include/Thread.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Core thread.
    ///
    /// \details
    /// This is the definition of the core thread, used by the
    /// scheduler(s).
    ///
    /// \example portable/core/tests/src/threads.cpp
    /// \example portable/core/tests/include/FakeScheduler.h
    /// \example portable/core/tests/src/FakeScheduler.cpp
    class Thread : public NamedObject
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Thread priority type.
      ///
      /// \details
      /// Redefined here, based on scheduler definitions.
      typedef Scheduler::threadPriority_t priority_t;

      /// \brief Thread ID.
      ///
      /// \details
      /// Redefined here, based on scheduler definitions.
      typedef Scheduler::threadId_t id_t;

      //static const id_t NO_ID = scheduler::NO_ID;

      /// \brief Thread context.
      ///
      /// \details
      /// Redefined here, based on architecture definitions.
      typedef hal::arch::ThreadContext Context;

      /// \brief Pointer to trampoline function.
      typedef void
      (*trampoline3_t)(void*, void*, void*);

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pName             Pointer to the null terminated thread name.
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed to the thread.
      /// \param [in] pStack            Pointer to the beginning of the stack area.
      /// \param [in] stackSizeBytes    Size of stack in Bytes.
      /// \param [in] priority          Initial priority.
      Thread(const char* const pName, threadEntryPoint_t entryPoint,
          void* pParameters, Stack::element_t* const pStack,
          Stack::size_t const stackSizeBytes, priority_t priority =
              Scheduler::DEFAULT_PRIORITY);

      /// \brief Template Constructor.
      ///
      /// \param [in] pName             Pointer to the null terminated thread name.
      /// \param [in] function          A lambda to be called with one parameter.
      /// \param [in] pObject           Pointer to the parameters passed to the thread.
      /// \param [in] pStack            Pointer to the beginning of the stack area.
      /// \param [in] stackSizeBytes    Size of stack in Bytes.
      /// \param [in] priority          Initial priority.
      template<class Lambda_T, class Object_T>
        Thread(const char* const pName, Lambda_T function, Object_T* pObject,
            Stack::element_t* const pStack, Stack::size_t const stackSizeBytes,
            priority_t priority = Scheduler::DEFAULT_PRIORITY);

      /// \brief Destructor.
      ~Thread();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Get the thread stack.
      ///
      /// \par Parameters
      ///    None.
      /// \return Reference to the stack object.
      Stack&
      getStack(void);

      /// \brief Get the thread priority.
      ///
      /// \par Parameters
      ///    None.
      /// \return The current thread priority.
      priority_t
      getPriority(void) volatile;

      /// \brief Set the thread priority.
      ///
      /// \param [in] priority The new priority.
      /// \par Returns
      ///    Nothing.
      void
      setPriority(priority_t priority);

      /// \brief Get the thread ID.
      ///
      /// \par Parameters
      ///    None.
      /// \return The current thread ID.
      id_t
      getId(void) const;

      /// \brief Get the thread entry point address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The thread entry point address.
      threadEntryPoint_t
      getEntryPointAddress(void) const;

      /// \brief Get the thread entry point parameter.
      ///
      /// \par Parameters
      ///    None.
      /// \return The thread entry point parameter.
      void*
      getEntryPointParameter(void) const;

      /// \brief Join the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      join(void);

      /// \brief Suspend the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      suspend(void);

      /// \brief Resume the thread from an interrupt.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      resumeFromInterrupt(void);

      /// \brief Resume the thread.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      resume(void);

      /// \brief Check if the thread is suspended.
      ///
      /// \par Parameters
      ///    None.
      /// \return True if the thread is suspended.
      bool
      isSuspended(void) const;

      /// \brief Check if the thread is waiting for attention.
      ///
      /// \par Parameters
      ///    None.
      /// \return True if the thread is waiting for attention.
      bool
      isAttentionRequested(void) const;

      /// \brief Request the thread for special attention.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      requestAttention(void);

      /// \brief Acknowledge that special attention was provided.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      acknowledgeAttention(void);

      /// \brief Get context
      ///
      /// \par Parameters
      ///    None.
      /// \return Reference to context (architecture dependent content).
      Context&
      getContext(void);

      /// \brief Static trampoline used to execute the thread.
      ///
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed
      ///                               to the thread code.
      /// \param [in] pThread           Pointer to the thread object.
      static void
      trampoline3(threadEntryPoint_t entryPoint, void* pParameters,
          Thread* pThread);

      /// @} end of Public member functions

    private:

      /// \name Private member functions
      /// @{

      /// \brief Initialise thread.
      ///
      /// \param [in] entryPoint        Pointer to the thread code.
      /// \param [in] pParameters       Pointer to the parameters passed
      ///                               to the thread code.
      /// \param [in] priority          Initial priority.
      void
      initialise(threadEntryPoint_t entryPoint, void* pParameters,
          priority_t priority);

      /// \brief Clean thread object after code completed.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      cleanup(void);

      /// @} end of Private member functions

      /// \name Private member variables
      /// @{

      /// \brief Boolean to remember when the thread is suspended.
      bool volatile m_isSuspended;

      /// \brief Boolean to remember when special attention is requested.
      bool volatile m_isAttentionRequested;

      /// \brief Storage for the architecture dependent context.
      Context m_context;

      /// \brief The stack object.
      Stack m_stack;

      /// \brief The current thread static priority.
      priority_t volatile m_staticPriority;

      /// \brief The ID used by the scheduler to identify the thread.
      ///
      /// \details
      /// After construction it is
      id_t m_id;

      /// \brief The address of entry point to call for execution.
      threadEntryPoint_t m_entryPointAddress;

      /// \brief The parameter passed when calling the entry point.
      void* m_entryPointParameter;

      /// \brief Pointer to the thread that requested to join().
      volatile Thread* m_pJoiner;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// Cast the lambda to an entryPoint pointer
    /// and process like the regular non-template call.
    ///
    /// When the thread is used as another object member,
    /// the recommended usage pattern is:
    /// \code{.cpp}
    /// Task::Task() :
    ///   m_thread([] (Task* pTask) { pTask->threadMain();}, this)
    /// {
    ///   ...
    /// }
    /// \endcode
    template<class Lambda_T, class Object_T>
      Thread::Thread(const char* const pName, Lambda_T function,
          Object_T* pObject, Stack::element_t* const pStack,
          Stack::size_t const stackSizeBytes, priority_t priority)
          : NamedObject(pName), //
          m_stack(pStack, stackSizeBytes)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructorWithName();
#endif
        initialise(reinterpret_cast<threadEntryPoint_t>(*function),
            static_cast<void*>(pObject), priority);

        m_id = os::scheduler.registerThread(this);
      }

    /// \details
    /// Return the reference to the stack object as stored in the private
    /// member variable.
    inline Stack&
    __attribute__((always_inline))
    Thread::getStack(void)
    {
      return m_stack;
    }

    /// \details
    /// Return the current thread static priority as stored in the private
    /// member variable.
    inline Thread::priority_t
    __attribute__((always_inline))
    Thread::getPriority(void) volatile
    {
      return m_staticPriority;
    }

    /// \details
    /// Set the new static priority in the private
    /// member variable.
    inline void
    __attribute__((always_inline))
    Thread::setPriority(priority_t priority)
    {
      m_staticPriority = priority;
    }

    /// \details
    /// Return the current thread ID, as assigned by the scheduler
    /// when the thread was registered.
    inline Thread::id_t
    __attribute__((always_inline))
    Thread::getId(void) const
    {
      return m_id;
    }

    /// \details
    /// Return the address of the code used for the thread.
    inline threadEntryPoint_t
    __attribute__((always_inline))
    Thread::getEntryPointAddress(void) const
    {
      return m_entryPointAddress;
    }

    /// \details
    /// Return the parameter used when calling the thread code. For
    /// Threads implemented with C++ classes, this is typically a
    /// pointer to the actual object.
    inline void*
    __attribute__((always_inline))
    Thread::getEntryPointParameter(void) const
    {
      return m_entryPointParameter;
    }

    inline Thread::Context&
    __attribute__((always_inline))
    Thread::getContext()
    {
      return m_context;
    }


     inline bool
    __attribute__((always_inline))
    Thread::isSuspended(void) const
    {
      return m_isSuspended;
    }

    inline bool
    __attribute__((always_inline))
    Thread::isAttentionRequested(void) const
    {
      return m_isAttentionRequested;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_THREAD_H_
