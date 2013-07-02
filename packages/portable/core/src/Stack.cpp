//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Stack member functions definitions.

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
    /// - create the initial thread context, that will be used on the
    /// first Context::restore()
    void
    Stack::initialise(threadEntryPoint_t entryPoint, void* pParameters)
    {
      // fill entire stack
      element_t* p = m_pStart;
      size_t cnt = m_size;
      for (; cnt > 0; --cnt)
        *p++ = STACK_FILL;

      // create initial context (architecture dependent)
      element_t* pTop = m_pStart + (m_size - 1);
      m_pCurrent = architecture.context.createInitial(pTop, entryPoint,
          pParameters);
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

