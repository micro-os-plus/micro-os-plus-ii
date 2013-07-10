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
      element_t* p = m_pStart;
      if (p != nullptr)
        {
          size_t cnt = m_sizeBytes / sizeof(element_t);
          for (; cnt > 0; --cnt)
            *p++ = STACK_FILL;
        }
    }

  // --------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
