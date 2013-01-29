/*
 *      Copyright (C) 2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION)

#include "portable/infra/include/TestSuiteImplementation.h"

#include <iostream>
#include <fcntl.h>
#include <errno.h>

namespace os
{
  namespace infra
  {

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
              std::cerr << "Unknown option character '\\x" << std::hex << optopt
                  << "'." << std::endl;
            exit(1);
          default:
            abort();
            }
        }

      return fileName;
    }

    int
    TestSuiteImplementation::createFile(const char *path)
    {
      return ::open(path, (O_CREAT | O_TRUNC | O_WRONLY), 0644);
    }

    ssize_t
    TestSuiteImplementation::writeFile(int fildes, const void *buf,
        size_t nbyte)
    {
      return ::write(fildes, buf, nbyte);
    }

    int
    TestSuiteImplementation::closeFile(int fildes)
    {
      return ::close(fildes);
    }

    void
    TestSuiteImplementation::putNewLine(void)
    {
      // on Unix, the new line is a single character
      ::write(1, "\n", 1);
      return;
    }

    ssize_t
    TestSuiteImplementation::putBytes(const void* cpBuf, size_t n)
    {
      // write the byte array in a single, atomic, sequence
      return ::write(1, cpBuf, n);
    }

  } /* namespace infra */
} /* namespace os */

#endif /* defined(OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRA_TESTSUITEIMPLEMENTATION) */
