//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Definition of system abort().

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/abort.h"

#include "portable/diagnostics/include/Trace.h"

#include "portable/core/include/Platform.h"

namespace os
{
  namespace std
  {

    void
    abort(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif

      os::platform.resetSystem();
    }

  } // namespace std
} // namespace os
