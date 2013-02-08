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
        /// \brief The file descriptor of the output device.
        static const int OUTPUT_DEVICE_FILE_DESCRIPTOR = 1;

        /// \brief Search parameters and extract the file name to be used
        /// for the XML output.
        ///
        /// \param [in] argc count of arguments.
        /// \param [in] argv array of pointer to strings.
        ///
        /// \return If successful, it returns a pointer to a zero terminating
        /// string containing
        /// the file name. It returns `nulptr` if not found.
        static char*
        getFileNamePointer(int argc, char* argv[]);

        /// \brief Create a file to write the XML output.
        ///
        /// \param [in] cpPath a string with the file system path
        ///
        /// \return If successful, it returns a non-negative integer,
        /// termed a file descriptor.  It returns -1 on failure.
        static int
        createFile(const char *cpPath);

        /// \brief Write an array of bytes to the file.
        ///
        /// \param [in] fildes system file descriptor obtained from open()
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
        ///
        /// \return Upon successful completion the number of bytes which
        /// were written is  returned.  Otherwise, a -1 is returned
        static ssize_t
        writeToFile(int fildes, const void *cpBuf, size_t numBytes);

        /// \brief Close the XML file.
        ///
        /// \param [in] fildes system file descriptor obtained from open()
        ///
        /// \return  Upon successful completion, a value of 0 is returned.
        /// Otherwise, a value of -1 is returned.
        static int
        closeFile(int fildes);

        /// \brief Send a new line to the test output device.
        /// \par Parameters
        /// None
        /// \par Returns
        /// Nothing
        static void
        putNewLine(void);

        /// \brief Write an array of bytes to the test output device.
        ///
        /// \param [in] cpBuf pointer to the array of bytes
        /// \param [in] numBytes the length of the array of bytes
        ///
        /// \return The actual number of bytes written to the output device.
        static ssize_t
        putBytes(const void* cpBuf, size_t numBytes);

      };
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
