//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief I2C declarations of the test suite implementation class.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C) || defined(__DOXYGEN__)
#include "portable/diagnostics/include/Trace.h"

// Platform headers
#include <unistd.h>

namespace hal
{
  namespace cortexm
  {
    namespace infra
    {

      // ======================================================================

#pragma GCC diagnostic push
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wpadded"
#endif

      /// \headerfile TestSuiteImplementationI2C.h "hal/architecture/arm/cortexm/infrastructure/include/TestSuiteImplementationI2C.h"
      /// \nosubgrouping
      /// \ingroup arm_cm3
      ///
      /// \brief The I2C version of the TestSuiteImplementation.
      ///
      /// \details
      /// Provide the system support to create/write/close file using
      /// the I2C
      /// calls. Also implement the output device as the standard output.
      ///
      /// Since these member functions need to preserve status between
      /// calls (the
      /// XML file name and the file descriptor),
      /// a static implementation is not possible,
      /// and this a regular object, embedded and constructed inside
      /// the TestSuite.
      class TestSuiteImplementationI2C
      {
      public:

        /// \name Constructors/destructor
        /// @{

        /// \brief Simple constructor.
        TestSuiteImplementationI2C(void);

        /// \brief Constructor with process parameters.
        ///
        /// \param [in] argc    Count of arguments.
        /// \param [in] argv    Array of pointer to strings.
        TestSuiteImplementationI2C(int argc, char* argv[]);

        /// \brief Destructor.
        ~TestSuiteImplementationI2C();

        /// @} end of name Constructors/destructor

        /// \name Public member functions
        /// @{

        /// \brief Process main() style parameters.
        ///
        /// \param [in] argc    Count of arguments.
        /// \param [in] argv    Array of pointer to strings.
        void
        processMainParameters(int argc, char* argv[]);

        /// \brief Create the XML file.
        ///
        /// \par Parameters
        ///     None.
        /// \return If successful, it returns a non-negative integer,
        /// termed a file descriptor.  It returns -1 on failure.
        int
        createXmlFile(void);

        /// \brief Write an array of bytes to the XML file.
        ///
        /// \param [in] cpBuf           Pointer to the array of bytes
        /// \param [in] numBytes        The length of the array of bytes
        /// \return Upon successful completion the number of bytes which
        ///     were written is  returned.  Otherwise, a -1 is returned.
        ssize_t
        writeToXmlFile(const void *cpBuf, size_t numBytes);

        /// \brief Close the XML file.
        ///
        /// \par Parameters
        ///    None.
        /// \return  Upon successful completion, a value of 0 is returned.
        ///     Otherwise, a value of -1 is returned.
        int
        closeXmlFile(void);

        /// \brief Send a new line to the test output device.
        ///
        /// \par Parameters
        ///     None.
        /// \par Returns
        ///     Nothing.
        void
        putNewLine(void);

        /// \brief Write an array of bytes to the test output device.
        ///
        /// \param [in] cpBuf           Pointer to the array of bytes.
        /// \param [in] numBytes        The length of the array of bytes.
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putBytes(const void* cpBuf, size_t numBytes);

        /// \brief Get the verbosity level.
        ///
        /// \par Parameters
        ///     None.
        /// \return The verbosity level.
        size_t
        getVerbosity(void) const;

        /// @} end of Public member functions

      private:
        /// \name Private constants
        /// @{

        /// \brief The file descriptor of the output device.
        static constexpr int OUTPUT_DEVICE_FILE_DESCRIPTOR = 1;

        /// @} end of Private constants

        /// \name Private member variables
        /// @{

        /// \brief The file descriptor of the XML output file.
        int m_xmlFileDescriptor;

        /// \brief The pointer to the file path.
        char* m_filePath;

        /// \brief The verbosity level, 0 is the lest verbose.
        size_t m_verbosity;

        os::diag::TraceImplementation m_implementation;
        /// @} end of name Private member variables

      };

      // ----------------------------------------------------------------------

      inline size_t
      __attribute__((always_inline))
      TestSuiteImplementationI2C::getVerbosity(void) const
      {
        return m_verbosity;
      }

#pragma GCC diagnostic pop

    // ========================================================================

    }// namespace infra
  } // namespace cortexm
} // namespace hal

// ============================================================================
#if !defined(__DOXYGEN__)
namespace os
{
  namespace infra
  {
    /// \brief Define the generic type to refer to the POSIX implementation.
    /// for the TestSuite.
    using TestSuiteImplementation = hal::cortexm::infra::TestSuiteImplementationI2C;
  } // namespace infra
} // namespace os
#endif // !defined(__DOXYGEN__)
// ============================================================================

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C_H_
