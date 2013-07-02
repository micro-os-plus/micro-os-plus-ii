//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Core thread.

#ifndef OS_PORTABLE_CORE_THREAD_H_
#define OS_PORTABLE_CORE_THREAD_H_

#include "portable/core/include/OS.h"

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

    /// \headerfile Thread.h "portable/core/include/Thread.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Core thread.
    ///
    /// \details
    /// This is the definition of the core thread, used by the
    /// scheduler(s).
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

      //typedef void
      //(*function_t)(void*);

      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pName Pointer to the null terminated thread name.
      /// \param [in] entryPoint Pointer to the thread code.
      /// \param [in] pParameters Pointer to the parameters passed to the thread.
      /// \param [in] pStack Pointer to the beginning of the stack area.
      /// \param [in] stackSize Number of stack elements.
      /// \param [in] priority Initial priority.
      Thread(const char* const pName, threadEntryPoint_t entryPoint,
          void* pParameters, Stack::element_t* const pStack,
          Stack::size_t const stackSize, priority_t priority =
              Scheduler::DEFAULT_PRIORITY);

      /// \brief Template Constructor.
      ///
      /// \param [in] pName Pointer to the null terminated thread name.
      /// \param [in] function A lambda to be called with one parameter.
      /// \param [in] pObject Pointer to the parameters passed to the thread.
      /// \param [in] pStack Pointer to the beginning of the stack area.
      /// \param [in] stackSize Number of stack elements.
      /// \param [in] priority Initial priority.
      template<class Lambda_T, class Object_T>
        Thread(const char* const pName, Lambda_T function, Object_T* pObject,
            Stack::element_t* const pStack, Stack::size_t const stackSize,
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
      getPriority(void) const;

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

      /// @} end of Public member functions

    private:

      /// \name Private member functions
      /// @{

      /// \brief Initialise thread.
      ///
      /// \param [in] entryPoint Pointer to the thread code.
      /// \param [in] pParameters Pointer to the parameters passed to the thread.
      /// \param [in] priority Initial priority.
      void
      initialise(threadEntryPoint_t entryPoint, void* pParameters,
          priority_t priority);

      /// @} end of Private member functions

      /// \name Private member variables
      /// @{

      /// \brief Instance of the stack object.
      Stack m_stack;

      /// \brief The current thread static priority.
      priority_t volatile m_staticPriority;

      /// \brief The ID used by the scheduler to identify the thread
      id_t m_id;

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
          Stack::size_t const stackSize, priority_t priority)
          : NamedObject(pName), //
          m_stack(pStack, stackSize)
      {
#if defined(DEBUG)
        os::diag::trace.putConstructorWithName();
#endif
        initialise(reinterpret_cast<threadEntryPoint_t>(*function),
            static_cast<void*>(pObject), priority);

        m_id = scheduler.registerThread(this);
      }

    /// \details
    /// Return the reference to the stack object from the private
    /// member variable.
    inline Stack&
    __attribute__((always_inline))
    Thread::getStack(void)
    {
      return m_stack;
    }

    /// \details
    /// Return the current thread static priority from the private
    /// member variable.
    inline Thread::priority_t
    __attribute__((always_inline))
    Thread::getPriority(void) const
    {
      return m_staticPriority;
    }

    /// \details
    /// Set the new static priority in the private
    /// member variable.
    inline
    void
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

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_THREAD_H_