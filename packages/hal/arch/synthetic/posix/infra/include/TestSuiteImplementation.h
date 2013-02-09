//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#ifndef HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_
#define HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_

#include <stdint.h>
#include <unistd.h>

#include "portable/infra/include/TestSuiteImplementation.h"

namespace hal
{
  namespace posix
  {
    namespace infra
    {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"

      /// \class TestSuiteImplementation TestSuiteImplementation.h "hal/arch/synthetic/posix/include/TestSuiteImplementation.h"
      /// \brief The POSIX implementation for the TestSuite.
      ///
      /// \details
      /// Provide the system support to create/write/close file using
      /// the POSIX
      /// calls. Also implement the output device as the standard output.
      ///
      /// Since none of these calls need to preserve any status between calls,
      /// all are implemented as static methods.
      class TestSuiteImplementation : public os::infra::TestSuiteImplementation
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

        /// \brief Create the XML file.
        ///
        /// \par Parameters
        ///     None
        ///
        /// \return If successful, it returns a non-negative integer,
        /// termed a file descriptor.  It returns -1 on failure.
        int
        createXmlFile(void);

        /// \brief Write an array of bytes to the XML file.
        ///
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
        ///
        /// \return Upon successful completion the number of bytes which
        /// were written is  returned.  Otherwise, a -1 is returned
        ssize_t
        writeToXmlFile(const void *cpBuf, size_t numBytes);

        /// \brief Close the XML file.
        ///
        /// \par Parameters
        ///    None
        ///
        /// \return  Upon successful completion, a value of 0 is returned.
        /// Otherwise, a value of -1 is returned.
        int
        closeXmlFile(void);

        /// \brief Send a new line to the test output device.
        /// \par Parameters
        /// None
        /// \par Returns
        /// Nothing
        void
        putNewLine(void);

        /// \brief Write an array of bytes to the test output device.
        ///
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
        ///
        /// \return The actual number of bytes written to the output device.
        ssize_t
        putBytes(const void* cpBuf, size_t numBytes);

      private:
        /// \brief The file descriptor of the output device.
        static const int OUTPUT_DEVICE_FILE_DESCRIPTOR = 1;

        /// \brief The file descriptor of the XML output file.
        int m_xmlFileDescriptor;

        /// \brief The
        char* m_fileName = nullptr;

      };
      // class TestSuiteImplementation

#pragma GCC diagnostic pop

    } // namespace infra
  } // namespace posix
} // namespace hal

namespace os
{
  namespace infra
  {
    /// \brief Define the generic type to refer to the POSIX implementation
    /// for the TestSuite.
    typedef hal::posix::infra::TestSuiteImplementation TestSuiteImplementation_t;
  } // namespace infra
} // namespace os

#endif /* HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_ */
