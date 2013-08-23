//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Generic Cortex-M semihosting definitions of the trace implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/diagnostics/include/TraceImplementationSemihosting.h"

#include "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"

namespace hal
{
  namespace cortexm
  {
    namespace diag
    {

      // ======================================================================

#if defined(DEBUG) || defined(__DOXYGEN__)

      /// \details
      /// Send the sequence of bytes to the
      /// bit banged I2C device. The operation is atomic.
      ssize_t
      TraceImplementationSemihosting::write(const void* pBuf, size_t numBytes)
      {
        if (!isDevicePresent())
          return 0;

        const char* p = reinterpret_cast<const char*>(pBuf);

        if (p[numBytes] == '\0')
          {
            // If the byte array is followed by a \0, optimise
            // and call the string output function.
            SemiHosting::writeString(p);
          }
        else
          {
            // Otherwise iterate and output one byte at a time.
            for (size_t i = 0; i < numBytes; ++i, ++p)
              {
                SemiHosting::writeChar(*p);
              }
          }
        return numBytes;
      }

#endif

    // ========================================================================

    }// namespace diag
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING)
