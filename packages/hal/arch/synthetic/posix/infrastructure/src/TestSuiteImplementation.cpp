//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "portable/core/include/OS.h"

#include "../include/TestSuiteImplementation.h"

#include <iostream>
#include <fcntl.h>
//#include <errno.h>

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
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        m_xmlFileDescriptor = -1;
        m_filePath = nullptr;
      }

      /// \details
      /// Process the command line parameters. If `-x filename` is
      /// encountered, a pointer to the given file path is stored in
      /// m_filePath.
      /// If errors occur, the process is abruptly terminated.
      TestSuiteImplementation::TestSuiteImplementation(int argc, char* argv[])
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);

        processMainParameters(argc, argv);
      }

      TestSuiteImplementation::~TestSuiteImplementation()
      {
        debug.putMethodNameWithAddress(__PRETTY_FUNCTION__, this);
      }

      void
      TestSuiteImplementation::processMainParameters(int argc, char* argv[])
      {
        opterr = 0;
        int c;

        char* filePath = nullptr;

        while ((c = getopt(argc, argv, "x:")) != -1)
          {
            switch (c)
              {
            case 'x':
              // TODO: copy string, do not use the environment variable
              filePath = optarg;
              break;
            case '?':
              if (optopt == 'x')
                std::cerr << "Option '-" << (char) optopt
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
      /// Open the file as a new one, truncate if present.
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
        ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, "\n", 1);
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

#endif /* defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION) */
