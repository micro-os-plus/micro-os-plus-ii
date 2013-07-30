//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief assert() definitions.

#include "portable/core/include/ConfigDefines.h"
#include "portable/language/cpp/include/cassert.h"
#include "portable/language/cpp/include/cstdlib.h"
#include "portable/diagnostics/include/Trace.h"

namespace os
{
  namespace infra
  {
#if defined(DEBUG) || defined(__DOXYGEN__)

    void
    assertFailed(const char* func, const char* file, int lineno, const char* expr)
    {
      os::diag::trace.putString(file);
      os::diag::trace.putChar(':');
      os::diag::trace.putDec(lineno);
      os::diag::trace.putString(": ");
      os::diag::trace.putString(func);
      os::diag::trace.putString(": Assertion '");
      os::diag::trace.putString(expr);
      os::diag::trace.putString("' failed.");
      os::diag::trace.putNewLine();

      os::std::abort();
    }

#endif // defined(DEBUG)
  } /* namespace infra */
} /* namespace os */

