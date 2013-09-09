//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Sample implementation for the Trace class.

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSAMPLE_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSAMPLE_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include <unistd.h>

namespace os
{
  namespace diag
  {
    // ========================================================================

    /// \headerfile TraceImplementationSample.h "portable/diagnostics/include/TraceImplementationSample.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief A sample platform specific TraceImplementation class.
    ///
    /// This class provides an example on how to
    /// write `TraceImplementation` classes. There is no
    /// implementation provided, only the interface is given.
    class TraceImplementationSample
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Constructor.
      TraceImplementationSample(void);

      /// \brief Destructor.
      ~TraceImplementationSample();

      /// @} end of name Constructors/destructor

      /// \name Hardware initialisations
      /// @{

      /// \brief Power up trace implementation hardware.
      ///
      /// \par Parameters
      ///       None.
      /// \par Returns
      ///       Nothing.
      void
      powerUp(void);

      /// \brief Power down trace implementation hardware.
      ///
      /// \par Parameters
      ///       None.
      /// \par Returns
      ///       Nothing.
      void
      powerDown(void);

      /// @} end of name Hardware initialisations

      /// \name Public member functions
      /// @{

      /// \brief Output a byte array.
      ///
      /// \param pBuf Pointer to byte array.
      /// \param numBytes Number of bytes.
      /// \return The number of bytes actually written.
      ssize_t
      write(const void* pBuf, size_t numBytes);

      /// \brief Flush content to device.
      ///
      /// \par Parameters
      /// None.
      /// \par Returns
      /// Nothing.
      void
      flush(void);

      /// @} end of name Public member functions
    };

    // ------------------------------------------------------------------------
    // Sample inline definitions

    inline
    TraceImplementationSample::TraceImplementationSample(void)
    {
    }

    inline
    TraceImplementationSample::~TraceImplementationSample()
    {
    }

    inline
    void
    TraceImplementationSample::powerUp(void)
    {
    }

    inline ssize_t
    TraceImplementationSample::write(const void* pBuf __attribute__((unused)),
        size_t numBytes __attribute__((unused)))
    {
      return 0;
    }

    inline
    void
    TraceImplementationSample::flush(void)
    {
    }

  // ==========================================================================

  }// namespace diag
} // namespace os

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATIONSAMPLE_H_
