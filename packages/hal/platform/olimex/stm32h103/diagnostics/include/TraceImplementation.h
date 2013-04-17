//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Olimex STM32-H103 declarations of the trace implementation class.

#ifndef HAL_PLATFORM_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
#define HAL_PLATFORM_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_PLATFORM_OLIMEX_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include <unistd.h>

namespace hal
{
  namespace stm32h103
  {
    namespace diag
    {

      // ======================================================================

      /// \headerfile  TraceImplementation.h "hal/architecture/synthetic/posix/include/TraceImplementation.h"
      /// \ingroup diag
      /// \nosubgrouping
      ///
      /// \brief The POSIX version of the TraceImplementation.
      ///
      /// \details
      /// This class provides the system support to output trace info using
      /// the POSIX calls.
      class TraceImplementation
      {
      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Simple constructor.
        TraceImplementation();

        /// \brief Simple destructor.
        ~TraceImplementation();

        /// @}

        /// \name Hardware initialisations
        /// @{

        /// \brief Power up trace hardware.
        ///
        /// \par Parameters
        /// None.
        /// \par Returns
        /// Nothing.
        static void
        powerUp(void);

        /// \brief Power down trace hardware.
        ///
        /// \par Parameters
        /// None.
        /// \par Returns
        /// Nothing.
        static void
        powerDown(void);

        /// @} end of name Hardware initialisations

        /// \name Public member functions
        /// @{

        /// \brief Output a byte array.
        ///
        /// \param pBuf Pointer to byte array.
        /// \param numBytes Number of bytes.
        /// \return The number of bytes actually written.
        static ssize_t
        write(const void* pBuf, size_t numBytes);

        /// \brief Flush content to device.
        ///
        /// \par Parameters
        /// None.
        /// \par Returns
        /// Nothing.
        static void
        flush(void);

        /// @} end of Public member functions

      private:
        /// \brief The file descriptor of the output device.
        static const int OUTPUT_DEVICE_FILE_DESCRIPTOR = 1;

      };

      /// \details
      /// On POSIX, writes are atomic and since no buffering is used,
      /// there is nothing to flush.
      inline
      void
      TraceImplementation::flush()
      {
      }

      // ======================================================================

    } // namespace diag
  } // namespace stm32h103
} // namespace hal

#if !defined(__DOXYGEN__)

// Leave Doxygen think that the os::diag sample class is the real one.

namespace os
{
  namespace diag
  {
    /// \brief Define the generic type to refer to the POSIX implementation.
    /// for the Trace.
    typedef hal::stm32h103::diag::TraceImplementation TraceImplementation;
  } // namespace diag
} // namespace os

#endif // !defined(__DOXYGEN__)

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION)

#endif // HAL_PLATFORM_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
