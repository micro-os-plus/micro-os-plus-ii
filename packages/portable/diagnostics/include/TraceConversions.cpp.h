//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACECONVERSIONS_CPP_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACECONVERSIONS_CPP_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include "Trace.h"

namespace os
{
  namespace diag
  {

    // ========================================================================
    // Conversion template functions.
    // All are instantiated in the TraceBase putX() functions.

    /// \ingroup diag_conv
    /// \relates TraceBase
    ///
    /// \brief Convert a generic unsigned to a hex representation.
    template<class Implementation_T, typename TNumber_T>
      inline __attribute__((always_inline))
      void
      __putHex(Implementation_T& implementation, TNumber_T n)
      {
        size_t pos;
        char buff[sizeof(n) * 2];

        // the size is fixed and is given by the size of the variable
        for (pos = sizeof(buff); pos > 0;)
          {
            char ch = (n & 0xF);
            // always use upper case letters
            buff[--pos] = (ch < 10) ? (ch + '0') : (ch + 'A' - 10);
            n >>= 4;
          }

        // atomic call to the implementation
        implementation.write(buff, sizeof(buff));
      }

    /// \ingroup diag_conv
    /// \relates TraceBase
    ///
    /// \brief Convert a generic signed to a decimal representation.
    template<class Implementation_T, typename TNumber_T>
      inline __attribute__((always_inline))
      void
      __putSigned(Implementation_T& implementation, TNumber_T n)
      {
        bool isNegative = false;

        if (n < 0)
          {
            isNegative = true;
            n = -n;
          }

        size_t pos;
        // the size is maximal and must fit all digits
        char buff[sizeof(n) * 5 / 2 + 1]; // one more for the sign

        for (pos = sizeof(buff); pos != 0;)
          {
            char ch = (n % 10);
            buff[--pos] = ch + '0';
            n /= 10;
            if (n == 0)
              break; // stop when there are no more digits
          }

        if (isNegative)
          {
            // add the sign for negative numbers
            buff[--pos] = '-';
          }

        // atomic call to the implementation
        implementation.write(&buff[pos], (sizeof(buff) - pos));
      }
  // ========================================================================

  }// namespace diag
} // namespace os

#endif // OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE
#endif // OS_PORTABLE_DIAGNOSTICS_TRACECONVERSIONS_CPP_H_
