//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Thread stack.

#ifndef OS_PORTABLE_CORE_STACK_H_
#define OS_PORTABLE_CORE_STACK_H_

#include "portable/core/include/Architecture.h"

namespace os
{
  namespace core
  {
    // ========================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

    /// \class Stack Stack.h "portable/core/include/Stack.h"
    /// \ingroup core
    /// \nosubgrouping
    ///
    /// \brief Base for all classes that have a name.
    ///
    /// \details
    /// Provide common support for all objects that have a name,
    /// used mainly to identify the objects.
    class Stack
    {
    public:
      /// \name Types and constants
      /// @{

      /// \brief Stack element type.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      typedef hal::arch::stackElement_t element_t;

      /// \brief Stack fill value.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      static const element_t STACK_FILL = hal::arch::STACK_FILL;

      /// \brief Stack size type.
      ///
      /// \details
      /// Portable redefinition, based on architecture definitions.
      typedef hal::arch::stackSize_t size_t;


      /// @} end of name Types and constants

      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      ///
      /// \param [in] pStack    Pointer to the beginning of the stack area.
      /// \param [in] sizeBytes Number of stack elements.
      Stack(element_t* const pStack, size_t const sizeBytes);

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
      size_t
      getSize(void) const;

      /// \brief Get stack start address.
      ///
      /// \par Parameters
      ///    None.
      /// \return The start of the stack area.
      element_t*
      getStart(void);


      /// @} end of Public member functions

    private:
      /// \name Private member variables
      /// @{

      /// \brief Pointer to the beginning of the stack area.
      element_t* const m_pStart;

      /// \brief The stack size, in bytes.
      size_t const m_sizeBytes;

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
    Stack::Stack(element_t* const pStack, size_t const sizeBytes)
        : m_pStart(pStack), //
        m_sizeBytes(sizeBytes)
    {
    }

    /// \details
    /// Return the stack size, configured by the constructor.
    inline Stack::size_t
    __attribute__((always_inline))
    Stack::getSize(void) const
    {
      return m_sizeBytes;
    }

    /// \details
    /// Return the start of the stack area, saved in the member variable.
    inline Stack::element_t*
    __attribute__((always_inline))
    Stack::getStart(void)
    {
      return m_pStart;
    }

  // ==========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_STACK_H_
