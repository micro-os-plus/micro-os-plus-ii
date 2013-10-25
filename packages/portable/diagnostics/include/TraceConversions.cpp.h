//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Conversion functions used in the Trace class.

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
    /// \relates TTraceBase
    ///
    /// \brief Convert a generic unsigned to a hex representation.
    template<class Implementation_T, typename number_T>
      inline void
      __attribute__((always_inline))
      __putHex(Implementation_T& implementation, number_T n)
      {
        // The extra byte is used to store a string terminator. It is
        // not required by write(), which receives a length, but
        // it helps implementations over semi-hosting.
        char buff[sizeof(n) * 2 + 1];

        size_t pos = sizeof(buff) - 1;
        buff[pos] = '\0';

        // the size is fixed and is given by the size of the variable
        for (; pos > 0;)
          {
            char ch = (n & 0xF);
            // always use upper case letters
            buff[--pos] = (ch < 10) ? (ch + '0') : (ch + 'A' - 10);
            n >>= 4;
          }

        // atomic call to the implementation
        implementation.write(buff, sizeof(buff) - 1);
      }

    /// \ingroup diag_conv
    /// \relates TTraceBase
    ///
    /// \brief Convert a generic signed to a decimal representation.
    template<class Implementation_T, typename number_T>
      inline void
      __attribute__((always_inline))
      __putSigned(Implementation_T& implementation, number_T n)
      {
        bool isNegative = false;

        if (n < 0)
          {
            isNegative = true;
            n = -n;
          }

        // the size is maximal and must fit all digits
        // one more for the sign and one more for the string terminator
        // the terminator is there only to optimise semi-hosting
        char buff[sizeof(n) * 5 / 2 + 1 + 1];

        size_t pos = sizeof(buff) - 1;
        buff[pos] = '\0';

        for (; pos > 0;)
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
        implementation.write(&buff[pos], (sizeof(buff) - pos - 1));
      }

    /// \ingroup diag_conv
    /// \relates TTraceBase
    ///
    /// \brief Convert a generic unsigned to a decimal representation.
    template<class Implementation_T, typename number_T>
      inline void
      __attribute__((always_inline))
      __putUnsigned(Implementation_T& implementation, number_T n)
      {
        // the size is maximal and must fit all digits
        // one more for the terminator
        // the terminator is there only to optimise semi-hosting
        char buff[sizeof(n) * 5 / 2 + 1];

        size_t pos = sizeof(buff) - 1;
        buff[pos] = '\0';

        for (; pos != 0;)
          {
            char ch = (n % 10);
            buff[--pos] = ch + '0';
            n /= 10;
            if (n == 0)
              break; // stop when there are no more digits
          }

        // atomic call to the implementation
        implementation.write(&buff[pos], (sizeof(buff) - pos - 1));
      }

  // ==========================================================================

  }// namespace diag
} // namespace os

#endif // OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE
#endif // OS_PORTABLE_DIAGNOSTICS_TRACECONVERSIONS_CPP_H_
