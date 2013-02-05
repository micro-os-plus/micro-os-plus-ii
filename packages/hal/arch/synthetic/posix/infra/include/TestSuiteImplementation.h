//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#ifndef HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_
#define HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_

#include <stdint.h>
#include <unistd.h>

namespace hal
{
  namespace arch
  {
    namespace synthetic
    {
      namespace posix
      {
        namespace infra
        {
          class TestSuiteImplementation
          {
          public:
            /// \brief Search parameters and identify XML file name
            ///
            /// \param [in] argc count of arguments.
            /// \param [in] argv array of pointer to strings.
            static char*
            getFileNamePointer(int argc, char* argv[]);

            /// \brief Create a file to be used as output for the XML file.
            ///
            /// \param [in] path a string with the file system path
            static int
            createFile(const char *path);

            /// \brief Write an array of bytes to the file.
            ///
            /// \param [in] fildes system file descriptor obtained from open()
            /// \param [in] buf pointer to the array of bytes
            /// \param [in] nbyte the length of the array of bytes
            static ssize_t
            writeFile(int fildes, const void *buf, size_t nbyte);

            /// \brief Close the file used for XML.
            ///
            /// \param [in] fildes system file descriptor obtained from open()
            static int
            closeFile(int fildes);

            /// \brief Send a new line to the test output device.
            static void
            putNewLine(void);

            /// \brief Write an array of bytes to the test output device.
            ///
            /// \param [in] cpBuf pointer to the array of bytes
            /// \param [in] nbyte the length of the array of bytes
            static ssize_t
            putBytes(const void* cpBuf, size_t nbyte);

          };
        } // namespace infra
      } // namespace posix
    } // namespace synthetic
  } // namespace arch
} // namespace hal

namespace os
{
  namespace infra
  {
    typedef hal::arch::synthetic::posix::infra::TestSuiteImplementation TestSuiteImplementation_t;
  } // namespace infra
} // namespace os

#endif /* HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION_H_ */
