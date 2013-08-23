//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Generic semihosting declarations of the trace implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING) || defined(__DOXYGEN__)

#include <unistd.h>

namespace hal
{
  namespace cortexm
  {
    namespace diag
    {

      // ======================================================================

      /// \headerfile TraceImplementationSemihosting.h "hal/architecture/arm/cortexm/diagnostics/include/TraceImplementationSemihosting.h"
      /// \ingroup cm3_diag
      /// \nosubgrouping
      ///
      /// \brief The generic semihosting version of the TraceImplementation.
      ///
      /// \details
      /// This class provides the system support to output trace info using
      /// the semihosting interface.
      class TraceImplementationSemihosting
      {
      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TraceImplementationSemihosting(void) = default;

        /// \brief Default destructor.
        ~TraceImplementationSemihosting(void) = default;

        /// @} end of name Constructors/destructor

        /// \name Hardware initialisations
        /// @{

        /// \brief Power up trace hardware.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        powerUp(void);

        /// \brief Power down trace hardware.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        powerDown(void);

        /// @} end of name Hardware initialisations

        /// \name Public member functions
        /// @{

        /// \brief Output a byte array.
        ///
        /// \param pBuf         Pointer to byte array.
        /// \param numBytes     Number of bytes.
        /// \return The number of bytes actually written.
        static ssize_t
        write(const void* pBuf, size_t numBytes);

        /// \brief Flush content to device.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        static void
        flush(void);

        /// \brief Check if I2C device is connected.
        ///
        /// \par Parameters
        ///     None.
        /// \retval true        Device present.
        /// \retval false       Device not present.
        static bool
        isDevicePresent(void);

        /// @} end of Public member functions

      private:
        /// \name Private constants
        /// @{

        /// @} end of Private constants

      };

      /// \details
      /// Called during early start-up, to perform
      /// initialisations required before constructor.
      inline void
      TraceImplementationSemihosting::powerUp(void)
      {
      }

      /// \details
      /// Called during late cleanup, to turn off
      /// hardware.
      inline void
      TraceImplementationSemihosting::powerDown(void)
      {
      }

      /// \details
      /// No buffering is used,
      /// there is nothing to flush.
      inline
      void
      TraceImplementationSemihosting::flush()
      {
      }

      /// \details
      /// The device is always connected.
      inline bool
      TraceImplementationSemihosting::isDevicePresent(void)
      {
        return true;
      }

    // ======================================================================

    }// namespace diag
  } // namespace cortexm
} // namespace hal

#if !defined(__DOXYGEN__)

// Leave Doxygen think that the os::diag sample class is the real one.

namespace os
{
  namespace diag
  {
    /// \brief Define the generic type to refer to the semihosting implementation.
    /// for the Trace.
    using TraceImplementation = hal::cortexm::diag::TraceImplementationSemihosting ;
  } // namespace diag
} // namespace os

#endif // !defined(__DOXYGEN__)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING_H_
