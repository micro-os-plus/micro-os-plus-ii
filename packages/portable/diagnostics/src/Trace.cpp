//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "../include/Trace.h"
#include "../include/Trace.cpp.h"

#include "portable/core/include/Greeting.h"

namespace os
{
  namespace diag
  {

    // ------------------------------------------------------------------------

    // explicit template instantiation
    template class TraceStreambufBase<TraceImplementation_t> ;

    // ------------------------------------------------------------------------

    // explicit template instantiation
    template class TraceOstreamBase<TraceStreambuf_t, TraceImplementation_t> ;

    // ------------------------------------------------------------------------

    // explicit template instantiations
    template class TraceBase<TraceOstreamBase_t, TraceImplementation_t>;
    template class TraceBase<TraceLightBase_t, TraceImplementation_t> ;

    // ========================================================================
    // Trace
    // (intentionally skipped on Release)

#if defined(DEBUG) || defined(__DOXYGEN__)

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
    }


#endif // DEBUG
  // ========================================================================

  }// namespace diag
}    // namespace os
#endif
