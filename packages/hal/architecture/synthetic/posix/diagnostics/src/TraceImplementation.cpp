//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "../include/TraceImplementation.h"

namespace hal
{
  namespace posix
  {
    namespace diag
    {

      // ======================================================================

#if defined(DEBUG) || defined(__DOXYGEN__)

      TraceImplementation::TraceImplementation()
      {
      }

      TraceImplementation::~TraceImplementation()
      {
      }

      /// \details
      /// Called during early start-up, to perform
      /// initialisations required before constructor.
      ///
      /// Nothing to do on POSIX, the standard output is already available.
      void
      TraceImplementation::earlyInitialise(void)
      {
      }

      /// \details
      /// Call the system `write()` function to send the sequence of bytes to the
      /// standard output. The operation is atomic.
      ssize_t
      TraceImplementation::write(const void* pBuf, size_t numBytes)
      {
        return ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, pBuf, numBytes);
      }

#endif

      // ======================================================================

    } // namespace diag
  } // namespace posix
} // namespace hal

#endif /* defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) */
