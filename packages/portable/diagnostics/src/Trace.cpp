//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "portable/diagnostics/include/Trace.h"
#include "portable/diagnostics/include/Trace.cpp.h"

#include "portable/core/include/Greeting.h"

namespace os
{
  namespace diag
  {

// ============================================================================

#if defined(DEBUG)

    // ------------------------------------------------------------------------
    // explicit templates instantiations

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

    template class TTraceStreambufBase<TraceImplementation> ;
    template class TTraceOstreamBase<TraceStreambuf, TraceImplementation> ;

    template class TTraceBase<TraceOstreamBase, TraceImplementation> ;

#endif

    template class TTraceLightBase<TraceImplementation> ;

    template class TTraceBase<TraceLightBase, TraceImplementation> ;

    // ========================================================================
    // Trace
    // (intentionally skipped on Release)

    /// \details
    /// This constructor is called from `EarlyInitialisations.cpp`
    /// to initialise the tracing output device as early as possible.
    ///
    /// The parent ostream was just initialised, so we can use it.
    Trace::Trace()
    {
      // This is the earliest time we can display something on the
      // trace device.

      // use the static object, in case we deal with another instance
      os::diag::trace.putNewLine();
      os::diag::trace.putConstructor();
    }

    /// \details
    /// Unless when used in testing environments,
    /// this destructor is normally called during the exit sequence
    /// (probably never in embedded environments).
    Trace::~Trace()
    {
      // use the static object, in case we deal with another instance
      os::diag::trace.putDestructor();

      os::diag::trace.putString("No more trace messages after this point...");
      os::diag::trace.putNewLine();
    }

#endif // DEBUG
// ============================================================================

  }
// namespace diag
}// namespace os
#endif
