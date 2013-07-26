//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Thread stack.

#ifndef OS_PORTABLE_CORE_STACK_H_
#define OS_PORTABLE_CORE_STACK_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"

#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    namespace stack
    {
      /// \name Types and constants
      /// @{

      /// \brief Stack element type.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      typedef hal::arch::stackElement_t element_t;

      /// \brief Stack size type.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      typedef hal::arch::stackSize_t size_t;

    /// @} end of name Types and constants

    }
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class Stack Stack.h "portable/core/include/Stack.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Thread stack.
    ///
    /// \details
    /// Provide support for stack storage.
    class Stack
    {
    public:

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pStack            Pointer to the beginning of the stack area.
      /// \param [in] sizeBytes         Size of stack in bytes.
      Stack(stack::element_t* const pStack, stack::size_t const sizeBytes);

      /// \brief No Copy constructor.
      Stack(Stack& stack) = delete;

      /// \brief Destructor.
      ~Stack();

      /// @} end of name Constructors/destructor

      /// \name Public member functions
      /// @{

      /// \brief Initialise stack for usage.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      initialise(void);

      /// \brief Get stack size.
      ///
      /// \par Parameters
      ///    None.
      /// \return The number of bytes in the stack.
      stack::size_t
      getSize(void) const;

      /// \brief Get stack start address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The start of the stack area.
      stack::element_t*
      getStart(void);

      /// @} end of Public member functions

    private:

      /// \brief Stack fill value.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      static constexpr stack::element_t STACK_FILL = hal::arch::STACK_FILL;

      /// \name Private member variables
      /// @{

      /// \brief Pointer to the beginning of the stack area.
      stack::element_t* const m_pStart;

      /// \brief The stack size, in bytes.
      stack::size_t const m_sizeBytes;

      /// @} end of Private member variables

    };

#pragma GCC diagnostic pop

    // ------------------------------------------------------------------------

    /// \details
    /// Store the pointer to the beginning and the size
    /// in the private member variables.
    ///
    /// Leave the compiler to decide if it is inlined.
    inline
    Stack::Stack(stack::element_t* const pStack, stack::size_t const sizeBytes)
        : m_pStart(pStack), //
        m_sizeBytes(sizeBytes)
    {
#if defined(DEBUG)
      os::diag::trace.putString("os::core::Stack::Stack(");
      os::diag::trace.putHex(pStack);
      os::diag::trace.putString(", ");
      os::diag::trace.putDec(sizeBytes);
      os::diag::trace.putString(") @");
      os::diag::trace.putHex(this);
      os::diag::trace.putNewLine();
#endif
    }

    inline
    Stack::~Stack()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
    }

    /// \details
    /// Return the stack size, configured by the constructor.
    inline stack::size_t
    __attribute__((always_inline))
    Stack::getSize(void) const
    {
      return m_sizeBytes;
    }

    /// \details
    /// Return the start of the stack area, saved in the member variable.
    inline stack::element_t*
    __attribute__((always_inline))
    Stack::getStart(void)
    {
      return m_pStart;
    }

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    template<stack::size_t SizeBytes_T = hal::arch::MIN_STACK_SIZE>
      class TStaticStack : public Stack
      {
      public:
        TStaticStack(void);
        ~TStaticStack();

      private:
        os::core::stack::element_t m_stackArray[SizeBytes_T
            / sizeof(os::core::stack::element_t)];
      };

    template<stack::size_t SizeBytes_T>
      inline
      __attribute__((always_inline))
      TStaticStack<SizeBytes_T>::TStaticStack(void)
          : Stack(m_stackArray, sizeof(m_stackArray))
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif
      }

    template<stack::size_t SizeBytes_T>
      inline
      __attribute__((always_inline))
      TStaticStack<SizeBytes_T>::~TStaticStack()
      {
#if defined(DEBUG)
        os::diag::trace.putDestructor();
#endif
      }

#pragma GCC diagnostic pop

    // ========================================================================

    template<class Allocator_T>
      class TAllocatedStack : public Stack
      {
      public:
        TAllocatedStack(stack::size_t const sizeBytes);
        ~TAllocatedStack();

      private:
      };

    // TODO: define it, using the given allocator

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class AllocatedStack Stack.h "portable/core/include/Stack.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief A stack with dynamic allocation.
    ///
    /// \details
    /// This special stack allocates the stack array on the free store, using
    /// the recommended RAII paradigm of calling delete only in the
    /// destructor.
    class AllocatedStack : public Stack
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] sizeBytes         Size of stack in bytes.
      AllocatedStack(stack::size_t const sizeBytes);

      /// \brief Destructor.
      ~AllocatedStack();

      /// @} end of name Constructors/destructor

    };

#pragma GCC diagnostic pop

    /// \details
    /// Allocate the requested buffer on the free store and pass its
    /// address to the parent constructor.
    inline
    AllocatedStack::AllocatedStack(stack::size_t const sizeBytes)
        : Stack(new stack::element_t[sizeBytes / sizeof(stack::element_t)],
            sizeBytes)
    {
#if defined(DEBUG)
      os::diag::trace.putConstructor();
#endif
    }

    /// \details
    /// Free the space allocated in the constructor.
    inline
    AllocatedStack::~AllocatedStack()
    {
#if defined(DEBUG)
      os::diag::trace.putDestructor();
#endif
      delete[] getStart();
    }

  // ==========================================================================
  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_STACK_H_
