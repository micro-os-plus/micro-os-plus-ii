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

#include "portable/language/cpp/include/memory.h"

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

      /// \ingroup core_thread
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

    /// @} end of ingroup core_thread

    /// @} end of name Types and constants
    }
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class Stack Stack.h "portable/core/include/Stack.h"
    /// \ingroup core_thread
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

      /// \brief No copy constructor.
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
      getSizeBytes(void) const;

      /// \brief Get stack start address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The start of the stack area.
      stack::element_t*
      getStart(void);

      /// \brief Get stack top aligned address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The start of the stack area.
      stack::element_t*
      getTopAligned(size_t align);

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
    /// Align both to the element size.
    ///
    /// Leave the compiler to decide if it is inlined.
    inline
    Stack::Stack(stack::element_t* const pStack, stack::size_t const sizeBytes) :
        m_pStart(
            (stack::element_t*) ((unsigned long) pStack
                & ~(sizeof(stack::element_t) - 1))), //
        m_sizeBytes(sizeBytes & ~(sizeof(stack::element_t) - 1))
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
    Stack::getSizeBytes(void) const
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

    /// \headerfile Stack.h "portable/core/include/Stack.h"
    /// \ingroup core_thread
    /// \nosubgrouping
    ///
    /// \brief A statically allocated stack.
    ///
    /// \tparam SizeBytes_T  The size of the stack, in bytes.
    ///
    /// \details
    /// This stack is intended for cases when the size
    /// is known at compile time and fixed. It allocates the
    /// stack space as a private member array inside this object.
    template<stack::size_t SizeBytes_T = hal::arch::MIN_STACK_SIZE>
      class TStaticStack : public Stack
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        ///
        /// \par Parameters
        ///    None.
        TStaticStack(void);

        /// \brief Destructor.
        ~TStaticStack();

        /// @} end of name Constructors/destructor

      private:
        /// \name Private member variables
        /// @{

        /// \brief The static storage where the stack will be located.
        os::core::stack::element_t m_stackArray[SizeBytes_T
            / sizeof(os::core::stack::element_t)];

        /// @} end of Private member variables
      };

    /// \details
    /// Pass the address of the privte member to the parent constructor.
    template<stack::size_t SizeBytes_T>
      inline
      __attribute__((always_inline))
      TStaticStack<SizeBytes_T>::TStaticStack(void) :
          Stack(m_stackArray, sizeof(m_stackArray))
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TStaticStack::TStaticStack()", this);
#endif
      }

    /// \details
    /// No functionality required.
    template<stack::size_t SizeBytes_T>
      inline
      __attribute__((always_inline))
      TStaticStack<SizeBytes_T>::~TStaticStack()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TStaticStack::~TStaticStack()", this);
#endif
      }

#pragma GCC diagnostic pop

    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \headerfile Stack.h "portable/core/include/Stack.h"
    /// \ingroup core_thread
    /// \nosubgrouping
    ///
    /// \brief A stack with dynamic allocation.
    ///
    /// \tparam Allocator_T  The allocator to use.
    ///
    /// \details
    /// This special stack allocates the stack storage on the free store, using
    /// the recommended RAII paradigm of allocating in the constructor
    /// and deallocating only in the
    /// destructor.
    template<class Allocator_T = os::std::allocator<stack::element_t>>
      class TAllocatedStack : public Stack
      {
      public:
        typedef Allocator_T allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        /// \name Constructors/destructor
        /// @{

        /// \brief Constructor.
        ///
        /// \param [in] sizeBytes         Size of stack in bytes.
        TAllocatedStack(stack::size_t const sizeBytes =
            hal::arch::MIN_STACK_SIZE);

        /// \brief Destructor.
        ~TAllocatedStack();

        /// @} end of name Constructors/destructor

      private:
        /// \name Private member variables
        /// @{

        /// \brief The allocator object.
        allocator_type m_allocator;

        /// @} end of Private member variables

      };

#pragma GCC diagnostic pop

    /// \details
    /// Allocate the requested buffer using the given allocator and pass its
    /// address to the parent constructor.
    template<class Allocator_T>
      inline
      TAllocatedStack<Allocator_T>::TAllocatedStack(
          stack::size_t const sizeBytes) :
          Stack(m_allocator.allocate(sizeBytes / sizeof(stack::element_t)),
              sizeBytes)
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TAllocatedStack::TAllocatedStack()", this);
#endif
      }

    /// \details
    /// Free the space allocated in the constructor.
    template<class Allocator_T>
      inline
      TAllocatedStack<Allocator_T>::~TAllocatedStack()
      {
#if defined(DEBUG)
        os::diag::trace.putStringAndAddress(
            "os::core::TAllocatedStack::~TAllocatedStack()", this);
#endif
        m_allocator.deallocate(getStart(),
            getSizeBytes() / sizeof(stack::element_t));
      }

    // ========================================================================

    /// \ingroup core_thread
    /// \brief Stack allocated via the default allocator.
    using AllocatedStack = TAllocatedStack<>;

  // ==========================================================================
  }// namespace core
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
#endif // OS_PORTABLE_CORE_STACK_H_
