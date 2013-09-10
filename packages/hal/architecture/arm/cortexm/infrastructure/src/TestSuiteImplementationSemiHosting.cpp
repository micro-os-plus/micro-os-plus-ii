//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief POSIX definitions of the test suite implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSEMIHOSTING) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/infrastructure/include/TestSuiteImplementationSemiHosting.h"
#include "hal/architecture/arm/cortexm/diagnostics/include/SemiHosting.h"
#include "portable/diagnostics/include/Trace.h"

// Platform headers
//#include <iostream>
//#include <fcntl.h>

namespace hal
{
  namespace cortexm
  {
    namespace infra
    {
      // ----------------------------------------------------------------------

      /// \details
      /// Initialise the object without XML output.
      TestSuiteImplementationSemiHosting::TestSuiteImplementationSemiHosting(void)
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
      TestSuiteImplementationSemiHosting::TestSuiteImplementationSemiHosting(int argc, char* argv[])
      {
#if defined(DEBUG)
        os::diag::trace.putConstructor();
#endif

        processMainParameters(argc, argv);
      }

      TestSuiteImplementationSemiHosting::~TestSuiteImplementationSemiHosting()
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
      TestSuiteImplementationSemiHosting::processMainParameters(int argc __attribute__((unused)), char* argv[] __attribute__((unused)))
      {
#if 0
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
                std::cerr << "Option '-x" << "' requires an argument."
                    << std::endl;
              else if (isprint(optopt))
                std::cerr << "Unknown option '-" << (char) optopt << "'."
                    << std::endl;
              else
                std::cerr << "Unknown option character '\\x" << std::hex
                    << optopt << "'." << std::endl;

              exit(1);

            default:
              ;
              abort();
              }
          }

        m_filePath = filePath;
        m_xmlFileDescriptor = -1;
#endif
        }

      /// \details
      /// Create the file (open as new), truncate if present.
      int
      TestSuiteImplementationSemiHosting::createXmlFile(void)
      {
#if 0
        m_xmlFileDescriptor = ::open(m_filePath, (O_CREAT | O_TRUNC | O_WRONLY),
            0644);
#endif
        return m_xmlFileDescriptor;
      }

      /// \details
      /// Call the system function to write a sequence of bytes to the
      /// XML file.
      ssize_t
      TestSuiteImplementationSemiHosting::writeToXmlFile(const void *cpBuf __attribute__((unused)),
          size_t numBytes __attribute__((unused)))
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

#if 0
        return ::write(m_xmlFileDescriptor, cpBuf, numBytes);
#else
        return -1;
#endif
      }

      /// \details
      /// Call the system function to close the XML file. Then
      /// invalidate the file descriptor.
      int
      TestSuiteImplementationSemiHosting::closeXmlFile(void)
      {
        if (m_xmlFileDescriptor == -1)
          return -1;

        int ret;
#if 0
        ret = ::close(m_xmlFileDescriptor);
#else
        ret = -1;
#endif

        m_xmlFileDescriptor = -1;

        return ret;
      }

      /// \details
      /// Call the system function to write the new line to the
      /// standard output.
      void
      TestSuiteImplementationSemiHosting::putNewLine(void)
      {
#if 0
        // on POSIX, the new line is a single character
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
        ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, "\n", 1);
#pragma GCC diagnostic pop
#else
        diag::SemiHosting::writeChar('\n');
#endif
        return;
      }

      /// \details
      /// Call the system function to write the sequence of bytes to the
      /// standard output. The operation is atomic.
      ssize_t
      TestSuiteImplementationSemiHosting::putBytes(const void* cpBuf __attribute__((unused)), size_t numBytes __attribute__((unused)))
      {
#if 0
        return ::write(OUTPUT_DEVICE_FILE_DESCRIPTOR, cpBuf, numBytes);
#else
        const char* p = reinterpret_cast<const char*>(cpBuf);

        if (p[numBytes] == '\0')
          {
            // If the byte array is followed by a \0, optimise
            // and call the string output function.
            diag::SemiHosting::writeString(p);
          }
        else
          {
            // Otherwise iterate and output one byte at a time.
            for (size_t i = 0; i < numBytes; ++i, ++p)
              {
                diag::SemiHosting::writeChar(*p);
              }
          }

        return numBytes;
#endif
      }

    // ----------------------------------------------------------------------

    }// namespace infra
  } // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSEMIHOSTING)
