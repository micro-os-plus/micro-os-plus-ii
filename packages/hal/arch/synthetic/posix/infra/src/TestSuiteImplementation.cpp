//
//      Copyright (C) 2012-2013 Liviu Ionescu.
//
//      This file is part of the uOS++ distribution.
//

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION)

#include "../include/TestSuiteImplementation.h"

#include <iostream>
#include <fcntl.h>
#include <errno.h>

namespace hal
{
  namespace posix
  {
    namespace infra
    {

      /// \details
      /// Process the command line parameters. If `-j filename` is
      /// encountered, a pointer to the given file name is returned.
      /// If errors occur, the process is abruptly terminated.
      char*
      TestSuiteImplementation::getFileNamePointer(int argc, char* argv[])
      {
        opterr = 0;
        int c;

        char* fileName = 0;

        while ((c = getopt(argc, argv, "j:")) != -1)
          {
            switch (c)
              {
            case 'j':
              // TODO: copy string
              fileName = optarg;
              break;
            case '?':
              if (optopt == 'j')
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

        return fileName;
      }

      /// \details
      /// Open the file as a new one, truncate if present.
      int
      TestSuiteImplementation::createFile(const char *cpPath)
      {
        return ::open(cpPath, (O_CREAT | O_TRUNC | O_WRONLY), 0644);
      }

      /// \details
      /// Call the system function to write a sequence of bytes to the
      /// given file.
      ssize_t
      TestSuiteImplementation::writeToFile(int fildes, const void *cpBuf,
          size_t numBytes)
      {
        return ::write(fildes, cpBuf, numBytes);
      }

      /// \details
      /// Call the system function to close the file.
      int
      TestSuiteImplementation::closeFile(int fildes)
      {
        return ::close(fildes);
      }

      /// \details
      /// Call the system function to write the new line to the
      /// standard output.
      void
      TestSuiteImplementation::putNewLine(void)
      {
        // on Unix, the new line is a single character
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

#endif /* defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION) */
