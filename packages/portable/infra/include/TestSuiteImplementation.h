/*       Copyright (C) 2012-2013 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_PORTABLE_INFRA_TESTSUITEIMPLEMENTATION_H_
#define OS_PORTABLE_INFRA_TESTSUITEIMPLEMENTATION_H_

#include <stdint.h>
#include <unistd.h>

namespace os
{
  namespace infra
  {

    class TestSuiteImplementation
    {
    public:
      static char*
      getFileNamePointer(int argc, char* argv[]);

      static int
      createFile(const char *path);

      static ssize_t
      writeFile(int fildes, const void *buf, size_t nbyte);

      static int
      closeFile(int fildes);

      static void
      putNewLine(void);

      static ssize_t
      putBytes(const void* cpBuf, size_t n);

    };
  } /* namespace infra */
} /* namespace os */

#endif /* OS_PORTABLE_INFRA_TESTSUITEIMPLEMENTATION_H_ */
