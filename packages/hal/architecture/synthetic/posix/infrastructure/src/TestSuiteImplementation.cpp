//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "../include/TestSuiteImplementation.h"

#include <iostream>
#include <fcntl.h>

namespace hal
{
  namespace posix
  {
    namespace infra
    {
      /// \details
      /// Initialise the object without XML output.
      TestSuiteImplementation::TestSuiteImplementation()
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif

        m_xmlFileDescriptor = -1;
        m_filePath = nullptr;
        m_verbosity = 0;
      }

      /// \details
      /// Process the command line parameters using `processMainParameters()`.
      TestSuiteImplementation::TestSuiteImplementation(int argc, char* argv[])
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif

        processMainParameters(argc, argv);
      }

      TestSuiteImplementation::~TestSuiteImplementation()
      {
#if defined(DEBUG)
        os::diag::trace.putDestructor();
#endif
      }

      /// \details
      /// Process the command line parameters. If `-x filename` is
      /// encountered, a pointer to the given file path is stored in
      /// m_filePath. Count all occurrences of `-v` as verbosity level.
      /// If errors occur, the process is abruptly terminated.
      void
      TestSuiteImplementation::processMainParameters(int argc, char* argv[])
      {
        opterr = 0;
        int c;

        char* filePath = nullptr;

        while ((c = getopt(argc, argv, "vx:")) != -1)
          {
            switch (c)
              {
            case 'x':
              // TODO: copy string, do not use the environment variable
              filePath = optarg;
              break;

            case 'v':
              m_verbosity++; // count the verbosity level
              break;

            case '?':
              if (optopt == 'x')
                std::cerr << "Option '-x"
                    << "' requires an argument." << std::endl;
              else if (isprint(optopt))
                std::cerr << "Unknown option '-" << (char) optopt << "'."
                    << std::endl;
              else
                std::cerr << "Unknown option character '\\x" << std::hex
                    << optopt << "'." << std::endl;

              exit(1);

            default:
              abort();
              }
          }

        m_xmlFileDescriptor = -1;
        m_filePath = filePath;
      }

      /// \details
      /// Create the file (open as new), truncate if present.
      int
      TestSuiteImplementation::createXmlFile(void)
      {
        m_xmlFileDescriptor = ::open(m_filePath,
            (O_CREAT | O_TRUNC | O_WRONLY), 0644);

        return m_xmlFileDescriptor;
      }

      /// \details
      /// Call the system function to write a sequence of bytes to the
      /// XML file.
      ssize_t
      TestSuiteImplementation::writeToXmlFile(const void *cpBuf,
          size_t numBytes)
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

        return ::write(m_xmlFileDescriptor, cpBuf, numBytes);
      }

      /// \details
      /// Call the system function to close the XML file. Then
      /// invalidate the file descriptor.
      int
      TestSuiteImplementation::closeXmlFile(void)
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

        int ret;
        ret = ::close(m_xmlFileDescriptor);

        m_xmlFileDescriptor = -1;

        return ret;
      }

      /// \details
      /// Call the system function to write the new line to the
      /// standard output.
      void
      TestSuiteImplementation::putNewLine(void)
      {
        // on POSIX, the new line is a single character
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
        ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, "\n", 1);
#pragma GCC diagnostic pop
        return;
      }

      /// \details
      /// Call the system function to write the sequence of bytes to the
      /// standard output. The operation is atomic.
      ssize_t
      TestSuiteImplementation::putBytes(const void* cpBuf, size_t numBytes)
      {
        return ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, cpBuf, numBytes);
      }

    } // namespace infra
  } // namespace posix
} // namespace hal

#endif /* defined(OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) */
