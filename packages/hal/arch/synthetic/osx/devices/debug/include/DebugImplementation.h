/*
 *      Copyright (C) 2012 Liviu Ionescu.
 *
 *      This file is part of the uOS++ distribution.
 */

#ifndef OS_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUG_IMPLEMENTATION_H_
#define OS_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUG_IMPLEMENTATION_H_

#include <unistd.h>

namespace os
{
  namespace hal
  {
    namespace device
    {
      namespace debug
      {
        class Implementation
        {
        public:
          ~Implementation();
          Implementation();

          static void
          earlyInitialise(void);

          static void
          putNewLine(void);

          static ssize_t
          putBytes(const void* cpBuf, size_t n);

        };
      } /* namespace debug */
    } /* namespace device */
  } /* namespace hal */
} /* namespace os */

#endif /* OS_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUG_IMPLEMENTATION_H_ */
