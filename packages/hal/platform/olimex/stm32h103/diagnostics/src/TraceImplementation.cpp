//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_OLIMEX_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "hal/platform/olimex/stm32h103/diagnostics/include/TraceImplementation.h"

namespace hal
{
  namespace stm32h103
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
      TraceImplementation::initialiseEarly(void)
      {
      }

      /// \details
      /// Call the system `write()` function to send the sequence of bytes to the
      /// standard output. The operation is atomic.
      ssize_t
      TraceImplementation::write(const void* pBuf __attribute__((unused)), size_t numBytes __attribute__((unused)))
      {
        return 0;
        //return ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, pBuf, numBytes);
      }

#endif

      // ======================================================================

    } // namespace diag
  } // namespace stm32h103
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_PLATFORM_OLIMEX_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION)
