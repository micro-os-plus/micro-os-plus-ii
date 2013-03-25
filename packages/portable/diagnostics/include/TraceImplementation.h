//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
#define OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE) || defined(__DOXYGEN__)

#include <unistd.h>

namespace os
{
  namespace diag
  {

    /// \class TraceImplementationSample TraceImplementation.h "portable/diagnostics/include/TraceImplementation.h"
    /// \ingroup diag
    /// \nosubgrouping
    ///
    /// \brief Sample TraceImplementation class.
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
      TraceImplementationSample();

      /// \brief Destructor.
      ~TraceImplementationSample();

      /// @}

      /// \name Early initialisations
      /// @{

      /// \brief Early initialisation
      ///
      /// \par Parameters
      /// None.
      /// \par Returns
      /// Nothing.
      void
      earlyInitialise(void);

      /// @}

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

      /// @}
    };

  } // namespace diag
} // namespace os

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION)

#include "hal/arch/synthetic/posix/diagnostics/include/TraceImplementation.h"

#elif defined(__DOXYGEN__)

namespace os
  {
    namespace diag
      {
        typedef os::diag::TraceImplementation TraceImplementation_t;
      } // namespace diag
  } // namespace os

#else

#error "Missing TraceImplementation.h"

#endif /* architecture selection */

#endif // defined(OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE)
#endif // OS_PORTABLE_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
