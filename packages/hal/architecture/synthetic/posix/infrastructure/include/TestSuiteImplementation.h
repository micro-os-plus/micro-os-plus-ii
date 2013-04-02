//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#ifndef HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_
#define HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) || defined(__DOXYGEN__)

namespace hal
{
  namespace posix
  {
    namespace infra
    {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"

      /// \class TestSuiteImplementation TestSuiteImplementation.h "hal/architecture/synthetic/posix/include/TestSuiteImplementation.h"
      /// \brief The POSIX version of the TestSuiteImplementation.
      ///
      /// \details
      /// Provide the system support to create/write/close file using
      /// the POSIX
      /// calls. Also implement the output device as the standard output.
      ///
      /// Since these member functions need to preserve status between
      /// calls (the
      /// XML file name and the file descriptor),
      /// a static implementation is not possible,
      /// and this a regular object, embedded and constructed inside
      /// the TestSuite.
      class TestSuiteImplementation
      {
      public:

        /// \brief Simple constructor.
        TestSuiteImplementation();

        /// \brief Constructor with process parameters
        ///
        /// \param [in] argc count of arguments.
        /// \param [in] argv array of pointer to strings.
        TestSuiteImplementation(int argc, char* argv[]);

        /// \brief Destructor.
        ~TestSuiteImplementation();

        /// \brief Process main() style parameters
        ///
        /// \param [in] argc count of arguments.
        /// \param [in] argv array of pointer to strings.
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
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
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
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
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

      private:
        /// \brief The file descriptor of the output device.
        static const int OUTPUT_DEVICE_FILE_DESCRIPTOR = 1;

        /// \brief The file descriptor of the XML output file.
        int m_xmlFileDescriptor;

        /// \brief The pointer to the file path
        char* m_filePath;

        /// \brief The verbosity level, 0 is the lest verbose
        size_t m_verbosity;

      };

      inline
      size_t
      TestSuiteImplementation::getVerbosity(void) const
      {
        return m_verbosity;
      }

#pragma GCC diagnostic pop

    } // namespace infra
  } // namespace posix
} // namespace hal

#if !defined(__DOXYGEN__)

// Leave Doxygen think that the os::infra sample class is the real one.

namespace os
{
  namespace infra
  {
    /// \brief Define the generic type to refer to the POSIX implementation
    /// for the TestSuite.
    typedef hal::posix::infra::TestSuiteImplementation TestSuiteImplementation_t;
  } // namespace infra
} // namespace os

#endif /* !defined(__DOXYGEN__) */

#endif /* defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) */

#endif /* HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_H_ */