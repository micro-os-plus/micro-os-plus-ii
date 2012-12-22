/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#include "../include/DebugImplementation.h"

#include <unistd.h>

namespace os
{
  namespace hal
  {
    namespace device
    {
      namespace debug
      {

        Implementation::~Implementation()
        {
          ;
        }

        Implementation::Implementation()
        {
          ;
        }

        void
        Implementation::earlyInitialise(void)
        {
          ; // Nothing to do, the file descriptor is already opened
        }

        void
        Implementation::putNewLine(void)
        {
          // on Unix, the new line is a single character
          ::write(1, "\n", 1);
          return;
        }

        int
        Implementation::putBytes(const void* cpBuf, size_t n)
        {
          // write the byte array in a single, atomic, sequence
          return ::write(1, cpBuf, (unsigned long) n);
        }

      } /* namespace debug */
    } /* namespace device */
  } /* namespace hal */
} /* namespace os */
