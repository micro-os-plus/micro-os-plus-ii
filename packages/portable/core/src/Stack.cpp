//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Stack member functions definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Architecture.h"
#include "portable/core/include/Stack.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    /// \details
    /// Prepare the stack for scheduler usage:
    /// - fill it entirely with a
    /// pattern, in order to know how much it was used;
    void
    Stack::initialise(void)
    {
      // fill entire stack
      stack::element_t* p = m_pStart;
      if (p != nullptr)
        {
          stack::size_t cnt = m_sizeBytes / sizeof(stack::element_t);
          for (; cnt > 0; --cnt)
            *p++ = STACK_FILL;
        }
    }

    /// \details
    /// Return the start of the stack area, saved in the member variable.
    stack::element_t*
    Stack::getTopAligned(size_t align)
    {
      // go to the end of the unaligned area
      char* p = reinterpret_cast<char*>(m_pStart) + m_sizeBytes;

      // compute how far we are from the alignment area
      // assume the input value is a power of 2
      size_t diff = ((size_t) p) & (align - 1);

      // diminish pointer to aligned border
#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wcast-align"
#endif
      return (stack::element_t*) (p - diff);
#pragma GCC diagnostic pop
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
