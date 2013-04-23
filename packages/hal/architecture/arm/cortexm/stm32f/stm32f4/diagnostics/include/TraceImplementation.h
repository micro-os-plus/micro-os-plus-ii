//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 declarations of the trace implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include <unistd.h>

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {

      // ======================================================================

      /// \headerfile TraceImplementation.h "hal/architecture/synthetic/posix/include/TraceImplementation.h"
      /// \ingroup stm32f10x_diag
      /// \nosubgrouping
      ///
      /// \brief The stm32f10x version of the TraceImplementation.
      ///
      /// \details
      /// This class provides the system support to output trace info using
      /// the bit banged I2C implementation.
      class TraceImplementation
      {
      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Default constructor.
        TraceImplementation() = default;

        /// \brief Default destructor.
        ~TraceImplementation() = default;

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
        /// \retval True        Device present.
        /// \retval False       Device not present.
        static bool
        isDevicePresent(void);

        /// @} end of Public member functions

      private:
        /// \name Private constants
        /// @{

        /// @} end of Private constants

      };

      /// \details
      /// Hmmm... writes are atomic and since no buffering is used,
      /// there is nothing to flush.
      inline
      void
      TraceImplementation::flush()
      {
      }

    // ======================================================================

    }// namespace diag
  } // namespace stm32f4
} // namespace hal

#if !defined(__DOXYGEN__)

// Leave Doxygen think that the os::diag sample class is the real one.

namespace os
{
  namespace diag
  {
    /// \brief Define the generic type to refer to the POSIX implementation.
    /// for the Trace.
    typedef hal::stm32f4::diag::TraceImplementation TraceImplementation;
  } // namespace diag
} // namespace os

#endif // !defined(__DOXYGEN__)
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION_H_
